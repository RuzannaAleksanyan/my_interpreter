#include "parser.h"

#include <regex>

std::string Parser::extract_content_in_brackets(const std::string& inputString) {
    std::regex pattern(R"(\[(.*?)\])");
    std::smatch match;

    if (std::regex_search(inputString, match, pattern)) {
        return match[1].str();
    } else {
        return "";  // No valid content found between '[' and ']'
    }
}

std::string Parser::extract_string_before_bracket(const std::string& inputString) {
    size_t bracketPos = inputString.find('[');

    if (bracketPos != std::string::npos) {
        return inputString.substr(0, bracketPos);
    } else {
        // '[' not found in the string
        return inputString;
    }
}

void Parser::name_verification(const std::string& token) {
    for(const auto& arr : int_array) {
        if(arr.first == token) {
            throw std::runtime_error("error: conflicting declaration");
        }
    }

    for(const auto& arr : int_variables) {
        if(arr.first == token) {
            throw std::runtime_error("error: conflicting declaration");
        }
    }

    for(const auto& arr : char_array) {
        if(arr.first == token) {
            throw std::runtime_error("error: conflicting declaration");
        }
    }

    for(const auto& arr : char_variables) {
        if(arr.first == token) {
            throw std::runtime_error("error: conflicting declaration");
        }
    }

    for(const auto& arr : float_array) {
        if(arr.first == token) {
            throw std::runtime_error("error: conflicting declaration");
        }
    }

    for(const auto& arr : float_variables) {
        if(arr.first == token) {
            throw std::runtime_error("error: conflicting declaration");
        }
    }

    for(const auto& arr : double_array) {
        if(arr.first == token) {
            throw std::runtime_error("error: conflicting declaration");
        }
    }

    for(const auto& arr : double_variables) {
        if(arr.first == token) {
            throw std::runtime_error("error: conflicting declaration");
        }
    }

    for(const auto& arr : bool_array) {
        if(arr.first == token) {
            throw std::runtime_error("error: conflicting declaration");
        }
    }

    for(const auto& arr : bool_variables) {
        if(arr.first == token) {
            throw std::runtime_error("error: conflicting declaration");
        }
    }
}

void Parser::int_array_declaration(std::vector<std::string>& tokens) {
    std::string size = extract_content_in_brackets(tokens[1]);
    int value = 0;
    std::string array_name = extract_string_before_bracket(tokens[1]);
    
    name_verification(array_name);

    if(size.empty()) {
        throw std::runtime_error("error: storage size of '" + array_name + "' isn't known");
    }

    bool is_num = is_number(size);

    if(!is_num) {
        if(int_variables.find(size) != int_variables.end()) {
            value = int_variables[size];
        } else if(char_variables.find(size) != char_variables.end()) {
            value = char_variables[size];
        } else if(float_variables.find(size) != float_variables.end()) {
            value = float_variables[size];
        } else if(double_variables.find(size) != double_variables.end()) {
            value = double_variables[size];
        } else if(bool_variables.find(size) != bool_variables.end()) {
            value = bool_variables[size];
        } else {
            throw std::runtime_error("'" + size + "' was not declared in this scope");
        }
    }

    if(tokens.size() >= 4 && tokens[2] == "=" && tokens[3] == "{" && tokens[tokens.size() - 2] == "}") {
        
        for(int i = 4; i < tokens.size(); ++i) {
            if(tokens[i][tokens[i].size() - 1] == ',') {
                tokens[i].pop_back();
            }

            if(is_number(tokens[i])) {
                int_array[array_name].push_back(std::stoi(tokens[i]));
            } else if(tokens[i][0] == '\'' && tokens[i][tokens[i].size() - 1] == '\'') {
                tokens[i].pop_back();
                tokens[i] = tokens[i].substr(1, tokens[i].size() - 1);

                if(tokens[i].size() == 1 && tokens[i][0] != '}') {
                    int val = tokens[i][0];
                    int_array[array_name].push_back(val);
                } else {
                    throw std::runtime_error("error: invalid conversion");
                }
            }
        }
    } else if(tokens.size() == 2) {
        int_array[extract_string_before_bracket(tokens[1])];
    } else {
        throw std::runtime_error(" ");
    }
}

