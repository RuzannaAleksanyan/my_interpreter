#include "parser.h"

void Parser::print_int() noexcept {
    for(const auto& map : int_variables) {
        std::cout << map.first << " " << map.second << std::endl;
    }
}

void Parser::print_scope_int() noexcept {
    for(const auto& map : scope_int_variables) {
        std::cout << map.first << " " << map.second << std::endl;
    }
}

void Parser::print_char() noexcept {
    for(const auto& map : char_variables) {
        std::cout << map.first << " " << map.second << std::endl;
    }
}

void Parser::print_float() noexcept {
    for(const auto& map : float_variables) {
        std::cout << map.first << " " << map.second << std::endl;
    }
}

void Parser::print_double() noexcept {
    for(const auto& map : double_variables) {
        std::cout << map.first << " " << map.second << std::endl;
    }
}

void Parser::print_bool() noexcept {
    for(const auto& map : bool_variables) {
        std::cout << map.first << " " << map.second << std::endl;
    }
}

void Parser::print_string() noexcept {
    for(const auto& map : string_variables) {
        std::cout << map.first << " " << map.second << std::endl;
    }
}

void Parser::print_include() noexcept {
    for(const auto& map : include_vector) {
        std::cout << map << std::endl;
    }
}