# 🧹 CleanWrap — Smart File Organization for Windows [v1.3.0]

> ![Language](https://img.shields.io/badge/Language-C%2B%2B20-blue)
> ![Platform](https://img.shields.io/badge/Platform-Windows-success)
> ![License](https://img.shields.io/badge/License-MIT-green)
> ![Version](https://img.shields.io/badge/v1.3.0-8A2BE2)

**CleanWrap v1.3.0** 🎉

# 🤔 What's New

- Added an optional installer task to organize the Desktop automatically when Windows starts.
- Desktop organization can be enabled independently from Downloads organization.
- Desktop startup uses the current user's Desktop path, so files are organized in the correct user profile.
- Desktop startup registration is removed automatically when CleanWrap is uninstalled.
- Preserved the existing Explorer context-menu workflow for organizing any selected folder.

## 🖥️ Optional Desktop Startup

- During installation, select **Automatically organize your Desktop when Windows starts** to enable the feature.
- When enabled, CleanWrap runs at Windows logon and organizes files directly on the Desktop.
- When left unchecked, CleanWrap does not add a Desktop startup entry.
- The existing **Automatically organize your Downloads folder when Windows starts** option remains available separately.

## 🔍 Duplicate Detection

- Added staged duplicate detection for faster file organization.
- Files are filtered by size before any content hashing is performed.
- Same-size files are compared using a partial hash of their first and last 64 KiB.
- A complete FNV-1a hash is calculated only when the earlier checks match.
- Reduced unnecessary disk reads and hashing work for files that cannot be duplicates.

## 🔄 Periodic Update Checker

- CleanWrap checks GitHub for a newer release automatically.
- Update checks run once every seven days instead of on every startup.
- The check interval is stored in a small file under `%LOCALAPPDATA%\\CleanWrap`.
- A version change triggers a fresh check immediately.
- Network failures do not interrupt file organization.
- A Windows notification is shown only when a newer version is available.

## 🧩 Centralized Version Management

- The application version is managed from one shared `Version.hpp` file.
- The application, update checker, build script, release script, and installer use the same version.
- Installer names and release tags can be updated without changing several source files manually.

## 🛠️ Build and Compatibility Improvements

- Added the Windows WinHTTP dependency for secure GitHub release checks.
- Preserved the lightweight, one-shot workflow of the application.
- Kept update checking non-blocking for offline users through short request timeouts.

## 📦 Installation

Download the latest installer from the GitHub Releases page:

[![Download Latest Release](https://img.shields.io/badge/📥-Download%20Latest%20Release-blue?style=for-the-badge)](https://github.com/ettisafxrup/CleanWrap/releases/latest)

The installer is named `CleanWrap_v1.3.0_Setup.exe`.

<small><i>CleanWrap © 2026 • Developed by Ettisaf Rup • Released under the MIT License</i></small>
