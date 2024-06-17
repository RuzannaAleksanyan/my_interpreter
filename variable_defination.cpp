#include "parser.h"

#include <random>

// Constants
const int DEFAULT_RANDOM_MAX = 1000000000;

void Parser::int_variable_declaration(std::vector<std::string>& tokens, bool flag) {
    // tokens[tokens.size() - 1].pop_back();

    if (tokens.size() == 1) {
        throw std::runtime_error("Declaration does not declare anything!");
    }
    check_variable_exists(tokens[1]);

    // Set up a random number generator
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(1, DEFAULT_RANDOM_MAX);

    if (tokens.size() == 2) {
        // Handle the case where there's no initializer
        if(flag == 1) {
            scope_int_variables[tokens[1]] = dist(gen);
        } else if(flag == 0) {
            int_variables[tokens[1]] = dist(gen); // You can assign a default value (e.g., 0) here
        }
    } else if (tokens.size() == 4 && tokens[2] == "=") {
        if(flag == 0) {
            if (is_number(tokens[3])) {
                int_variables[tokens[1]] = std::stoi(tokens[3]);
            } else {
                int_variables[tokens[1]] = search_variable(tokens[3], int_variables);
            }
        } else if(flag == 1) {
            if (is_number(tokens[3])) {
                scope_int_variables[tokens[1]] = std::stoi(tokens[3]);
            } else {
                scope_int_variables[tokens[1]] = search_variable(tokens[3], scope_int_variables);
            }
        }
        
    } else {
        throw std::runtime_error("error: expected initializer before");
    }
}

void Parser::char_variable_declaration(std::vector<std::string>& tokens, bool flag) {
    // tokens[tokens.size() - 1].pop_back();
    if(tokens.size() == 1) {
        throw std::runtime_error("Declaration does not declare anything!");
    }
    check_variable_exists(tokens[1]);
    if (tokens.size() == 2) {
        // Initialize char variables with a default value (e.g., ' ')
        if(flag == 0) {
            char_variables[tokens[1]] = ' ';
        } else if(flag == 1) {
            scope_char_variables[tokens[1]] = ' ';
        }
    } else if (tokens.size() == 4 && tokens[2] == "=") {
        if(flag == 0) {
            if (tokens[3].size() == 3 && tokens[3][0] == '\'' && tokens[3][2] == '\'') {
                // Assign a character literal enclosed in single quotes
                char_variables[tokens[1]] = tokens[3][1];
            } else if (is_number(tokens[3])) {
                // Convert numeric values to char (if in the ASCII range)
                int numeric_value = std::stoi(tokens[3]);
                if (numeric_value >= 0 && numeric_value <= 127) {
                    char_variables[tokens[1]] = static_cast<char>(numeric_value);
                } else {
                    throw std::runtime_error("Invalid numeric value for char variable: " + tokens[1]);
                }
            } else {
                char_variables[tokens[1]] = search_variable(tokens[3], char_variables);
            }
        } else if(flag == 1) {
            if (tokens[3].size() == 3 && tokens[3][0] == '\'' && tokens[3][2] == '\'') {
                // Assign a character literal enclosed in single quotes
                scope_char_variables[tokens[1]] = tokens[3][1];
            } else if (is_number(tokens[3])) {
                // Convert numeric values to char (if in the ASCII range)
                int numeric_value = std::stoi(tokens[3]);
                if (numeric_value >= 0 && numeric_value <= 127) {
                    scope_char_variables[tokens[1]] = static_cast<char>(numeric_value);
                } else {
                    throw std::runtime_error("Invalid numeric value for char variable: " + tokens[1]);
                }
            } else {
                scope_char_variables[tokens[1]] = search_variable(tokens[3], scope_char_variables);
            }
        }
        
    } else {
        throw std::runtime_error("error: xpected initializer before");
    }   
}

void Parser::float_variable_declaration(std::vector<std::string>& tokens, bool flag) {
    // tokens[tokens.size() - 1].pop_back();
    if(tokens.size() == 1) {
        throw std::runtime_error("Declaration does not declare anything!");
    } 
    check_variable_exists(tokens[1]);

    if(flag == 0) {
        if(tokens.size() == 2) {
            // float_map[tokens[1]] = dist(gen);
        } else if(tokens[2] == "=") {
            if(is_number(tokens[3])) {
                float_variables[tokens[1]] = std::stof(tokens[3]);
            } else {
                float_variables[tokens[1]] = search_variable(tokens[3], float_variables);
            }
        } else {
            throw std::runtime_error("error: xpected initializer before");
        }
    } else if(flag == 1) {
        if(tokens.size() == 2) {
            // scope_float_map[tokens[1]] = dist(gen);
        } else if(tokens[2] == "=") {
            if(is_number(tokens[3])) {
                scope_float_variables[tokens[1]] = std::stof(tokens[3]);
            } else {
                scope_float_variables[tokens[1]] = search_variable(tokens[3], scope_float_variables);
            }
        } else {
            throw std::runtime_error("error: xpected initializer before");
        }
    }
    
}

