#include <cstdlib>
#include <filesystem>
#include <iostream>
#include "include/FileOrganizer.hpp"
#include "include/UpdateChecker.hpp"
namespace fs = std::filesystem;

int main(int argc, char *argv[])
{
    UpdateChecker::checkForUpdates();

    const char *userProfile = std::getenv("USERPROFILE");
    if (!userProfile)
    {
        std::cerr << "Could not find USERPROFILE.\n";
        return 1;
    }

    fs::path targetFolderPath;

    if (argc >= 2)
    {
        // Windows passed a folder path
        targetFolderPath = argv[1];
    }
    else
    {
        // Normal startup
        targetFolderPath = fs::path(userProfile) / "Downloads";
    }

    try
    {
        // Including File Organizer class to organize files in the Downloads folder
        FileOrganizer organizer(targetFolderPath);
        organizer.organize();
    }
    catch (const std::exception &e)
    {
        std::cerr << "\nFATAL ERROR: " << e.what() << '\n';
        return 1;
    }
    return 0;
}
