#include "util.h"
#include <iostream>
#include <fstream>
#include <sstream>

std::ifstream* openFile(const std::string& fileName) {
    auto* file = new std::ifstream(fileName);
    if (!file->is_open()) {
        printError("Could not open file: " + fileName);
        delete file;
        return nullptr;
    }
    return file;
}

bool validateArgCount(int argc, char* argv[]) {
    if (argc != 4) {
        printError("Usage: " + std::string(argv[0]) + " <InputFile> <GraphType> <Flag>");
        return false;
    }
    return true;
}

std::vector<std::string> parseInstructions() {
    std::vector<std::string> instructions;
    std::string line;
    while (getline(std::cin, line)) {
        std::istringstream iss(line);
        instructions.push_back(line);
    }
    return instructions;
}

void printError(const std::string& message) {
    std::cerr << "Error: " << message << std::endl;
}