void Parser::char_array_declaration(std::vector<std::string>& tokens) {
    std::string size = extract_content_in_brackets(tokens[1]);
    int value = 0;
    std::string array_name = extract_string_before_bracket(tokens[1]);
    
    name_verification(array_name);

    if(size.empty()) {
        throw std::runtime_error("error: storage size of '" + array_name + "' isn't known");
    }

    bool is_num = is_number(size);

    if(!is_num) {
        if(int_variables.find(size) != int_variables.end()) {
            value = int_variables[size];
        } else if(char_variables.find(size) != char_variables.end()) {
            value = char_variables[size];
        } else if(float_variables.find(size) != float_variables.end()) {
            value = float_variables[size];
        } else if(double_variables.find(size) != double_variables.end()) {
            value = double_variables[size];
        } else if(bool_variables.find(size) != bool_variables.end()) {
            value = bool_variables[size];
        } else {
            throw std::runtime_error("'" + size + "' was not declared in this scope");
        }
    }

    if(tokens.size() >= 4 && tokens[2] == "=" && tokens[3] == "{" && tokens[tokens.size() - 2] == "}") {
        for(int i = 4; i < tokens.size() - 2; ++i) {
            if(tokens[i][tokens[i].size() - 1] == ',') {
                tokens[i].pop_back();
            }

            if(is_number(tokens[i])) {
                char_array[array_name].push_back(std::stoi(tokens[i]));
            } else if(tokens[i][0] == '\'' && tokens[i][tokens[i].size() - 1] == '\'') {
                tokens[i].pop_back();
                tokens[i] = tokens[i].substr(1, tokens[i].size() - 1);

                if(tokens[i].size() == 1 && tokens[i][0] != '}') {
                    char val = tokens[i][0];
                    char_array[array_name].push_back(val);
                } else {
                    throw std::runtime_error("error: invalid conversion");
                }
            } else {
                char_array[array_name].push_back(0);
            }
        }
    } else if(tokens.size() == 2) {
        char_array[extract_string_before_bracket(tokens[1])];
    } else {
        throw std::runtime_error(" ");
    }
}

void Parser::float_array_declaration(std::vector<std::string>& tokens) {
    std::string size = extract_content_in_brackets(tokens[1]);
    int value = 0;
    std::string array_name = extract_string_before_bracket(tokens[1]);
    
    name_verification(array_name);

    if(size.empty()) {
        throw std::runtime_error("error: storage size of '" + array_name + "' isn't known");
    }

    bool is_num = is_number(size);

    if(!is_num) {
        if(int_variables.find(size) != int_variables.end()) {
            value = int_variables[size];
        } else if(char_variables.find(size) != char_variables.end()) {
            value = char_variables[size];
        } else if(float_variables.find(size) != float_variables.end()) {
            value = float_variables[size];
        } else if(double_variables.find(size) != double_variables.end()) {
            value = double_variables[size];
        } else if(bool_variables.find(size) != bool_variables.end()) {
            value = bool_variables[size];
        } else {
            throw std::runtime_error("'" + size + "' was not declared in this scope");
        }
    }

    if(tokens.size() >= 4 && tokens[2] == "=" && tokens[3] == "{" && tokens[tokens.size() - 2] == "}") {
        
        for(int i = 4; i < tokens.size(); ++i) {
            if(tokens[i][tokens[i].size() - 1] == ',') {
                tokens[i].pop_back();
            }

            if(is_number(tokens[i])) {
                float_array[array_name].push_back(std::stof(tokens[i]));
            } else if(tokens[i][0] == '\'' && tokens[i][tokens[i].size() - 1] == '\'') {
                tokens[i].pop_back();
                tokens[i] = tokens[i].substr(1, tokens[i].size() - 1);

                if(tokens[i].size() == 1 && tokens[i][0] != '}') {
                    int val = tokens[i][0];
                    float_array[array_name].push_back(val);
                } else {
                    throw std::runtime_error("error: invalid conversion");
                }
            }
        }
    } else if(tokens.size() == 2) {
        float_array[extract_string_before_bracket(tokens[1])];
    } else {
        throw std::runtime_error(" ");
    }
}

