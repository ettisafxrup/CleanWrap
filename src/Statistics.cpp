#include "Statistics.hpp"
#include <iostream>
#include <set>
#include <fstream>
#include <chrono>
#include <iomanip>
#include <filesystem>
#include <cstdlib>

namespace fs = std::filesystem;

void Statistics::addFile(const std::string &c) { categoryCounts[c]++; }
void Statistics::addDuplicate() { duplicateCount++; }
void Statistics::addError() { errorCount++; }

// I want this Statisis to print the summery to a .log text file in the downloads directory with mentioning the date and time while the program ran. With proper details of what the program did. Make sure the log doesn't override, it appends

void Statistics::print(const fs::path &targetFolderPath, const std::set<std::string> &categories) const
{
        // Log Table Width
        int LABEL_WIDTH = 32;

        const fs::path logPath =
            targetFolderPath /
            "_CleanWrap.log";

        std::ofstream logFile(
            logPath,
            std::ios::out |
                std::ios::app);

        if (!logFile.is_open())
        {
                return;
        }

        std::size_t totalFiles = 0;

        auto now = std::chrono::system_clock::now();
        std::time_t now_time = std::chrono::system_clock::to_time_t(now);

        logFile << "___x______x______x______x______x______x___\n"
                << "\n";

        // "%I:%M%p | %d %B, %Y"
        logFile << "_CleanWrap: " << std::put_time(std::localtime(&now_time), "> %I:%M%p | %d %B, %Y") << "\n";

        logFile << "===================================="
                << "\n";

        logFile << "[log]_CleanWrap__Cleanup" << "\n";

        logFile << "===================================="
                << "\n";

        for (const auto &c : categories)
        {

                auto it = categoryCounts.find(c);
                totalFiles += (it == categoryCounts.end() ? 0 : it->second);
                logFile << std::left
                        << std::setw(LABEL_WIDTH) << c << ": " << (it == categoryCounts.end() ? 0 : it->second) << '\n';
        }

        logFile << "===================================="
                << "\n";
        logFile << std::left
                << std::setw(LABEL_WIDTH) << "Total Files Handled" << ": " << totalFiles << "\n";

        logFile << "____________________________________"
                << "\n";

        logFile
            << std::left
            << std::setw(LABEL_WIDTH) << "Duplicates" << ": " << duplicateCount << "\n"
            << std::left
            << std::setw(LABEL_WIDTH) << "Errors" << ": " << errorCount << "\n";

        logFile << "===================================="
                << "\n";

        logFile << "\n___x______x______x______x______x______x___" << "\n";

        logFile.flush();

        // Even though the destructor of std::ofstream will close the file automatically, it's a good practice to explicitly close it when done.
        logFile.close();
}
