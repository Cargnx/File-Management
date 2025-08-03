#include "FileHandler.h"
#include <fstream>

FileHandler::FileHandler(const std::filesystem::path &filePath) : filePath(filePath) {
}

FileOperationResult FileHandler::writeMetaData(const FileMetaData &metaData) {
    std::ofstream outFile(filePath);
    if (!outFile) {
        return FileOperationResult(FileResult::WRITE_ERROR,
                                   "Error opening for writing: " + filePath.string());
    }

    outFile << metaData.toString();
    return FileOperationResult(FileResult::SUCCESS, "File written successfully");
}

FileOperationResult FileHandler::writeContent(const std::string &content) {
    std::ofstream outFile(filePath);
    if (!outFile) {
        return FileOperationResult(FileResult::WRITE_ERROR,
                                   "Error opening for writing: " + filePath.string());
    }

    outFile << content;
    return FileOperationResult(FileResult::SUCCESS, "Content written successfully");
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

std::filesystem::path FileHandler::getFilePath() const {
    return filePath;
}