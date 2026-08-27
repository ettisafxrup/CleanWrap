# Learn Modern C++20 with CleanWrap

> **CleanWrap** is a modern C++20 file-organizing application for Windows. This project is designed not only to be useful, but also to serve as a practical learning resource for understanding **Modern C++**, filesystem programming, hashing, object-oriented design, error handling, build systems, and software engineering practices.

---

## 🎯 What You Will Learn

By studying and modifying CleanWrap, you will learn how concepts from C++ textbooks and university courses come together in a real application.

You will work with:

- C++20 language features
- Object-Oriented Programming
- RAII and resource management
- `std::filesystem`
- File and directory manipulation
- Hashing and duplicate detection
- `std::unordered_set`
- `std::unordered_map`
- `std::vector`
- `std::string` and `std::string_view`
- Functions and modular design
- Enumerations and strongly typed enums
- Exception handling
- Error handling strategies
- Const correctness
- References and pointers
- Lambda expressions
- Algorithms and ranges
- Compile-time features
- Logging
- Windows-specific functionality
- Command-line applications
- Context-menu integration
- Build automation
- CMake / compiler workflows
- Static linking
- Application packaging with Inno Setup
- Git and GitHub-based development

The bigger goal is to learn **how to think like a systems/software engineer**, rather than simply learning C++ syntax.

---

# 🧠 Why CleanWrap?

A common way to learn programming is:

```text
Learn syntax
    ↓
Solve small exercises
    ↓
Build a calculator
    ↓
Build another small program
```

That is useful, but eventually you need to understand how individual concepts interact inside a real application.

CleanWrap gives you a different learning path:

```text
C++ Concepts
     ↓
Small Components
     ↓
File-System Operations
     ↓
Duplicate Detection
     ↓
Application Architecture
     ↓
Windows Integration
     ↓
Build & Packaging
     ↓
Complete Software
```

Instead of asking:

> "What does this C++ feature do?"

you can ask:

> "Why did this project need this C++ feature?"

That distinction is extremely important when learning software engineering.

---

# 📚 Prerequisites

You do not need to be an advanced C++ programmer.

However, you should be comfortable with basic programming concepts:

- Variables
- Conditions
- Loops
- Functions
- Basic data structures
- Basic pointers and references
- Basic C++ syntax
- Basic command-line usage
- Basic Git/GitHub knowledge

If you already know C, this project is particularly useful because you can see how C-style programming concepts evolve into modern C++ abstractions.

---

# 🛠️ Recommended Learning Path

Do **not** immediately read the entire codebase from top to bottom.

Instead, study CleanWrap in stages.

---

## Level 1 — Understand the Problem

Before looking at the implementation, understand what CleanWrap is supposed to do.

A simplified version of the problem is:

```text
Downloads Folder
       │
       ├── image.jpg
       ├── document.pdf
       ├── video.mp4
       ├── program.exe
       ├── source.cpp
       ├── music.mp3
       └── duplicate.jpg
```

CleanWrap analyzes the files and organizes them:

```text
Downloads/
│
├── Images/
│   └── image.jpg
│
├── PDFs/
│   └── document.pdf
│
├── Videos/
│   └── video.mp4
│
├── Executables/
│   └── program.exe
│
├── Code/
│   └── source.cpp
│
├── Audio/
│   └── music.mp3
│
└── Duplicates/
    └── duplicate.jpg
```

Before studying the code, try to design this system yourself.

Ask:

1. How would I detect files?
2. How would I identify their types?
3. How would I create directories?
4. How would I move files?
5. How would I detect duplicates?
6. What happens when a file cannot be moved?
7. What happens when two files have the same name?
8. What happens if the destination folder already exists?

These questions are more important than memorizing syntax.

---

# Level 2 — Explore `std::filesystem`

One of the most important components of CleanWrap is the C++ filesystem library.

Modern C++ provides:

```cpp
#include <filesystem>

namespace fs = std::filesystem;
```

This allows you to work with files and directories without relying entirely on operating-system-specific APIs.

For example:

```cpp
fs::path downloads = "C:/Users/User/Downloads";
```

You can inspect a directory:

```cpp
for (const auto& entry : fs::directory_iterator(downloads)) {
    std::cout << entry.path() << '\n';
}
```

You should understand:

