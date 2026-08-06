#ifndef FILE_ORGANIZER_HPP
#define FILE_ORGANIZER_HPP

#include <filesystem>
#include <string>
#include <vector>
#include "DuplicateDetector.hpp"
#include "Statistics.hpp"

namespace fs = std::filesystem;

class FileOrganizer
{
public:
    explicit FileOrganizer(const fs::path &downloadsPath);
    void organize();

private:
    fs::path downloadsPath;

    std::vector<std::string> categories;

    DuplicateDetector duplicateDetector;

    Statistics statistics;

    void createFolders();

    void getDownloadPath();

    fs::path getUniquePath(const fs::path &desiredPath);

    void organizeFile(const fs::path &source);
};

#endif
