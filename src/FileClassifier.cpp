#include "FileClassifier.hpp"
#include "FileTypes.hpp"
#include <algorithm>
#include <cctype>

std::string FileClassifier::toLower(std::string text)
{
    std::transform(text.begin(), text.end(), text.begin(), [](unsigned char c)
                   { return static_cast<char>(std::tolower(c)); });
    return text;
}

std::string FileClassifier::classify(const fs::path &filePath)
{
    return FileTypes::getCategory(toLower(filePath.extension().string()));
}
