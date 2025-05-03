
# Mini C++ Interpreter 🖥️🚀

## Introduction 📚

The **Mini C++ Interpreter** is a lightweight and versatile interpreter designed to evaluate mathematical expressions, manage variables, and execute functions in a C++ environment. This tool simulates the behavior of a simple C++ interpreter, allowing users to assign variables, perform mathematical operations, and work with advanced functions like `sin`, `abs`, and `pow`. The interpreter also supports binary operations, history tracking, and variable management with the ability to clear and delete variables.

## Technologies & Coding Topics 💻🔧

- **C++**: Core language for implementing the interpreter and logic.
- **Data Structures**: Use of hash maps (`unordered_map`) to store variables.
- **Mathematical Functions**: Implemented mathematical operations like `abs`, `sin`, etc.
- **Regular Expressions**: Used to identify functions and variable assignments.
- **Error Handling**: Exception handling with `try-catch` blocks.
- **File Handling**: Saving variables to a file (`variables.txt`) for persistent storage.

## Features ✨

- **Basic Arithmetic Operations**: Support for addition (+), subtraction (-), multiplication (*), division (/).
- **Advanced Mathematical Functions**: 
  - `abs()`: Absolute value function
  - `sin()`: Sine function
  - `sqrt()`: Square root function
  - `pow()`: Exponentiation (currently squares the number)
  - `round()`: Rounding to the nearest integer.
- **Binary Operations**: Bitwise operations like `|` (OR) and `&` (AND).
- **Variable Assignment**: Assign values to variables using the `=` operator.
- **History Tracking**: Keep a history of executed statements.
- **Clear & Delete Variables**: Clear all variables or delete specific variables.
- **Save Variables**: Save all variables to a file (`variables.txt`) for future use.
- **Interactive REPL**: A Read-Eval-Print Loop (REPL) for interactive execution of code.
- **Error Handling**: Provides meaningful error messages for undefined variables, invalid operations, and more.

## How the Code Works ⚙️

### Lexer
The lexer is responsible for breaking down the input code into individual tokens, such as numbers, variables, operators, and functions.

### Parser
The parser takes these tokens and constructs an expression tree, evaluating the mathematical expressions and performing any required operations. It also handles variable assignments and function calls.

### REPL (Read-Eval-Print Loop)
The REPL prompts users for input, evaluates expressions, and outputs the results. It supports commands like `exit`, `clear`, `vars`, and `history`. The interpreter continues running until the `exit` command is given.

### Command Examples:
- **Variable Assignment**: `x = 9`
- **Arithmetic Operations**: `x + y`, `x - y`, `x * y`, `x / y`
- **Functions**: `abs(-9)`, `sin(0)`
- **History**: View the history of previous expressions by typing `history`.
- **Save Variables**: Save the current variables to a file using the `save` command.
- **Binary Operations**: `x | y`, `x & y`
- **Clear Variables**: Clear all variables using the `clear` command.
- **Delete Specific Variable**: `del x`

## How to Run the Code 🔨

To compile and run the Mini C++ Interpreter, follow these steps:

1. **Compile**: 
   ```bash
   g++ MiniInterpreter.cpp -o MiniInterpreter
   ```

2. **Run**:
   ```bash
   ./MiniInterpreter
   ```

   The REPL will start, and you can begin entering commands.

## Output 
  ```bash
  Mini C++ Interpreter. Type 'exit' to quit.
>>> x = 9
9
>>> -9
-9
>>> x + y
Error: Variable 'y' not defined.
>>> y = 9 
9
>>> x + y 
18
>>> abs(-9)
9
>>> save
Variables saved to 'variables.txt'.
>>> x | y 
9
>>> x & y
9
>>> x = 0 
0
>>> y = 1
1
>>> x & y
0
>>> sin(x)
0
>>> history
x = 9.000000
temp = -9.000000
y = 9.000000
temp = 18.000000
temp = 9.000000
temp = 9.000000
temp = 9.000000
x = 0.000000
y = 1.000000
temp = 0.000000
temp = 0.000000
>>> del x
Deleted variable: x
>>> vars 
y = 1
>>> clear
All variables cleared.

```

## Future Plans & Implementations 🚀

- **Additional Mathematical Functions**: Support for more mathematical functions such as `log`, `exp`, `tan`, etc.
- **Extended Error Handling**: Better error messages and improved handling of edge cases.
- **Functionality for Lists/Arrays**: Implement support for lists and arrays for more complex data handling.
- **Optimization**: Improve performance for large-scale calculations and variable management.
- **GUI Support**: Create a graphical user interface for a more user-friendly experience.

## Author ✨

**Bhuvaneswari Kapuluru** 👩‍💻

A passionate coder, constantly exploring new technologies and improving skills in various programming languages. This project demonstrates my skills in C++, data structures, and mathematical operations.

---

Feel free to contribute or provide suggestions to make this project even better!
