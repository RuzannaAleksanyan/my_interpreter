#include "parser.h"

bool Parser::condition_check(std::vector<std::string>& tokens) {
    if (tokens.size() < 5) {
        throw std::runtime_error("Insufficient number of tokens for condition check.");
    }

    if(tokens.size() == 5) {
        if(is_number(tokens[2]) && std::stoi(tokens[2]) != 0) {
            return true;
        } 
        
        return false;
    }

    std::string op = tokens[3];
    std::string op1 = tokens[2];
    std::string op2 = tokens[4];

    // auto value1 = get_variable_value(op1);
    // auto value2 = get_variable_value(op2);

    return perform_comparison(op, op1, op2);
}

bool Parser::perform_comparison(const std::string& op, const std::string& op1, const std::string& op2) {
    auto value1 = get_variable_value(op1);
    auto value2 = get_variable_value(op2);

    if(op == "==") {
        return value1 == value2;
    } else if(op == ">=") {
        return value1 >= value2;
    } else if(op == "<=") {
        return value1 <= value2;
    } else if(op == "<") {
        return value1 < value2;
    } else if(op == ">") {
        return value1 > value2;
    } else {
        throw std::runtime_error("error: '" + op + "' was not declared in this scope");
    }
}