- `fs::path`
- `fs::directory_iterator`
- `fs::exists()`
- `fs::is_directory()`
- `fs::is_regular_file()`
- `fs::create_directory()`
- `fs::create_directories()`
- `fs::rename()`
- `fs::remove()`
- `fs::file_size()`

### Challenge

Write a small program that prints:

```text
Filename
File extension
File size
File type
```

for every file in a directory.

Do this **before** trying to understand CleanWrap's complete organizer logic.

---

# Level 3 — File Categorization

CleanWrap needs to determine where a file belongs.

Conceptually:

```text
File
 │
 ├── .jpg/.png/.gif → Images
 ├── .pdf            → PDFs
 ├── .mp4/.mkv       → Videos
 ├── .mp3/.wav       → Audio
 ├── .cpp/.c/.h      → Code
 ├── .exe/.msi       → Executables
 ├── .docx/.txt      → Documents
 └── everything else → Others
```

This teaches an important software engineering concept:

> **Separate decision-making from execution.**

For example, one part of the program should determine:

```text
Where should this file go?
```

while another part performs:

```text
Move the file there.
```

This separation makes the system easier to test and maintain.

---

# Level 4 — Learn Containers

CleanWrap makes extensive use of standard library containers.

You should understand why different containers are appropriate for different jobs.

### `std::vector`

Useful when you need an ordered collection:

```cpp
std::vector<std::string> files;
```

Think:

> "I have a list of things."

---

### `std::unordered_set`

Useful when you need fast membership checking:

```cpp
std::unordered_set<std::string> extensions;
```

Think:

> "Is this value already present?"

CleanWrap also uses the concept of a set when dealing with duplicate detection.

---

### `std::unordered_map`

Useful for key-value relationships:

```cpp
std::unordered_map<std::string, std::string> categories;
```

Conceptually:

```text
".jpg" → "Images"
".pdf" → "PDFs"
".mp4" → "Videos"
```

Think:

> "Given this key, what value belongs to it?"

---

# Level 5 — Understand Hashing

Duplicate detection is one of the more interesting engineering problems in CleanWrap.

Consider:

```text
photo1.jpg
photo2.jpg
```

They have different filenames.

That does **not** necessarily mean they are different files.

The program needs to compare their contents.

A simplified idea is:

```text
File
 ↓
Read contents
 ↓
Hash contents
 ↓
Hash value
 ↓
Compare with previously seen hashes
```

Conceptually:

```text
photo1.jpg
     ↓
   HASH
     ↓
ABC123

photo2.jpg
     ↓
   HASH
     ↓
ABC123
```

Same hash → potential duplicate.

This introduces several important concepts:

- Hash functions
- Deterministic computation
- Collision considerations
- Binary file reading
- Data integrity
- Performance trade-offs

---

# 🔬 Challenge: Build a Duplicate Detector

Before reading CleanWrap's implementation, try building a simplified duplicate detector.

Your program should:

1. Scan a directory.
2. Read each file.
3. Calculate a hash.
4. Store previously seen hashes.
5. Report files with duplicate hashes.

This is a fantastic exercise because it transforms a seemingly simple feature into several engineering problems.

---

# Level 6 — Understand RAII

One of the most important ideas in Modern C++ is:

> **Resource Acquisition Is Initialization (RAII).**

Resources include:

- Files
- Memory
- Locks
- Sockets
- Handles
- Other system resources

C++ allows objects to manage resources automatically through constructors and destructors.

For example:

```cpp
{
    std::ifstream file("example.txt");

    // Use file
}
```

When `file` leaves scope, its destructor handles cleanup.

You should learn why this is safer than manually managing resources.

Compare the mindset:

```text
Open
 ↓
Use
 ↓
Remember to close
```

with:

```text
Create object
 ↓
Use object
 ↓
Object leaves scope
 ↓
Automatic cleanup
```

This is one of the major differences between writing C++ as "C with classes" and actually using Modern C++.

---

# Level 7 — Const Correctness

When reading the CleanWrap source, pay attention to:

```cpp
const
```

For example:

```cpp
const fs::path& path
```

This communicates two things:

1. The object should not be modified.
2. Passing by reference avoids an unnecessary copy.

Understand the difference between:

```cpp
fs::path path
```

```cpp
fs::path& path
```

```cpp
const fs::path& path
```

and:

```cpp
fs::path&& path
```

You do not need to master move semantics immediately, but understanding why C++ has different ways of passing objects is essential.

---

# Level 8 — Error Handling

File-system software cannot assume that everything will always work.

