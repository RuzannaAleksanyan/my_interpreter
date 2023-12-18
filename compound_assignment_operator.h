#ifndef CAO
#define CAO

#include <unordered_map>
#include <string>

class Compound_Assignment_Operator {
public:
    template <typename T, typename F>
    void handle_plus_equal(std::unordered_map<std::string, T>& variable_map,
                            std::unordered_map<std::string, F>& operand_map, 
                            const std::string& variable, 
                            const std::string& operand) noexcept {
        if (variable_map.find(variable) != variable_map.end() && operand_map.find(operand) != operand_map.end()) {
            T& x = variable_map[variable]; 
            const T& y = operand_map[operand];

            x += y;
        } else {
            throw std::runtime_error("Undefined variable: " + variable + " or " + operand);
        }
    }

    template <typename T, typename F>
    void handle_minus_equal(std::unordered_map<std::string, T>& variable_map,
                            std::unordered_map<std::string, F>& operand_map, 
                            const std::string& variable, 
                            const std::string& operand) noexcept {
        if (variable_map.find(variable) != variable_map.end() && operand_map.find(operand) != operand_map.end()) {
            T& x = variable_map[variable];
            const T& y = operand_map[operand];

            x -= y;
        } else {
            throw std::runtime_error("Undefined variable: " + variable + " or " + operand);
        }
    }

    template <typename T, typename F>
    void handle_multiply_equal(std::unordered_map<std::string, T>& variable_map,
                            std::unordered_map<std::string, F>& operand_map, 
                            const std::string& variable, 
                            const std::string& operand) noexcept {
        if (variable_map.find(variable) != variable_map.end() && operand_map.find(operand) != operand_map.end()) {
            T& x = variable_map[variable];   
            const T& y = operand_map[operand];

            x *= y; 
        } else {
            throw std::runtime_error("Undefined variable: " + variable + " or " + operand);
        }
    }

    template <typename T, typename F>
    void handle_divide_equal(std::unordered_map<std::string, T>& variable_map,
                            std::unordered_map<std::string, F>& operand_map, 
                            const std::string& variable, 
                            const std::string& operand) noexcept {
        if (variable_map.find(variable) != variable_map.end() && operand_map.find(operand) != operand_map.end()) {
            T& x = variable_map[variable];
            const T& y = operand_map[operand];

            if (y == 0) {
                throw std::runtime_error("Division by 0");
            }
            x /= y;
        } else {
            throw std::runtime_error("Undefined variable: " + variable + " or " + operand);
        }
    }

    template <typename T, typename F>
    void handle_assignment(std::unordered_map<std::string, T>& variable_map,
                            std::unordered_map<std::string, F>& operand_map, 
                            const std::string& variable, 
                            const std::string& operand) noexcept {
        if (variable_map.find(variable) != variable_map.end() && operand_map.find(operand) != operand_map.end()) {
            T& x = variable_map[variable];
            const T& y = operand_map[operand]; 

            x = y;
        } else {
            throw std::runtime_error("Undefined variable: " + variable + " or " + operand);
        }
    }
    
    template <typename T, typename F>
    void compound_assignment_operator_impl(
            std::unordered_map<std::string, T>& variable_map,
            std::unordered_map<std::string, F>& operand_map,
            const std::string& variable,
            const std::string& operand,
            const std::string& assignment) noexcept {
        if (variable_map.find(variable) != variable_map.end() && operand_map.find(operand) != operand_map.end()) {
            if (assignment == "+=") {
                handle_plus_equal<T>(variable_map, operand_map, variable, operand);
            } else if (assignment == "-=") {
                handle_minus_equal<T>(variable_map, operand_map, variable, operand);
            } else if (assignment == "*=") {
                handle_multiply_equal<T>(variable_map, operand_map, variable, operand);
            } else if (assignment == "/=") {
                handle_divide_equal<T>(variable_map, operand_map, variable, operand);
            } else if (assignment == "=") {
                handle_assignment<T>(variable_map, operand_map, variable, operand);
            }
        } else {
            throw std::runtime_error("Undefined variable: " + variable + " or " + operand);
        }
    }

    template <typename T>
    void compound_assignment_operator_impl_literal(
                            std::unordered_map<std::string, T>& variable_map, 
                            const std::string& variable, 
                            const std::string& assignment,
                            T& operand) noexcept {
        if(assignment == "+=") {
            variable_map[variable] += operand;
        } else if(assignment == "-=") {
            variable_map[variable] -= operand;
        } else if(assignment == "*=") {
            variable_map[variable] *= operand;
        } else if(assignment == "/=") {
            variable_map[variable] /= operand;
        } else if(assignment == "=") {
            variable_map[variable] = operand;
        }
    }
};

#endif  // CAO