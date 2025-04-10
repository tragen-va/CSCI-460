
#include <fstream>
#include <sstream>
#include <unistd.h>
#include "Token.h"







    
    

    void Token::setType(TOKEN _type) {
        type = _type;
    }


    void Token::setLineNum(int _lineNum) {
        lineNum = _lineNum;
    }


    void Token::setToken(std::string _token) {
        token = _token;
    }


    void Token::setNext(Token* _next) {
        next = _next;
    }

    Token* Token::getNext() {
        return next;
    }

    int Token::getLineNum() {
        return lineNum;
    }

    TOKEN Token::getType() {
        return type;
    }



    std::string Token::typeToStr() const {
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
            case EXPRESSION_STATEMENT: return "EXPRESSION_STATEMENT";
            default: return "UNKNOWN_TOKEN";
        }
    
    }





std::ostream& operator<<(std::ostream& out, const Token &t) {
    out << "Token type: " << t.typeToStr() << "\nToken: " << t.token << "\n";
    return out;
}



