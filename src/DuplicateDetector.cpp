#include "DuplicateDetector.hpp"
#include <fstream>
#include <stdexcept>
#include <regex>

std::uint64_t DuplicateDetector::calculateHash(const fs::path &p)
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
    const std::uint64_t hash =
        calculateHash(filePath);

    const auto categoryIt =
        knownFiles.find(category);

    if (categoryIt == knownFiles.end())
    {
        return false;
    }

    return categoryIt
               ->second
               .find(hash) != categoryIt
                                  ->second
                                  .end();
}

void DuplicateDetector::rememberOriginal(
    const fs::path &originalPath,
    const std::string &category)
{
    const std::uint64_t hash =
        calculateHash(originalPath);

    knownFiles[category][hash] =
        originalPath;
}

bool DuplicateDetector::hasDuplicateNamePattern(
    const fs::path &filePath)
{
    const std::string fileStem =
        filePath.stem().string();

    // Matches:
    // "New File (1)"
    // "My Family (5)"
    // "Document (123)"
    const std::regex numberedPattern(
        R"(\s*\(\d+\)\s*$)");

    // Matches:
    // "New File - Copy"
    // "My Family - Copy"
    // "Document - Copy (1)"
    // "Photo - Copy (5)"
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
