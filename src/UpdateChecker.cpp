#include "UpdateChecker.hpp"
#include "Version.hpp"

#include <windows.h>
#include <shellapi.h>
#include <winhttp.h>

#include <chrono>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

namespace fs = std::filesystem;

namespace
{
    constexpr auto CHECK_INTERVAL = std::chrono::hours(24 * 3);

    constexpr wchar_t GITHUB_HOST[] = L"api.github.com";
    constexpr wchar_t RELEASE_PATH[] =
        L"/repos/ettisafxrup/CleanWrap/releases/latest";

    constexpr char RELEASE_URL[] =
        "https://github.com/ettisafxrup/CleanWrap/releases/latest";

    fs::path getCachePath()
    {
        const char *localAppData = std::getenv("LOCALAPPDATA");

        if (!localAppData || *localAppData == '\0')
        {
            return {};
        }

        return fs::path(localAppData) /
               "CleanWrap" /
               "update-check.txt";
    }

    bool shouldCheckForUpdates(const fs::path &cachePath)
    {
        if (cachePath.empty())
        {
            return true;
        }

        std::ifstream cache(cachePath);

        std::string cachedVersion;
        long long lastCheck = 0;

        if (!(cache >> cachedVersion >> lastCheck))
        {
            return true;
        }

        // Check immediately after the application itself is updated.
        if (cachedVersion != CLEANWRAP_VERSION)
        {
            return true;
        }

        if (lastCheck <= 0)
        {
            return true;
        }

        const auto now = std::chrono::system_clock::now();

        const auto lastCheckTime =
            std::chrono::system_clock::from_time_t(
                static_cast<std::time_t>(lastCheck));

        // System clock moved backwards.
        if (lastCheckTime > now)
        {
            return true;
        }

        return now - lastCheckTime >= CHECK_INTERVAL;
    }

    void rememberCheckTime(const fs::path &cachePath)
    {
        if (cachePath.empty())
        {
            return;
        }

        std::error_code error;

        fs::create_directories(
            cachePath.parent_path(),
            error);

        if (error)
        {
            return;
        }

        const auto now =
            std::chrono::system_clock::to_time_t(
                std::chrono::system_clock::now());

        std::ofstream cache(
            cachePath,
            std::ios::trunc);

        if (cache)
        {
            cache << CLEANWRAP_VERSION
                  << ' '
                  << static_cast<long long>(now);
        }
    }

    std::vector<int> parseVersion(const std::string &version)
    {
        std::string value = version;

        // Accept both "1.2.3" and "v1.2.3".
        if (!value.empty() && value.front() == 'v')
        {
            value.erase(value.begin());
        }

        if (value.empty())
        {
            return {};
        }

        std::vector<int> parts;
        std::stringstream stream(value);
        std::string part;

        while (std::getline(stream, part, '.'))
        {
            if (part.empty())
            {
                return {};
            }

            for (char c : part)
            {
                if (c < '0' || c > '9')
                {
                    return {};
                }
            }

            try
            {
                parts.push_back(std::stoi(part));
            }
            catch (...)
            {
                return {};
            }
        }

        return parts;
    }

