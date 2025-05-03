#include <iostream>
#include <string>
#include <unordered_map>
#include <sstream>
#include <cctype>
#include <stdexcept>
#include <vector>
#include <regex>
#include <cmath>
#include <fstream>

// Global map to store variable names and their values
std::unordered_map<std::string, double> variables;
std::vector<std::string> history;  // Store the history of executed commands

enum class TokenType {
    NUMBER, IDENTIFIER, ASSIGN, OPERATOR, KEYWORD, FUNCTION, END, UNKNOWN
};

struct Token {
    TokenType type;
    std::string value;
    double number_value;

    Token(TokenType t, std::string v = "", double n = 0.0) : type(t), value(v), number_value(n) {}
};

class Lexer {
public:
    Lexer(const std::string& input) : input(input), current_index(0) {}

    Token getNextToken() {
        skipWhitespace();

        if (current_index >= input.length()) {
            return Token(TokenType::END);
        }

        char current_char = input[current_index];

        if (std::isdigit(current_char) || current_char == '.' || current_char == '-') {
            return number();
        }

        if (std::isalpha(current_char)) {
            return identifierOrKeyword();
        }

        if (current_char == '=') {
            current_index++;
            return Token(TokenType::ASSIGN, "=");
        }

        if (current_char == '(' || current_char == ')') {
            current_index++;
            return Token(TokenType::OPERATOR, std::string(1, current_char));
        }

        if (current_char == '+' || current_char == '-' || current_char == '*' || current_char == '/' ||
            current_char == '&' || current_char == '|' || current_char == '^') {
            current_index++;
            return Token(TokenType::OPERATOR, std::string(1, current_char));
        }

        return Token(TokenType::UNKNOWN);
    }

private:
    std::string input;
    size_t current_index;

    void skipWhitespace() {
        while (current_index < input.length() && std::isspace(input[current_index])) {
            current_index++;
        }
    }

    Token number() {
        size_t start = current_index;
        bool negative = false;

        if (input[current_index] == '-') {
            negative = true;
            current_index++;
        }

        while (current_index < input.length() && (std::isdigit(input[current_index]) || input[current_index] == '.')) {
            current_index++;
        }

        std::string num_str = input.substr(start, current_index - start);
        double num = std::stod(num_str);
        return Token(TokenType::NUMBER, num_str, num);
    }

    Token identifierOrKeyword() {
        size_t start = current_index;
        while (current_index < input.length() && (std::isalnum(input[current_index]) || input[current_index] == '_')) {
            current_index++;
        }

        std::string identifier = input.substr(start, current_index - start);

        if (identifier == "abs" || identifier == "sqrt" || identifier == "pow" || identifier == "round" ||
            identifier == "sin" || identifier == "cos") {
            return Token(TokenType::FUNCTION, identifier);
        }

        return Token(TokenType::IDENTIFIER, identifier);
    }
};

class Parser {
public:
    Parser(Lexer& lexer) : lexer(lexer), current_token(lexer.getNextToken()) {}

    double parse() {
        if (current_token.type == TokenType::IDENTIFIER && peekNextToken().type == TokenType::ASSIGN) {
            return assignment();
        }
        return expression();
    }

private:
    Lexer& lexer;
    Token current_token;

    void advance() {
        current_token = lexer.getNextToken();
    }

    Token peekNextToken() {
        Lexer temp_lexer = lexer;
        return temp_lexer.getNextToken();
    }

    double expression() {
        double result = term();

        while (current_token.type == TokenType::OPERATOR && (current_token.value == "+" || current_token.value == "-")) {
            char op = current_token.value[0];
            advance();
            double rhs = term();
            if (op == '+') result += rhs;
            else result -= rhs;
        }

        return result;
    }

    double term() {
        double result = factor();

        while (current_token.type == TokenType::OPERATOR && (current_token.value == "*" || current_token.value == "/")) {
            char op = current_token.value[0];
            advance();
            double rhs = factor();
            if (op == '*') result *= rhs;
            else result /= rhs;
        }

        return result;
    }

