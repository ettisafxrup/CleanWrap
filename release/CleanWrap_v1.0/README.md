# CleanWrap — Your Download Directory CareTaker [v1.0]

> ![Language](https://img.shields.io/badge/Language-C%2B%2B20-blue) ![Github](https://img.shields.io/badge/github-repo-blue?logo=github) ![License](https://img.shields.io/badge/License-MIT-green) ![Version](https://img.shields.io/badge/v1.0-8A2BE2)

**CleanWrap v1.0.0** is the first stable release of a lightweight Windows file organizer built with Modern C++17. It automatically categorizes files into dedicated folders, detects duplicates using file hashing and filename patterns, and generates detailed cleanup logs after every execution. This release establishes the foundation for future features such as Windows context menu integration, drag-and-drop support, automatic updates, and a graphical user interface.
Designed primarily for the **Windows Downloads Folder** (v1.0), CleanWrap can sort files **in seconds** while intelligently handling duplicates and generating cleanup reports.

---

## ✨ v1.0 Features

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

---

## 🔍 Smart Duplicate Detection

CleanWrap detects duplicates using:

- Fast FNV-1a 64-bit File Hashing (built-in C++)
- Windows duplicate filename patterns:
  - `(1)`
  - `(2)`
  - `- Copy`
  - `- Copy (1)`

While your directory having multiple copy files, CleanWrap wipes out all the copy files and puts them in a separated file. And yes, you can delete them later anytime. Duplicate files are automatically moved into dedicated duplicate folders. Every Category having their own dedicated Duplicate folder.

---

## 📊 Cleanup Report

Every execution generates:

```
_CleanWrap.log
```

The report contains:

- Date & Time
- Files processed
- Category statistics
- Duplicate count
- Error count

Logs are appended instead of overwritten. Newer logs can be found at the last of the file.

---

## 📦 Project Structure

```text
CleanWrap/
.
├── CleanWrap.exe
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

---

## ⚡ Built With

- Modern C++20
- STL
- Standard Filesystem Library (`<filesystem> | std::filesystem`)
- Object-Oriented Programming (.hpp and .cpp separated)
- Modular Project Structure

---

## 📦 Included with CleanWrap v1.0

- CleanWrap.exe
- Source Code
- README

## 🖋 Author

**Ettisaf Rup**
<br><small> Former Technical Lead, ProximaIT </small><br>
<small> Software Lead, XtendArena </small><br>
<small>BSc. in Computer Science & Engineering, KUET </small>

![Instagram](https://img.shields.io/badge/Instagram-ettisafxrup-red?logo=instagram)
![Linkedin](https://img.shields.io/badge/Linkedin-ettisafxrup-blue?logo=instagram) ![Facebook](https://img.shields.io/badge/Facebook-ettisafxrup-indigo?logo=facebook)
![Instagram](https://img.shields.io/badge/Github-ettisafxrup-red?logo=github)

---

## 🤲 Support CleanWrap

If you found this project useful, consider giving it a ⭐ on GitHub.
It helps others discover the project and motivates future improvements.

and if anyone wills to donate, you can bring me to a tong.

<a href="https://github.com/ettisafxrup/CleanWrap/releases" target="_blank">

![Download](https://img.shields.io/badge/📥-Download-blue) </a> ![Stars](https://img.shields.io/github/stars/ettisafxrup/CleanWrap)

---

<small> _ettisafxrup CleanWrap@2026 | all rights reserved_ </small>

---

## 🚀 Upcoming Features

- Right-click "Organize with CleanWrap" One-Click Formattion.
- Installer.
- Run on Windows Startup.
- Auto Update Checker.
- Configuration File.
- GUI Version.
- SHA-256 Duplicate Detection.

---

Thank you for checking out CleanWrap!
If you find the project useful, consider leaving a star (⭐) on the repository.

Thank you.
