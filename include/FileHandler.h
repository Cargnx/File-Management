#pragma once

#include <filesystem>
#include "FileOperationResult.h"
#include "FileMetadata.h"

// RAII File Handler Class - focused only on core file operations
class FileHandler {
private:
    std::filesystem::path filePath;

public:
    explicit FileHandler(const std::filesystem::path &filePath);
    
    // Core file operations
    FileOperationResult writeMetaData(const FileMetaData &metaData);
    FileOperationResult writeContent(const std::string &content);
    FileOperationResult readAllLines();
    
    // Path utilities
    std::filesystem::path getAbsolutePath() const;
    std::filesystem::path getFilePath() const;
};