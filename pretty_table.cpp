#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>
#include <stdexcept>
using namespace std;

// Alignment Enum
enum Alignment {
    LEFT,
    RIGHT,
    CENTER
};

// Style Class
class Style {
public:
    char vertical_border;
    char horizontal_border;
    char corner;
    Alignment alignment;

    Style(char vertical, char horizontal, char corner, Alignment align)
        : vertical_border(vertical), horizontal_border(horizontal), corner(corner), alignment(align) {}
};

class Table {
private:
    vector<string> column_names;
    vector<vector<string>> data;
    Style style;
    size_t column_count;

    // Helper to compute column widths
    vector<size_t> computeColumnWidths() const {
        vector<size_t> widths(column_count, 0);
        for (size_t i = 0; i < column_count; ++i) {
            widths[i] = max(widths[i], column_names[i].length());
            for (const auto& row : data) {
                if (i < row.size()) {
                    widths[i] = max(widths[i], row[i].length());
                }
            }
        }
        return widths;
    }

    // Helper to center-align text
    string alignText(const string& text, size_t width, Alignment align) const {
        if (align == LEFT) {
            return text + string(width - text.length(), ' ');
        } else if (align == RIGHT) {
            return string(width - text.length(), ' ') + text;
        } else {
            size_t pad_left = (width - text.length()) / 2;
            size_t pad_right = width - text.length() - pad_left;
            return string(pad_left, ' ') + text + string(pad_right, ' ');
        }
    }

    // Helper to print a row
    void printRow(const vector<string>& row, const vector<size_t>& widths) const {
        cout << style.vertical_border;
        for (size_t i = 0; i < column_count; ++i) {
            if (i < row.size()) {
                cout << " " << alignText(row[i], widths[i], style.alignment) << " ";
            } else {
                cout << " " << string(widths[i], ' ') << " ";
            }
            cout << style.vertical_border;
        }
        cout << endl;
    }

    // Helper to print a separator row
    void printSeparator(const vector<size_t>& widths) const {
        cout << style.corner;
        for (size_t i = 0; i < column_count; ++i) {
            cout << string(widths[i] + 2, style.horizontal_border) << style.corner;
        }
        cout << endl;
    }

public:
    // Constructor
    Table(const vector<string>& columns, const Style& style = Style('|', '-', '+', LEFT))
        : column_names(columns), style(style), column_count(columns.size()) {}

    // Add a row to the table
    void addRow(const vector<string>& row) {
        if (row.size() > column_count) {
            throw invalid_argument("Row size exceeds column count");
        }
        data.push_back(row);
    }

    // Add a column to the table
    void addColumn(const string& column_name, const vector<string>& column_data) {
        column_names.push_back(column_name);
        ++column_count;
        for (size_t i = 0; i < max(data.size(), column_data.size()); ++i) {
            if (i >= data.size()) {
                data.emplace_back(vector<string>(column_count - 1, ""));
            }
            if (i < column_data.size()) {
                data[i].push_back(column_data[i]);
            } else {
                data[i].push_back("");
            }
        }
    }

    // Set table style
    void setStyle(const Style& new_style) {
        style = new_style;
    }

    // Print the table to the console
    void print() const {
        vector<size_t> widths = computeColumnWidths();
        printSeparator(widths);
        printRow(column_names, widths);
        printSeparator(widths);
        for (const auto& row : data) {
            printRow(row, widths);
        }
        printSeparator(widths);
    }

    // Save the table to a file
    void saveToFile(const string& file_name, bool append = false) const {
        ofstream file;
        if (append) {
            file.open(file_name, ios::app);
        } else {
            file.open(file_name);
        }
        if (!file.is_open()) {
            throw runtime_error("Could not open file");
        }

        vector<size_t> widths = computeColumnWidths();
        auto writeSeparator = [&]() {
            file << style.corner;
            for (size_t i = 0; i < column_count; ++i) {
                file << string(widths[i] + 2, style.horizontal_border) << style.corner;
            }
            file << endl;
        };

        auto writeRow = [&](const vector<string>& row) {
            file << style.vertical_border;
            for (size_t i = 0; i < column_count; ++i) {
                if (i < row.size()) {
                    file << " " << alignText(row[i], widths[i], style.alignment) << " ";
                } else {
                    file << " " << string(widths[i], ' ') << " ";
                }
                file << style.vertical_border;
            }
            file << endl;
        };

        writeSeparator();
        writeRow(column_names);
        writeSeparator();
        for (const auto& row : data) {
            writeRow(row);
        }
        writeSeparator();
        file.close();
    }
};

int main() {
    Table table({"Name", "Age", "City"});
    table.addRow({"Alice", "30", "New York"});
    table.addRow({"Bob", "25", "Los Angeles"});
    table.addRow({"Charlie", "35", "Chicago"});

    table.setStyle(Style('|', '=', '+', CENTER));
    table.print();

    table.saveToFile("output.txt");

    return 0;
}
