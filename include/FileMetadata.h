#pragma once

#include <string>

// Simple metadata struct to organize related data
struct FileMetaData {
    std::string compileDate;
    std::string compileTime;
    int sourceLine;

    FileMetaData();

    // Helper method to format metadata as string
    std::string toString() const;
};