For example:

```text
File exists
Directory does not exist
Permission denied
File is locked
Destination already exists
Drive disconnected
Invalid path
```

A robust application needs to account for failure.

Study how CleanWrap handles filesystem errors and exceptions.

Pay attention to:

```cpp
try
{
    // filesystem operation
}
catch (...)
{
    // error handling
}
```

Also learn the difference between:

- Returning an error
- Throwing an exception
- Logging an error
- Ignoring an error
- Recovering from an error

A useful engineering question is:

> "What should the program do when this operation fails?"

---

# Level 9 — Functions and Separation of Responsibilities

Look at how CleanWrap divides functionality into separate operations.

A well-structured application should avoid having one giant function such as:

```cpp
void organizeEverything()
{
    // 500 lines of code
}
```

Instead, responsibilities should be separated conceptually:

```text
Discover files
      ↓
Classify files
      ↓
Detect duplicates
      ↓
Create directories
      ↓
Move files
      ↓
Log results
```

Each component should have a clear responsibility.

This introduces an important software engineering principle:

> **High cohesion and low coupling.**

---

# Level 10 — Logging

CleanWrap maintains a log of its operations.

Logging is different from simply printing random debugging messages.

A useful log can answer:

```text
What happened?
When did it happen?
Which file was affected?
Was the operation successful?
Why did something fail?
```

For example:

```text
[INFO] Organizing Downloads directory
[INFO] Moved photo.jpg → Images
[INFO] Duplicate detected: photo-copy.jpg
[ERROR] Failed to move locked.pdf
```

Study how logging can make debugging and maintenance easier.

---

# Level 11 — C++20 Features

CleanWrap targets **C++20**, so pay attention to features that make the implementation more expressive and safer.

Depending on the version of the source code, look for concepts such as:

### `std::string_view`

Useful for reading string data without unnecessary ownership/copies.

### `contains()`

Modern associative containers provide convenient membership checks:

```cpp
if (my_set.contains(value)) {
    // Found
}
```

### Structured bindings

For example:

```cpp
auto [key, value] = something;
```

This can make code involving pairs and maps much easier to read.

### `constexpr`

Used when something can be evaluated at compile time.

### Attributes

For example:

```cpp
[[nodiscard]]
```

These allow the programmer to communicate useful information to the compiler and other developers.

---

# Level 12 — Windows Integration

CleanWrap is more than a generic console application.

It interacts with Windows.

This gives you an opportunity to learn about the boundary between:

```text
Portable C++
       │
       ↓
Operating System
```

Study the Windows-specific portions separately from the portable C++ code.

Ask:

> "Could this component run on Linux?"

If not:

> "Why?"

This is a great way to understand the difference between:

- Language features
- Standard library features
- Operating-system APIs

---

# Level 13 — Context Menu Integration

CleanWrap can be integrated with Windows Explorer so that it can be used from the context menu.

This introduces another layer of systems engineering.

You are no longer only writing:

```text
Application
```

You are integrating:

```text
Windows Explorer
       ↓
Context Menu
       ↓
CleanWrap
       ↓
Filesystem
```

Study how applications can interact with the operating system and how command-line arguments can be used to control application behavior.

---

# Level 14 — Startup and Silent Execution

CleanWrap also demonstrates how an application can run without requiring a traditional interactive interface.

This is useful for understanding:

- Command-line arguments
- Background execution
- Startup integration
- Process behavior
- User experience considerations

Think about the difference between:

```text
Interactive application
```

and:

```text
Utility application
```

A utility should often perform its job with minimal user interaction.

---

# Level 15 — Compilation

You should understand how the source code becomes an executable.

The basic pipeline is:

```text
Source Code
    ↓
Preprocessor
    ↓
Compiler
    ↓
Object Files
    ↓
Linker
    ↓
Executable
```

Do not treat:

```bash
g++ main.cpp -o CleanWrap.exe
```

as magic.

Learn what each stage actually does.

Also understand:

- Compiler flags
- C++ language standards
- Optimization
- Debug builds
- Release builds
- Linking
- Static libraries
- Dynamic libraries

---

# Level 16 — Static Linking

CleanWrap has been built with static linking to reduce runtime dependency problems.

This introduces an important deployment concept:

```text
Dynamically linked application
        ↓
Requires external runtime libraries
```

versus:

```text
Statically linked application
        ↓
More dependencies bundled into executable
```

