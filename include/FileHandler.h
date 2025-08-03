#pragma once

#include <filesystem>
#include <string>
#include <vector>

// Simple metadata struct to organize related data
struct FileMetaData {
    std::string compileDate;
    std::string compileTime;
    int sourceLine;

    FileMetaData();
};

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

// RAII File Handler Class
class FileHandler {
private:
    std::filesystem::path filePath;

public:
    explicit FileHandler(const std::filesystem::path &filePath);
    FileOperationResult writeMetaData(const FileMetaData &metaData);
    FileOperationResult readAllLines();
    std::filesystem::path getAbsolutePath() const;
};

// Utility functions for directory and file operations
namespace FileUtils {
    bool createDirectoryIfNotExists(const std::filesystem::path &directoryPath);
    bool createFileWithContent(const std::filesystem::path &filepath, const std::string &content);

    // Helper function for creating files in directories relative to source
    FileOperationResult createFileInDirectory(const std::filesystem::path& dirName,
                                             const std::filesystem::path& fileName,
                                             const std::string& content,
                                             const std::filesystem::path& basePath = "");
}