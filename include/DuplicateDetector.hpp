#ifndef DUPLICATE_DETECTOR_HPP
#define DUPLICATE_DETECTOR_HPP

#include <cstdint>
#include <filesystem>
#include <string>
#include <unordered_map>
#include <unordered_set>

namespace fs = std::filesystem;

class DuplicateDetector
{
public:
    bool isDuplicate(
        const fs::path &filePath,
        const std::string &category);

    void rememberOriginal(
        const fs::path &originalPath,
        const std::string &category);

    bool hasDuplicateNamePattern(
        const fs::path &filePath);

private:
    using FullHashIndex =
        std::unordered_map<
            std::uint64_t,
            fs::path>;
    using PartialHashIndex =
        std::unordered_map<
            std::uint64_t,
            FullHashIndex>;
    using SizeIndex =
        std::unordered_map<
            std::uintmax_t,
            PartialHashIndex>;

    std::uintmax_t getFileSize(
        const fs::path &filePath) const;

    std::uint64_t calculatePartialHash(
        const fs::path &filePath) const;

    std::uint64_t calculateHash(
        const fs::path &filePath) const;

    std::unordered_map<
        std::string,
        SizeIndex>
        knownFiles;
};

#endif