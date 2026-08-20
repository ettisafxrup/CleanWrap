#ifndef UPDATE_CHECKER_HPP
#define UPDATE_CHECKER_HPP

#include <string>

class UpdateChecker
{
public:
    static void checkForUpdates();

private:
    static bool isNewerVersion(
        const std::string &latestVersion);
};

#endif