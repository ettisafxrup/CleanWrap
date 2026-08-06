#ifndef STATISTICS_HPP
#define STATISTICS_HPP
#include <string>
#include <unordered_map>
#include <filesystem>

namespace fs = std::filesystem;
class Statistics
{
public:
    void addFile(const std::string &category);
    void addDuplicate();
    void addError();
    void print(const fs::path &downloadsPath) const;

private:
    std::unordered_map<std::string, int> categoryCounts;
    int duplicateCount = 0, errorCount = 0;
};
#endif
