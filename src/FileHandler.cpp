#include "FileHandler.h"
#include <iostream>
#include <fstream>
#include <utility>

// FileMetaData implementation
FileMetaData::FileMetaData() : compileDate(__DATE__),
                               compileTime(__TIME__),
                               sourceLine(__LINE__) {
}

// FileOperationResult implementation
FileOperationResult::FileOperationResult(FileResult r, std::string msg)
    : result(r), message(std::move(msg)) {
}

bool FileOperationResult::isSuccess() const {
    return result == FileResult::SUCCESS;
}

void FileOperationResult::addLine(const std::string &line) {
    lines.push_back(line);
}

// FileHandler implementation
FileHandler::FileHandler(const std::filesystem::path &filePath) : filePath(filePath) {
}

FileOperationResult FileHandler::writeMetaData(const FileMetaData &metaData) {
    std::ofstream outFile(filePath);
    if (!outFile) {
        return FileOperationResult(FileResult::WRITE_ERROR,
                                   "Error opening for writing: " + filePath.string());
    }

    outFile << "Hello, this is a simple file." << '\n';
    outFile << "Date: " << metaData.compileDate << '\n';
    outFile << "Time: " << metaData.compileTime << '\n';
    outFile << "Line: " << metaData.sourceLine << '\n';

    return FileOperationResult(FileResult::SUCCESS, "File written successfully");
}

FileOperationResult FileHandler::readAllLines() {
    std::ifstream readFile(filePath);
    if (!readFile) {
        return FileOperationResult(FileResult::READ_ERROR,
                                   "Error opening file for reading: " + filePath.string());
    }

    FileOperationResult result(FileResult::SUCCESS, "File read successfully.");
    std::string line;
    while (std::getline(readFile, line)) {
        result.addLine(line);
    }

    return result;
}

std::filesystem::path FileHandler::getAbsolutePath() const {
    return std::filesystem::absolute(filePath);
}

// FileUtils namespace implementation
namespace FileUtils {
    bool createDirectoryIfNotExists(const std::filesystem::path &directoryPath) {
        if (!std::filesystem::exists(directoryPath)) {
            try {
                std::filesystem::create_directory(directoryPath);
                std::cout << "Directory created: " << directoryPath.string() << '\n';
                return true;
            } catch (const std::filesystem::filesystem_error &e) {
                std::cerr << "Failed to create directory: " << e.what() << '\n';
                return false;
            }
        }
        return true; // Directory already exists
    }

    bool createFileWithContent(const std::filesystem::path &filepath, const std::string &content) {
        std::ofstream file(filepath);
        if (file.is_open()) {
            file << content;
            file.close();
            std::cout << "File created: " << filepath << '\n';
            return true;
        } else {
            std::cerr << "Failed to create file: " << filepath << '\n';
            return false;
        }
    }

    FileOperationResult createFileInDirectory(const std::filesystem::path& dirName,
                                             const std::filesystem::path& fileName,
                                             const std::string& content,
                                             const std::filesystem::path& basePath) {
        try {
            // Determine base path - use provided basePath or derive from __FILE__
            std::filesystem::path actualBasePath;
            if (basePath.empty()) {
                // Note: __FILE__ won't work here since we're in the utility function
                // Use current working directory as fallback, or let caller provide basePath
                actualBasePath = std::filesystem::current_path();
            } else {
                actualBasePath = basePath;
            }

            // Construct full paths
            std::filesystem::path directoryPath = actualBasePath / dirName;
            std::filesystem::path filePath = directoryPath / fileName;

            // Create directory if it doesn't exist
            if (!createDirectoryIfNotExists(directoryPath)) {
                return FileOperationResult(FileResult::DIRECTORY_ERROR,
                                          "Failed to create directory: " + directoryPath.string());
            }

            // Create file with content
            if (!createFileWithContent(filePath, content)) {
                return FileOperationResult(FileResult::WRITE_ERROR,
                                          "Failed to create file: " + filePath.string());
            }

            return FileOperationResult(FileResult::SUCCESS,
                                      "Successfully created file: " + filePath.string());

        } catch (const std::exception& e) {
            return FileOperationResult(FileResult::WRITE_ERROR,
                                      "Exception occurred: " + std::string(e.what()));
        }
    }
}