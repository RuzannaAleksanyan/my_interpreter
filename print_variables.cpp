#include "parser.h"

void Parser::print_int() {
    for(const auto& map : int_variables) {
        std::cout << map.first << " " << map.second << std::endl;
    }
}

void Parser::print_char() {
    for(const auto& map : char_variables) {
        std::cout << map.first << " " << map.second << std::endl;
    }
}

void Parser::print_float() {
    for(const auto& map : float_variables) {
        std::cout << map.first << " " << map.second << std::endl;
    }
}

void Parser::print_double() {
    for(const auto& map : double_variables) {
        std::cout << map.first << " " << map.second << std::endl;
    }
}

void Parser::print_bool() {
    for(const auto& map : bool_variables) {
        std::cout << map.first << " " << map.second << std::endl;
    }
}

void Parser::print_string() {
    for(const auto& map : string_variables) {
        std::cout << map.first << " " << map.second << std::endl;
    }
}

void Parser::print_include() {
    for(const auto& map : include_vector) {
        std::cout << map << std::endl;
    }
}