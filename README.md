<div align="center">

<img width="800" height="400" alt="CleanWrap" src="https://github.com/user-attachments/assets/d111e073-c3c8-47ec-92e2-553ace4b329f" />

# 🧹 CleanWrap

**A lightweight Windows utility for automatically organizing files, detecting duplicates, and cleaning temporary files.**

[![Language](https://img.shields.io/badge/Language-C%2B%2B20-blue)](https://isocpp.org/)
[![Platform](https://img.shields.io/badge/Platform-Windows-success)](https://www.microsoft.com/windows)
[![License](https://img.shields.io/badge/License-MIT-green)](LICENSE)
[![Latest Release](https://img.shields.io/github/v/release/ettisafxrup/CleanWrap)](https://github.com/ettisafxrup/CleanWrap/releases/latest)

</div>

---

## 📖 Overview

**CleanWrap** is a lightweight Windows desktop utility built with **Modern C++20** that automatically organizes files, detects duplicate copies, and cleans temporary files.

It is designed primarily around the **Downloads** folder, but can also organize other directories directly through the Windows Explorer context menu.

Instead of manually sorting files, identifying duplicate downloads, and removing accumulated temporary files, CleanWrap handles these tasks automatically in a single execution.

The application follows a simple workflow:

<center>

> **Scan → Classify → Detect → Organize → Clean → Report**

</center>

CleanWrap is designed to perform its work quickly and exit without continuously running in the background.

---

## ✨ Features

### 📂 File Organization

- Automatically organizes files in the Downloads folder
- Supports organizing any directory through Windows Explorer
- Classifies files into dedicated category folders
- Creates category directories only when required
- Preserves the original directory structure where possible
- Handles files with unknown or unsupported extensions safely

### 🧠 Duplicate Detection

- Multi-stage duplicate detection pipeline
- File-size based filtering
- Partial-content hashing using the first and last 64 KiB
- Full-content verification for potential duplicates
- High-speed **64-bit FNV-1a hashing**
- Recognition of common Windows duplicate filename patterns
- Timestamp-aware duplicate handling
- Dedicated duplicate folders created only when necessary

### 🧹 Windows Cleanup

- Cleans user temporary files
- Cleans Windows temporary files where permitted
- Attempts to clear the Windows Prefetch cache
- Skips files that are locked or inaccessible
- Continues execution when individual cleanup operations fail
- Reports cleanup errors instead of silently ignoring them

### 📝 Reporting & Logging

- Generates a detailed cleanup report after every execution
- Records cleanup session timestamps
- Tracks category-wise file counts
- Reports duplicate statistics
- Records errors and skipped operations
- Appends new sessions instead of overwriting previous logs

### ⚙️ Windows Integration

- Windows Explorer context menu integration
- Optional startup automation
- Optional automatic Downloads organization at Windows startup
- Windows Registry integration
- Lightweight standalone executable

---

## 🧹 Windows Cleanup

CleanWrap can remove unnecessary temporary files that accumulate over time.

The application operates conservatively:

- Directory structures are preserved.
- Files that are currently locked are skipped.
- Files requiring elevated permissions may be skipped.
- Cleanup continues even when individual files cannot be removed.
- Failed operations are recorded in the generated log.

CleanWrap **does not attempt to remove arbitrary personal files** simply because they are old or unused. Cleanup operations are limited to the locations and file types explicitly handled by the application.

---

## 📂 File Organization

CleanWrap analyzes files and places them into appropriate categories.

For example:

```text
Downloads/
├── Documents/
├── Images/
├── Videos/
├── Audio/
├── Archives/
├── Applications/
├── Code/
├── Others/
└── Duplicates/
```

> Category names and supported file types may change between releases.

Directories are created **only when at least one file belongs to that category**.

Likewise, the `Duplicates` directory is created only when duplicate files are detected.

---

## 🧠 Duplicate Detection

CleanWrap uses a staged duplicate-detection pipeline designed to avoid unnecessarily hashing every file in its entirety.

### 1. File Size Filtering

Files are initially grouped by file size.

Two files with different sizes cannot contain identical content, so they can immediately be excluded from duplicate comparison.

This significantly reduces the number of files requiring further analysis.

### 2. Partial Hash Filtering

Files with matching sizes are partially hashed using:

- The first 64 KiB
- The last 64 KiB

This provides a fast way to eliminate files that happen to share the same size but contain different data.

### 3. Full Hash Verification

Only files that pass the previous stages are processed using a complete content hash.

CleanWrap uses the **64-bit FNV-1a hashing algorithm** for this stage.

A matching full-content hash identifies files as potential duplicates, after which CleanWrap applies its duplicate-handling rules.

---

### 🤔 Windows Filename Pattern Recognition

CleanWrap additionally recognizes common filename patterns produced by Windows when duplicate files are downloaded or copied.

Examples:

```text
My File (1).pdf
My File (2).pdf
Holiday - Copy.jpg
Assignment - Copy (3).docx
```

These patterns are considered alongside content-based duplicate detection.

---

### 🕒 Timestamp-Aware Handling

When identical files are detected, CleanWrap attempts to preserve the original file while separating generated duplicate copies.

For example:

```text
Documents/
└── Assignment.docx

Duplicates/
├── Assignment (1).docx
└── Assignment (2).docx
```

This keeps the primary category directory clean while retaining duplicate files instead of immediately deleting them.

---

## 📝 Logging

After every execution, CleanWrap generates or updates:

```text
_CleanWrap.log
```

The log contains information such as:

```text
Cleanup session timestamp
Category-wise file counts
Total files processed
Duplicate statistics
Cleanup statistics
Skipped files
Error statistics
```

Logs are **appended rather than overwritten**, allowing previous cleanup sessions to remain available for reference.

---

## 🛠️ Technology Stack

CleanWrap is built using:

- **C++20**
- C++ Standard Library
- `<filesystem>`
- `<unordered_map>`
- `<regex>`
- `<fstream>`
- FNV-1a 64-bit hashing
- Object-Oriented Programming
- Modular project architecture
- Windows Registry APIs
- Windows Explorer integration
- Shell scripting
- Inno Setup

---

## 📦 Project Structure

```text
CleanWrap/
│
├── assets/
│   ├── cleanwrap.ico
│   ├── icon.rc
│   ├── installer_banner.bmp
│   ├── installer_icon.bmp
│   └── logo.png
│
├── docs/
│   ├── .txt/
│   │   ├── CleanWrap_User_Manual_v1.0.txt
│   │   ├── GREETING.txt
│   │   ├── README.txt
│   │   ├── THANK_YOU.txt
│   │   ├── UNINSTALL.txt
│   │   └── User_Manual.txt
│   │
│   ├── index.html
│   ├── release_v1.4.0.md
│   │
│   └── web/
│       ├── assets/
│       ├── css/
│       ├── fonts/
│       └── js/
│
├── include/
│   ├── DuplicateDetector.hpp
│   ├── FileClassifier.hpp
│   ├── FileOrganizer.hpp
│   ├── FileTypes.hpp
│   ├── Notifications.hpp
│   ├── Statistics.hpp
│   ├── UpdateChecker.hpp
│   └── WindowsCleanup.hpp
│
├── innosetup/
│   └── cleanwrap_inno.iss
│
├── release/
│   └── CleanWrap_v1.4.0.exe
│
├── scripts/
│   └── build.sh
│
├── src/
│   ├── DuplicateDetector.cpp
│   ├── FileClassifier.cpp
│   ├── FileOrganizer.cpp
│   ├── FileTypes.cpp
│   ├── Statistics.cpp
│   ├── UpdateChecker.cpp
│   └── WindowsCleanup.cpp
│
├── main.cpp
├── LICENSE
├── README.md
└── release.json
```

---

## 💻 Installation

Download and Install CleanWrap from the Website:
[Download CleanWrap (Latest)](https://ettisafxrup.github.io/CleanWrap)

Or, You can download the latest installer from the project's [Release](https://github.com/ettisafxrup/CleanWrap/releases/latest) page.

During installation, you may optionally enable:

- **Windows Explorer Context Menu Integration**
- **Automatic Downloads Organization at Windows Startup**

After installation, CleanWrap can be used in two ways.

### Normal Execution

Launch CleanWrap to organize and clean the configured Downloads directory.

### Windows Explorer

Right-click inside a supported directory and select:

```text
🧹 Organize with CleanWrap
```

CleanWrap will process the selected directory and exit after completing the operation.

---

## 🔨 Building Locally

### Requirements

- Windows
- MinGW-w64 / GCC
- C++20-compatible compiler
- Git

### Manual Build

From the project root:

```bash
g++ -O2 -std=c++20 ^
-Iinclude ^
main.cpp ^
src/*.cpp ^
-o CleanWrap.exe
```

### One-Click Build

```bash
cd scripts
./build.sh
```

> The project targets **C++20**, so the compiler must support the required C++20 features.

---

## 🧪 Testing

Before submitting changes, verify the application against:

- Empty directories
- Large directories
- Files with unknown extensions
- Files with identical sizes but different contents
- Exact duplicate files
- Windows-generated duplicate filenames
- Locked files
- Permission-restricted files
- Files with Unicode names
- Very large files
- Empty files
- Startup execution
- Explorer context-menu execution

When modifying duplicate detection or file organization logic, testing should include both normal and edge-case scenarios to ensure that files are not accidentally moved or classified incorrectly.

---

## 🐛 Reporting Issues

Found a bug?
Please open an [issue](https://github.com/ettisafxrup/CleanWrap/issues) with enough information to reproduce the problem.

Please **do not upload private or sensitive files** merely to demonstrate a problem.

---

## 💡 Feature Requests

Feature suggestions are welcome.

Before opening a feature request:

1. Check whether the feature has already been requested.
2. Explain the problem the feature would solve.
3. Describe the proposed behavior.
4. Include examples where appropriate.

Features that improve reliability, safety, performance, accessibility, or Windows integration are particularly useful areas for discussion.

# 💖 Sponsoring CleanWrap

CleanWrap is developed as an independent open-source project.

If you find the project useful and would like to support its continued development, sponsorship can help fund:

- Development and maintenance
- Testing across Windows environments
- Infrastructure and hosting
- Documentation
- Distribution and release tooling
- Future features and improvements

You can support the project through the repository's **Sponsor** options when available.

---

## 📜 License

CleanWrap is distributed under the **MIT License**.

See [`LICENSE`](LICENSE) for the complete license text.

In short, the MIT License permits use, modification, distribution, and private or commercial use, subject to the conditions specified in the license.

---

## 🔐 Privacy & Safety

CleanWrap is designed to operate locally on the user's Windows machine.

The application does not need to upload the user's personal files to a remote server to perform its core organization and duplicate-detection functions.

---

## 👨‍💻 Author

**Ettisaf Rup**

Computer Science & Engineering undergraduate and independent software developer.

- GitHub: [@ettisafxrup](https://github.com/ettisafxrup)
- Project: [CleanWrap](https://github.com/ettisafxrup/CleanWrap)

Designed and developed with ❤️ using **Modern C++**.

---

## ⭐ Support the Project

If CleanWrap helped you keep your system organized, consider:

- ⭐ Starring the repository
- 🐛 Reporting bugs
- 💡 Suggesting features
- 🤝 Contributing code
- 📖 Improving documentation
- 📢 Sharing the project
- 💖 Sponsoring development

Even a GitHub star helps more people discover the project.

---

<div align="center">

**CleanWrap — Because your folders deserve better.**

Made with ❤️ by **Ettisaf Rup**
© 2026 ettisafxrup. All rights reserved.

</div>
