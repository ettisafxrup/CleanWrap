#include "FileOrganizer.hpp"
#include "FileClassifier.hpp"

#include <iostream>
#include <stdexcept>

FileOrganizer::FileOrganizer(
    const fs::path &p)
    : downloadsPath(p)
{
    categories =
        {
            "Images",
            "PDFs",
            "Videos",
            "Audio",
            "Code",
            "Zips",
            "Executables and Installers",
            "Documents",
            "Others"};
}

void FileOrganizer::createFolders()
{
    for (const auto &category : categories)
    {
        fs::create_directories(
            downloadsPath /
            category);

        fs::create_directories(
            downloadsPath /
            category /
            ("Duplicates_" + category));
    }
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

    const fs::path categoryFolder =
        (downloadsPath /
         category);

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
            ("Duplicates_" + category);

        statistics.addDuplicate();
    }
    else
    {
        duplicateDetector.rememberOriginal(
            source,
            category);
        destinationFolder =
            categoryFolder;
    }

    // Ensure the destination exists.
    fs::create_directories(
        destinationFolder);

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

    // Counts every moved file,
    // including duplicates.
    statistics.addFile(
        category);
}

void FileOrganizer::organize()
{
    if (!fs::exists(downloadsPath))
    {
        throw std::runtime_error(
            "Downloads folder does not exist: " +
            downloadsPath.string());
    }

    if (!fs::is_directory(downloadsPath))
    {
        throw std::runtime_error(
            "Downloads path is not a directory.");
    }

    createFolders();

    for (
        const auto &entry :
        fs::directory_iterator(
            downloadsPath))
    {
        // Ignore downTidy's own log.
        if (
            entry.path().filename() ==
            "_downTidy.log")
        {
            continue;
        }

        // Ignore category folders.
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
        downloadsPath);
}