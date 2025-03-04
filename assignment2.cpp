#include <iostream>
#include <fstream>
#include <sstream>
#include <unistd.h>
#include <string>







    enum TOKEN  {BASE, DOUBLE_QUOTE, SINGLE_QUOTE, L_PAREN, R_PAREN, L_BRACE, R_BRACE, L_BRACKET, R_BRACKET, SEMICOLON, ASSIGNMENT_OPERATOR, BOOLEAN_TRUE, BOOLEAN_FALSE, MODULO, ASTERISK, GT, LT, PLUS, MINUS, DIVIDE, CARET, GT_EQUAL, LT_EQUAL, BOOLEAN_AND, BOOLEAN_OR, BOOLEAN_NOT, BOOLEAN_NOT_EQUAL,  IDENTIFIER, INTEGER, COMMA, STRING, BOOLEAN_EQUAL};



class Token{

    TOKEN type;
    int lineNum;
    std::string token;
    Token* next;



    public:
    Token(TOKEN _type, int _lineNum, std::string _token, Token* _next) : 
        type(_type), lineNum(_lineNum), token(_token), next(_next) {}

    Token(TOKEN _type, int _lineNum, std::string _token) : 
        type(_type), lineNum(_lineNum), token(_token) {
        next = nullptr;
    }
    friend std::ostream& operator<<(std::ostream& out, const Token &t);
    

    void setType(TOKEN _type) {
        type = _type;
    }


    void setLineNum(int _lineNum) {
        lineNum = _lineNum;
    }


    void setToken(std::string _token) {
        token = _token;
    }


    void setNext(Token* _next) {
        next = _next;
    }

    Token* getNext() {
        return next;
    }


    std::string typeToStr() const {
        switch (type) {
            case BASE: return "BASE";
            case DOUBLE_QUOTE: return "DOUBLE_QUOTE";
            case SINGLE_QUOTE: return "SINGLE_QUOTE";
            case L_PAREN: return "L_PAREN";
            case R_PAREN: return "R_PAREN";
            case L_BRACE: return "L_BRACE";
            case R_BRACE: return "R_BRACE";
            case L_BRACKET: return "L_BRACKET";
            case R_BRACKET: return "R_BRACKET";
            case SEMICOLON: return "SEMICOLON";
            case ASSIGNMENT_OPERATOR: return "ASSIGNMENT_OPERATOR";
            case BOOLEAN_TRUE: return "BOOLEAN_TRUE";
            case BOOLEAN_FALSE: return "BOOLEAN_FALSE";
            case MODULO: return "MODULO";
            case ASTERISK: return "ASTERISK";
            case PLUS: return "PLUS";
            case MINUS: return "MINUS";
            case DIVIDE: return "DIVIDE";
            case CARET: return "CARET";
            case GT_EQUAL: return "GT_EQUAL";
            case LT_EQUAL: return "LT_EQUAL";
            case BOOLEAN_AND: return "BOOLEAN_AND";
            case BOOLEAN_OR: return "BOOLEAN_OR";
            case BOOLEAN_NOT: return "BOOLEAN_NOT";
            case BOOLEAN_NOT_EQUAL: return "BOOLEAN_NOT_EQUAL";
            case IDENTIFIER: return "IDENTIFIER";
            case INTEGER: return "INTEGER";
            case COMMA: return "COMMA";
            case STRING: return "STRING";
            case BOOLEAN_EQUAL: return "BOOLEAN_EQUAL";
            case GT: return "GT";
            case LT: return "LT";
            default: return "UNKNOWN_TOKEN";
        }
    
    }

};




