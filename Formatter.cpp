#include "Formatter.h"
#include <string>
#include <vector>
#include <map>

class MyJSON {
public:
    static std::string toJSON(const std::map<std::string, std::string>& data);
    static std::map<std::string, std::string> fromJSON(const std::string& jsonString);
};

class MyStringStream {
public:
    static std::string toString(int value);
    static std::string toString(double value);
    static std::vector<std::string> split(const std::string& str, char delimiter);
};

void Formatter::toCSV(const std::vector<std::string>& column_names, const std::vector<std::vector<std::string>>& data, const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file to write CSV");
    }
    
    // Write column names
    for (size_t i = 0; i < column_names.size(); ++i) {
        file << column_names[i];
        if (i < column_names.size() - 1) {
            file << ",";
        }
    }
    file << "\n";
    
    // Write data rows
    for (const auto& row : data) {
        for (size_t i = 0; i < row.size(); ++i) {
            file << row[i];
            if (i < row.size() - 1) {
                file << ",";
            }
        }
        file << "\n";
    }

    file.close();
}

void Formatter::toJSON(const std::vector<std::string>& column_names, const std::vector<std::vector<std::string>>& data, const std::string& filename) {
    Json::Value root;
    Json::StreamWriterBuilder writer;
    
    for (const auto& row : data) {
        Json::Value json_row;
        for (size_t i = 0; i < column_names.size(); ++i) {
            json_row[column_names[i]] = row[i];
        }
        root.append(json_row);
    }
    
    std::ofstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file to write JSON");
    }

    file << Json::writeString(writer, root);
    file.close();
}
