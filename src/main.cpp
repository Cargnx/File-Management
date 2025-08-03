#include <iostream>
#include <filesystem>
#include "FileHandler.h"

int main() {
    // Get the project root directory
    const std::filesystem::path basePath = std::filesystem::path(__FILE__).parent_path().parent_path();

    // Create just the output directory (no file)
    const std::filesystem::path outputDir = basePath / "output";
    if (!FileUtils::createDirectoryIfNotExists(outputDir)) {
        std::cerr << "Failed to create output directory\n";
        return 1;
    }

    // Now use FileHandler to create and write the file
    const std::filesystem::path filePath = outputDir / "test.txt";
    FileHandler handler(filePath);
    FileMetaData metaData;

    // Write using FileHandler's method
    const auto writeResult = handler.writeMetaData(metaData);
    if (!writeResult.isSuccess()) {
        std::cerr << writeResult.message << '\n';
        return 1;
    }

    // Read and display
    auto readResult = handler.readAllLines();
    if (!readResult.isSuccess()) {
        std::cerr << readResult.message << '\n';
        return 1;
    }

    std::cout << "File contents:\n";
    for (const auto &line : readResult.lines) {
        std::cout << line << '\n';
    }

    return 0;
}