#include "parser.h"
#include <valarray>

void Parser::cin_implementation(std::vector<std::string>& tokens) {
    bool flag = false;
    for(const auto& in : include_vector) {
        if(in == "<iostream>") {
            flag = true;
        }
    }

    if(!flag) {
        throw std::runtime_error("'" + tokens[0] + "' is defined in header '<iostream>'; did you forget to '#include <iostream>'?");
    }

            // std::cout << tokens.size() << std::endl;
    if(tokens.size() == 2) {
        throw std::runtime_error("error: expected primary-expression before ';' token");
    }

    for(size_t i = 1; i < tokens.size() - 1; i += 2) {
        if(tokens[i] != ">>") {
            throw std::runtime_error("error: not match for 'operator" + tokens[i] + "'");
        } 

        if(int_variables.find(tokens[i + 1]) != int_variables.end()) {
            std::cin >> int_variables[tokens[i + 1]];
        } else if(char_variables.find(tokens[i + 1]) != char_variables.end()) {
            std::cin >> char_variables[tokens[i + 1]];
        } else if(float_variables.find(tokens[i + 1]) != float_variables.end()) {
            std::cin >> float_variables[tokens[i + 1]];
        } else if(double_variables.find(tokens[i + 1]) != double_variables.end()) {
            std::cin >> double_variables[tokens[i + 1]];
        } else if(bool_variables.find(tokens[i + 1]) != bool_variables.end()) {
            std::cin >> bool_variables[tokens[i + 1]];
        } else if(string_variables.find(tokens[i + 1]) != string_variables.end()) {
            std::cin >> string_variables[tokens[i + 1]];
        } else {
            throw std::runtime_error("'" + tokens[i] + "' was not declared in this scope");
        }
    } 
    
}

void Parser::cout_implementation(std::vector<std::string> tokens) {
    bool flag = false;
    for(const auto& in : include_vector) {
        if(in == "<iostream>") {
            flag = true;
        }
    }

    if(!flag) {
        throw std::runtime_error("'" + tokens[0] + "' is defined in header '<iostream>'; did you forget to '#include <iostream>'?");
    }

    for(size_t i = 1; i < tokens.size() - 1; i += 2) {
        if(tokens[i] != "<<") {
            throw std::runtime_error("error: not match for 'operator" + tokens[i] + "'");
        } 

        if(tokens.size() == 2) {
            throw std::runtime_error("error: expected primary-expression before ';' token");
        }

        if(tokens[i + 1] == "endl") {
            throw std::runtime_error("'" + tokens[i + 1] + "' was not declared in this scope");
        }   

        if(int_variables.find(tokens[i + 1]) != int_variables.end()) {
            std::cout << int_variables[tokens[i + 1]];
        } else if(char_variables.find(tokens[i + 1]) != char_variables.end()) {
            std::cout << char_variables[tokens[i + 1]];
        } else if(float_variables.find(tokens[i + 1]) != float_variables.end()) {
            std::cout << float_variables[tokens[i + 1]];
        } else if(double_variables.find(tokens[i + 1]) != double_variables.end()) {
            std::cout << double_variables[tokens[i + 1]];
        } else if(bool_variables.find(tokens[i + 1]) != bool_variables.end()) {
            std::cout << bool_variables[tokens[i + 1]];
        } else if(string_variables.find(tokens[i + 1]) != string_variables.end()) {
            std::cout << string_variables[tokens[i + 1]];
        }  else if(tokens[i + 1] == "std::endl") {
            std::cout << std::endl;
        } else if(tokens[i + 1][0] == '"' && tokens[i + 1][tokens[i + 1].size() - 1] == '"') {
            tokens[i + 1] = tokens[i + 1].substr(1, tokens[i + 1].size() - 2);
            std::cout << tokens[i + 1];
        }else {
            throw std::runtime_error("'" + tokens[i] + "' was not declared in this scope");
        }
    } 
}

