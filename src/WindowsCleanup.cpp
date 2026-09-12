#include "WindowsCleanup.hpp"

#include <cstdlib>
#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;

namespace
{
    bool isSafeCleanupDirectory(const fs::path &directory)
    {
        if (directory.empty() || !fs::exists(directory) || !fs::is_directory(directory))
        {
            return false;
        }

        const fs::path normalized = fs::weakly_canonical(directory);
        const fs::path root = normalized.root_path();

        return normalized != root && normalized.parent_path() != root.parent_path();
    }

    void clearDirectory(const fs::path &directory)
    {
        if (!isSafeCleanupDirectory(directory))
        {
            return;
        }

        std::error_code iteratorError;
        for (fs::directory_iterator entry(directory, iteratorError); !iteratorError && entry != fs::directory_iterator(); entry.increment(iteratorError))
        {
            std::error_code removeError;
            fs::remove_all(entry->path(), removeError);

            if (removeError)
            {
                std::cerr << "Could not remove temporary item " << entry->path()
                          << ": " << removeError.message() << '\n';
            }
        }

        if (iteratorError)
        {
            std::cerr << "Could not scan cleanup directory " << directory
                      << ": " << iteratorError.message() << '\n';
        }
    }

    fs::path getEnvironmentPath(const char *name)
    {
        const char *value = std::getenv(name);
        return value ? fs::path(value) : fs::path();
    }
}

void WindowsCleanup::run()
{
#ifdef _WIN32
    const fs::path windowsDirectory = getEnvironmentPath("WINDIR");
    const fs::path userTemp = getEnvironmentPath("TEMP");
    const fs::path localAppData = getEnvironmentPath("LOCALAPPDATA");

    clearDirectory(userTemp);

    if (!localAppData.empty())
    {
        clearDirectory(localAppData / "Temp");
    }

    if (!windowsDirectory.empty())
    {
        clearDirectory(windowsDirectory / "Temp");
        clearDirectory(windowsDirectory / "Prefetch");
    }
#else
    std::cerr << "Windows cleanup is unavailable on this platform.\n";
#endif
}