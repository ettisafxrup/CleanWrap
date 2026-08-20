#include "DuplicateDetector.hpp"
#include <fstream>
#include <stdexcept>
#include <regex>
#include <algorithm>

// 64KB size will be checked by hashing if the file are the same or not
// If yes, then the total hashing will be checked.

namespace
{
    constexpr std::streamsize PARTIAL_HASH_BLOCK_SIZE = 64 * 1024;
}

// getFIleSize Function
std::uintmax_t DuplicateDetector::getFileSize(
    const fs::path &filePath) const
{
    std::error_code error;

    const std::uintmax_t size =
        fs::file_size(filePath, error);

    if (error)
    {
        throw std::runtime_error(
            "Could not determine file size: " +
            filePath.string());
    }

    return size;
}

// Partial Hash (64KB)
std::uint64_t DuplicateDetector::calculatePartialHash(
    const fs::path &filePath) const
{
    constexpr std::uint64_t O = 14695981039346656037ULL;
    constexpr std::uint64_t P = 1099511628211ULL;
    std::uint64_t hash = O;
    std::ifstream file(filePath, std::ios::binary);

    // Error Handling: File Opening Error
    if (!file)
    {
        throw std::runtime_error(
            "Could not open file: " +
            filePath.string());
    }

    char buffer[PARTIAL_HASH_BLOCK_SIZE];

    const std::uintmax_t fileSize =
        getFileSize(filePath);
    const std::streamsize firstBlockSize =
        static_cast<std::streamsize>(
            std::min<std::uintmax_t>(
                fileSize,
                PARTIAL_HASH_BLOCK_SIZE));

    file.read(buffer, firstBlockSize);

    for (std::streamsize i = 0; i < file.gcount(); ++i)
    {
        hash ^= static_cast<unsigned char>(buffer[i]);
        hash *= P;
    }

    if (fileSize > PARTIAL_HASH_BLOCK_SIZE)
    {
        file.clear();
        file.seekg(
            -static_cast<std::streamoff>(PARTIAL_HASH_BLOCK_SIZE),
            std::ios::end);
        file.read(buffer, PARTIAL_HASH_BLOCK_SIZE);

        for (std::streamsize i = 0; i < file.gcount(); ++i)
        {
            hash ^= static_cast<unsigned char>(buffer[i]);
            hash *= P;
        }
    }

    return hash;
}

std::uint64_t DuplicateDetector::calculateHash(
    const fs::path &p) const
{
    constexpr std::uint64_t O = 14695981039346656037ULL, P = 1099511628211ULL;
    std::uint64_t h = O;
    std::ifstream f(p, std::ios::binary);
    if (!f)
        throw std::runtime_error("Could not open file: " + p.string());
    char b[65536];
    while (f.read(b, sizeof(b)) || f.gcount() > 0)
        for (std::streamsize i = 0; i < f.gcount(); ++i)
        {
            h ^= static_cast<unsigned char>(b[i]);
            h *= P;
        }
    return h;
}

bool DuplicateDetector::isDuplicate(
    const fs::path &filePath,
    const std::string &category)
{
    const auto categoryIterator =
        knownFiles.find(category);

    if (categoryIterator == knownFiles.end())
    {
        return false;
    }

    const std::uintmax_t fileSize =
        getFileSize(filePath);

    const auto sizeIterator =
        categoryIterator->second.find(fileSize);

    if (sizeIterator == categoryIterator->second.end())
    {
        return false;
    }

    const std::uint64_t partialHash =
        calculatePartialHash(filePath);
    const auto partialIterator =
        sizeIterator->second.find(partialHash);

    if (partialIterator == sizeIterator->second.end())
    {
        return false;
    }

    const std::uint64_t fullHash =
        calculateHash(filePath);

    return partialIterator->second.find(fullHash) !=
           partialIterator->second.end();
}

void DuplicateDetector::rememberOriginal(
    const fs::path &originalPath,
    const std::string &category)
{
    const std::uintmax_t fileSize =
        getFileSize(originalPath);
    const std::uint64_t partialHash =
        calculatePartialHash(originalPath);
    const std::uint64_t fullHash =
        calculateHash(originalPath);

    knownFiles[category][fileSize][partialHash][fullHash] =
        originalPath;
}

bool DuplicateDetector::hasDuplicateNamePattern(
    const fs::path &filePath)
{
    const std::string fileStem =
        filePath.stem().string();

    /* Matches:
     "New File (1)"
     "My Family (5)"
     "Document (123)"
     */
    const std::regex numberedPattern(
        R"(\s*\(\d+\)\s*$)");

    /* Matches:
     "New File - Copy"
     "My Family - Copy"
     "Document - Copy (1)"
     "Photo - Copy (5)"
    */
    const std::regex copyPattern(
        R"(\s*-\s*Copy(\s*\(\d+\))?\s*$)",
        std::regex::icase);

    return std::regex_search(
               fileStem,
               numberedPattern) ||
           std::regex_search(
               fileStem,
               copyPattern);
}
