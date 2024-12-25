#include "Validator.h"
#include <regex>
#include <stdexcept>

bool Validator::validateInteger(const std::string& str) {
    std::regex pattern("^[+-]?[0-9]+$");
    return std::regex_match(str, pattern);
}

bool Validator::validateFloat(const std::string& str) {
    std::regex pattern("^[+-]?([0-9]*[.])?[0-9]+$");
    return std::regex_match(str, pattern);
}

bool Validator::validateEmail(const std::string& str) {
    std::regex pattern("[\\w-]+(\\.[\\w-]+)*@([\\w-]+\\.)+[a-zA-Z]{2,7}");
    return std::regex_match(str, pattern);
}

bool Validator::validateDate(const std::string& str) {
    std::regex pattern("\\d{4}-\\d{2}-\\d{2}");
    return std::regex_match(str, pattern);
}

bool Validator::validateRowData(const std::vector<std::string>& row, const std::vector<std::string>& column_types) {
    for (size_t i = 0; i < row.size(); ++i) {
        if (column_types[i] == "int" && !validateInteger(row[i])) {
            throw std::invalid_argument("Invalid integer value at row " + std::to_string(i));
        } else if (column_types[i] == "float" && !validateFloat(row[i])) {
            throw std::invalid_argument("Invalid float value at row " + std::to_string(i));
        } else if (column_types[i] == "email" && !validateEmail(row[i])) {
            throw std::invalid_argument("Invalid email value at row " + std::to_string(i));
        } else if (column_types[i] == "date" && !validateDate(row[i])) {
            throw std::invalid_argument("Invalid date value at row " + std::to_string(i));
        }
    }
    return true;
}