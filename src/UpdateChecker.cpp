#include "UpdateChecker.hpp"
#include "Version.hpp"

#include <windows.h>
#include <winhttp.h>
#include <chrono>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <regex>
#include <sstream>
#include <string>
#include <vector>

namespace fs = std::filesystem;

namespace
{
    constexpr auto CHECK_INTERVAL = std::chrono::hours(24 * 7);
    constexpr wchar_t REPOSITORY_HOST[] = L"api.github.com";
    constexpr wchar_t RELEASE_PATH[] =
        L"/repos/ettisafxrup/CleanWrap/releases/latest";

    fs::path getCachePath()
    {
        const char *localAppData = std::getenv("LOCALAPPDATA");
        if (!localAppData)
        {
            return {};
        }

        return fs::path(localAppData) /
               "CleanWrap" /
               "update-check.txt";
    }

    bool shouldCheckForUpdates(
        const fs::path &cachePath)
    {
        std::ifstream cache(cachePath);
        long long lastCheck = 0;
        std::string checkedVersion;

        if (!(cache >> checkedVersion >> lastCheck) ||
            checkedVersion != CLEANWRAP_VERSION)
        {
            return true;
        }

        const auto now =
            std::chrono::system_clock::now();
        const auto lastCheckTime =
            std::chrono::system_clock::from_time_t(
                static_cast<std::time_t>(lastCheck));

        return now - lastCheckTime >= CHECK_INTERVAL;
    }

    void rememberCheckTime(
        const fs::path &cachePath)
    {
        std::error_code error;
        fs::create_directories(cachePath.parent_path(), error);
        if (error)
        {
            return;
        }

        const auto now = std::chrono::system_clock::to_time_t(
            std::chrono::system_clock::now());
        std::ofstream cache(cachePath, std::ios::trunc);
        if (cache)
        {
            cache << CLEANWRAP_VERSION << ' ' << now;
        }
    }

    std::vector<int> parseVersion(const std::string &version)
    {
        std::vector<int> parts;
        std::stringstream stream(version);
        std::string part;

        while (std::getline(stream, part, '.'))
        {
            try
            {
                parts.push_back(std::stoi(part));
            }
            catch (const std::exception &)
            {
                return {};
            }
        }

        return parts;
    }
}

void UpdateChecker::checkForUpdates()
{
    const fs::path cachePath = getCachePath();
    if (cachePath.empty() || !shouldCheckForUpdates(cachePath))
    {
        return;
    }

    rememberCheckTime(cachePath);

    HINTERNET session = WinHttpOpen(
        L"CleanWrap-UpdateChecker/1.0",
        WINHTTP_ACCESS_TYPE_DEFAULT_PROXY,
        WINHTTP_NO_PROXY_NAME,
        WINHTTP_NO_PROXY_BYPASS,
        0);

    if (!session)
    {
        return;
    }

    WinHttpSetTimeouts(session, 2000, 2000, 2000, 2000);
    HINTERNET connection = WinHttpConnect(
        session,
        REPOSITORY_HOST,
        INTERNET_DEFAULT_HTTPS_PORT,
        0);

    if (!connection)
    {
        WinHttpCloseHandle(session);
        return;
    }

    HINTERNET request = WinHttpOpenRequest(
        connection,
        L"GET",
        RELEASE_PATH,
        nullptr,
        WINHTTP_NO_REFERER,
        WINHTTP_DEFAULT_ACCEPT_TYPES,
        WINHTTP_FLAG_SECURE);

    if (!request || !WinHttpSendRequest(request, WINHTTP_NO_ADDITIONAL_HEADERS, 0, WINHTTP_NO_REQUEST_DATA, 0, 0, 0) ||
        !WinHttpReceiveResponse(request, nullptr))
    {
        if (request)
        {
            WinHttpCloseHandle(request);
        }
        WinHttpCloseHandle(connection);
        WinHttpCloseHandle(session);
        return;
    }

    std::string response;
    DWORD bytesAvailable = 0;
    while (WinHttpQueryDataAvailable(request, &bytesAvailable) &&
           bytesAvailable > 0)
    {
        std::string buffer(bytesAvailable, '\0');
        DWORD bytesRead = 0;
        if (!WinHttpReadData(
                request,
                buffer.data(),
                bytesAvailable,
                &bytesRead))
        {
            response.clear();
            break;
        }
        response.append(buffer.data(), bytesRead);
    }

    WinHttpCloseHandle(request);
    WinHttpCloseHandle(connection);
    WinHttpCloseHandle(session);

    std::smatch match;
    if (!std::regex_search(
            response,
            match,
            std::regex(
                "\\\"tag_name\\\"\\s*:\\s*\\\"v?([0-9]+(?:\\.[0-9]+)*)\\\"")))
    {
        return;
    }

    const std::string latestVersion = match[1].str();
    if (isNewerVersion(latestVersion))
    {
        const std::string message =
            "CleanWrap v" + latestVersion +
            " is available. Download it from:\n\n"
            "https://github.com/ettisafxrup/CleanWrap/releases/latest";
        MessageBoxA(
            nullptr,
            message.c_str(),
            "CleanWrap Update Available",
            MB_OK | MB_ICONINFORMATION);
    }
}

bool UpdateChecker::isNewerVersion(
    const std::string &latestVersion)
{
    const std::vector<int> current =
        parseVersion(CLEANWRAP_VERSION);
    const std::vector<int> latest = parseVersion(latestVersion);

    if (latest.empty() || current.empty())
    {
        return false;
    }

    const std::size_t count =
        current.size() > latest.size()
            ? current.size()
            : latest.size();

    for (std::size_t i = 0; i < count; ++i)
    {
        const int currentPart =
            i < current.size() ? current[i] : 0;
        const int latestPart =
            i < latest.size() ? latest[i] : 0;

        if (latestPart != currentPart)
        {
            return latestPart > currentPart;
        }
    }

    return false;
}