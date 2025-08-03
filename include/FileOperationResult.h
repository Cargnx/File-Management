#pragma once

#include <string>
#include <vector>

// Result enum for clear error handling
enum class FileResult {
    SUCCESS,
    WRITE_ERROR,
    READ_ERROR,
    DIRECTORY_ERROR  // Added for directory creation errors
};

// Result class to return both status and data
class FileOperationResult {
public:
    FileResult result;
    std::string message;
    std::vector<std::string> lines;

    FileOperationResult(FileResult r, std::string msg = "");
    bool isSuccess() const;
    void addLine(const std::string &line);
};