std::ostream& operator<<(std::ostream& out, const Token &t) {
    out << "Token type: " << t.typeToStr() << "\nToken: " << t.token << "\n";
    return out;
}







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
                currState = STRING;
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
                currState = STRING;
                {
                Token* tok = new Token(SINGLE_QUOTE, lineNum, currToken);
                curr->setNext(tok);
                curr = tok;
                }
                currToken.erase();
                currToken += ch;
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





        case BOOLEAN_NOT:               // 23
            switch(ch) {
            case ' ':   // " ! "
                {
                Token* tok = new Token(currState, lineNum, currToken);
                curr->setNext(tok);
                curr = tok;
                }
                currState = BASE;
                currToken.erase();
                break;  
            case '\n':   // " ! "
                lineNum += 1;
                currState = BASE;
                {
                Token* tok = new Token(currState, lineNum, currToken);
                curr->setNext(tok);
                curr = tok;
                }
                currToken.erase();
                break;  
            case '=':   // " != "
                currState = BASE;
                currToken += ch;   
                {
                Token* tok = new Token(BOOLEAN_NOT_EQUAL, lineNum, currToken);
                curr->setNext(tok);
                curr = tok;
                }
                currToken.erase();
                break;  
            default:
                std::cerr << "[-] Syntax Error !" << ch << ".  Line: " << lineNum << std::endl;   
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
                currState = BOOLEAN_TRUE;
                currToken += ch;
                break;
            case 'L':
                if (currToken.back() != 'A') {
                    currState = IDENTIFIER;
                    currToken += ch;
                    break;
                }
                currState = BOOLEAN_TRUE;
                currToken += ch;
                break;
            case 'S':
                if (currToken.back() != 'L') {
                    currState = IDENTIFIER;
                    currToken += ch;
                    break;
                }
                currState = BOOLEAN_TRUE;
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
                std::cerr << "[-] Error Un-Recognized Symbol: " << ch << ".  Line: " << lineNum << std::endl;   
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






        case STRING:
            switch(ch) {
            case '"':
                {
                Token* tok = new Token(currState, lineNum, currToken);
                curr->setNext(tok);
                curr = tok;
                }
                currToken.erase();
                currToken += ch;
                currState = DOUBLE_QUOTE;
                {
                Token* tok = new Token(currState, lineNum, currToken);
                curr->setNext(tok);
                curr = tok;
                }
                currState = BASE;
                currToken.erase();
                break;  
            case '\'':
                {
                Token* tok = new Token(currState, lineNum, currToken);
                curr->setNext(tok);
                curr = tok;
                }
                currToken.erase();
                currToken += ch;
                currState = SINGLE_QUOTE;
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
        return head->getNext();


}









/*
*    takes an input c-style file and removes all comments replacing them with blank space
*/
bool parseComments(char* inFileName, char* outFileName) {

    enum States {PROGRAM, F_SLASH, LINE_COMMENT, BLOCK_COMMENT, B_SLASH, ASTERISK, UN_TERMINATED, QUOTE, ESCAPE};

    //- initilize and check files
    std::ifstream inFile(inFileName);
    std::ofstream outFile(outFileName);
    if (!inFile) {
        std::cerr << "Unable to open: " << inFileName << std::endl;
        return false;
    } else if (!outFile) {
        std::cerr << "Unable to open: " << outFileName << std::endl;
        return false;
    }


    int currLine = 1;
    int comStartLine = 0;
    char ch = 0;
    int buffLimit = 4096;      
    States currState = PROGRAM;
    std::ostringstream buffer;

    //- retrive input char by char from file
    while (inFile.get(ch)) {
        switch (currState) {

        //- normal non-comment code
        case PROGRAM: // S/0
            switch (ch) {
            case '/':
                currState = F_SLASH;
                break;
            case '*':
                currState = ASTERISK;
                buffer << ch;
                break;
            case '\n':
                currLine += 1;
                buffer << ch;
                break;
            case '"':
                currState = QUOTE;
                buffer << ch;
                break;
            default:
                currState = PROGRAM;
                buffer << ch;
                break;
            }
            break;


        //- possibly start of line comment
        case F_SLASH:   //1
            switch(ch) {
            case '/':
                currState = LINE_COMMENT;
                comStartLine = currLine;
                buffer << "  ";
                break;
            case '*':
                currState = BLOCK_COMMENT;
                comStartLine = currLine;
                buffer << "  ";
                break;
            case '\n':
                currLine += 1;
                buffer << ch;
                break;
            default:
                currState = PROGRAM;
                buffer << '/';
                buffer << ch;
                break;
            }
            break;


        //- line comment
        case LINE_COMMENT: //2
            switch(ch) {
            case '\n':
                currLine += 1;
                currState = PROGRAM;
                buffer << '\n';
                break;
            default:
                buffer << ' ';
                break;
            }
            break;


        //- block comment
        case BLOCK_COMMENT: //3
            switch(ch) {
            case '*':
                currState = B_SLASH;
                buffer << ' ';
                break;
            case '\n':
                currLine += 1;
                currState = B_SLASH;
                buffer << '\n';
                break;
            default:
                currState = BLOCK_COMMENT;
                buffer << ' ';
                break;
            }
            break;


        //- possibly end of block comment
        case B_SLASH: //4
            switch(ch) {
            case '*':
                currState = B_SLASH;
                buffer << ' ';
                break;
            case '/':
                currState = PROGRAM;
                buffer << ' ';
                break;
            case '\n':
                currLine += 1;
                currState = B_SLASH;
                buffer << '\n';
                break;
            default:
                currState = BLOCK_COMMENT;
                buffer << ' ';
                break;
            }
            break;


        //- possibly end of block comment with no start
        case ASTERISK: //5
            switch(ch) {
            case '/':
                currState = UN_TERMINATED;
                break;
            case '\n':
                currLine += 1;
                buffer << '\n';
                break;
            default:
                currState = PROGRAM;
                buffer << ch;
                break;
            }
            break;


        //- end of block comment with no start    '*/'
        case UN_TERMINATED: //6
            std::cerr << "[-] Error: Program contains C-style, unterminated comment on line " << currLine << std::endl;
            return false;
        



        //- start of quote
        case QUOTE: //7
            switch(ch) {
            case '\\':
                currState = ESCAPE;
                buffer << '\\';
                break;
            case '\n':
                currLine += 1;
                buffer << '\n';
                break;
            case '"':
                currState = PROGRAM;
                buffer << ch;
                break;
            default:
                currState = QUOTE;
                buffer << ch;
                break;
            }
            break;

        //- possibly start of escaped charactor
        case ESCAPE: //8
            switch(ch) {
            case '\\':
                currState = ESCAPE;
                buffer << '\\';
                break;
            case '\n':
                currLine += 1;
                buffer << '\n';
                break;
            default:
                currState = QUOTE;
                buffer << ch;
                break;
            }
            break;



        //- unexpected unacounted for input
        default:
            std::cerr << "Syntax Error on line: " << currLine << std::endl;
            break;

        }

        //- check buffer size and ouput and clar it if exceeds limit
        if (buffer.tellp() >= buffLimit) {  
            outFile << buffer.str();  
            buffer.str("");           
            buffer.clear();         
        }

    }


    //- program reached end without ccompleteing block comment, or only contained line comment
    if (currState == UN_TERMINATED) {
        std::cerr << "[-] Error: Program contains C-style, unterminated comment on line " << comStartLine << std::endl;
        inFile.close();
        outFile.close();
        return false;
    }


    //- final write to file and close
    outFile << buffer.str();
    inFile.close();
    outFile.close();
    return true;

}










int main(int argc, char* argv[]) {


    if (argc < 3) {
        std::cerr << "[-] Too few arguments: Usage ./program [inputFile] [outputFile]" << std::endl;
        return -1;
    }


    if (!parseComments(argv[1], argv[2])) return -1;
        
    
   Token* head = tokenize(argv[2]);
    if (head == nullptr) return -1; 
    
    while(head != nullptr) {
        std::cout << *head << std::endl;
        head = head->getNext();
    }




}

