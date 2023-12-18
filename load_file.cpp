#include "parser.h"
#include <iostream>
#include <fstream>
#include <stack>
#include <string>
#include <algorithm>
#include <stdexcept>

std::string Parser::trim(const std::string& str) {
    size_t start = str.find_first_not_of(" \t\n\r");
    if (start == std::string::npos) {
        return "The string contains only whitespace";  // The string contains only whitespace
    }

    size_t end = str.find_last_not_of(" \t\n\r");
    return str.substr(start, end - start + 1);
}

void Parser::load_from_file(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file");
    }

    bool in_block_comment = false;

    std::string line {};
    int address = 0;
    std::stack<int> if_starts;
    std::stack<int> while_starts;
    int brace_count = 1;

    while (std::getline(file, line)) {
        ++address;
        line = trim(line);

        size_t comment_start = line.find("/*");
        size_t comment_end = line.find("*/");

        if (comment_start != std::string::npos) {
            if (comment_end != std::string::npos && comment_end > comment_start) {
                line = line.substr(0, comment_start) + line.substr(comment_end + 2);
            } else {
                in_block_comment = true;
                line = line.substr(0, comment_start);
            }
        } else if (in_block_comment) {
            comment_end = line.find("*/");
            if (comment_end != std::string::npos) {
                in_block_comment = false;
                line = line.substr(comment_end + 2);
            } else {
                line = "";
            }
        }

        // Remove line comments (everything after //)
        size_t line_commentPos = line.find("//");
        if (line_commentPos != std::string::npos) {
            line = line.substr(0, line_commentPos);
        }

        // Check for "if" statements
        if (line.find("if ") == 0) {
            if_starts.push(address);
            ++brace_count;
        }

        // Check for "while" statements
        if (line.find("while ") == 0) {
            while_starts.push(address);
            ++brace_count;
        }

        // Process closing curly braces
        if (line == "}") {
            --brace_count;
            if (!if_starts.empty() && !while_starts.empty()) {
                // if or while closing brace
                int if_top = if_starts.top();
                int while_top = while_starts.top();

                if (if_top > while_top) {
                    int start_address = if_starts.top();
                    if_starts.pop();
                    if_map[start_address] = std::make_pair(start_address, address);
                } else {
                    int start_address = while_starts.top();
                    while_starts.pop();
                    while_map[start_address] = std::make_pair(start_address, address);
                }
            } else if (!if_starts.empty()) {
                int start_address = if_starts.top();
                if_starts.pop();
                if_map[start_address] = std::make_pair(start_address, address);
            } else if (!while_starts.empty()) {
                int start_address = while_starts.top();
                while_starts.pop();
                while_map[start_address] = std::make_pair(start_address, address);
            }
        }

        line_map[address] = line;
    }

    file.close();

    if (brace_count) {
        throw std::runtime_error("You missed or overused { or }");
    }
}