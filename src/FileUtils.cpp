#include "FileUtils.h"
#include <iostream>
#include <fstream>

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
            // Determine base path - use provided basePath or current directory
            std::filesystem::path actualBasePath;
            if (basePath.empty()) {
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
