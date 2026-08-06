#include <cstdlib>
#include <filesystem>
#include <iostream>
#include "include/FileOrganizer.hpp"
namespace fs = std::filesystem;

int main()
{
    const char *userProfile = std::getenv("USERPROFILE");
    if (!userProfile)
    {
        std::cerr << "Could not find USERPROFILE.\n";
        return 1;
    }

    fs::path downloadsPath = fs::path(userProfile) / "Downloads";
    
    try
    {
        // Including File Organizer class to organize files in the Downloads folder
        FileOrganizer organizer(downloadsPath);
        organizer.organize();
    }
    catch (const std::exception &e)
    {
        std::cerr << "\nFATAL ERROR: " << e.what() << '\n';
        return 1;
    }
    return 0;
}
