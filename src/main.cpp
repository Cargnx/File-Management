#include <iostream>
#include <filesystem>
#include "FileHandler.h"

int main() {
    // Get the directory of this file and create file path
    const std::filesystem::path basePath = std::filesystem::path(__FILE__).parent_path();
    const std::filesystem::path filePath = basePath / "test.txt";

    // Create file handler and metadata
    FileHandler handler(filePath);
    FileMetaData metaData;

    // Write file
    const auto writeResult = handler.writeMetaData(metaData);
    if (!writeResult.isSuccess()) {
        std::cerr << writeResult.message << '\n';
        return 1;
    }

    // Read file
    auto readResult = handler.readAllLines();
    if (!readResult.isSuccess()) {
        std::cerr << readResult.message << '\n';
        return 1;
    }

    // Display content
    std::cout << "File contents:\n";
    for (const auto &line : readResult.lines) {
        std::cout << line << '\n';
    }

    // Create directory and file using utility functions
    std::filesystem::path directoryPath = "myDirectory";
    std::filesystem::path newFilePath = directoryPath / "my_file.txt";

    if (FileUtils::createDirectoryIfNotExists(directoryPath)) {
        FileUtils::createFileWithContent(newFilePath, "Hello, FileSystem!");
    }

    return 0;
}