#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <vector>

// Function to open a file and return an ifstream object. Returns nullptr if file cannot be opened.
std::ifstream* openFile(const std::string& fileName);

// Validates the number of command-line arguments.
bool validateArgCount(int argc, char* argv[]);

// Parses and validates instructions from stdin. Returns a vector of strings.
std::vector<std::string> parseInstructions();

// Prints an error message to stderr.
void printError(const std::string& message);

#endif // UTIL_H
