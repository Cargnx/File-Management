# File Management System
### Introduction
This is a learning project about an idea that came randomly in my mind which 
i found interesting.

#### I thought about a File Management System as a good learning project since:
- I/O concept is interesting to me
- How it actually works
- Using C++ basics / Advanced concepts like OOP, RAII etc
- ...

---

### Future ideas / Tasks
I started with an basic Write and Read File program and use this foundation 
to build from and build more functions & ideas on top of it, e.g:
- Replace hardcoded file name & content with dynamic user input
- Selection list like Move, Copy, Delete, Duplicate File and so on
- Possibly add an Algorithm for something (just thought about it...)

---

### What i hope to learn from this project?
- Learn more about I/O Streams
- File handling
- RAII
- Abstractions
- OOP
- Thinking as a programmer
- solving problems
- improve my code
- ...

---

# File descriptions

Here is a small explanation about the codebase and what different files are 
doing. Im still working on it so it may change later on...

## File Responsibilities
### FileHandler.cpp/h

- **Purpose**: Core file read/write operations
- **Responsible for**: Single file operations, RAII file management

### FileOperationResult.cpp/h

- **Purpose**: Standardized return values and error handling
- **Responsible for**: Success/failure states, error messages, result data

### FileMetadata.cpp/h

- **Purpose**: Compile-time information and metadata formatting
- **Responsible for**: Build info, timestamps, version data

### FileUtils.cpp/h

- **Purpose**: File system utilities and batch operations
- **Responsible for**: Directory operations, file system helpers

---

| Task              | Code                                                    |
|-------------------|---------------------------------------------------------|
| Create directory  | FileUtils::createDirectoryIfNotExists("path")           |
| Create file       | FileUtils::createFileWithContent("file.txt", "content") |
| Read file         | FileHandler("file.txt").readAllLines()                  |
| Write file        | FileHandler("file.txt").writeContent("content")         |
| Check result      | result.isSuccess()                                      |
| Get error message | result.message                                          |