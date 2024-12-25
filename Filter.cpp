#include "Filter.h"
#include <algorithm>

std::vector<std::vector<std::string>> Filter::filterByColumn(const std::vector<std::vector<std::string>>& data, size_t column_index, const std::string& value) {
    std::vector<std::vector<std::string>> filtered_data;
    for (const auto& row : data) {
        if (row[column_index] == value) {
            filtered_data.push_back(row);
        }
    }
    return filtered_data;
}

std::vector<std::vector<std::string>> Filter::paginate(const std::vector<std::vector<std::string>>& data, size_t page, size_t page_size) {
    size_t start = (page - 1) * page_size;
    size_t end = std::min(start + page_size, data.size());

    std::vector<std::vector<std::string>> paginated_data(data.begin() + start, data.begin() + end);
    return paginated_data;
}
