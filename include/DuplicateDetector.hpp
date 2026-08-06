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
    std::uint64_t calculateHash(
        const fs::path &filePath);

    std::unordered_map<
        std::string,
        std::unordered_map<
            std::uint64_t,
            fs::path>>
        knownFiles;
};

#endif