Static linking is not always the correct solution, but understanding why it can be useful is valuable.

Study the trade-offs:

- Executable size
- Portability
- Dependency management
- Licensing
- Runtime compatibility
- Updates

---

# Level 17 — Build Systems

Once your project grows, manually compiling every source file becomes inconvenient.

This is where build systems become important.

Learn how tools such as:

- CMake
- Make
- Ninja
- MSBuild

help automate:

```text
Compilation
Linking
Dependencies
Build configurations
Installation
Testing
```

A useful exercise is to reproduce the CleanWrap build process yourself using CMake.

---

# Level 18 — Packaging

Writing software is only part of software engineering.

Users need a way to install it.

CleanWrap uses **Inno Setup** for Windows installation.

The general pipeline becomes:

```text
C++ Source
    ↓
Compiler
    ↓
CleanWrap.exe
    ↓
Installer configuration
    ↓
Windows Installer
    ↓
User
```

This teaches an important lesson:

> **Software engineering does not end when the compiler produces an executable.**

Deployment matters.

---

# 🧪 Suggested Exercises

After understanding the existing implementation, try modifying CleanWrap.

### Beginner

- [ ] Add a new file category.
- [ ] Add another supported file extension.
- [ ] Improve the console output.
- [ ] Add more logging information.
- [ ] Add a `--help` command.
- [ ] Add a `--version` command.

### Intermediate

- [ ] Add a dry-run mode.
- [ ] Add configurable destination directories.
- [ ] Allow users to choose which categories are enabled.
- [ ] Improve duplicate detection.
- [ ] Add better error reporting.
- [ ] Prevent filename collisions.
- [ ] Add recursive directory scanning.

### Advanced

- [ ] Introduce a configuration file.
- [ ] Implement multithreaded hashing.
- [ ] Benchmark different hashing strategies.
- [ ] Add unit tests.
- [ ] Add integration tests.
- [ ] Refactor the project using stronger separation of concerns.
- [ ] Add a CMake-based build system.
- [ ] Create a cross-platform version.
- [ ] Design a plugin-based categorization system.

---

# 🔍 Questions to Ask While Reading the Code

Do not just read the source.

Interrogate it.

For every important function, ask:

### Design

- Why does this function exist?
- What responsibility does it have?
- Could it be smaller?
- Should this responsibility belong somewhere else?

### Performance

- How many times is this file read?
- What happens if there are 100,000 files?
- Is this operation `O(1)`, `O(n)`, or worse?
- Are unnecessary copies being made?

### Safety

- What happens if the file disappears during processing?
- What happens if permissions change?
- What happens if the destination already exists?
- What happens if the disk becomes unavailable?

### Maintainability

- Can another developer understand this?
- Are names meaningful?
- Is the code duplicated?
- Is behavior hidden inside a large function?

### Portability

- Is this standard C++?
- Is this Windows-specific?
- Could this work on Linux?
- What would need to change?

These questions are where programming starts becoming **engineering**.

---

# 🧩 Suggested Learning Experiments

A particularly effective way to study CleanWrap is to intentionally break parts of it.

For example:

### Experiment 1 — Remove duplicate detection

Observe what happens.

Then implement it yourself.

---

### Experiment 2 — Replace a container

Replace an `unordered_set` with a `vector`.

Benchmark the difference.

Ask:

> Why might the original developer have chosen `unordered_set`?

---

### Experiment 3 — Remove error handling

Run the program against:

- Locked files
- Missing directories
- Invalid paths
- Permission-restricted files

Observe the consequences.

Then restore robust handling.

---

### Experiment 4 — Profile large directories

Test the application with:

```text
100 files
1,000 files
10,000 files
100,000 files
```

Measure:

- Execution time
- Memory usage
- Hashing time
- Filesystem operations

This is where theoretical complexity starts becoming practical engineering.

---

# 🏗️ Architecture Thinking

Try to visualize CleanWrap as a system rather than a collection of source files.

A simplified architecture looks like:

```text
                 ┌──────────────────┐
                 │   User / Shell   │
                 └────────┬─────────┘
                          │
                          ▼
                 ┌──────────────────┐
                 │   Application    │
                 │     Control      │
                 └────────┬─────────┘
                          │
             ┌────────────┼────────────┐
             ▼            ▼            ▼
        ┌─────────┐ ┌──────────┐ ┌──────────┐
        │Scanner  │ │Classifier│ │Hasher    │
        └────┬────┘ └─────┬────┘ └────┬─────┘
             │             │           │
             └─────────────┼───────────┘
                           ▼
                    ┌─────────────┐
                    │ File Mover  │
                    └──────┬──────┘
                           │
                           ▼
                    ┌─────────────┐
                    │  Filesystem  │
                    └─────────────┘
```

