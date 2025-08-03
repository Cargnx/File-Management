#pragma once

#include <filesystem>
#include <string>
#include "FileOperationResult.h"

// Utility functions for directory and file operations
namespace FileUtils {
    // Basic utility functions
    bool createDirectoryIfNotExists(const std::filesystem::path &directoryPath);
    bool createFileWithContent(const std::filesystem::path &filepath, const std::string &content);

    // Advanced helper function
    FileOperationResult createFileInDirectory(const std::filesystem::path& dirName,
                                             const std::filesystem::path& fileName,
                                             const std::string& content,
                                             const std::filesystem::path& basePath = "");
}