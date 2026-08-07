<center>
<img width="800" height="400" alt="WhatsApp Image 2026-08-06 at 22 19 22" src="https://github.com/user-attachments/assets/d111e073-c3c8-47ec-92e2-553ace4b329f" />
</center>

# 📂 CleanWrap

> A lightweight C++ application that automatically organizes your Downloads folder into categorized directories with smart duplicate detection.

![Language](https://img.shields.io/badge/Language-C%2B%2B20-blue)
![Platform](https://img.shields.io/badge/Platform-Windows-success)
![License](https://img.shields.io/badge/License-MIT-green)

---

## 📖 Overview

**CleanWrap** is a desktop utility built entirely in modern C++ that helps keep your **Downloads** folder clean and organized.

Instead of manually sorting downloaded files, CleanWrap automatically classifies them into dedicated folders while intelligently handling duplicate files.

The application is designed to run once, organize everything in seconds, generate a cleanup report, and exit.

---

## ✨ Features

- Automatically organizes downloaded files
- Organizes any folder through the Windows Explorer Context Menu
- Categorizes files by extension
- Creates category folders only when needed
- Creates duplicate folders only when duplicates are detected
- Supports documents, images, videos, audio, code files, archives, executables, installers, and many more
- Detects duplicate files using high-speed 64-bit FNV-1a hashing
- Recognizes common Windows duplicate filename patterns
- Places duplicate files into dedicated duplicate folders
- Automatically generates detailed cleanup logs
- Can automatically organize Downloads every time Windows starts (optional)
- Lightweight and extremely fast
- Modular object-oriented architecture
- Built entirely using Modern C++20

---

After Installing CleanWrap, your **Downloads** Folder will look never cleaner than this-

## 📂 Downloads Folder Structure

Folders are created only when at least one file belongs to that category. Likewise, duplicate folders are created only when duplicate files are detected.

```text
Downloads/

├── Images/
│   └── Duplicates/ (if any)
│
├── PDFs/
│   └── Duplicates/ (if any)
│
├── Videos/
│   └── Duplicates/ (if any)
│
├── Audio/
│   └── Duplicates/ (if any)
│
├── Code/
│   └── Duplicates/ (if any)
│
├── Documents/
│   └── Duplicates/ (if any)
│
├── Zips/
│   └── Duplicates/ (if any)
│
├── Executables and Installers/
│   └── Duplicates/ (if any)
│
├── Others/
│   └── Duplicates/ (if any)
│
└── _CleanWrap.log

```

---

## 🧠 Duplicate Detection

CleanWrap uses a two-stage duplicate detection system.

### 1. Hash-Based Detection

Every file is hashed using a fast 64-bit FNV-1a hashing algorithm.

If another file with the exact same content already exists, CleanWrap identifies it as a duplicate.

---

### 2. Windows Copy Pattern Recognition

CleanWrap also recognizes common Windows duplicate filename patterns, including:

```text
My File (1).pdf
My File (2).pdf
Holiday - Copy.jpg
Assignment - Copy (3).docx
```

These filename patterns are checked alongside hash matching before classifying them as duplicates.

### 3. Timestamp-Aware Duplicate Handling

When identical files are detected, CleanWrap intelligently keeps the original file in the main category folder while moving Windows-generated duplicate copies (such as `(1)` or `- Copy`) into the corresponding duplicate folder.

This preserves the original file structure while separating unnecessary duplicates.

---

## 📝 Logging

After every execution, CleanWrap generates a report named

```text
_CleanWrap.log
```

The report includes:

- Cleanup session timestamp
- Category-wise file counts
- Total files handled
- Duplicate statistics
- Error statistics

Logs are appended instead of overwritten, preserving the history of every cleanup session.

---

## 🛠 Technologies Used

- Modern C++20
- STL
- FNV-1a 64-bit Hashing
- `<filesystem>`
- `<unordered_map>`
- `<regex>`
- `<fstream>`
- Object-Oriented Programming
- Modular Project Architecture
- Windows Registry Integration
- Windows Explorer Context Menu
- Shell Scripts
- Inno Scripts

---

## 📦 Project Structure

```text
CleanWrap/
📁 Application Structure:

.
├── main.cpp
├── release.sh (Compilation ShellScript)
│
├── 📂 assets
│   ├── cleanwrap.ico
│   ├── installer_banner.bmp
│   ├── installer_icon.bmp
│   ├── logo.png
│
├── 📂 include
│   ├── DuplicateDetector.hpp
│   ├── FileClassifier.hpp
│   ├── FileOrganizer.hpp
│   ├── FileTypes.hpp
│   ├── Notifications.hpp
│   ├── Statistics.hpp
│
├── 📂 src
│   ├── DuplicateDetector.cpp
│   ├── FileClassifier.cpp
│   ├── FileOrganizer.cpp
│   ├── FileTypes.cpp
│   ├── Statistics.cpp
│
├── 📂 innosetup
│   ├── cleanwrap_v1.0.iss
│

```

---

## 💻 Installation

Download the latest installer from the Releases page.

Run the installer and optionally enable:

- Windows Explorer Context Menu Integration
- Automatically organize Downloads when Windows starts

After installation, you can:

- Launch CleanWrap normally to organize the Downloads folder.
- Right-click inside any folder and select **Organize with CleanWrap**.

---

## 🚀 Building in Local

Compile using g++:

```bash
g++ -O2 -std=c++17 ^
-Iinclude ^
main.cpp ^
src/*.cpp ^
-o CleanWrap.exe
```

For release builds:

```bash
./release.sh
```

---

## ✅ Scored Targeted Improvements

- Configuration file support ✅
- File-type icons ✅
- Easier Installation with Installer ✅
- One-Click Tide Directory Feature ✅
- Better Logging ✅

---

## Future Improvements

- Drag & Drop Support
- Automatic Update Checker
- Dark Mode GUI
- Custom Category Rules
- Configuration File (.json)
- File Preview
- Localization

---

## 🖋 Author

**Ettisaf Rup**  
GitHub: https://github.com/ettisafxrup

Designed and developed with ❤️ using Modern C++.

---

## 🤲 Support CleanWrap

If you found this project useful, consider giving it a ⭐ on GitHub.
It helps others discover the project and motivates future improvements.

and if anyone wills to donate, you can bring me to a tong.

[![Download Latest Release](https://img.shields.io/badge/Download-CleanWrap%20v1.0-success?style=for-the-badge)](https://github.com/ettisafxrup/CleanWrap/releases/latest)

---

<small> _ettisafxrup CleanWrap@2026 | all rights reserved_ </small>
