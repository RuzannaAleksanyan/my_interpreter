#ifndef PARSER
#define PARSER

#include <unordered_map>
#include <vector>
#include <map>
#include <string>
#include <exception>  
#include <stdexcept>
#include <iostream>
#include <variant>
// #include <boost/variant.hpp>

using variable_value = std::variant<int, bool, char, float, double, std::string>;

class Parser {
private:
    std::string m_filename;
    std::unordered_map<std::string, int> int_variables;
    std::unordered_map<std::string, bool> bool_variables;
    std::unordered_map<std::string, char> char_variables;
    std::unordered_map<std::string, float> float_variables;
    std::unordered_map<std::string, double> double_variables;
    std::unordered_map<std::string, std::string> string_variables;

    std::map<std::string, std::vector<int>> int_array;
    std::map<std::string, std::vector<char>> char_array;
    std::map<std::string, std::vector<float>> float_array;
    std::map<std::string, std::vector<double>> double_array;
    std::map<std::string, std::vector<bool>> bool_array;

    std::unordered_map<std::string, int> scope_int_variables;
    std::unordered_map<std::string, bool> scope_bool_variables;
    std::unordered_map<std::string, char> scope_char_variables;
    std::unordered_map<std::string, float> scope_float_variables;
    std::unordered_map<std::string, double> scope_double_variables;
    std::unordered_map<std::string, std::string> scope_string_variables;

    std::map<std::string, std::vector<int>> scope_int_array;
    std::map<std::string, std::vector<char>> scope_char_array;
    std::map<std::string, std::vector<float>> scope_float_array;
    std::map<std::string, std::vector<double>> scope_double_array;
    std::map<std::string, std::vector<bool>> scope_bool_array;

    std::vector<std::string> include_vector;
    std::map<int, std::string> line_map;

    std::unordered_map<int, std::pair<int, int>> if_map;
    std::unordered_map<int, std::pair<int, int>> while_map;

    std::string trim(const std::string& str) noexcept;
    
    bool has_ordered_brackets(const std::string& input) noexcept;
    std::string extract_content_in_brackets(const std::string& inputString) noexcept;
    std::string extract_string_before_bracket(const std::string& inputString) noexcept;
    bool is_number(const std::string& str) noexcept;
    void name_verification(const std::string& token);
    bool contains_if_condition(const std::string& line) noexcept;

    void clear_scope_maps();

    bool condition_check(std::vector<std::string>& tokens);

    std::vector<std::string> tokenize_line(const std::string& line) noexcept;

    void handle_variable_declaration(std::vector<std::string>& tokens, bool flag);

    void make_the_body(std::vector<std::string>& block_lines);

    bool perform_comparison(const std::string& op, const std::string& op1, const std::string& op2);

