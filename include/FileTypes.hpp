#ifndef FILE_TYPES_HPP
#define FILE_TYPES_HPP
#include <string>
#include <unordered_map>
namespace FileTypes
{
    extern const std::unordered_map<std::string, std::string> extensionMap;
    const std::string &getCategory(const std::string &extension);
}
#endif
