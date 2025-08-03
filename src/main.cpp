#include "FileHandler.h"
#include "FileUtils.h"
#include "FileMetadata.h"

int main() {
    const auto basePath = std::filesystem::path(__FILE__).parent_path().parent_path();

    // Create directory structure
    if (!FileUtils::createDirectoryIfNotExists(basePath / "output")) {
        return 1;
    }

    // Use FileHandler for file operations
    FileHandler handler(basePath / "output" / "test.txt");
    FileMetaData metaData;

    auto result = handler.writeMetaData(metaData);
    // ... rest of your code
}