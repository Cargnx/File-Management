#include "../include/FileOperationResult.h"
#include <utility>

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