    bool getLatestVersion(std::string &latestVersion)
    {
        HINTERNET session = WinHttpOpen(
            L"CleanWrap-UpdateChecker/1.0",
            WINHTTP_ACCESS_TYPE_DEFAULT_PROXY,
            WINHTTP_NO_PROXY_NAME,
            WINHTTP_NO_PROXY_BYPASS,
            0);

        if (!session)
        {
            return false;
        }

        WinHttpSetTimeouts(
            session,
            2000,
            2000,
            2000,
            4000);

        HINTERNET connection = WinHttpConnect(
            session,
            GITHUB_HOST,
            INTERNET_DEFAULT_HTTPS_PORT,
            0);

        if (!connection)
        {
            WinHttpCloseHandle(session);
            return false;
        }

        HINTERNET request = WinHttpOpenRequest(
            connection,
            L"GET",
            RELEASE_PATH,
            nullptr,
            WINHTTP_NO_REFERER,
            WINHTTP_DEFAULT_ACCEPT_TYPES,
            WINHTTP_FLAG_SECURE);

        if (!request)
        {
            WinHttpCloseHandle(connection);
            WinHttpCloseHandle(session);
            return false;
        }

        constexpr wchar_t HEADERS[] =
            L"Accept: application/vnd.github+json\r\n"
            L"X-GitHub-Api-Version: 2022-11-28\r\n";

        if (!WinHttpSendRequest(
                request,
                HEADERS,
                static_cast<DWORD>(-1),
                WINHTTP_NO_REQUEST_DATA,
                0,
                0,
                0) ||
            !WinHttpReceiveResponse(request, nullptr))
        {
            WinHttpCloseHandle(request);
            WinHttpCloseHandle(connection);
            WinHttpCloseHandle(session);
            return false;
        }

        // Make sure GitHub actually returned HTTP 200.
        DWORD statusCode = 0;
        DWORD statusSize = sizeof(statusCode);

        if (!WinHttpQueryHeaders(
                request,
                WINHTTP_QUERY_STATUS_CODE |
                    WINHTTP_QUERY_FLAG_NUMBER,
                WINHTTP_HEADER_NAME_BY_INDEX,
                &statusCode,
                &statusSize,
                WINHTTP_NO_HEADER_INDEX) ||
            statusCode != 200)
        {
            WinHttpCloseHandle(request);
            WinHttpCloseHandle(connection);
            WinHttpCloseHandle(session);
            return false;
        }

        std::string response;

        while (true)
        {
            DWORD bytesAvailable = 0;

            if (!WinHttpQueryDataAvailable(
                    request,
                    &bytesAvailable))
            {
                WinHttpCloseHandle(request);
                WinHttpCloseHandle(connection);
                WinHttpCloseHandle(session);
                return false;
            }

            if (bytesAvailable == 0)
            {
                break;
            }

            std::string buffer(
                bytesAvailable,
                '\0');

            DWORD bytesRead = 0;

            if (!WinHttpReadData(
                    request,
                    buffer.data(),
                    bytesAvailable,
                    &bytesRead))
            {
                WinHttpCloseHandle(request);
                WinHttpCloseHandle(connection);
                WinHttpCloseHandle(session);
                return false;
            }

            response.append(
                buffer.data(),
                bytesRead);
        }

        WinHttpCloseHandle(request);
        WinHttpCloseHandle(connection);
        WinHttpCloseHandle(session);

        // Find: "tag_name": "v1.2.3"
        const std::string key = "\"tag_name\"";

        const std::size_t keyPosition =
            response.find(key);

        if (keyPosition == std::string::npos)
        {
            return false;
        }

        const std::size_t colon =
            response.find(':', keyPosition);

        if (colon == std::string::npos)
        {
            return false;
        }

        const std::size_t firstQuote =
            response.find('"', colon + 1);

        if (firstQuote == std::string::npos)
        {
            return false;
        }

        const std::size_t secondQuote =
            response.find('"', firstQuote + 1);

        if (secondQuote == std::string::npos)
        {
            return false;
        }

        latestVersion =
            response.substr(
                firstQuote + 1,
                secondQuote - firstQuote - 1);

        return !latestVersion.empty();
    }
}

void UpdateChecker::checkForUpdates()
{
    const fs::path cachePath = getCachePath();

    // Do not check again until the interval has passed.
    if (!shouldCheckForUpdates(cachePath))
    {
        return;
    }

    /*
     * Remember the attempt BEFORE contacting GitHub.
     *
     * This prevents repeated network requests every time the
     * application starts while the user is offline.
     */
    rememberCheckTime(cachePath);

    std::string latestVersion;

    if (!getLatestVersion(latestVersion))
    {
        return;
    }

    if (!isNewerVersion(latestVersion))
    {
        return;
    }

    const std::string message =
        "CleanWrap v" + latestVersion +
        " is available.\n\n"
        "Would you like to open the download page?";

    const int result = MessageBoxA(
        nullptr,
        message.c_str(),
        "CleanWrap Update Available",
        MB_YESNO | MB_ICONINFORMATION);

    if (result == IDYES)
    {
        ShellExecuteA(
            nullptr,
            "open",
            RELEASE_URL,
            nullptr,
            nullptr,
            SW_SHOWNORMAL);
    }
}

bool UpdateChecker::isNewerVersion(
    const std::string &latestVersion)
{
    const std::vector<int> current =
        parseVersion(CLEANWRAP_VERSION);

    const std::vector<int> latest =
        parseVersion(latestVersion);

    if (current.empty() || latest.empty())
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
            i < current.size()
                ? current[i]
                : 0;

        const int latestPart =
            i < latest.size()
                ? latest[i]
                : 0;

        if (latestPart > currentPart)
        {
            return true;
        }

        if (latestPart < currentPart)
        {
            return false;
        }
    }

    return false;
}