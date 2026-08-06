# 📂 downTidy

> A lightweight C++ application that automatically organizes your Downloads folder into categorized directories with smart duplicate detection.

![Language](https://img.shields.io/badge/Language-C%2B%2B20-blue)
![Platform](https://img.shields.io/badge/Platform-Windows-success)
![License](https://img.shields.io/badge/License-MIT-green)

![![Download](https://github.com/ettisafxrup/downTidy/releases)](https://img.shields.io/badge/📥-Download-blue)
![Stars](https://img.shields.io/github/stars/ettisafxrup/downTidy)

---

## 📖 Overview

**downTidy** is a desktop utility built entirely in modern C++ that helps keep your **Downloads** folder clean and organized.

Instead of manually sorting downloaded files, downTidy automatically classifies them into dedicated folders while intelligently handling duplicate files.

The application is designed to run once, organize everything in seconds, generate a cleanup report, and exit.

---

## ✨ Features

- Automatically organizes downloaded files
- Categorizes files by extension
- Supports documents, images, videos, audio, code files, archives, executables, and more
- Detects duplicate files using file hashing
- Places duplicate files into dedicated duplicate folders
- Generates a cleanup log after every execution
- Lightweight and fast
- Modular architecture using multiple C++ classes
- Built with Modern C++20

---

After Installing downTidy, your **Downloads** Folder will look never cleaner than this-

## 📂 Downloads Folder Structure

```text
Downloads/

├── Images/
│   └── Duplicates_Images/
│
├── PDFs/
│   └── Duplicates_PDFs/
│
├── Videos/
│   └── Duplicates_Videos/
│
├── Audio/
│   └── Duplicates_Audio/
│
├── Code/
│   └── Duplicates_Code/
│
├── Documents/
│   └── Duplicates_Documents/
│
├── Zips/
│   └── Duplicates_Zips/
│
├── Executables and Installers/
│   └── Duplicates_Executables and Installers/
│
├── Others/
│   └── Duplicates_Others/
│
└── _downTidy.log
```

---

## 🧠 Duplicate Detection

downTidy uses a two-stage duplicate detection system.

### 1. Hash-Based Detection

Every file is hashed using a fast 64-bit FNV-1a hashing algorithm.

If another file with the exact same content already exists, downTidy identifies it as a duplicate.

---

### 2. Windows Copy Pattern Recognition

downTidy also recognizes common Windows duplicate filename patterns, including:

```text
My File (1).pdf
My File (2).pdf
Holiday - Copy.jpg
Assignment - Copy (3).docx
```

These filename patterns are checked alongside hash matching before classifying them as duplicates.

---

## 📝 Logging

After every execution, downTidy generates a report named

```text
_downTidy.log
```

The report includes:

- Date & time
- Number of files processed
- Category-wise statistics
- Duplicate count
- Error count

Logs are appended instead of overwritten, preserving the history of every cleanup session.

---

## 🛠 Technologies Used

- Modern C++20
- STL
- `<filesystem>`
- `<unordered_map>`
- `<regex>`
- `<fstream>`
- Object-Oriented Programming
- Modular Project Architecture
- Shell Scripts

---

## 📦 Project Structure

```text
downTidy/
.
├── downTidy.exe
│
├── 📂 include
│   ├── DuplicateDetector.hpp
│   ├── FileClassifier.hpp
│   ├── FileOrganizer.hpp
│   ├── FileTypes.hpp
│   ├── Statistics.hpp
│
├── 📂 src
│   ├── DuplicateDetector.cpp
│   ├── FileClassifier.cpp
│   ├── FileOrganizer.cpp
│   ├── FileTypes.cpp
│   ├── Statistics.cpp
│
├── main.cpp
├── README.md

```

---

## 🚀 Building in Local

Compile using g++:

```bash
g++ -O2 -std=c++17 ^
-Iinclude ^
main.cpp ^
src/*.cpp ^
-o downTidy.exe
```

For release builds:

```bash
./release.sh
```

---

## 🎯 Future Improvements

- Configuration file support
- User-defined categories
- SHA-256 hashing option
- File-type icons
- GUI version
- One-Click Tide Directory Feature
- Undo Last Organization
- File Size statistics
- Multi-Threaded processing

---

## 🖋 Author

**Ettisaf Rup**

![Instagram](https://img.shields.io/badge/Instagram-ettisafxrup-red?logo=instagram)
![Linkedin](https://img.shields.io/badge/Linkedin-ettisafxrup-blue?logo=instagram) ![Facebook](https://img.shields.io/badge/Facebook-ettisafxrup-indigo?logo=facebook)
![Instagram](https://img.shields.io/badge/Github-ettisafxrup-red?logo=github)

---

## 🤲 Support downTidy

If you found this project useful, consider giving it a ⭐ on GitHub.
It helps others discover the project and motivates future improvements.

and if anyone wills to donate, you can bring me to a tong.

---

_ettisafxrup downTidy@2026 | all rights reserved_