void Parser::double_variable_declaration(std::vector<std::string>& tokens, bool flag) {
    // lack_of_a_comma(line);
    // tokens[tokens.size() - 1].pop_back();
    if(tokens.size() == 1) {
        throw std::runtime_error("Declaration does not declare anything!");
    }
    check_variable_exists(tokens[1]);

    if(flag == 0) {
        if(tokens.size() == 2) {
            // double_map[tokens[1]] = dist(gen);
        } else if(tokens.size() == 4 && tokens[2] == "=") {
            if(is_number(tokens[3])) {
                double_variables[tokens[1]] = std::stod(tokens[3]);
            } else {
                double_variables[tokens[1]] = search_variable(tokens[3], double_variables);
            }
        } else {
            throw std::runtime_error("error: xpected initializer before");
        }
    } else if(flag == 1) {
        if(tokens.size() == 2) {
            // scope_double_map[tokens[1]] = dist(gen);
        } else if(tokens.size() == 4 && tokens[2] == "=") {
            if(is_number(tokens[3])) {
                scope_double_variables[tokens[1]] = std::stod(tokens[3]);
            } else {
                scope_double_variables[tokens[1]] = search_variable(tokens[3], scope_double_variables);
            }
        } else {
            throw std::runtime_error("error: xpected initializer before");
        }
    }
    
}

void Parser::bool_variable_declaration(std::vector<std::string>& tokens, bool flag) {
    if(tokens.size() == 1) {
        throw std::runtime_error("Declaration does not declare anything!");
    } 
    check_variable_exists(tokens[1]);

    if(flag == 0) {
        if (tokens.size() == 2) {
            // Initialize bool variables with a default value (e.g., false)
            bool_variables[tokens[1]] = false;
        } else if (tokens.size() == 4 && tokens[2] == "=") {
            if (is_number(tokens[3])) {
                // Convert numeric values to bool (0 = false, 1 = true)
                bool_variables[tokens[1]] = std::stoi(tokens[3]) != 0;
            } else if (tokens[3] == "true") {
                bool_variables[tokens[1]] = true;
            } else if (tokens[3] == "false") {
                bool_variables[tokens[1]] = false;
            } else {
                bool_variables[tokens[1]] = search_variable(tokens[3], bool_variables);
            }
        } else {
            throw std::runtime_error("error: xpected initializer before");
        }
    } else if(flag == 1) {
        if (tokens.size() == 2) {
            // Initialize bool variables with a default value (e.g., false)
            scope_bool_variables[tokens[1]] = false;
        } else if (tokens.size() == 4 && tokens[2] == "=") {
            if (is_number(tokens[3])) {
                // Convert numeric values to bool (0 = false, 1 = true)
                scope_bool_variables[tokens[1]] = std::stoi(tokens[3]) != 0;
            } else if (tokens[3] == "true") {
                scope_bool_variables[tokens[1]] = true;
            } else if (tokens[3] == "false") {
                scope_bool_variables[tokens[1]] = false;
            } else {
                scope_bool_variables[tokens[1]] = search_variable(tokens[3], scope_bool_variables);
            }
        } else {
            throw std::runtime_error("error: xpected initializer before");
        }
    }
}

void Parser::string_variable_declaration(std::vector<std::string>& tokens, bool flag) {
    if (tokens.size() < 2) {
        throw std::runtime_error("error: invalid syntax for string variable declaration");
    }

    std::string variable_name = tokens[1];
    name_verification(variable_name); // Assuming name_verification checks if the name is valid

    if(flag == 0) {
        if (tokens.size() == 2) {
            // Declaration without initialization
            string_variables[variable_name] = "";
        } else if (tokens.size() >= 4 && tokens[2] == "=") {
            // Declaration with initialization
            std::string value = "";

            for (size_t i = 3; i < tokens.size(); ++i) {
                std::string token = tokens[i];
                // Check and remove double quotes at the beginning and end
                if (!token.empty() && token.front() == '\"' && token.back() == '\"') {
                    token = token.substr(1, token.size() - 2);
                }
                value += (i > 3 ? " " : "") + token; // Add space between tokens, but not before the first one
            }

            value += '\n';
            string_variables[variable_name] = value;
        } else {
            throw std::runtime_error("error: invalid syntax for string variable declaration");
        }
    } else if(flag == 1) {
        if (tokens.size() == 2) {
            // Declaration without initialization
            scope_string_variables[variable_name] = "";
        } else if (tokens.size() >= 4 && tokens[2] == "=") {
            // Declaration with initialization
            std::string value = "";

            for (size_t i = 3; i < tokens.size(); ++i) {
                std::string token = tokens[i];
                // Check and remove double quotes at the beginning and end
                if (!token.empty() && token.front() == '\"' && token.back() == '\"') {
                    token = token.substr(1, token.size() - 2);
                }
                value += (i > 3 ? " " : "") + token; // Add space between tokens, but not before the first one
            }

            value += '\n';
            scope_string_variables[variable_name] = value;
        } else {
            throw std::runtime_error("error: invalid syntax for string variable declaration");
        }
    }
}