    template <typename T, typename F>
    bool perform_comparison(const std::string& op, const T& value1, const F& value2) {
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

    variable_value get_variable_value(const std::string& variable_name) {
        if (int_variables.find(variable_name) != int_variables.end()) {
            return int_variables[variable_name];
        } else if (bool_variables.find(variable_name) != bool_variables.end()) {
            return bool_variables[variable_name];
        } else if (char_variables.find(variable_name) != char_variables.end()) {
            return char_variables[variable_name];
        } else if (float_variables.find(variable_name) != float_variables.end()) {
            return float_variables[variable_name];
        } else if (double_variables.find(variable_name) != double_variables.end()) {
            return double_variables[variable_name];
        } else if (string_variables.find(variable_name) != string_variables.end()) {
            return string_variables[variable_name];
        } else {
            throw std::runtime_error("Variable not found: " + variable_name);
        }
    }


public:
    Parser(const std::string& filename);

    void print_int() noexcept;
    void print_char() noexcept;
    void print_float() noexcept;
    void print_double() noexcept;
    void print_bool() noexcept;
    void print_string() noexcept;
    void print_include() noexcept;

    void print_int_array() noexcept;
    void print_char_array() noexcept;
    void print_float_array() noexcept;
    void print_double_array() noexcept;
    void print_bool_array() noexcept;

    void print_scope_int() noexcept;

    void int_variable_declaration(std::vector<std::string>& tokens, bool flag);
    void char_variable_declaration(std::vector<std::string>& tokens, bool flag);
    void float_variable_declaration(std::vector<std::string>& tokens, bool flag);
    void double_variable_declaration(std::vector<std::string>& tokens, bool flag);
    void bool_variable_declaration(std::vector<std::string>& tokens, bool flag);
    void string_variable_declaration(std::vector<std::string>& tokens, bool flag);

    void int_array_declaration(std::vector<std::string>& tokens, bool flag);
    void char_array_declaration(std::vector<std::string>& tokens, bool flag);
    void float_array_declaration(std::vector<std::string>& tokens, bool flag);
    void double_array_declaration(std::vector<std::string>& tokens, bool flag);
    void bool_array_declaration(std::vector<std::string>& tokens, bool flag);

    void load_from_file();

    bool has_main_function(const std::string& code) noexcept;
    std::string remove_comments(const std::string& code);

    void parse();

    void lack_of_a_comma(std::string& line);

    void check_variable_exists(const std::string& variable_name);

    void cin_implementation(std::vector<std::string>& tokens);
    void cout_implementation(std::vector<std::string> tokens);

    template <typename T>
    T search_variable(const std::string& variable, const std::unordered_map<std::string, T>& map) {
        auto it = map.find(variable);
        if (it != map.end()) {
            return it->second;
        } else {
            throw std::runtime_error("Variable not found: " + variable);
        }
    }

    void compound_assignment_operator(const std::string& variable, 
                       const std::string& operand, 
                       const std::string& assignment);

    void arithmetic_operations(const std::string& variable, 
                       const std::string& operand1,
                       const std::string& operand2, 
                       const std::string& assignment);

    template <typename T>
    void arithmetic_operations_literal_operand(std::unordered_map<std::string, T>& variable_map,
                        const std::string& variable, 
                        int operand1,
                        const std::string& operand2, 
                        const std::string& assignment) {
        if(int_variables.find(operand2) != int_variables.end()) {
            arithmetic_operations_literal_operand_impl(variable_map, int_variables, variable, operand2, assignment, operand1);
        } else if(char_variables.find(operand2) != char_variables.end()) {
            arithmetic_operations_literal_operand_impl(variable_map, char_variables, variable, operand2, assignment, operand1);
        } else if(float_variables.find(operand2) != float_variables.end()) {
            arithmetic_operations_literal_operand_impl(variable_map, float_variables, variable, operand2, assignment, operand1);
        } else if(double_variables.find(operand2) != double_variables.end()) {
            arithmetic_operations_literal_operand_impl(variable_map, double_variables, variable, operand2, assignment, operand1);
        } else if(bool_variables.find(operand2) != bool_variables.end()) {
            arithmetic_operations_literal_operand_impl(variable_map, bool_variables, variable, operand2, assignment, operand1);
        } else if(is_number(operand2)) {
            // op1 and op2 literal
            int op2 = std::stoi(operand2);
            if(assignment == "+") {
                variable_map[variable] = operand1 + op2;
            } else if(assignment == "-") {
                variable_map[variable] = operand1 - op2;
            } else if(assignment == "*") {
                variable_map[variable] = operand1 * op2;
            } else if(assignment == "/") {
                variable_map[variable] = operand1 / op2;
            } else {
                throw std::runtime_error("Undefined arithmetic operation " + assignment);
            }
        }
    }

    template <typename T>
    void arithmetic_operations_impl(std::unordered_map<std::string, T>& variable_map,
                        const std::string& variable, 
                        const std::string& operand1,
                        const std::string& operand2, 
                        const std::string& assignment) noexcept {
        if(int_variables.find(operand1) != int_variables.end()) {
            arithmetic_operations_impl_impl(variable_map, int_variables, variable, operand1, operand2, assignment);
        } else if(char_variables.find(operand1) != char_variables.end()) {
            arithmetic_operations_impl_impl(variable_map, char_variables, variable, operand1, operand2, assignment);
        } else if(float_variables.find(operand1) != float_variables.end()) {
            arithmetic_operations_impl_impl(variable_map, float_variables, variable, operand1, operand2, assignment);
        } else if(double_variables.find(operand1) != double_variables.end()) {
            arithmetic_operations_impl_impl(variable_map, double_variables, variable, operand1, operand2, assignment);
        } else if(bool_variables.find(operand1) != bool_variables.end()) {
            arithmetic_operations_impl_impl(variable_map, bool_variables, variable, operand1, operand2, assignment);
        } else if(is_number(operand1)) {
            // op1 literal
            int op = std::stoi(operand1);
            arithmetic_operations_literal_operand(variable_map, variable, op, operand2, assignment);
        }
    }

    template <typename T, typename F>
    void arithmetic_operations_impl_impl(std::unordered_map<std::string, T>& variable_map,
                        std::unordered_map<std::string, F>& operand1_map,
                        const std::string& variable, 
                        const std::string& operand1,
                        const std::string& operand2, 
                        const std::string& assignment) noexcept {
        if(int_variables.find(operand2) != int_variables.end()) {
            arithmetic_operations_impl_imple_impl(variable_map, operand1_map, int_variables, variable, operand1, operand2, assignment);
        } else if(char_variables.find(operand2) != char_variables.end()) {
            arithmetic_operations_impl_imple_impl(variable_map, operand1_map, char_variables, variable, operand1, operand2, assignment);
        } else if(float_variables.find(operand2) != float_variables.end()) {
            arithmetic_operations_impl_imple_impl(variable_map, operand1_map, float_variables, variable, operand1, operand2, assignment);
        } else if(double_variables.find(operand2) != double_variables.end()) {
            arithmetic_operations_impl_imple_impl(variable_map, operand1_map, double_variables, variable, operand1, operand2, assignment);
        } else if(bool_variables.find(operand2) != bool_variables.end()) {
            arithmetic_operations_impl_imple_impl(variable_map, operand1_map, bool_variables, variable, operand1, operand2, assignment);
        } else if(is_number(operand2)) {
            // op2 literal
            int op = std::stoi(operand2);
            arithmetic_operations_literal_operand_impl(variable_map, operand1_map, variable, operand1, assignment, op);
        }
    }

    template <typename T, typename N, typename M>
    void arithmetic_operations_impl_imple_impl(std::unordered_map<std::string, T>& variable_map, 
                    std::unordered_map<std::string, N>& operand1_map,
                    std::unordered_map<std::string, M>& operand2_map,
                    const std::string& variable,
                    const std::string& operand1,
                    const std::string& operand2,
                    const std::string& assignment) {
        if (variable_map.find(variable) != variable_map.end() && operand1_map.find(operand1) != operand1_map.end() && operand2_map.find(operand2) != operand2_map.end()) {
            if(assignment == "+") {
                variable_map[variable] = operand1_map[operand1] + operand2_map[operand2];
            } else if(assignment == "-") {
                variable_map[variable] = operand1_map[operand1] - operand2_map[operand2];
            } else if(assignment == "*") {
                variable_map[variable] = operand1_map[operand1] * operand2_map[operand2];
            } else if(assignment == "/") {
                variable_map[variable] = operand1_map[operand1] / operand2_map[operand2];
            }
        } else {
            throw std::runtime_error("Undefined variable: " + variable );
        }
    }

    template <typename T, typename F>
    void arithmetic_operations_literal_operand_impl(std::unordered_map<std::string, T>& variable_map, 
                std::unordered_map<std::string, F>& operand_map,
                const std::string& variable,
                const std::string& operand,
                const std::string& assignment,
                int& literal ) {
        if(variable_map.find(variable) != variable_map.end() && operand_map.find(operand) != operand_map.end()) {
            if(assignment == "+") {
                variable_map[variable] = operand_map[operand] + literal;
            } else if(assignment == "-") {
                variable_map[variable] = operand_map[operand] - literal;
            } else if(assignment == "*") {
                variable_map[variable] = operand_map[operand] * literal;
            } else if(assignment == "/") {
                variable_map[variable] = operand_map[operand] / literal;
            }
        } else {
            throw std::runtime_error("Undefined variable: " + variable );
        }
    }

    template <typename T>
    std::unordered_map<std::string, T>& get_variable_map(const std::string& variable) {
        if (int_variables.find(variable) != int_variables.end()) {
            return int_variables;
        } else if (char_variables.find(variable) != char_variables.end()) {
            return char_variables;
        } else if (float_variables.find(variable) != float_variables.end()) {
            return float_variables;
        } else if (double_variables.find(variable) != double_variables.end()) {
            return double_variables;
        } else if (bool_variables.find(variable) != bool_variables.end()) {
            return bool_variables;
        } else {
            throw std::runtime_error("Undefined variable: " + variable);
        }
    }

};

#endif  // PARSER