Try to identify where each responsibility exists in the actual source code.

---

# 💡 Engineering Lessons

CleanWrap is intentionally useful for learning lessons that extend beyond C++.

## 1. Abstractions exist for a reason

Instead of manually manipulating strings representing file paths, Modern C++ provides:

```cpp
std::filesystem::path
```

Use abstractions that represent the thing you are actually working with.

---

## 2. Correctness comes before optimization

First make:

```text
Correct
```

Then make it:

```text
Fast
```

Then make it:

```text
Elegant
```

Optimizing incorrect software simply produces incorrect software faster.

---

## 3. Failure is normal

Real software interacts with a world that can fail.

Files disappear.

Permissions change.

Disks fill up.

Processes crash.

Users provide unexpected input.

Good software expects this.

---

## 4. Small functions are easier to reason about

A function should ideally have a clear purpose.

If you cannot explain what a function does in one sentence, it may be doing too much.

---

## 5. Standard library first

Before writing your own data structure or utility, ask:

> "Does the C++ standard library already provide this?"

Modern C++ provides an enormous amount of functionality.

Learn to use it.

---

# 🚀 Final Project Challenge

After studying CleanWrap, build your own version.

Do **not** copy the implementation.

Start with the requirements:

```text
1. Scan a directory
2. Detect files
3. Determine categories
4. Create required directories
5. Detect duplicates
6. Move files
7. Handle errors
8. Log operations
```

Then design your own architecture.

Your implementation may be completely different from CleanWrap.

That is the point.

If you can build the same functionality using your own architecture, you have moved from:

> **Reading code**

to:

> **Engineering software.**

---

# 📖 Recommended Study Order

For the most effective learning experience:

```text
C++ Fundamentals
       ↓
Modern C++ Syntax
       ↓
STL Containers
       ↓
std::filesystem
       ↓
File I/O
       ↓
Hashing
       ↓
Error Handling
       ↓
RAII
       ↓
OOP & Design
       ↓
C++20 Features
       ↓
Windows APIs
       ↓
Build Systems
       ↓
Packaging
       ↓
Performance
       ↓
Software Architecture
```

Do not rush through the list.

Build small experiments between each stage.

---

# 🎓 What You Should Be Able to Do Afterwards

After completing this learning path, you should be able to:

- Read a medium-sized C++ codebase.
- Design a small C++ application.
- Work with files and directories programmatically.
- Use the STL effectively.
- Understand hashing and duplicate detection.
- Write safer resource-managing code.
- Handle filesystem failures.
- Understand basic C++20 features.
- Understand the compilation and linking process.
- Build and package a Windows application.
- Identify OS-specific versus portable code.
- Think about performance and complexity.
- Break a problem into independent components.
- Reason about software architecture.

Most importantly, you should become more comfortable asking:

> **"Why is the software designed this way?"**

instead of only asking:

> **"How does this syntax work?"**

---

# 🤝 Contributing as a Learner

You do not need to be an expert to contribute.

Good contributions can include:

- Documentation improvements
- Bug fixes
- New file categories
- Better error handling
- Performance improvements
- Tests
- Refactoring
- Build improvements
- Cross-platform experiments
- New learning exercises

If you discover something while studying the project, document it.

Someone else may learn from your discovery.

---

# ⭐ The Philosophy Behind CleanWrap

CleanWrap is ultimately an exercise in **engineering thinking**.

The goal is not to memorize:

```cpp
std::filesystem::directory_iterator
```

The goal is to understand:

```text
Problem
  ↓
Requirements
  ↓
Design
  ↓
Abstraction
  ↓
Implementation
  ↓
Testing
  ↓
Failure Handling
  ↓
Performance
  ↓
Deployment
  ↓
Maintenance
```

That is the mindset this project is intended to teach.

**Learn the language.  
Understand the system.  
Question the design.  
Build your own.**

---

## 📌 Project

**CleanWrap — Modern C++20 File Organizer**

Use the main repository to explore the implementation, experiment with the code, open issues, and contribute improvements.

Happy hacking! 🚀