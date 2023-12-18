#include "parser.h"

void Parser::print_int_array() {
    for(const auto& i : int_array) {
        std::cout << i.first << " ";
        for(const auto& val : i.second) {
            std::cout << val << " ";
        }
    }
    std::cout << std::endl;
}

void Parser::print_char_array() {
    for(const auto& i : char_array) {
        std::cout << i.first << " ";
        for(const auto& val : i.second) {
            std::cout << val << " ";
        }
    }
    std::cout << std::endl;
}

void Parser::print_float_array() {
    for(const auto& i : float_array) {
        std::cout << i.first << " ";
        for(const auto& val : i.second) {
            std::cout << val << " ";
        }
    }
    std::cout << std::endl;
}

void Parser::print_double_array() {
    for(const auto& i : double_array) {
        std::cout << i.first << " ";
        for(const auto& val : i.second) {
            std::cout << val << " ";
        }
    }
    std::cout << std::endl;
}

void Parser::print_bool_array() {
    for(const auto& i : bool_array) {
        std::cout << i.first << " ";
        for(const auto& val : i.second) {
            std::cout << val << " ";
        }
    }
    std::cout << std::endl;
}