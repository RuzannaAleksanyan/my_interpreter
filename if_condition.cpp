// #include "parser.h"



// bool Parser::condition_check(std::vector<std::string>& tokens) {
//     if (tokens.size() < 5) {
//         throw std::runtime_error("Insufficient number of tokens for condition check.");
//     }

//     if(tokens.size() == 5) {
//         if(is_number(tokens[2]) && std::stoi(tokens[2]) != 0) {
//             return true;
//         } 
        
//         return false;
//     }

//     std::string op = tokens[3];
//     std::string op1 = tokens[2];
//     std::string op2 = tokens[4];

//     auto value2 = get_variable_value(op1);
//     auto value4 = get_variable_value(op2);

//     // if(op == "==") {
//     //     return value2 == value4;
//     // } else if(op == ">=") {
//     //     return value2 >= value4;
//     // } else if(op == "<=") {
//     //     return value2 <= value4;
//     // } else if(op == "<") {
//     //     return value2 < value4;
//     // } else if(op == ">") {
//     //     return value2 > value4;
//     // } 
//     // // else if(op == "-") {
//     // //     return perform_operation<double>(value2, value4, "-");
//     // // } else if(op == "+") {
//     // //     return perform_operation<double>(value2, value4, "+");
//     // // } else if(op == "*") {
//     // //     return perform_operation<double>(value2, value4, "*");
//     // // } else if(op == "/") {
//     // //     return perform_operation<double>(value2, value4, "/");
//     // // } 
//     // else {
//     //     throw std::runtime_error("error: '" + op2 + "' was not declared in this scope");
//     // }

// }

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

    auto value2 = get_variable_value(op1);
    auto value4 = get_variable_value(op2);

    return perform_comparison(op, value2, value4);
}

// bool Parser::perform_comparison(const std::string& op, const auto& value1, const auto& value2) {
//     if(op == "==") {
//         return value1 == value2;
//     } else if(op == ">=") {
//         return value1 >= value2;
//     } else if(op == "<=") {
//         return value1 <= value2;
//     } else if(op == "<") {
//         return value1 < value2;
//     } else if(op == ">") {
//         return value1 > value2;
//     } else {
//         throw std::runtime_error("error: '" + op + "' was not declared in this scope");
//     }
// }
