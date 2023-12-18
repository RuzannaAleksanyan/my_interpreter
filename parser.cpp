#include "parser.h"
#include "compound_assignment_operator.h"

#include <fstream>
#include <iostream>
#include <regex>
#include <vector>

Parser::Parser(const std::string& filename) : m_filename{filename}
{ }

bool Parser::has_main_function(const std::string& code) {
    std::regex mainRegex(R"(\bint\s+main\s*\(\s*\)\s*\{)");

    return std::regex_search(code, mainRegex);
}

std::string Parser::remove_comments(const std::string& code) {
    // Regular expression to match C++ comments (both single-line and multi-line)
    std::regex commentRegex("//[^\n]*|/\\*(.|\\n)*?\\*/");

    // Replace comments with an empty string
    return std::regex_replace(code, commentRegex, "");
}

bool Parser::has_ordered_brackets(const std::string& input_string) {
    if (input_string.empty() || input_string.back() != ']') {
        return false;
    }

    for (std::size_t i = 0; i < input_string.size(); ++i) {
        if (input_string[i] == '[') {
            return true;
        }
    }

    return false;
}

void Parser::parse() {
    std::size_t address = 1;

    std::vector<std::string> tokens;
    
    while(address < line_map.size()) {
        std::string line = line_map[address];

        // skip empty lines
        if (line.empty()) {
            ++address;
            continue;
        }

        // remove whitespace
        line = trim(line);

        std::istringstream iss(line);  // Create a string stream from the line
        std::string token;

        while (iss >> token) {
            tokens.push_back(token);  // Store each token in the vector
        }

        if(tokens[0] == "#include") {
            if(tokens.size() > 2 || tokens[1][tokens[1].size() - 1] != '>' || tokens[1][0] != '<') {
                throw std::runtime_error("Extra tokens at end of #include directive");
            }
            include_vector.push_back(tokens[1]);

            tokens.clear();
            ++address;
            continue;
        } else if(tokens.size() == 3 && tokens[0] == "int" && tokens[1] == "main()" && tokens[2] == "{") {
            // Skip the main() declaration
            tokens.clear();
            ++address;
            continue;
        } else if(tokens.size() == 1 && tokens[0] == "}" ) {
            // Skip the { declaration
            tokens.clear();
            ++address;
            continue;
            std::cout << "yes" << std::endl;
        } 

        if(tokens[0] == "if" && tokens[1] == "(" && tokens[tokens.size() - 2] == ")" && tokens[tokens.size() - 1] == "{") {
            if(condition_check(tokens)) {
                std::vector<std::string> if_block_lines;

                ++address;
                while (line_map[address] != "}") {
                    if_block_lines.push_back(line_map[address]);
                    ++address;
                }

                // katarel marminy

                tokens.clear();
                ++address;
                continue;
            }

            while(line_map[address] != "}") {
                ++address;
            }

            tokens.clear();
            ++address;
            continue;
        }

        lack_of_a_comma(line);
        tokens[tokens.size() - 1].pop_back();
        
        if(tokens.size() != 1 && tokens[0] == "int") { 
            if(has_ordered_brackets(tokens[1])) {
                int_array_declaration(tokens);
            } else {
                int_variable_declaration(tokens);
            }
        } else if(tokens.size() != 1 && tokens[0] == "char") {
            if(has_ordered_brackets(tokens[1])) {
                char_array_declaration(tokens);
            } else {
                char_variable_declaration(tokens);
            }
        } else if(tokens.size() != 1 && tokens[0] == "bool") {
            if(has_ordered_brackets(tokens[1])) {
                bool_array_declaration(tokens);
            } else {
                bool_variable_declaration(tokens);
            }
        } else if(tokens.size() != 1 && tokens[0] == "float") {
            if(has_ordered_brackets(tokens[1])) {
                float_array_declaration(tokens);
            } else {
                float_variable_declaration(tokens);
            }
        } else if(tokens.size() != 1 && tokens[0] == "double") {
            if(has_ordered_brackets(tokens[1])) {
                double_array_declaration(tokens);
            } else {
                double_variable_declaration(tokens);
            }
        } else if(tokens.size() != 1 && tokens[0] == "string") {
            string_variable_declaration(tokens);
        } else if(tokens.size() == 1 && (tokens[0] == "int" || tokens[0] == "char" || tokens[0] == "float" || tokens[0] == "double" || tokens[0] == "bool")) {
            throw std::runtime_error("error: declaration does not declare anything [-fpermissive]");
        }
        
        if(tokens.size() == 3 && (tokens[1] == "+=" || tokens[1] == "-=" || tokens[1] == "*=" || tokens[1] == "/=" || tokens[1] == "=")) {
            const std::string& variable = tokens[0];
            const std::string& operation = tokens[1];
            const std::string& operand = tokens[2];

            compound_assignment_operator(variable, operand, operation);
        }        
        
        if(tokens.size() == 5 && (tokens[3] == "+" || tokens[3] == "-" || tokens[3] == "*" || tokens[3] == "/")) {
            arithmetic_operations(tokens[0], tokens[2], tokens[4], tokens[3]);  
        }

        if(tokens[0] == "cin" ) {
            throw std::runtime_error("error: 'cin' was not declared in this scope; did you mean 'std::cin'?");
        }

        if(tokens.size() == 1 && tokens[0] == "std::cin") {
            ++address;
            tokens.clear();
            continue;
        }

        if(tokens.size() >= 3 && tokens[0] == "std::cin") {
            cin_implementation(tokens);
        }

        if(tokens[0] == "cout") {
            throw std::runtime_error("error: 'cin' was not declared in this scope; did you mean 'std::cin'?");
        }

        if(token.size() == 1 && tokens[0] == "std::cout") {
            ++address;
            tokens.clear();
            continue;
        }

        if(tokens.size() >= 3 && tokens[0] == "std::cout" ) {
            cout_implementation(tokens);
        }

        ++address;
        tokens.clear();
    }
}

