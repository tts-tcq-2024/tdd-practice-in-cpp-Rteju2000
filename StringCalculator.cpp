#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

// Function to split the string based on delimiters
std::vector<int> splitAndParse(const std::string& input, const std::string& delimiters) {
    std::vector<int> numbers;
    std::string token;
    size_t start = 0, end;
    
    while ((end = input.find_first_of(delimiters, start)) != std::string::npos) {
        token = input.substr(start, end - start);
        start = end + 1;
        if (!token.empty()) {
            numbers.push_back(std::stoi(token));
        }
    }
    // Add the last token
    token = input.substr(start);
    if (!token.empty()) {
        numbers.push_back(std::stoi(token));
    }
    
    return numbers;
}

// Add function that processes the input string
int add(const std::string& numbers) {
    if (numbers.empty()) {
        return 0;
    }

    std::string input = numbers;
    std::string delimiters = ",\n";
    
    // Handle custom delimiter
    if (input.substr(0, 2) == "//") {
        size_t pos = input.find('\n');
        if (pos == std::string::npos) {
            throw std::invalid_argument("Invalid custom delimiter format");
        }
        delimiters = input.substr(2, pos - 2);
        input = input.substr(pos + 1);
    }

    std::vector<int> parsedNumbers = splitAndParse(input, delimiters);
    int sum = 0;
    std::vector<int> negatives;

    for (int num : parsedNumbers) {
        if (num < 0) {
            negatives.push_back(num);
        } else if (num <= 1000) {
            sum += num;
        }
    }

    if (!negatives.empty()) {
        std::ostringstream msg;
        msg << "Negative numbers not allowed: ";
        for (size_t i = 0; i < negatives.size(); ++i) {
            if (i > 0) msg << ", ";
            msg << negatives[i];
        }
        throw std::invalid_argument(msg.str());
    }

    return sum;
}