    double factor() {
        if (current_token.type == TokenType::OPERATOR && current_token.value == "-") {
            advance();
            return -factor();
        }

        if (current_token.type == TokenType::NUMBER) {
            double value = current_token.number_value;
            advance();
            return value;
        }

        if (current_token.type == TokenType::IDENTIFIER) {
            std::string var_name = current_token.value;
            if (variables.find(var_name) != variables.end()) {
                advance();
                return variables[var_name];
            } else {
                throw std::runtime_error("Variable '" + var_name + "' not defined.");
            }
        }

        if (current_token.type == TokenType::FUNCTION) {
            std::string func_name = current_token.value;
            advance();
            if (current_token.value != "(") {
                throw std::runtime_error("Expected '(' after function name.");
            }
            advance();
            double arg = expression();
            if (current_token.value != ")") {
                throw std::runtime_error("Mismatched parenthesis.");
            }
            advance();
            return callFunction(func_name, arg);
        }

        if (current_token.value == "(") {
            advance();
            double val = expression();
            if (current_token.value != ")") {
                throw std::runtime_error("Mismatched parenthesis.");
            }
            advance();
            return val;
        }

        throw std::runtime_error("Invalid expression.");
    }

    double callFunction(const std::string& func_name, double value) {
        if (func_name == "abs") return std::abs(value);
        if (func_name == "sqrt") return std::sqrt(value);
        if (func_name == "round") return std::round(value);
        if (func_name == "sin") return std::sin(value);
        if (func_name == "cos") return std::cos(value);
        if (func_name == "pow") return std::pow(value, 2);  // Placeholder: default square

        throw std::runtime_error("Unknown function: " + func_name);
    }

    double assignment() {
        std::string var_name = current_token.value;
        advance(); // variable
        advance(); // '='
        double value = expression();
        variables[var_name] = value;
        history.push_back(var_name + " = " + std::to_string(value));  // Store assignment in history
        return value;
    }
};

void saveVariablesToFile() {
    std::ofstream file("variables.txt");
    for (const auto& v : variables) {
        file << v.first << " = " << v.second << "\n";
    }
    std::cout << "Variables saved to 'variables.txt'.\n";
}

void loadVariablesFromFile() {
    std::ifstream file("variables.txt");
    std::string line;
    while (std::getline(file, line)) {
        size_t equal_pos = line.find("=");
        if (equal_pos != std::string::npos) {
            std::string var_name = line.substr(0, equal_pos);
            double value = std::stod(line.substr(equal_pos + 1));
            variables[var_name] = value;
        }
    }
    std::cout << "Variables loaded from 'variables.txt'.\n";
}

void showHelp() {
    std::cout << "Commands:\n";
    std::cout << "  exit         - Exit the interpreter\n";
    std::cout << "  clear        - Clear all variables\n";
    std::cout << "  vars         - Show all variables\n";
    std::cout << "  del <var>    - Delete a variable\n";
    std::cout << "  history      - Show command history\n";
    std::cout << "  save         - Save variables to 'variables.txt'\n";
    std::cout << "  load         - Load variables from 'variables.txt'\n";
    std::cout << "  help         - Show this help\n";
}

void repl() {
    std::cout << "Mini C++ Interpreter. Type 'exit' to quit.\n";
    std::string line;
    while (true) {
        std::cout << ">>> ";
        std::getline(std::cin, line);

        if (line == "exit") break;
        if (line == "clear") {
            variables.clear();
            std::cout << "All variables cleared.\n";
            continue;
        }
        if (line == "vars") {
            for (const auto& v : variables) {
                if (v.first != "temp") {
                    std::cout << v.first << " = " << v.second << "\n";
                }
            }
            continue;
        }
        if (line.rfind("del ", 0) == 0) {
            std::string var_to_delete = line.substr(4);
            if (variables.erase(var_to_delete)) {
                std::cout << "Deleted variable: " << var_to_delete << "\n";
            } else {
                std::cout << "Variable '" << var_to_delete << "' not found.\n";
            }
            continue;
        }
        if (line == "history") {
            for (const auto& cmd : history) {
                std::cout << cmd << "\n";
            }
            continue;
        }
        if (line == "help") {
            showHelp();
            continue;
        }
        if (line == "save") {
            saveVariablesToFile();
            continue;
        }
        if (line == "load") {
            loadVariablesFromFile();
            continue;
        }

        // For simple expressions without '=', use temp assignment
        if (line.find('=') == std::string::npos) {
            line = "temp = " + line;
        }

        Lexer lexer(line);
        Parser parser(lexer);
        try {
            double result = parser.parse();
            std::cout << result << std::endl;
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }
}

int main() {
    repl();
    return 0;
}
