
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <unistd.h>


#include "Token.h"

#include "part_2_functions.h"



/*
* Takes input file with commens removed and breakes down into tokens
* Returns pointer to head node, or nullptr if error
*/
Token* tokenize(char* inFileName) {        


    

    //- initilize and check files
    std::ifstream inFile(inFileName);
    if (!inFile) {
        std::cerr << "Unable to open: " << inFileName << std::endl;
        return nullptr;
    } 

    int lineNum = 1;
    char ch;
    std::string currToken;
    TOKEN currState = BASE;
    Token* head = new Token(BASE, lineNum, currToken);
    Token* curr = head;
    while (inFile.get(ch)) {
        

        switch(currState) {




        case BASE:   // 0
            switch(ch) {
            case '\"':
                currState = DOUBLE_QUOTE;
                currToken += ch;
                break;  
            case '\'':                              
                currState = SINGLE_QUOTE;
                currToken += ch;
                break;  
            case '(': // 3
                currState = BASE;
                currToken += ch;
                {
                Token* tok = new Token(L_PAREN, lineNum, currToken);
                curr->setNext(tok);
                curr = tok;
                }
                currToken.erase();
                break;  
            case ')': // 4
                currState = BASE;
                currToken += ch;
                {
                Token* tok = new Token(R_PAREN, lineNum, currToken);
                curr->setNext(tok);
                curr = tok;
                }
                currToken.erase();
                break;  
            case '{': // 5
                currState = BASE;
                currToken += ch;
                {
                Token* tok = new Token(L_BRACE, lineNum, currToken);
                curr->setNext(tok);
                curr = tok;
                }
                currToken.erase();
                break;  
            case '}': // 6
                currState = BASE;
                currToken += ch;
                {
                Token* tok = new Token(R_BRACE, lineNum, currToken);
                curr->setNext(tok);
                curr = tok;
                }
                currToken.erase();
                break;  
            case '[': // 7
                currState = BASE;
                currToken += ch;
                {
                Token* tok = new Token(L_BRACKET, lineNum, currToken);
                curr->setNext(tok);
                curr = tok;
                }
                currToken.erase();
                break;  
            case ']': // 8
                currState = BASE;
                currToken += ch;
                {
                Token* tok = new Token(R_BRACKET, lineNum, currToken);
                curr->setNext(tok);
                curr = tok;
                }
                currToken.erase();
                break;  
            case ';': // 9
                currState = BASE;
                currToken += ch;
                {
                Token* tok = new Token(SEMICOLON, lineNum, currToken);
                curr->setNext(tok);
                curr = tok;
                }
                currToken.erase();
                break;  
            case '=': // 10
                currState = ASSIGNMENT_OPERATOR;
                currToken += ch;
                break; 
            case '%': // 11
                currState = BASE;
                currToken += ch;
                {
                Token* tok = new Token(MODULO, lineNum, currToken);
                curr->setNext(tok);
                curr = tok;
                }
                currToken.erase();
                break;  
            case '*': // 12
                currState = BASE;
                currToken += ch;
                {
                Token* tok = new Token(ASTERISK, lineNum, currToken);
                curr->setNext(tok);
                curr = tok;
                }
                currToken.erase();
                break;  
            case '+': // 13
                currState = BASE;
                currToken += ch;
                {
                Token* tok = new Token(PLUS, lineNum, currToken);
                curr->setNext(tok);
                curr = tok;
                }
                currToken.erase();
                break;  
            case '-': // 14
                currState = MINUS;
                currToken += ch;
                break;
            case '/': // 15
                currState = BASE;
                currToken += ch;
                {
                Token* tok = new Token(DIVIDE, lineNum, currToken);
                curr->setNext(tok);
                curr = tok;
                }
                currToken.erase();
                break;  
            case '^': // 16
                currState = BASE;
                currToken += ch;
                {
                Token* tok = new Token(CARET, lineNum, currToken);
                curr->setNext(tok);
                curr = tok;
                }
                currToken.erase();
                break;  
            case '<': // 17
                currState = LT;
                currToken += ch;
                break;  
            case '>': // 18
                currState = GT;
                currToken += ch;
                break;  
            case '&': // 21
                currState = BOOLEAN_AND;
                currToken += ch;
                break;  
            case '|': // 22
                currState = BOOLEAN_OR;
                currToken += ch;
                break;  
            case '!': //23
                currState = BOOLEAN_NOT;
                currToken += ch;
                break;
            case 'T': //25
                currState = BOOLEAN_TRUE;
                currToken += ch;
                break;
            case 'F': //26
                currState = BOOLEAN_FALSE;
                currToken += ch;
                break;
            case 'a': //27
                currState = IDENTIFIER;
                currToken += ch;
                break;
            case 'b': //27
                currState = IDENTIFIER;
                currToken += ch;
                break;
            case 'c': //27
                currState = IDENTIFIER;
                currToken += ch;
                break;
            case 'd': //27
                currState = IDENTIFIER;
                currToken += ch;
                break;
            case 'e': //27
                currState = IDENTIFIER;
                currToken += ch;
                break;
            case 'g': //27
                currState = IDENTIFIER;
                currToken += ch;
                break;
            case 'h': //27
                currState = IDENTIFIER;
                currToken += ch;
                break;
            case 'i': //27
                currState = IDENTIFIER;
                currToken += ch;
                break;
            case 'j': //27
                currState = IDENTIFIER;
                currToken += ch;
                break;
            case 'k': //27
                currState = IDENTIFIER;
                currToken += ch;
                break;
            case 'l': //27
                currState = IDENTIFIER;
                currToken += ch;
                break;
            case 'm': //27
                currState = IDENTIFIER;
                currToken += ch;
                break;
            case 'n': //27
                currState = IDENTIFIER;
                currToken += ch;
                break;
            case 'o': //27
                currState = IDENTIFIER;
                currToken += ch;
                break;
            case 'p': //27
                currState = IDENTIFIER;
                currToken += ch;
                break;
            case 'q': //27
                currState = IDENTIFIER;
                currToken += ch;
                break;
            case 'r': //27
                currState = IDENTIFIER;
                currToken += ch;
                break;
            case 's': //27
                currState = IDENTIFIER;
                currToken += ch;
                break;
            case 'u': //27
                currState = IDENTIFIER;
                currToken += ch;
                break;
            case 'v': //27
                currState = IDENTIFIER;
                currToken += ch;
                break;
            case 'w': //27
                currState = IDENTIFIER;
                currToken += ch;
                break;
            case 'x': //27
                currState = IDENTIFIER;
                currToken += ch;
                break;
            case 'y': //27
                currState = IDENTIFIER;
                currToken += ch;
                break;
            case 'z': //27
                currState = IDENTIFIER;
                currToken += ch;
                break;
            case 't': //25
                currState = IDENTIFIER;
                currToken += ch;
                break;
            case 'f': //26
                currState = IDENTIFIER;
                currToken += ch;
                break;
            case 'A': //27
                currState = IDENTIFIER;
                currToken += ch;
                break;
            case 'B': //27
                currState = IDENTIFIER;
                currToken += ch;
                break;
            case 'C': //27
                currState = IDENTIFIER;
                currToken += ch;
                break;
            case 'D': //27
                currState = IDENTIFIER;
                currToken += ch;
                break;
            case 'E': //27
                currState = IDENTIFIER;
                currToken += ch;
                break;
            case 'G': //27
                currState = IDENTIFIER;
                currToken += ch;
                break;
            case 'H': //27
                currState = IDENTIFIER;
                currToken += ch;
                break;
            case 'I': //27
                currState = IDENTIFIER;
                currToken += ch;
                break;
            case 'J': //27
                currState = IDENTIFIER;
                currToken += ch;
                break;
            case 'K': //27
                currState = IDENTIFIER;
                currToken += ch;
                break;
            case 'L': //27 
                currState = IDENTIFIER;
                currToken += ch;
                break;
            case 'M': //27
                currState = IDENTIFIER;
                currToken += ch;
                break;
            case 'N': //27
                currState = IDENTIFIER;
                currToken += ch;
                break;
            case 'O': //27
                currState = IDENTIFIER;
                currToken += ch;
                break;
            case 'P': //27
                currState = IDENTIFIER;
                currToken += ch;
                break;
            case 'Q': //27
                currState = IDENTIFIER;
                currToken += ch;
                break;
            case 'R': //27
                currState = IDENTIFIER;
                currToken += ch;
                break;
            case 'S': //27
                currState = IDENTIFIER;
                currToken += ch;
                break;
            case 'U': //27
                currState = IDENTIFIER;
                currToken += ch;
                break;
            case 'V': //27
                currState = IDENTIFIER;
                currToken += ch;
                break;
            case 'W': //27
                currState = IDENTIFIER;
                currToken += ch;
                break;
            case 'X': //27
                currState = IDENTIFIER;
                currToken += ch;
                break;
            case 'Y': //27
                currState = IDENTIFIER;
                currToken += ch;
                break;
            case 'Z': //27
                currState = IDENTIFIER;
                currToken += ch;
                break;
            case '\n':
                lineNum += 1;
                break;
            case ',':
                currState = BASE;
                currToken += ch;
                {
                Token* tok = new Token(COMMA, lineNum, currToken);
                curr->setNext(tok);
                curr = tok;
                }
                currToken.erase();
                break;  
            case '0': 
                currState = INTEGER;
                currToken += ch;
                break;
            case '1': 
                currState = INTEGER;
                currToken += ch;
                break;
            case '2': 
                currState = INTEGER;
                currToken += ch;
                break;
            case '3': 
                currState = INTEGER;
                currToken += ch;
                break;
            case '4': 
                currState = INTEGER;
                currToken += ch;
                break;
            case '5': 
                currState = INTEGER;
                currToken += ch;
                break;
            case '6': 
                currState = INTEGER;
                currToken += ch;
                break;
            case '7': 
                currState = INTEGER;
                currToken += ch;
                break;
            case '8': 
                currState = INTEGER;
                currToken += ch;

            case '9': 
                currState = INTEGER;
                currToken += ch;
                break;
            case ' ':
                break;
            default:
                std::cerr << "[-] Error Un-Recognized symbol, line: " << lineNum << std::endl;
                return nullptr;
            }
            break;





        case DOUBLE_QUOTE:   // 1
            switch(ch) {

            case '"': // ""
                {
                Token* tok = new Token(DOUBLE_QUOTE, lineNum, currToken);
                curr->setNext(tok);
                curr = tok;
                }
                {
                Token* tok = new Token(DOUBLE_QUOTE, lineNum, currToken);
                curr->setNext(tok);
                curr = tok;
                }
                currState = BASE;
                currToken.erase();
            default:
                currState = DOUBLE_QUOTED_STRING;
                {
                Token* tok = new Token(DOUBLE_QUOTE, lineNum, currToken);
                curr->setNext(tok);
                curr = tok;
                }
                currToken.erase();
                currToken += ch;
            }
             break;


        






        case SINGLE_QUOTE:                   // 2
            switch(ch) {

            case '\'': // ''
                {
                Token* tok = new Token(SINGLE_QUOTE, lineNum, currToken);
                curr->setNext(tok);
                curr = tok;
                }
                {
                Token* tok = new Token(SINGLE_QUOTE, lineNum, currToken);
                curr->setNext(tok);
                curr = tok;
                }
                currState = BASE;
                currToken.erase();
            default:
                currState = SINGLE_QUOTED_STRING;
                {
                Token* tok = new Token(SINGLE_QUOTE, lineNum, currToken);
                curr->setNext(tok);
                curr = tok;
                }
                currToken.erase();
                currToken += ch;
            }
             break;





        case BOOLEAN_NOT:
            switch(ch) {
            case '=':
                // boolean not equal
                currToken += ch;
                {
                Token* tok = new Token(BOOLEAN_NOT_EQUAL, lineNum, currToken);
                curr->setNext(tok);
                curr = tok;
                }
                currToken.erase();
                currState = BASE;
                break;
            default:
                // boolean not    
                {
                Token* tok = new Token(BOOLEAN_NOT, lineNum, currToken);
                curr->setNext(tok);
                curr = tok; 
                }
                currToken.erase();
                currToken += ch;
                currState = BASE;
                
            }
            break;





        case ASSIGNMENT_OPERATOR:               // 10
            switch(ch) {
            case ' ':   // " = "
                currState = BASE;
                {
                Token* tok = new Token(ASSIGNMENT_OPERATOR, lineNum, currToken);
                curr->setNext(tok);
                curr = tok;
                }
                currToken.erase();
                break;  
            case '=':   // " == "
                currToken += ch;
                {
                Token* tok = new Token(BOOLEAN_EQUAL, lineNum, currToken);
                curr->setNext(tok);
                curr = tok;
                }
                currToken.erase();
                currState = BASE;
                break;  
            case '\n':   // " = "
                lineNum += 1;
                currState = BASE;
                {
                Token* tok = new Token(ASSIGNMENT_OPERATOR, lineNum, currToken);
                curr->setNext(tok);
                curr = tok;
                }
                currToken.erase();
                break;  
            case '-':       
                {
                Token* tok = new Token(ASSIGNMENT_OPERATOR, lineNum, currToken);
                curr->setNext(tok);
                curr = tok;
                }
                currToken.erase();
                currState = MINUS;
                currToken += ch;
                break;
            case '0':
                {
                Token* tok = new Token(ASSIGNMENT_OPERATOR, lineNum, currToken);
                curr->setNext(tok);
                curr = tok;
                }
                currToken.erase();
                currState = INTEGER;
                currToken += ch;
                break;
            case '1':
                {
                Token* tok = new Token(ASSIGNMENT_OPERATOR, lineNum, currToken);
                curr->setNext(tok);
                curr = tok;
                }
                currToken.erase();
                currState = INTEGER;
                currToken += ch;
                break;
            case '2':
                {
                Token* tok = new Token(ASSIGNMENT_OPERATOR, lineNum, currToken);
                curr->setNext(tok);
                curr = tok;
                }
                currToken.erase();
                currState = INTEGER;
                currToken += ch;
                break;
            case '3':
                {
                Token* tok = new Token(ASSIGNMENT_OPERATOR, lineNum, currToken);
                curr->setNext(tok);
                curr = tok;
                }
                currToken.erase();
                currState = INTEGER;
                currToken += ch;
                break;
            case '4':
                {
                Token* tok = new Token(ASSIGNMENT_OPERATOR, lineNum, currToken);
                curr->setNext(tok);
                curr = tok;
                }
                currToken.erase();
                currState = INTEGER;
                currToken += ch;
                break;
            case '5':
                {
                Token* tok = new Token(ASSIGNMENT_OPERATOR, lineNum, currToken);
                curr->setNext(tok);
                curr = tok;
                }
                currToken.erase();
                currState = INTEGER;
                currToken += ch;
                break;
            case '6':
                {
                Token* tok = new Token(ASSIGNMENT_OPERATOR, lineNum, currToken);
                curr->setNext(tok);
                curr = tok;
                }
                currToken.erase();
                currState = INTEGER;
                currToken += ch;
                break;
            case '7':
                {
                Token* tok = new Token(ASSIGNMENT_OPERATOR, lineNum, currToken);
                curr->setNext(tok);
                curr = tok;
                }
                currToken.erase();
                currState = INTEGER;
                currToken += ch;
                break;
            case '8':
                {
                Token* tok = new Token(ASSIGNMENT_OPERATOR, lineNum, currToken);
                curr->setNext(tok);
                curr = tok;
                }
                currToken.erase();
                currState = INTEGER;
                currToken += ch;
                break;
            case '9':
                {
                Token* tok = new Token(ASSIGNMENT_OPERATOR, lineNum, currToken);
                curr->setNext(tok);
                curr = tok;
                }
                currToken.erase();
                currState = INTEGER;
                currToken += ch;
                break;
            case 't':
                {
                Token* tok = new Token(BOOLEAN_TRUE, lineNum, currToken);
                curr->setNext(tok);
                curr = tok;
                }
                currToken.erase();
                currState = INTEGER;
                currToken += ch;
                break;
            case 'f':
                {
                Token* tok = new Token(BOOLEAN_FALSE, lineNum, currToken);
                curr->setNext(tok);
                curr = tok;
                }
                currToken.erase();
                currState = INTEGER;
                currToken += ch;
                break;
            default:
                std::cerr << "[-] Error Un-Recognized Symbol: " << ch << ".  Line: " << lineNum << std::endl;   
                return nullptr;
            }
            break;






        case LT:               // 17
            switch(ch) {
            case ' ':   // " LT "
                {
                Token* tok = new Token(currState, lineNum, currToken);
                curr->setNext(tok);
                curr = tok;
                }
                currToken.erase();
                currState = BASE;
                break;  
            case '\n':   
                lineNum += 1;
                currState = BASE;
                {
                Token* tok = new Token(currState, lineNum, currToken);
                curr->setNext(tok);
                curr = tok;
                }
                currToken.erase();
                break;  
            case '=':
                currToken += ch;
                {
                Token* tok = new Token(LT_EQUAL, lineNum, currToken);
                curr->setNext(tok);
                curr = tok;
                }
                currToken.erase();
                currState = BASE;
                break;
            case '0':
                {
                Token* tok = new Token(currState, lineNum, currToken);
                curr->setNext(tok);
                curr = tok;
                }
                currToken.erase();
                currState = INTEGER;
                currToken += ch;
                break;
            case '1':
                {
                Token* tok = new Token(currState, lineNum, currToken);
                curr->setNext(tok);
                curr = tok;
                }
                currToken.erase();
                currState = INTEGER;
                currToken += ch;
                break;
            case '2':
                {
                Token* tok = new Token(currState, lineNum, currToken);
                curr->setNext(tok);
                curr = tok;
                }
                currToken.erase();
                currState = INTEGER;
                currToken += ch;
                break;
            case '3':
                {
                Token* tok = new Token(currState, lineNum, currToken);
                curr->setNext(tok);
                curr = tok;
                }
                currToken.erase();
                currState = INTEGER;
                currToken += ch;
                break;
            case '4':
                {
                Token* tok = new Token(currState, lineNum, currToken);
                curr->setNext(tok);
                curr = tok;
                }
                currToken.erase();
                currState = INTEGER;
                currToken += ch;
                break;
            case '5':
                {
                Token* tok = new Token(currState, lineNum, currToken);
                curr->setNext(tok);
                curr = tok;
                }
                currToken.erase();
                currState = INTEGER;
                currToken += ch;
                break;
            case '6':
                {
                Token* tok = new Token(currState, lineNum, currToken);
                curr->setNext(tok);
                curr = tok;
                }
                currToken.erase();
                currState = INTEGER;
                currToken += ch;
                break;
            case '7':
                {
                Token* tok = new Token(currState, lineNum, currToken);
                curr->setNext(tok);
                curr = tok;
                }
                currToken.erase();
                currState = INTEGER;
                currToken += ch;
                break;
            case '8':
                {
                Token* tok = new Token(currState, lineNum, currToken);
                curr->setNext(tok);
                curr = tok;
                }
                currToken.erase();
                currState = INTEGER;
                currToken += ch;
                break;
            case '9':
                {
                Token* tok = new Token(currState, lineNum, currToken);
                curr->setNext(tok);
                curr = tok;
                }
                currToken.erase();
                currState = INTEGER;
                currToken += ch;
                break;
            case 'T':
                {
                Token* tok = new Token(currState, lineNum, currToken);
                curr->setNext(tok);
                curr = tok;
                }
                currToken.erase();
                currState = INTEGER;
                currToken += ch;
                break;
            case 'F':
                {
                Token* tok = new Token(currState, lineNum, currToken);
                curr->setNext(tok);
                curr = tok;
                }
                currToken.erase();
                currState = INTEGER;
                currToken += ch;
                break;
            default:
                std::cerr << "[-] Error Un-Recognized Symbol: " << ch << ".  Line: " << lineNum << std::endl;   
                return nullptr;
            }
            break;








        case GT:               // 18
            switch(ch) {
            case ' ':   // " LT "
                {
                Token* tok = new Token(currState, lineNum, currToken);
                curr->setNext(tok);
                curr = tok;
                }
                currToken.erase();
                currState = BASE;
                break;  
            case '\n':  
                lineNum += 1;
                currState = BASE;
                {
                Token* tok = new Token(currState, lineNum, currToken);
                curr->setNext(tok);
                curr = tok;
                }
                currToken.erase();
                break;  
            case '=':
                currToken += ch;
                {
                Token* tok = new Token(GT_EQUAL, lineNum, currToken);
                curr->setNext(tok);
                curr = tok;
                }
                currToken.erase();
                currState = BASE;
                break;
            case '0':
                {
                Token* tok = new Token(currState, lineNum, currToken);
                curr->setNext(tok);
                curr = tok;
                }
                currToken.erase();
                currState = INTEGER;
                currToken += ch;
                break;
            case '1':
                {
                Token* tok = new Token(currState, lineNum, currToken);
                curr->setNext(tok);
                curr = tok;
                }
                currToken.erase();
                currState = INTEGER;
                currToken += ch;
                break;
            case '2':
                {
                Token* tok = new Token(currState, lineNum, currToken);
                curr->setNext(tok);
                curr = tok;
                }
                currToken.erase();
                currState = INTEGER;
                currToken += ch;
                break;
            case '3':
                {
                Token* tok = new Token(currState, lineNum, currToken);
                curr->setNext(tok);
                curr = tok;
                }
                currToken.erase();
                currState = INTEGER;
                currToken += ch;
                break;
            case '4':
                {
                Token* tok = new Token(currState, lineNum, currToken);
                curr->setNext(tok);
                curr = tok;
                }
                currToken.erase();
                currState = INTEGER;
                currToken += ch;
                break;
            case '5':
                {
                Token* tok = new Token(currState, lineNum, currToken);
                curr->setNext(tok);
                curr = tok;
                }
                currToken.erase();
                currState = INTEGER;
                currToken += ch;
                break;
            case '6': 
                {
                Token* tok = new Token(currState, lineNum, currToken);
                curr->setNext(tok);
                curr = tok;
                }
                currToken.erase();
                currState = INTEGER;
                currToken += ch;
                break;
            case '7': 
                {
                Token* tok = new Token(currState, lineNum, currToken);
                curr->setNext(tok);
                curr = tok;
                }
                currToken.erase();
                currState = INTEGER;
                currToken += ch;
                break;
            case '8':  
                {
                Token* tok = new Token(currState, lineNum, currToken);
                curr->setNext(tok);
                curr = tok;
                }
                currToken.erase();
                currState = INTEGER;
                currToken += ch;
                break;
            case '9':   
                {
                Token* tok = new Token(currState, lineNum, currToken);
                curr->setNext(tok);
                curr = tok;
                }
                currToken.erase();
                currState = INTEGER;
                currToken += ch;
                break;
            case 'T': 
                {
                Token* tok = new Token(currState, lineNum, currToken);
                curr->setNext(tok);
                curr = tok;
                }
                currToken.erase();
                currState = BOOLEAN_TRUE;
                currToken += ch;
                break;
            case 'F':  
                {
                Token* tok = new Token(currState, lineNum, currToken);
                curr->setNext(tok);
                curr = tok;
                }
                currToken.erase();
                currState = BOOLEAN_FALSE;
                currToken += ch;
                break;
            default:
                std::cerr << "[-] Error Un-Recognized Symbol: " << ch << ".  Line: " << lineNum << std::endl;   
                return nullptr;
            }   
            break;





        case BOOLEAN_AND:               // 21
            switch(ch) {
            case '&':   // " && "
                currToken += ch;   
                {
                Token* tok = new Token(currState, lineNum, currToken);
                curr->setNext(tok);
                curr = tok;
                }
                currToken.erase();
                currState = BASE;
                break;  
            default:
                std::cerr << "[-] single '&' not valid, line: " << lineNum << std::endl;
                return nullptr;
            }
            break;





        case BOOLEAN_OR:               // 22
            switch(ch) {
            case '|':   // " || "
                currState = BASE;
                currToken += ch;   
                {
                Token* tok = new Token(currState, lineNum, currToken);
                curr->setNext(tok);
                curr = tok;
                }
                currToken.erase();
                break;  

            default:
                std::cerr << "[-] single '|' not valid, line: " << lineNum << std::endl;
                return nullptr;
            }
            break;




        case BOOLEAN_TRUE:               // 25
            switch(ch) {
            
            case 'R':
                if (currToken.back() != 'T') {
                    currState = IDENTIFIER;
                    currToken += ch;
                    break;
                }
                currState = BOOLEAN_TRUE;
                currToken += ch;
                break;
            case 'U':
                if (currToken.back() != 'R') {
                    currState = IDENTIFIER;
                    currToken += ch;
                    break;
                }
                currState = BOOLEAN_TRUE;
                currToken += ch;
                break;
            case 'E':
                if (currToken.back() != 'U') {
                    currState = IDENTIFIER;
                    currToken += ch;
                    break;
                }
                currState = BASE;
                currToken += ch;
                {
                Token* tok = new Token(BOOLEAN_TRUE, lineNum, currToken);
                curr->setNext(tok);
                curr = tok;
                }
                currToken.erase();
                break;
            case 'a':
                currState = IDENTIFIER;
                currToken += ch;
                break;
            case 'b':
                currState = IDENTIFIER;
                currToken += ch;
                break;
            case 'c':
                currState = IDENTIFIER;
                currToken += ch;
                break;
            case 'd':
                currState = IDENTIFIER;
                currToken += ch;
                break;
            case 'f':
                currState = IDENTIFIER;
                currToken += ch;
                break;
            case 'g':
                currState = IDENTIFIER;
                currToken += ch;
                break;
            case 'h':
                currState = IDENTIFIER;
                currToken += ch;
                break;
            case 'i':
                currState = IDENTIFIER;
                currToken += ch;
                break;
            case 'j':
                currState = IDENTIFIER;
                currToken += ch;
                break;
            case 'k':
                currState = IDENTIFIER;
                currToken += ch;
                break;
            case 'l':
                currState = IDENTIFIER;
                currToken += ch;
                break;
            case 'm':
                currState = IDENTIFIER;
                currToken += ch;
                break;
            case 'n':
                currState = IDENTIFIER;
                currToken += ch;
                break;
            case 'o':
                currState = IDENTIFIER;
                currToken += ch;
                break;
            case 'p':
                currState = IDENTIFIER;
                currToken += ch;
                break;
            case 'q':
                currState = IDENTIFIER;
                currToken += ch;
                break;
            case 's':
                currState = IDENTIFIER;
                currToken += ch;
                break;
            case 't':
                currState = IDENTIFIER;
                currToken += ch;
                break;
            case 'v':
                currState = IDENTIFIER;
                currToken += ch;
                break;
            case 'w':
                currState = IDENTIFIER;
                currToken += ch;
                break;
            case 'x':
                currState = IDENTIFIER;
                currToken += ch;
                break;
            case 'y':
                currState = IDENTIFIER;
                currToken += ch;
                break;
            case 'z':
                currState = IDENTIFIER;
                currToken += ch;
                break;
            case '_':
                currState = IDENTIFIER;
                currToken += ch;
                break;
            case 'A': //27
                currState = IDENTIFIER;
                currToken += ch;
                break;
            case 'B': //27
                currState = IDENTIFIER;
                currToken += ch;
                break;
            case 'C': //27
                currState = IDENTIFIER;
                currToken += ch;
                break;
            case 'D': //27
                currState = IDENTIFIER;
                currToken += ch;
                break;
            case 'G': //27
                currState = IDENTIFIER;
                currToken += ch;
                break;
            case 'H': //27
                currState = IDENTIFIER;
                currToken += ch;
                break;
            case 'I': //27
                currState = IDENTIFIER;
                currToken += ch;
                break;
            case 'J': //27
                currState = IDENTIFIER;
                currToken += ch;
                break;
            case 'K': //27
                currState = IDENTIFIER;
                currToken += ch;
                break;
            case 'L': //27
                currState = IDENTIFIER;
                currToken += ch;
                break;
            case 'M': //27
                currState = IDENTIFIER;
                currToken += ch;
                break;
            case 'N': //27
                currState = IDENTIFIER;
                currToken += ch;
                break;
            case 'O': //27
                currState = IDENTIFIER;
                currToken += ch;
                break;
            case 'P': //27
                currState = IDENTIFIER;
                currToken += ch;
                break;
            case 'Q': //27
                currState = IDENTIFIER;
                currToken += ch;
                break;
            case 'S': //27
                currState = IDENTIFIER;
                currToken += ch;
                break;
            case 'V': //27
                currState = IDENTIFIER;
                currToken += ch;
                break;
            case 'W': //27
                currState = IDENTIFIER;
                currToken += ch;
                break;
            case 'X': //27
                currState = IDENTIFIER;
                currToken += ch;
                break;
            case 'Y': //27
                currState = IDENTIFIER;
                currToken += ch;
                break;
            case 'Z': //27
                currState = IDENTIFIER;
                currToken += ch;
                break;
            default:
                std::cerr << "[-] Error Un-Recognized Symbol: " << ch << ".  Line: " << lineNum << std::endl;   
                return nullptr;
            }
            break;






        case BOOLEAN_FALSE:               // 26
            switch(ch) {
            case 'A':
                if (currToken.back() != 'F') {
                    currState = IDENTIFIER;
                    currToken += ch;
                    break;
                }
                currState = BOOLEAN_FALSE;
                currToken += ch;
                break;
            case 'L':
                if (currToken.back() != 'A') {
                    currState = IDENTIFIER;
                    currToken += ch;
                    break;
                }
                currState = BOOLEAN_FALSE;
                currToken += ch;
                break;
            case 'S':
                if (currToken.back() != 'L') {
                    currState = IDENTIFIER;
                    currToken += ch;
                    break;
                }
                currState = BOOLEAN_FALSE;
                currToken += ch;
                break;
            case 'E':
                if (currToken.back() != 'S') {
                    currState = IDENTIFIER;
                    currToken += ch;
                    break;
                }
                currState = BASE;
                currToken += ch;
                {
                Token* tok = new Token(BOOLEAN_FALSE, lineNum, currToken);
                curr->setNext(tok);
                curr = tok;
                }
                currToken.erase();
                break;
            case 'b':
                currState = IDENTIFIER;
                currToken += ch;
                break;
            case 'c':
                currState = IDENTIFIER;
                currToken += ch;
                break;
            case 'd':
                currState = IDENTIFIER;
                currToken += ch;
                break;
            case 'g':
                currState = IDENTIFIER;
                currToken += ch;
                break;
            case 'h':
                currState = IDENTIFIER;
                currToken += ch;
                break;
            case 'i':
                currState = IDENTIFIER;
                currToken += ch;
                break;
            case 'j':
                currState = IDENTIFIER;
                currToken += ch;
                break;
            case 'k':
                currState = IDENTIFIER;
                currToken += ch;
                break;
            case 'm':
                currState = IDENTIFIER;
                currToken += ch;
                break;
            case 'n':
                currState = IDENTIFIER;
                currToken += ch;
                break;
            case 'o':
                currState = IDENTIFIER;
                currToken += ch;
                break;
            case 'p':
                currState = IDENTIFIER;
                currToken += ch;
                break;
            case 'q':
                currState = IDENTIFIER;
                currToken += ch;
                break;
            case 'r':
                currState = IDENTIFIER;
                currToken += ch;
                break;
            case 't':
                currState = IDENTIFIER;
                currToken += ch;
                break;
            case 'u':
                currState = IDENTIFIER;
                currToken += ch;
                break;
            case 'v':
                currState = IDENTIFIER;
                currToken += ch;
                break;
            case 'w':
                currState = IDENTIFIER;
                currToken += ch;
                break;
            case 'x':
                currState = IDENTIFIER;
                currToken += ch;
                break;
            case 'y':
                currState = IDENTIFIER;
                currToken += ch;
                break;
            case 'z':
                currState = IDENTIFIER;
                currToken += ch;
                break;
            case '_':
                currState = IDENTIFIER;
                currToken += ch;
            case 'B': //27
                currState = IDENTIFIER;
                currToken += ch;
                break;
            case 'C': //27
                currState = IDENTIFIER;
                currToken += ch;
                break;
            case 'D': //27
                currState = IDENTIFIER;
                currToken += ch;
                break;
            case 'G': //27
                currState = IDENTIFIER;
                currToken += ch;
                break;
            case 'H': //27
                currState = IDENTIFIER;
                currToken += ch;
                break;
            case 'I': //27
                currState = IDENTIFIER;
                currToken += ch;
                break;
            case 'J': //27
                currState = IDENTIFIER;
                currToken += ch;
                break;
            case 'K': //27
                currState = IDENTIFIER;
                currToken += ch;
                break;
            case 'M': //27
                currState = IDENTIFIER;
                currToken += ch;
                break;
            case 'N': //27
                currState = IDENTIFIER;
                currToken += ch;
                break;
            case 'O': //27
                currState = IDENTIFIER;
                currToken += ch;
                break;
            case 'P': //27
                currState = IDENTIFIER;
                currToken += ch;
                break;
            case 'Q': //27
                currState = IDENTIFIER;
                currToken += ch;
                break;
            case 'R': //27
                currState = IDENTIFIER;
                currToken += ch;
                break;
            case 'U': //27
                currState = IDENTIFIER;
                currToken += ch;
                break;
            case 'V': //27
                currState = IDENTIFIER;
                currToken += ch;
                break;
            case 'W': //27
                currState = IDENTIFIER;
                currToken += ch;
                break;
            case 'X': //27
                currState = IDENTIFIER;
                currToken += ch;
                break;
            case 'Y': //27
                currState = IDENTIFIER;
                currToken += ch;
                break;
            case 'Z': //27
                currState = IDENTIFIER;
                currToken += ch;
                break;
            default:
                std::cerr << "[-] Error Un-Recognized Symbol: " << ch << ".  Line: " << lineNum << std::endl;   
                return nullptr;
            }
            break;




        case IDENTIFIER:               // 27
            switch(ch) {
            case 't': 
                currToken += ch;
                break;
            case 'f': 
                currToken += ch;
                break;
            case 'a': 
                currToken += ch;
                break;
            case 'b': 
                currToken += ch;
                break;
            case 'c': 
                currToken += ch;
                break;
            case 'd': 
                currToken += ch;
                break;
            case 'e': 
                currToken += ch;
                break;
            case 'g': 
                currToken += ch;
                break;
            case 'h': 
                currToken += ch;
                break;
            case 'i': 
                currToken += ch;
                break;
            case 'j': 
                currToken += ch;
                break;
            case 'k': 
                currToken += ch;
                break;
            case 'l': 
                currToken += ch;
                break;
            case 'm': 
                currToken += ch;
                break;
            case 'n': 
                currToken += ch;
                break;
            case 'o': 
                currToken += ch;
                break;
            case 'p': 
                currToken += ch;
                break;
            case 'q': 
                currToken += ch;
                break;
            case 'r': 
                currToken += ch;
                break;
            case 's': 
                currToken += ch;
                break;
            case 'u': 
                currToken += ch;
                break;
            case 'v': 
                currToken += ch;
                break;
            case 'w': 
                currToken += ch;
                break;
            case 'x': 
                currToken += ch;
                break;
            case 'y': 
                currToken += ch;
                break;
            case 'z': 
                currToken += ch;
                break;
            case '_': 
                currToken += ch;
                break;
            case 'A': //27
                currToken += ch;
                break;
            case 'B': //27
                currToken += ch;
                break;
            case 'C': //27
                currToken += ch;
                break;
            case 'D': //27
                currToken += ch;
                break;
            case 'E': //27
                currToken += ch;
                break;
            case 'G': //27
                currToken += ch;
                break;
            case 'H': //27
                currToken += ch;
                break;
            case 'I': //27
                currToken += ch;
                break;
            case 'J': //27
                currToken += ch;
                break;
            case 'K': //27
                currToken += ch;
                break;
            case 'L': //27
                currToken += ch;
                break;
            case 'M': //27
                currToken += ch;
                break;
            case 'N': //27
                currToken += ch;
                break;
            case 'O': //27
                currToken += ch;
                break;
            case 'P': //27
                currToken += ch;
                break;
            case 'Q': //27
                currToken += ch;
                break;
            case 'R': //27
                currToken += ch;
                break;
            case 'S': //27
                currToken += ch;
                break;
            case 'U': //27
                currToken += ch;
                break;
            case 'V': //27
                currToken += ch;
                break;
            case 'W': //27
                currToken += ch;
                break;
            case 'X': //27
                currToken += ch;
                break;
            case 'Y': //27
                currToken += ch;
                break;
            case 'Z': //27
                currToken += ch;
                break;
            //case '!':
            //    currToken += ch;
            //    break;
            //case '\\':
            //    currToken += ch;
            //    break;

            case ' ':
                {
                Token* tok = new Token(currState, lineNum, currToken);
                curr->setNext(tok);
                curr = tok;
                }
                currToken.erase();
                currState = BASE;
                break;  
            case '\n':
                lineNum += 1;
                {
                Token* tok = new Token(currState, lineNum, currToken);
                curr->setNext(tok);
                curr = tok;
                }
                currToken.erase();
                currState = BASE;
                break;  
            case ')': 
                {
                Token* tok = new Token(currState, lineNum, currToken);
                curr->setNext(tok);
                curr = tok;
                }
                currToken.erase();
                currState = BASE;
                currToken += ch;
                {
                Token* tok = new Token(R_PAREN, lineNum, currToken);
                curr->setNext(tok);
                curr = tok;
                }
                currToken.erase();
                break;  
            case ';': 
                {
                Token* tok = new Token(currState, lineNum, currToken);
                curr->setNext(tok);
                curr = tok;
                }
                currToken.erase();
                currState = BASE;
                currToken += ch;
                {
                Token* tok = new Token(SEMICOLON, lineNum, currToken);
                curr->setNext(tok);
                curr = tok;
                }
                currToken.erase();
                break;  
            case ',': 
                {
                Token* tok = new Token(currState, lineNum, currToken);
                curr->setNext(tok);
                curr = tok;
                }
                currToken.erase();
                currState = BASE;
                currToken += ch;
                {
                Token* tok = new Token(COMMA, lineNum, currToken);
                curr->setNext(tok);
                curr = tok;
                }
                currToken.erase();
                break;  
            case '(': 
                {
                Token* tok = new Token(currState, lineNum, currToken);
                curr->setNext(tok);
                curr = tok;
                }
                currToken.erase();
                currState = BASE;
                currToken += ch;
                {
                Token* tok = new Token(L_PAREN, lineNum, currToken);
                curr->setNext(tok);
                curr = tok;
                }
                currToken.erase();
                break;  
            case '[': 
                {
                Token* tok = new Token(currState, lineNum, currToken);
                curr->setNext(tok);
                curr = tok;
                }
                currToken.erase();
                currState = BASE;
                currToken += ch;
                {
                Token* tok = new Token(L_BRACKET, lineNum, currToken);
                curr->setNext(tok);
                curr = tok;
                }
                currToken.erase();
                break;  
            case ']': 
                {
                Token* tok = new Token(currState, lineNum, currToken);
                curr->setNext(tok);
                curr = tok;
                }
                currToken.erase();
                currState = BASE;
                currToken += ch;
                {
                Token* tok = new Token(R_BRACKET, lineNum, currToken);
                curr->setNext(tok);
                curr = tok;
                }
                currToken.erase();
                break;  
           case '0':
                currToken += ch;
                break;
            case '1':
                currToken += ch;
                break;
            case '2':
                currToken += ch;
                break;
            case '3':
                currToken += ch;
                break;
            case '4':
                currToken += ch;
                break;
            case '5':
                currToken += ch;
                break;
            case '6':
                currToken += ch;
                break;
            case '7':
                currToken += ch;
                break;
            case '8':
                currToken += ch;
                break;
            case '9':
                currToken += ch;
                break;
            default:
                std::cerr << "[-] Error Un-Recognized Symbol: " << ch << "  Line: " << lineNum << std::endl;   
                return nullptr;
        }
        break;






        case INTEGER:
            switch(ch) {
            case ' ':
                {
                Token* tok = new Token(currState, lineNum, currToken);
                curr->setNext(tok);
                curr = tok;
                }
                currState = BASE;
                currToken.erase();
                break;  
            case '0':
                currToken += ch;
                break;
            case '1':
                currToken += ch;
                break;
            case '2':
                currToken += ch;
                break;
            case '3':
                currToken += ch;
                break;
            case '4':
                currToken += ch;
                break;
            case '5':
                currToken += ch;
                break;
            case '6':
                currToken += ch;
                break;
            case '7':
                currToken += ch;
                break;
            case '8':
                currToken += ch;
                break;
            case '9':
                currToken += ch;
                break;
            case ';':
                {
                Token* tok = new Token(currState, lineNum, currToken);
                curr->setNext(tok);
                curr = tok;
                }
                currToken.erase();
                currToken += ch;
                currState = SEMICOLON;
                {
                Token* tok = new Token(currState, lineNum, currToken);
                curr->setNext(tok);
                curr = tok;
                }
                currState = BASE;
                currToken.erase();
                break;  
            case ')':
                {
                Token* tok = new Token(currState, lineNum, currToken);
                curr->setNext(tok);
                curr = tok;
                }
                currToken.erase();
                currToken += ch;
                currState = R_PAREN;
                {
                Token* tok = new Token(currState, lineNum, currToken);
                curr->setNext(tok);
                curr = tok;
                }
                currState = BASE;
                currToken.erase();
                break;  
            case '(':
                {
                Token* tok = new Token(currState, lineNum, currToken);
                curr->setNext(tok);
                curr = tok;
                }
                currToken.erase();
                currToken += ch;
                currState = L_PAREN;
                {
                Token* tok = new Token(currState, lineNum, currToken);
                curr->setNext(tok);
                curr = tok;
                }
                currState = BASE;
                currToken.erase();
                break;  
            case '}':
                {
                Token* tok = new Token(currState, lineNum, currToken);
                curr->setNext(tok);
                curr = tok;
                }
                currToken.erase();
                currToken += ch;
                currState = R_BRACE;
                {
                Token* tok = new Token(currState, lineNum, currToken);
                curr->setNext(tok);
                curr = tok;
                }
                currState = BASE;
                currToken.erase();
                break;  
            case '[': 
                {
                Token* tok = new Token(currState, lineNum, currToken);
                curr->setNext(tok);
                curr = tok;
                }
                currToken.erase();
                currState = BASE;
                currToken += ch;
                {
                Token* tok = new Token(L_BRACKET, lineNum, currToken);
                curr->setNext(tok);
                curr = tok;
                }
                currToken.erase();
                break;  
            case ']': 
                {
                Token* tok = new Token(currState, lineNum, currToken);
                curr->setNext(tok);
                curr = tok;
                }
                currToken.erase();
                currState = BASE;
                currToken += ch;
                {
                Token* tok = new Token(R_BRACKET, lineNum, currToken);
                curr->setNext(tok);
                curr = tok;
                }
                currToken.erase();
                break;  
            case ',':
                {
                Token* tok = new Token(currState, lineNum, currToken);
                curr->setNext(tok);
                curr = tok;
                }
                currToken.erase();
                currToken += ch;
                currState = COMMA;
                {
                Token* tok = new Token(currState, lineNum, currToken);
                curr->setNext(tok);
                curr = tok;
                }
                currState = BASE;
                currToken.erase();
                break;  
            default:
                std::cerr << "[-] Syntax error on line " << lineNum << ": Invalid integer " << currToken << std::endl;   
                return nullptr;
            } 
            break;





        case MINUS:
            switch(ch) {
            case ' ':
                {
                Token* tok = new Token(currState, lineNum, currToken);
                curr->setNext(tok);
                curr = tok;
                }
                currState = BASE;
                currToken.erase();
                break;  
            case '\n':
                lineNum += 1;
                {
                Token* tok = new Token(currState, lineNum, currToken);
                curr->setNext(tok);
                curr = tok;
                }
                currState = BASE;
                currToken.erase();
                break;  
            case '0':
                currToken += ch;
                currState = INTEGER;
                break;
            case '1':
                currToken += ch;
                currState = INTEGER;
                break;
            case '2':
                currToken += ch;
                currState = INTEGER;
                break;
            case '3':
                currToken += ch;
                currState = INTEGER;
                break;
            case '4':
                currToken += ch;
                currState = INTEGER;
                break;
            case '5':
                currToken += ch;
                currState = INTEGER;
                break;
            case '6':
                currToken += ch;
                currState = INTEGER;
                break;
            case '7':
                currToken += ch;
                currState = INTEGER;
                break;
            case '8':
                currToken += ch;
                currState = INTEGER;
                break;
            case '9':
                currToken += ch;
                currState = INTEGER;
                break;
            default:
                std::cerr << "[-] Error Un-Recognized Symbol: " << ch << ".  Line: " << lineNum << std::endl;   
                return nullptr;
            }
            break;





        case DOUBLE_QUOTED_STRING:
            switch(ch) {
            case '"':
            if (currToken.back() != '\\') { 
                    {
                    Token* tok = new Token(STRING, lineNum, currToken);
                    curr->setNext(tok);
                    curr = tok;
                    }
                    currToken.erase();
                    currToken += ch;
                    currState = DOUBLE_QUOTE;
                    {
                    Token* tok = new Token(DOUBLE_QUOTE, lineNum, currToken);
                    curr->setNext(tok);
                    curr = tok;
                    }
                    currState = BASE;
                    currToken.erase();
            } else {
                currToken += ch;
            }
                break;  
            case '\n':
                {
                Token* tok = new Token(STRING, lineNum, currToken);
                curr->setNext(tok);
                curr = tok;
                }
                lineNum += 1;
                currToken.erase();
                currToken = BASE;
                break;

            default:
                currToken += ch;
                break; 
            }
            break;




        case SINGLE_QUOTED_STRING:
            switch(ch) {
            case '\'':
            if (currToken.back() != '\\') { 
                    {
                    Token* tok = new Token(STRING, lineNum, currToken);
                    curr->setNext(tok);
                    curr = tok;
                    }
                    currToken.erase();
                    currToken += ch;
                    currState = SINGLE_QUOTE;
                    {
                    Token* tok = new Token(SINGLE_QUOTE, lineNum, currToken);
                    curr->setNext(tok);
                    curr = tok;
                    }
                    currState = BASE;
                    currToken.erase();

            } else {
                currToken += ch;
            }
                break;  
            case '\n':
                {
                Token* tok = new Token(STRING, lineNum, currToken);
                curr->setNext(tok);
                curr = tok;
                }
                lineNum += 1;
                currToken.erase();
                currToken = BASE;
                break;

            default:
                currToken += ch;
                break; 
            }
            break;





        default:
            std::cerr << "[-] Error Unrecognized State" << std::endl;
            break;


        }
    }




        Token* realHead = head->getNext();
        delete(head);
        inFile.close();
        return realHead;


}



