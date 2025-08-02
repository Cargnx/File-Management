#include <iostream>
#include <fstream>
#include <filesystem>
#include <utility>
#include <vector>
#include <string>

// Simple metadata struct to organize related data
struct FileMetaData {
    std::string compileDate;
    std::string compileTime;
    int sourceLine;

    FileMetaData() : compileDate(__DATE__),
                     compileTime(__TIME__),
                     sourceLine(__LINE__) {
    }
};

// Result enum for clear error handling
enum class FileResult {
    SUCCESS,
    WRITE_ERROR,
    READ_ERROR
};

// Result class to return both status and data
class FileOperationResult {
public:
    FileResult result;
    std::string message;
    std::vector<std::string> lines;

    FileOperationResult(FileResult r, std::string msg = "")
        : result(r), message(std::move(msg)) {
    }

    bool isSuccess() const {
        return result == FileResult::SUCCESS;
    }

    void addLine(const std::string &line) {
        lines.push_back(line);
    }
};

// RAII File Handler Class
class FileHandler {
private:
    std::filesystem::path filePath;

public:
    explicit FileHandler(const std::filesystem::path &filePath) : filePath(
        filePath) {
    }

    FileOperationResult writeMetaData(const FileMetaData &metaData) {
        std::ofstream outFile(filePath);
        if (!outFile) {
            return FileOperationResult(FileResult::WRITE_ERROR,
                                       "Error opening for writing: " + filePath.
                                       string());
        }

        outFile << "Hello, this is a simple file." << '\n';
        outFile << "Date: " << metaData.compileDate << '\n';
        outFile << "Date: " << metaData.compileTime << '\n';
        outFile << "Date: " << metaData.sourceLine << '\n';

        return FileOperationResult(FileResult::SUCCESS,
                                   "File written successfully");
    }

    FileOperationResult readAllLines() {
        std::ifstream readFile(filePath);
        if (!readFile) {
            return FileOperationResult(FileResult::READ_ERROR,
                                       "Error opening file for reading: " +
                                       filePath.string());
        }

        FileOperationResult result(FileResult::SUCCESS,
                                   "File read successfully.");
        std::string line;
        while (std::getline(readFile, line)) {
            result.addLine(line);
        }

        return result;
    }

    std::filesystem::path getAbsolutePath() const {
        return std::filesystem::absolute(filePath);
    }
};

int main() {
    // Get the Directory of this file and create file path
    const std::filesystem::path basePath = std::filesystem::path(__FILE__).
            parent_path();
    const std::filesystem::path filePath = basePath / "test.txt";

    // Create file handler and metadata
    FileHandler handler(filePath);
    FileMetaData metaData;

    // Write File
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
    for (const auto &line: readResult.lines) {
        std::cout << line << '\n';
    }

    // Define the path to create directory
    std::filesystem::path directoryPath = "myDirectory";

    // To check if the directory exist or not, create it if doesn't exist
    if (!std::filesystem::exists(directoryPath)) {
        std::filesystem::create_directory(directoryPath);
        std::cout << "Directory created: " << directoryPath.string() << '\n';
    }

    // Define the file path within the directory and combining the directory
    std::filesystem::path filepath = directoryPath / "my_file.txt";

    // Create and open the file for writing using std::ofstream
    if (std::ofstream file(filepath); file.is_open()) {
        // Write data to the file
        file << "Hello, FileSystem!";
        file.close();
        std::cout << "File created: " << filepath << '\n';
    }
    else {
        // Handle the case if any error occured
        std::cerr << "Failed to create file: " << filepath
             << '\n';
    }

    return 0;
}
