#include "Aggregator.h"
#include <sstream>

class MyException {
public:
    MyException(const std::string& message) : message_(message) {}
    const std::string& what() const { return message_; }
    
private:
    std::string message_;
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
