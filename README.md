# Interpreter From Scratch

#### CSCI-460 Programming Assignments Repository
This repository contains programming assignments for CSCI-460. Each assignment involves implementing components that will eventualy lead to a fully fledged interpreter for a c-style language.

## Assignments

### Programming Assignment 1: Ignore Comments
Develop a procedurally-driven deterministic finite state automaton (DFA) to identify and ignore comments in a C-like programming language. The program should correctly handle both single-line (`//`) and multi-line (`/* */`) comments.

### Programming Assignment 2: Tokenization
Using a C-like programming language grammar defined in Bacus-Naur Form (BNF), implement a tokenizer (lexical analyzer) that reads an input file and outputs the identified tokens.

### Programming Assignment 3: Recursive Descent Parser
Develop a recursive descent parser using a procedurally-driven DFA based on a BNF-defined grammar. The parser should generate a Concrete Syntax Tree (CST) representing the structure of the input program.

### Programming Assignment 4: Symbol Table
Implement a symbol table as a linked list to store defined variables (including their type and scope) and function/procedure names. The table should also store function parameter lists and return types, ensuring correct scoping.

### Programming Assignment 5: Abstract Syntax Tree
Extend the parser to generate an Abstract Syntax Tree (AST) from the CST. Boolean and numeric expressions should be converted to postfix notation using the Shunting Yard Algorithm.

### Programming Assignment 6: Interpreter
Develop an interpreter that executes programs written in the C-like language. The interpreter should track variables, values, and control flow while handling syntax and run-time errors.

---
## Usage
  - ./program [inputFile] [outputFile(for part 1)] [part]
  - [part] 0 = all
  - [part] 1 = ouput file with comments removed
  - [part] 2 = print token list
  - [part] 3 = print CST
  - [part] 4 = print Symbol Table

## How to run 
1. **Clone the Repository**

   Clone the repo using SSH and move into the project directory:
   ```bash
   git clone https://github.com/tragen-va/CSCI-460.git
   cd your-repo

2. **Build The project**

   Run this command in root directory:
   ```bash
   make
   
3. **Run The program**

   Ether run the test script(only for part 1 right now):
   ```bash
   ./test/testScript 
  

Or run the program with one of the test input files
   ```bash
   ./parser test/testFiles/programming_assignment_4-test_file_4.c out 4
  ```

### Test files 
    - sample input files /test/testFiles/programming_assignment{part}-test_file_{number}.c
    - sample ouput files can be found in test/solutionFiles/ and may be .c, .txt, or .pdf depeding on the part

