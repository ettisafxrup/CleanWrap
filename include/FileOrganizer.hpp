#ifndef FILE_ORGANIZER_HPP
#define FILE_ORGANIZER_HPP

#include <filesystem>
#include <string>
#include <set>
#include "DuplicateDetector.hpp"
#include "Statistics.hpp"

namespace fs = std::filesystem;

class FileOrganizer
{
public:
    explicit FileOrganizer(const fs::path &targetFolderPath);
    void organize();
    std::set<std::string> categories;

private:
    fs::path targetFolderPath;

    DuplicateDetector duplicateDetector;

    Statistics statistics;

    void createFolders();

    fs::path getUniquePath(const fs::path &desiredPath);

    void organizeFile(const fs::path &source);
};

#endif
