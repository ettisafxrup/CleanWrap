#ifndef FILE_CLASSIFIER_HPP
#define FILE_CLASSIFIER_HPP
#include <filesystem>
#include <string>

namespace fs = std::filesystem;
class FileClassifier
{
public:
    static std::string classify(const fs::path &filePath);

private:
    static std::string toLower(std::string text);
};
#endif
