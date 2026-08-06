#ifndef NOTIFICATIONS_HPP
#define NOTIFICATIONS_HPP

#include <string>
#include <unordered_map>
#include <wintoastlib.h>


class Notifications
{
public:
    Notifications();
    void showNotification(
        const std::string &title,
        const std::string &message);

private:
    WinToastLib::WinToastTemplate toastTemplate;
    WinToastLib::WinToast toast;
};