#include "../include/FileMetadata.h"

// FileMetaData implementation
FileMetaData::FileMetaData() : compileDate(__DATE__),
                               compileTime(__TIME__),
                               sourceLine(__LINE__) {
}

std::string FileMetaData::toString() const {
    std::string result = "Hello, this is a simple file.\n";
    result += "Date: " + compileDate + "\n";
    result += "Time: " + compileTime + "\n";
    result += "Line: " + std::to_string(sourceLine) + "\n";
    return result;
}