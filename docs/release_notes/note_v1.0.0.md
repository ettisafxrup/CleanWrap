# 🧹 CleanWrap — Smart File Organization for Windows [v1.0.0]

> ![Language](https://img.shields.io/badge/Language-C%2B%2B20-blue)
> ![Platform](https://img.shields.io/badge/Platform-Windows-success)
> ![License](https://img.shields.io/badge/License-MIT-green)
> ![Version](https://img.shields.io/badge/v1.0.0-8A2BE2)
> ![GitHub](https://img.shields.io/badge/GitHub-Repository-black?logo=github)

**CleanWrap v1.0.0** is the first stable release of a lightweight Windows file organization utility built entirely with **Modern C++20**.

Originally designed for the **Windows Downloads folder**, CleanWrap can now organize **any folder** through Windows Explorer integration. It intelligently categorizes files into dedicated folders, detects duplicate files using content hashing and Windows duplicate filename patterns, generates detailed cleanup reports, and exits within seconds.

CleanWrap is designed to stay lightweight, fast, and dependency-free while keeping your directories clean with minimal user interaction.

---

# ✨ Features

- Automatically organizes downloaded files
- Organizes **any folder** through Windows Explorer Context Menu
- Categorizes files by extension
- Creates category folders **only when required**
- Creates duplicate folders **only when duplicate files exist**
- Supports documents, images, videos, audio, archives, source code, executables, installers, and many more
- Detects duplicate files using **64-bit FNV-1a hashing**
- Recognizes common Windows duplicate filename patterns
- Automatically generates detailed cleanup logs
- Optional Windows Startup integration
- Lightweight and extremely fast
- Modular object-oriented architecture
- Built entirely using **Modern C++20**

---

# 📂 Folder Structure

After running CleanWrap, your directory is automatically organized like this:

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
└── _CleanWrap.log
```

> **Note:** Category folders are created only when files belonging to that category exist. Likewise, duplicate folders are created only if duplicate files are detected.

---

# 🔍 Smart Duplicate Detection

CleanWrap uses a **multi-stage duplicate detection system**.

## ① Content-Based Hash Detection

Every file is hashed using a fast **64-bit FNV-1a hashing algorithm**.

If another file with the exact same content already exists, CleanWrap identifies it as a duplicate regardless of its filename.

---

## ② Windows Duplicate Filename Recognition

CleanWrap also recognizes common Windows duplicate filename patterns such as:

```text
My File (1).pdf
My File (2).pdf
Holiday - Copy.jpg
Assignment - Copy (3).docx
```

These filename patterns are checked alongside file hashes before classifying a file as a duplicate.

---

## ③ Intelligent Duplicate Placement

When duplicate files are found:

- The original file remains inside its main category folder.
- Windows-generated copies such as `(1)` or `- Copy` are automatically moved into the corresponding **Duplicates** folder.
- If identical files have different names, the original file is preserved while later duplicates are isolated.

This keeps your directories clean without risking accidental loss of the original file.

---

# 📊 Cleanup Report

Every execution generates:

```text
_CleanWrap.log
```

The report contains:

- Date & Time
- Cleanup session summary
- Total files handled
- Category-wise statistics
- Duplicate count
- Error count

Logs are **appended instead of overwritten**, preserving the history of every cleanup session.

---

# ⚙ Windows Integration

CleanWrap integrates directly with Windows.

### Windows Explorer Context Menu

Right-click inside **any folder** and choose:

```text
Organize with CleanWrap
```

CleanWrap instantly organizes the selected directory.

---

### Windows Startup (Optional)

During installation you may enable:

```text
Automatically organize Downloads when Windows starts
```

CleanWrap launches once during Windows startup, organizes the Downloads folder, generates a cleanup report, and exits automatically.

---

# 📦 Project Structure

```text
CleanWrap/

.
├── 📂 assets
│   ├── cleanwrap.ico
│   ├── installer_banner.bmp
│   ├── installer_small.bmp
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
│   ├── Notifications.cpp
│   ├── Statistics.cpp
│
├── 📂 release
│   ├── CleanWrap_v1.0
│   │   ├── CleanWrap_v1.0.exe
│   │   ├── CleanWrap_v1.0_Setup.exe
│
├── 📂 script
│   ├── cleanwrap_v1.0.iss
│
├── LICENSE
├── README.md
├── main.cpp
├── release.sh
```

---

# ⚡ Built With

- Modern C++20
- Standard Template Library (STL)
- `<filesystem>`
- `<unordered_map>`
- `<unordered_set>`
- `<regex>`
- `<fstream>`
- Object-Oriented Programming
- Modular Project Architecture
- Windows Registry Integration
- Windows Explorer Context Menu
- Inno Setup Installer

---

# 📦 Included with CleanWrap v1.0

- CleanWrap Installer
- CleanWrap Executable
- User Manual
- README
- Source Code
- MIT License

---

# 🚀 Building Locally

Compile using **g++**

```bash
g++ -O2 -std=c++20 ^
-Iinclude ^
main.cpp ^
src/*.cpp ^
-o CleanWrap.exe
```

Release build:

```bash
./release.sh
```

---

# 🖋 Author

**Ettisaf Rup**

<small>Software Lead, XtendArena</small><br>
<small>B.Sc. in Computer Science & Engineering</small><br>
<small>Khulna University of Engineering & Technology (KUET)</small>

![GitHub](https://img.shields.io/badge/GitHub-ettisafxrup-black?logo=github)
![LinkedIn](https://img.shields.io/badge/LinkedIn-ettisafxrup-blue?logo=linkedin)
![Instagram](https://img.shields.io/badge/Instagram-ettisafxrup-E4405F?logo=instagram)
![Facebook](https://img.shields.io/badge/Facebook-ettisafxrup-1877F2?logo=facebook)

---

# 🤲 Support CleanWrap

If you found this project useful, consider giving it a ⭐ on GitHub.

It helps others discover the project and motivates future improvements.

And if anyone ever wishes to donate, you can always bring me to a **tong** for a cup of tea. ☕

[![Download Latest Release](https://img.shields.io/badge/📥-Download%20Latest%20Release-blue?style=for-the-badge)](http://github.com/ettisafxrup/CleanWrap/releases/download/CleanWrap_v1.0/CleanWrap_v1.0_Setup.exe)

![GitHub Stars](https://img.shields.io/github/stars/ettisafxrup/CleanWrap?style=social)

---

# 🚀 Roadmap

- Drag & Drop Support
- Automatic Update Checker
- Undo Last Organization
- Configuration File (.json)
- User-defined Categories
- SHA-256 Duplicate Detection
- File Type Icons
- Statistics Dashboard
- GUI Version
- Multi-threaded Processing
- Localization Support

---

Thank you for checking out **CleanWrap**.

If this project helped you organize your files or inspired you, consider leaving a ⭐ on the repository. Every star motivates future development and helps the project reach more people.

Happy organizing! 🧹

---

<small><i>CleanWrap © 2026 • Developed by Ettisaf Rup • Released under the MIT License</i></small>