bool Parser::contains_if_condition(const std::string& line) {
    // Regular expression to match an 'if' statement with any condition
    std::regex if_regex(R"(if\s*\(.+\)\s*\{)");

    return std::regex_search(line, if_regex);
}

void Parser::lack_of_a_comma(std::string& line) {
    // Check if there is a semicolon at the end
    if (line.back() != ';') {
        throw std::runtime_error("Error: Missing semicolon at the end of the line.");
    }

    // Remove the semicolon from the end of the line
    line.pop_back();
}

void Parser::check_variable_exists(const std::string& variable_name) {
    if (int_variables.find(variable_name) != int_variables.end() ||
        char_variables.find(variable_name) != char_variables.end() ||
        float_variables.find(variable_name) != float_variables.end() ||
        double_variables.find(variable_name) != double_variables.end() ||
        bool_variables.find(variable_name) != bool_variables.end()) {
        throw std::runtime_error("Variable already exists: " + variable_name);
    }
}

bool Parser::is_number(const std::string& str) noexcept {
    std::istringstream iss(str);
    double number;

    // Attempt to extract a number from the string
    return (iss >> number) ? true : false;
}

void Parser::compound_assignment_operator(const std::string& variable, const std::string& operand, const std::string& assignment) {
    Compound_Assignment_Operator obj;
    if (int_variables.find(variable) != int_variables.end() && int_variables.find(operand) != int_variables.end()) {
        obj.compound_assignment_operator_impl<int, int>(int_variables, int_variables, variable, operand, assignment);
    } else if (int_variables.find(variable) != int_variables.end() && char_variables.find(operand) != char_variables.end()) {
        obj.compound_assignment_operator_impl<int, char>(int_variables, char_variables, variable, operand, assignment);
    } else if (int_variables.find(variable) != int_variables.end() && float_variables.find(operand) != float_variables.end()) {
        obj.compound_assignment_operator_impl<int, float>(int_variables, float_variables, variable, operand, assignment);
    } else if (int_variables.find(variable) != int_variables.end() && double_variables.find(operand) != double_variables.end()) {
        obj.compound_assignment_operator_impl<int, double>(int_variables, double_variables, variable, operand, assignment);
    } else if (int_variables.find(variable) != int_variables.end() && bool_variables.find(operand) != bool_variables.end()) {
        obj.compound_assignment_operator_impl<int, bool>(int_variables, bool_variables, variable, operand, assignment);
    }  else if (char_variables.find(variable) != char_variables.end() && char_variables.find(operand) != char_variables.end()) {
        obj.compound_assignment_operator_impl<char, char>(char_variables, char_variables, variable, operand, assignment);
    } else if (char_variables.find(variable) != char_variables.end() && double_variables.find(operand) != double_variables.end()) {
        obj.compound_assignment_operator_impl<char, int>(char_variables, int_variables, variable, operand, assignment);
    } else if (char_variables.find(variable) != char_variables.end() && float_variables.find(operand) != float_variables.end()) {
        obj.compound_assignment_operator_impl<char, float>(char_variables, float_variables, variable, operand, assignment);
    } else if (char_variables.find(variable) != char_variables.end() && bool_variables.find(operand) != bool_variables.end()) {
        obj.compound_assignment_operator_impl<char, bool>(char_variables, bool_variables, variable, operand, assignment);
    }  else if (char_variables.find(variable) != char_variables.end() && double_variables.find(operand) != double_variables.end()) {
        obj.compound_assignment_operator_impl<char, double>(char_variables, double_variables, variable, operand, assignment);
    } else if (float_variables.find(variable) != float_variables.end() && float_variables.find(operand) != float_variables.end()) {
        obj.compound_assignment_operator_impl<float, float>(float_variables, float_variables, variable, operand, assignment);
    } else if (float_variables.find(variable) != float_variables.end() && int_variables.find(operand) != int_variables.end()) {
        obj.compound_assignment_operator_impl<float, int>(float_variables, int_variables, variable, operand, assignment);
    } else if (float_variables.find(variable) != float_variables.end() && char_variables.find(operand) != char_variables.end()) {
        obj.compound_assignment_operator_impl<float, char>(float_variables, char_variables, variable, operand, assignment);
    }  else if (float_variables.find(variable) != float_variables.end() && double_variables.find(operand) != double_variables.end()) {
        obj.compound_assignment_operator_impl<float, double>(float_variables, double_variables, variable, operand, assignment);
    } else if (float_variables.find(variable) != float_variables.end() && bool_variables.find(operand) != bool_variables.end()) {
        obj.compound_assignment_operator_impl<float, bool>(float_variables, bool_variables, variable, operand, assignment);
    } else if (double_variables.find(variable) != double_variables.end() && double_variables.find(operand) != double_variables.end()) {
        obj.compound_assignment_operator_impl<double, double>(double_variables, double_variables, variable, operand, assignment);
    } else if (double_variables.find(variable) != double_variables.end() && int_variables.find(operand) != int_variables.end()) {
        obj.compound_assignment_operator_impl<double, int>(double_variables, int_variables, variable, operand, assignment);
    } else if (double_variables.find(variable) != double_variables.end() && char_variables.find(operand) != char_variables.end()) {
        obj.compound_assignment_operator_impl<double, char>(double_variables, char_variables, variable, operand, assignment);
    } else if (double_variables.find(variable) != double_variables.end() && float_variables.find(operand) != float_variables.end()) {
        obj.compound_assignment_operator_impl<double, float>(double_variables, float_variables, variable, operand, assignment);
    } else if (double_variables.find(variable) != double_variables.end() && bool_variables.find(operand) != bool_variables.end()) {
        obj.compound_assignment_operator_impl<double, bool>(double_variables, bool_variables, variable, operand, assignment);
    } else if (bool_variables.find(variable) != bool_variables.end() && bool_variables.find(operand) != bool_variables.end()) {
        obj.compound_assignment_operator_impl<bool, bool>(bool_variables, bool_variables, variable, operand, assignment);
    } else if (bool_variables.find(variable) != bool_variables.end() && int_variables.find(operand) != int_variables.end()) {
        obj.compound_assignment_operator_impl<bool, int>(bool_variables, int_variables, variable, operand, assignment);
    } else if (bool_variables.find(variable) != bool_variables.end() && char_variables.find(operand) != char_variables.end()) {
        obj.compound_assignment_operator_impl<bool, char>(bool_variables, char_variables, variable, operand, assignment);
    } else if (bool_variables.find(variable) != bool_variables.end() && float_variables.find(operand) != float_variables.end()) {
        obj.compound_assignment_operator_impl<bool, float>(bool_variables, float_variables, variable, operand, assignment);
    } else if (bool_variables.find(variable) != bool_variables.end() && double_variables.find(operand) != double_variables.end()) {
        obj.compound_assignment_operator_impl<bool, double>(bool_variables, double_variables, variable, operand, assignment);
    } else if(int_variables.find(variable) != int_variables.end() && is_number(operand)) {
        int i = std::stoi(operand);
        obj.compound_assignment_operator_impl_literal<int>(int_variables, variable, assignment, i);
    } else if(char_variables.find(variable) != char_variables.end() ) {
        char ch;
        if(is_number(operand)) {
            ch = std::stoi(operand);
        } else if(operand.size() == 3 && operand[0] == '\'' && operand[2] == '\'') {
            ch = operand[1];
        } else {
            throw std::runtime_error("Variable type mismatch or undefined variable: " + operand);
        }
        obj.compound_assignment_operator_impl_literal<char>(char_variables, variable, assignment, ch);
    } else if(float_variables.find(variable) != float_variables.end() && is_number(operand)) {
        float f = std::stof(operand);
        obj.compound_assignment_operator_impl_literal<float>(float_variables, variable, assignment, f);
    } else if(double_variables.find(variable) != double_variables.end() && is_number(operand)) {
        double d = std::stod(operand);
        obj.compound_assignment_operator_impl_literal<double>(double_variables, variable, assignment, d);
    } else if(bool_variables.find(variable) != bool_variables.end() && is_number(operand)) {
        bool b = std::stoi(operand) == 0 ? 0 : 1;
        obj.compound_assignment_operator_impl_literal<bool>(bool_variables, variable, assignment, b);
    } else {
        throw std::runtime_error("Variable type mismatch or undefined variable: " + variable);
    }
}

void Parser::arithmetic_operations(const std::string& variable, const std::string& operand1, 
                                   const std::string& operand2, const std::string& assignment) {
    if(int_variables.find(variable) != int_variables.end()){
        arithmetic_operations_impl(int_variables, variable, operand1, operand2, assignment);
    } else if(char_variables.find(variable) != char_variables.end()) {
        arithmetic_operations_impl(char_variables, variable, operand1, operand2, assignment);
    } else if(float_variables.find(variable) != float_variables.end()) {
        arithmetic_operations_impl(float_variables, variable, operand1, operand2, assignment);
    } else if(double_variables.find(variable) != double_variables.end()) {
        arithmetic_operations_impl(double_variables, variable, operand1, operand2, assignment);
    } else if(bool_variables.find(variable) != bool_variables.end()) {
        arithmetic_operations_impl(bool_variables, variable, operand1, operand2, assignment);
    } else {
        throw std::runtime_error("Variable type mismatch or undefined variable: " + variable);
    }
}






