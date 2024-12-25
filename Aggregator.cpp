#include "Aggregator.h"

class MyException {
public:
    MyException(const std::string& message) : message_(message) {}
    const std::string& what() const { return message_; }
    
private:
    std::string message_;
};

class MyStringStream {
public:
    static std::string toString(int value);
    static std::string toString(double value);
    static std::vector<std::string> split(const std::string& str, char delimiter);
};

double Aggregator::sumColumn(const std::vector<std::vector<std::string>>& data, size_t column_index) {
    double sum = 0;
    for (const auto& row : data) {
        if (column_index >= row.size()) {
            throw std::out_of_range("Column index out of range");
        }
        std::istringstream(row[column_index]) >> sum;
    }
    return sum;
}

double Aggregator::averageColumn(const std::vector<std::vector<std::string>>& data, size_t column_index) {
    double sum = sumColumn(data, column_index);
    return sum / data.size();
}
