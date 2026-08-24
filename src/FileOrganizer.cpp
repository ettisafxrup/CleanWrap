#include "FileOrganizer.hpp"
#include "FileClassifier.hpp"

#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <set>

FileOrganizer::FileOrganizer(
    const fs::path &p)
    : targetFolderPath(p)
{
}

fs::path FileOrganizer::getUniquePath(
    const fs::path &path)
{
    if (!fs::exists(path))
    {
        return path;
    }

    const fs::path parent =
        path.parent_path();

    const std::string stem =
        path.stem().string();

    const std::string extension =
        path.extension().string();

    for (int number = 1;; ++number)
    {
        const fs::path newPath =
            parent /
            (stem +
             " (" +
             std::to_string(number) +
             ")" +
             extension);

        if (!fs::exists(newPath))
        {
            return newPath;
        }
    }
}

void FileOrganizer::organizeFile(
    const fs::path &source)
{

    const std::string category =
        FileClassifier::classify(
            source);

    categories.insert(category);

    const fs::path categoryFolder =
        (targetFolderPath /
         category);

    fs::create_directories(categoryFolder);

    fs::path destinationFolder;

    const bool duplicate =
        duplicateDetector.hasDuplicateNamePattern(
            source) ||
        duplicateDetector.isDuplicate(
            source,
            category);

    if (duplicate)
    {
        destinationFolder =
            categoryFolder /
            "Duplicates";

        fs::create_directories(destinationFolder);

        statistics.addDuplicate();
    }
    else
    {
        duplicateDetector.rememberOriginal(
            source,
            category);

        // Category folder is the destination if the file is not a duplicate.
        destinationFolder =
            categoryFolder;
    }

    fs::path destination =
        destinationFolder /
        source.filename();

    // Prevent filename collisions.
    destination =
        getUniquePath(
            destination);

    fs::rename(
        source,
        destination);

    // Counts with how many files it worked.
    statistics.addFile(
        category);
}

void FileOrganizer::organize()
{
    if (!fs::exists(targetFolderPath))
    {
        throw std::runtime_error(
            "Target folder does not exist: " +
            targetFolderPath.string());
    }

    if (!fs::is_directory(targetFolderPath))
    {
        throw std::runtime_error(
            "Target folder is not a directory.");
    }

    for (
        const auto &entry :
        fs::directory_iterator(
            targetFolderPath))
    {
        // Ignoring CleanWrap's own log.
        if (
            entry.path().filename() ==
            "_CleanWrap.log")
        {
            continue;
        }

        // Ignoring category folders. (Otherwise it may cause a infinite loop of directories.)
        if (!entry.is_regular_file())
        {
            continue;
        }

        try
        {
            organizeFile(
                entry.path());
        }
        catch (
            const std::exception &error)
        {
            statistics.addError();

            std::cerr
                << "Could not organize: "
                << entry.path()
                << "\nReason: "
                << error.what()
                << "\n";
        }
    }

    statistics.print(
        targetFolderPath, categories);
}