void Parser::double_array_declaration(std::vector<std::string>& tokens) {
    std::string size = extract_content_in_brackets(tokens[1]);
    int value = 0;
    std::string array_name = extract_string_before_bracket(tokens[1]);
    
    name_verification(array_name);

    if(size.empty()) {
        throw std::runtime_error("error: storage size of '" + array_name + "' isn't known");
    }

    bool is_num = is_number(size);

    if(!is_num) {
        if(int_variables.find(size) != int_variables.end()) {
            value = int_variables[size];
        } else if(char_variables.find(size) != char_variables.end()) {
            value = char_variables[size];
        } else if(float_variables.find(size) != float_variables.end()) {
            value = float_variables[size];
        } else if(double_variables.find(size) != double_variables.end()) {
            value = double_variables[size];
        } else if(bool_variables.find(size) != bool_variables.end()) {
            value = bool_variables[size];
        } else {
            throw std::runtime_error("'" + size + "' was not declared in this scope");
        }
    }

    if(tokens.size() >= 4 && tokens[2] == "=" && tokens[3] == "{" && tokens[tokens.size() - 2] == "}") {
        
        for(int i = 4; i < tokens.size(); ++i) {
            if(tokens[i][tokens[i].size() - 1] == ',') {
                tokens[i].pop_back();
            }

            if(is_number(tokens[i])) {
                double_array[array_name].push_back(std::stod(tokens[i]));
            } else if(tokens[i][0] == '\'' && tokens[i][tokens[i].size() - 1] == '\'') {
                tokens[i].pop_back();
                tokens[i] = tokens[i].substr(1, tokens[i].size() - 1);

                if(tokens[i].size() == 1 && tokens[i][0] != '}') {
                    int val = tokens[i][0];
                    double_array[array_name].push_back(val);
                } else {
                    throw std::runtime_error("error: invalid conversion");
                }
            }
        }
    } else if(tokens.size() == 2) {
        double_array[extract_string_before_bracket(tokens[1])];
    } else {
        throw std::runtime_error(" ");
    }
}

void Parser::bool_array_declaration(std::vector<std::string>& tokens) {
    std::string size = extract_content_in_brackets(tokens[1]);
    int value = 0;
    std::string array_name = extract_string_before_bracket(tokens[1]);
    
    name_verification(array_name);

    if(size.empty()) {
        throw std::runtime_error("error: storage size of '" + array_name + "' isn't known");
    }

    bool is_num = is_number(size);

    if(!is_num) {
        if(int_variables.find(size) != int_variables.end()) {
            value = int_variables[size];
        } else if(char_variables.find(size) != char_variables.end()) {
            value = char_variables[size];
        } else if(float_variables.find(size) != float_variables.end()) {
            value = float_variables[size];
        } else if(double_variables.find(size) != double_variables.end()) {
            value = double_variables[size];
        } else if(bool_variables.find(size) != bool_variables.end()) {
            value = bool_variables[size];
        } else {
            throw std::runtime_error("'" + size + "' was not declared in this scope");
        }
    }

    if(tokens.size() >= 4 && tokens[2] == "=" && tokens[3] == "{" && tokens[tokens.size() - 2] == "}") {
        for(int i = 4; i < tokens.size() - 2; ++i) {
            if(tokens[i][tokens[i].size() - 1] == ',') {
                tokens[i].pop_back();
            }

            // Check for explicit 0/1 or false/true values
            if (tokens[i] == "0" || tokens[i] == "false") {
                bool_array[array_name].push_back(false);
            } else if (tokens[i] == "1" || tokens[i] == "true") {
                bool_array[array_name].push_back(true);
            } else {
                throw std::runtime_error("error: invalid boolean value '" + tokens[i] + "'");
            }
        }
    } else if(tokens.size() == 2) {
        bool_array[extract_string_before_bracket(tokens[1])];
    } else {
        throw std::runtime_error(" ");
    }
}