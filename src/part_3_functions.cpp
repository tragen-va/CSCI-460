#include <string>
#include <iostream>
#include <unistd.h>


#include "CSTNode.h"
#include "STNode.h"
#include <unordered_set>
#include <stack>

#include "part_3_functions.h"


int ERROR = 0;






// <ITERATION_ASSIGNMENT> ::= <IDENTIFIER> <ASSIGNMENT_OPERATOR> <EXPRESSION> | 
//                            <IDENTIFIER> <ASSIGNMENT_OPERATOR> <SINGLE_QUOTED_STRING> | 
//                            <IDENTIFIER> <ASSIGNMENT_OPERATOR> <DOUBLE_QUOTED_STRING>
CSTNode* parseIterationAssignment(CSTNode*& currNode, Token*& currToken) {

    if (currNode == nullptr) { return nullptr;} 
    if (currToken == nullptr) {return currNode;}




    // <IDENTIFIER>
    CSTNode* identifierNode = parseIdentifier(currNode, currToken);
    if (identifierNode == nullptr) {return nullptr;}
    currNode = currNode->link(identifierNode);




    // <ASSIGNMENT_OPERATOR>
    if (currToken->getType() != ASSIGNMENT_OPERATOR) {
        if(!ERROR) {std::cerr << "Syntac error on line " << currToken->getLineNum() << " missing '=' in assignment statement" << "\n";}
        return nullptr;
    }
    CSTNode* assignmentNode = new CSTNode(ASSIGNMENT_OPERATOR, "=", currToken->getLineNum());
    currNode = currNode->link(assignmentNode);
    if (currToken->getNext() == nullptr) { return currNode;}
    currToken = currToken->getNext();




    // <SINGLE_QUOTED_STRING> | <DOUBLE_QUOTED_STRING> | <EXPRESSION>
    CSTNode* unknownNode;
    if (currToken->getType() == SINGLE_QUOTE) {
        unknownNode = parseSingleQuotedString(currNode, currToken);
    } else if (currToken->getType() == DOUBLE_QUOTE) {
        unknownNode = parseDoubleQuotedString(currNode, currToken);
    } else {
        unknownNode = parseExpression(currNode, currToken);
    }
    if (unknownNode == nullptr) {return nullptr;} 
    currNode = currNode->link(unknownNode);



    return currNode;

}













// <IDENTIFIER_AND_IDENTIFIER_ARRAY_PARAMETER_LIST_DECLARATION> ::= <IDENTIFIER> | 
//                                                                  <IDENTIFIER> <L_BRACKET> <WHOLE_NUMBER> <R_BRACKET> | 
//                                                                  <IDENTIFIER> <L_BRACKET> <WHOLE_NUMBER> <R_BRACKET> | 
//                                                                  <IDENTIFIER> <L_BRACKET> <WHOLE_NUMBER> <R_BRACKET> <COMMA>  <IDENTIFIER_AND_IDENTIFIER_ARRAY_PARAMETER_LIST_DECLARATION> | 
//                                                                  <IDENTIFIER> <L_BRACKET> <WHOLE_NUMBER> <R_BRACKET> <COMMA>  <IDENTIFIER_AND_IDENTIFIER_ARRAY_PARAMETER_LIST_DECLARATION>
//                                                                  <IDENTIFIER> <COMMA> <IDENTIFIER_AND_IDENTIFIER_ARRAY_PARAMETER_LIST_DECLARATION> | 
CSTNode* parseIdentifierAndIdentifierArrayParameterListDeclaration(CSTNode*& currNode, Token*& currToken) {


    if (currNode == nullptr) { return nullptr;} 
    if (currToken == nullptr) {return currNode;}



    // <IDENTIFIER>
    CSTNode* identifierNode = parseIdentifier(currNode, currToken);
    if (identifierNode == nullptr) {return nullptr;}
    currNode = currNode->link(identifierNode);
    


    // <L_BRACKET>
    if (currToken->getType() == L_BRACKET) {
        CSTNode* lBracketNode = new CSTNode(L_BRACKET, "[", currToken->getLineNum());
        currNode = currNode->link(lBracketNode);
        if (currToken->getNext() == nullptr) { return currNode;}
        currToken = currToken->getNext();


        // <WHOLE_NUMBER>
        CSTNode* wholeNumberNode = parseWholeNumber(currNode, currToken);
        if (wholeNumberNode == nullptr) {return nullptr;}
        currNode = currNode->link(wholeNumberNode);


        // <R_BRACKET>
        if (currToken->getType() != R_BRACKET) {
            if(!ERROR) {std::cerr << "syntax error at line  " << currToken->getLineNum() << " unclosed ]" << "\n";}
            return nullptr;
        }
        CSTNode* rBracketNode = new CSTNode(R_BRACKET, "]", currToken->getLineNum());
        currNode = currNode->link(rBracketNode);
        currToken = currToken->getNext();
        if (currToken->getNext() == nullptr) { return currNode;}



        
            // <COMMA>
        if (currToken->getType() == COMMA && currToken->getNext() && (currToken->getNext()->token != "char" && currToken->getNext()->token != "int" && currToken->getNext()->token != "bool")) {
            CSTNode* commaNode = new CSTNode(COMMA, ",", currToken->getLineNum());
            currNode = currNode->link(commaNode);
            if (currToken->getNext() == nullptr) { return currNode;}
            currToken = currToken->getNext();
            

            // <IDENTIFIER_AND_IDENTIFIER_ARRAY_PARANETER_LIST_DECLARATION>
            CSTNode* identifierArrayListNode = parseIdentifierAndIdentifierArrayParameterListDeclaration(currNode, currToken);
            if (identifierArrayListNode == nullptr) {return nullptr;}
            currNode = currNode->link(identifierArrayListNode);
        }
    }





    // <COMMA>
    else if (currToken->getType() == COMMA && currToken->getNext() && (currToken->getNext()->token != "char" && currToken->getNext()->token != "int" && currToken->getNext()->token != "bool")) {
            CSTNode* commaNode = new CSTNode(COMMA, ",", currToken->getLineNum());
            currNode = currNode->link(commaNode);
            if (currToken->getNext() == nullptr) { return currNode;}
            currToken = currToken->getNext();
            

            // <IDENTIFIER_AND_IDENTIFIER_ARRAY_PARANETER_LIST_DECLARATION>
            CSTNode* identifierArrayListNode = parseIdentifierAndIdentifierArrayParameterListDeclaration(currNode, currToken);
            if (identifierArrayListNode == nullptr) {return nullptr;}
            currNode = currNode->link(identifierArrayListNode);
    }




    return currNode;
}







// <IDENTIFIER_AND_IDENTIFIER_ARRAY_PARAMETER_LIST> ::= <IDENTIFIER> | 
//                                                      <IDENTIFIER> <L_BRACKET> <IDENTIFIER> <R_BRACKET> | 
//                                                      <IDENTIFIER> <L_BRACKET> <IDENTIFIER> <R_BRACKET> <COMMA>  <IDENTIFIER_AND_IDENTIFIER_ARRAY_PARAMETER_LIST> | 
//                                                      <IDENTIFIER> <L_BRACKET> <NUMERICAL_EXPRESSION> <R_BRACKET> <COMMA>  <IDENTIFIER_AND_IDENTIFIER_ARRAY_PARAMETER_LIST>
//                                                      <IDENTIFIER> <L_BRACKET> <NUMERICAL_EXPRESSION> <R_BRACKET> | 
//                                                      <IDENTIFIER> <COMMA> <IDENTIFIER_AND_IDENTIFIER_ARRAY_PARAMETER_LIST> | 
CSTNode* parseIdentifierAndIdentifierArrayParameterList(CSTNode*& currNode, Token*& currToken) {


    if (currNode == nullptr) { return nullptr;} 
    if (currToken == nullptr) {return currNode;}



    // <IDENTIFIER>
    CSTNode* identifierNode = parseIdentifier(currNode, currToken);
    if (identifierNode == nullptr) {return nullptr;}
    currNode = currNode->link(identifierNode);
    


    // <L_BRACKET>
    if (currToken->getType() == L_BRACKET) {
        CSTNode* lBracketNode = new CSTNode(L_BRACKET, "[", currToken->getLineNum());
        currNode = currNode->link(lBracketNode);
        if (currToken->getNext() == nullptr) { return currNode;}
        currToken = currToken->getNext();


        // <IDENTIFIER_AND_IDENTIFIER_ARRAY_PARAMETER_LIST> | <EXPRESSION>
        CSTNode* unknownNode;
        if (currToken->getType() == IDENTIFIER) {unknownNode = parseIdentifierAndIdentifierArrayParameterList(currNode, currToken);}
        else {unknownNode = parseExpression(currNode, currToken);}
        if (unknownNode == nullptr) {return nullptr;}




        // <R_BRACKET>
        if (currToken->getType() != R_BRACKET) {
            if(!ERROR) {std::cerr << "syntax error at line  " << currToken->getLineNum() << " unclosed ]" << "\n";}
            return nullptr;
        }
        CSTNode* rBracketNode = new CSTNode(R_BRACKET, "]", currToken->getLineNum());
        currNode = currNode->link(rBracketNode);
        currToken = currToken->getNext();
        if (currToken->getNext() == nullptr) { return currNode;}



        
            // <COMMA>
        if (currToken->getType() == COMMA) {
            CSTNode* commaNode = new CSTNode(COMMA, ",", currToken->getLineNum());
            currNode = currNode->link(commaNode);
            if (currToken->getNext() == nullptr) { return currNode;}
            currToken = currToken->getNext();
            

            // <IDENTIFIER_AND_IDENTIFIER_ARRAY_PARANETER_LIST>
            CSTNode* identifierArrayListNode = parseIdentifierAndIdentifierArrayParameterList(currNode, currToken);
            if (identifierArrayListNode == nullptr) {return nullptr;}
            currNode = currNode->link(identifierArrayListNode);
        }
    }





    // <COMMA>
    else if (currToken->getType() == COMMA) {
            CSTNode* commaNode = new CSTNode(COMMA, ",", currToken->getLineNum());
            currNode = currNode->link(commaNode);
            if (currToken->getNext() == nullptr) { return currNode;}
            currToken = currToken->getNext();
            

            // <IDENTIFIER_AND_IDENTIFIER_ARRAY_PARANETER_LIST>
            CSTNode* identifierArrayListNode = parseIdentifierAndIdentifierArrayParameterList(currNode, currToken);
            if (identifierArrayListNode == nullptr) {return nullptr;}
            currNode = currNode->link(identifierArrayListNode);
    }




    return currNode;
}








// <USER_DEFINED_PROCEDURE_CALL_STATEMENT> ::= <IDENTIFIER> <L_PAREN> <IDENTIFIER_AND_IDENTIFIER_ARRAY_PARAMETER_LIST> <R_PAREN> <SEMICOLON> | 
//                                             <IDENTIFIER> <L_PAREN> <EXPRESSION> <R_PAREN> <SEMICOLON>
CSTNode* parseUserDefinedProcedureCallStatement(CSTNode*& currNode, Token*& currToken) {



    if (currNode == nullptr) { return nullptr;} 
    if (currToken == nullptr) {return currNode;}




    // <IDENTIFIER>
    CSTNode* identifierNode = parseIdentifier(currNode, currToken);
    if (identifierNode == nullptr) {return nullptr;}
    currNode = currNode->link(identifierNode);



    // <L_PAREN>
    if (currToken->getType() != L_PAREN) { 
       if(!ERROR) { std::cerr << "Syntac error on line " << currToken->getLineNum() << "exprected (" << std::endl;}
        return nullptr;
    }
    CSTNode* lParenNode = new CSTNode(L_PAREN, "(", currToken->getLineNum());
    currNode = currNode->link(lParenNode);
    currToken = currToken->getNext();
    if (currToken->getNext() == nullptr) { return currNode;}




    // <IDENTIFIER_AND_IDENTIFIER_ARRAY_PARAMETER_LIST> | <EXPRESSION>
    CSTNode* unknownNode;
    if (currToken->getType() == IDENTIFIER) {unknownNode = parseIdentifierAndIdentifierArrayParameterList(currNode, currToken);}
    else {unknownNode = parseExpression(currNode, currToken);}
    if (unknownNode == nullptr) {return nullptr;}
    currNode = currNode->link(unknownNode);





    // <R_PAREN>
    if (currToken->getType() != R_PAREN) {
       if(!ERROR) { std::cerr << "syntax error at line << " << currToken->getLineNum() << " expected (" << "\n";}
        return nullptr;
    }
    CSTNode* rParenNode = new CSTNode(R_PAREN, ")", currToken->getLineNum());
    currNode = currNode->link(rParenNode);
    if (currToken->getNext() == nullptr) { return currNode;}
    currToken = currToken->getNext();




    // <SEMICOLON>
    if (currToken->getType() != SEMICOLON) {
        if(!ERROR) {std::cerr << "syntax error on line " << currToken->getLineNum() << " missing ';' " << "\n";}
        return nullptr;
    }
    CSTNode* semiColonNode = new CSTNode(SEMICOLON, ";", currToken->getLineNum());
    currNode = currNode->link(semiColonNode);
    if (currToken->getNext() == nullptr) { return currNode;}
    currToken = currToken->getNext();




    return currNode;
    
}









// CSTNode* parseUserDefinedFunction(CSTNode*& currNode, Token*& currToken) {
CSTNode* parseSizeofFunction(CSTNode*& currNode, Token*& currToken) {



    if (currNode == nullptr) { return nullptr;} 
    if (currToken == nullptr) {return currNode;}



    // sizeof
    CSTNode* sizeofNode = new CSTNode(IDENTIFIER, currToken->token, currToken->getLineNum());
    if (sizeofNode == nullptr) { return nullptr;}
    currNode = currNode->link(sizeofNode);

    // <L_PAREN>
    if (currToken->getType() != L_PAREN) { 
       if(!ERROR) { std::cerr << "Syntac error on line " << currToken->getLineNum() << "exprected (" << std::endl;}
        return nullptr;
    }
    CSTNode* lParenNode = new CSTNode(L_PAREN, "(", currToken->getLineNum());
    currNode = currNode->link(lParenNode);
    currToken = currToken->getNext();
    if (currToken->getNext() == nullptr) { return currNode;}


    // <IDENTIFIER>
    CSTNode* identifierNode = parseIdentifier(currNode, currToken);
    if (identifierNode == nullptr) {return nullptr;}
    currNode = currNode->link(identifierNode);



    // <R_PAREN>
    if (currToken->getType() != R_PAREN) {
       if(!ERROR) { std::cerr << "syntax error at line << " << currToken->getLineNum() << " expected (" << "\n";}
        return nullptr;
    }
    CSTNode* rParenNode = new CSTNode(R_PAREN, ")", currToken->getLineNum());
    currNode = currNode->link(rParenNode);
    if (currToken->getNext() == nullptr) { return currNode;}
    currToken = currToken->getNext();

    return currNode;



}








bool isReservedWord(Token* currToken) {
    static const std::unordered_set<std::string> reservedWords = {
        "int", "bool", "char", "void",
        "if", "else", "while", "for", "return",
        "TRUE", "FALSE",
        "printf", "getchar",
        "function", "procedure", "main"
    };
    return reservedWords.count(currToken->token) > 0;
}






CSTNode* copyTree(CSTNode* currNode) {

    CSTNode* newRoot = copyHelper(currNode->root);
    newRoot->setAllRoots(newRoot);
    CSTNode* correctNode = findCopyOfNode(currNode->root, newRoot, currNode);
    return correctNode;
}



CSTNode* copyHelper(CSTNode* currNode)  {
    if (!currNode) return nullptr;
    
    CSTNode* newNode = new CSTNode(currNode->type, currNode->value, currNode->lineNum);
        
    if (currNode->leftChild) {
        newNode->leftChild = copyHelper(currNode->leftChild);
    }
    if (currNode->rightSibling) {
        newNode->rightSibling = copyHelper(currNode->rightSibling); 
    }
    return newNode;
}


CSTNode* findCopyOfNode(CSTNode* original, CSTNode* copy, CSTNode* target) {
    if (!original || !copy) return nullptr;
    if (original == target) return copy;

    CSTNode* found = findCopyOfNode(original->leftChild, copy->leftChild, target);
    if (found) return found;
    return findCopyOfNode(original->rightSibling, copy->rightSibling, target);
}



void deleteTree(CSTNode* node) {
    if (!node) return;
    deleteTree(node->leftChild);
    deleteTree(node->rightSibling);
    delete node;
}









// <USER_DEFINED_FUNCTION> ::= <IDENTIFIER> <L_PAREN> <IDENTIFIER_AND_IDENTIFIER_ARRAY_LIST> <R_PAREN> | 
//                             <IDENTIFIER> <L_PAREN> <EXPRESSION> <R_PAREN>
CSTNode* parseUserDefinedFunction(CSTNode*& currNode, Token*& currToken) {


    if (currNode == nullptr) { return nullptr;} 
    if (currToken == nullptr) {return currNode;}

    

    // <IDENTIFIER>
    CSTNode* identifierNode = parseIdentifier(currNode, currToken);
    if (identifierNode == nullptr) {return nullptr;}
    currNode = currNode->link(identifierNode);




    // <L_PAREN>
    if (currToken->getType() != L_PAREN) { 
        if(!ERROR) {std::cerr << "Syntac error on line " << currToken->getLineNum() << "exprected (" << std::endl;}
        return nullptr;
    }
    CSTNode* lParenNode = new CSTNode(L_PAREN, "(", currToken->getLineNum());
    currNode = currNode->link(lParenNode);
    if (currToken->getNext() == nullptr) { return currNode;}
    currToken = currToken->getNext();


    ERROR++;
    CSTNode* unknownNode = nullptr;
    bool usedCopy = false;
    Token* copyToken = nullptr;
    CSTNode* copyNode = nullptr;

    // --- Try IDENTIFIER_AND_IDENTIFIER_ARRAY_LIST ---
    {
        copyToken = currToken;
        copyNode = copyTree(currNode);
        CSTNode* test = parseIdentifierAndIdentifierArrayList(copyNode, copyToken);

        if (test && copyToken && copyToken->getType() == R_PAREN) {
            currToken = copyToken;
            unknownNode = test;
            usedCopy = true;
        } else {
            deleteTree(copyNode);
            copyNode = nullptr;
        }
    }

    // --- Try Numerical Expression ---
    if (!unknownNode && couldBeNumericalExpression(currToken)) {
        copyToken = currToken;
        copyNode = copyTree(currNode);
        CSTNode* test = parseNumericalExpression(copyNode, copyToken);

        if (test && copyToken && copyToken->getType() == R_PAREN) {
            currToken = copyToken;
            unknownNode = test;
            usedCopy = true;
        } else {
            deleteTree(copyNode);
            copyNode = nullptr;
        }
    }

    // --- Try Boolean Expression ---
    if (!unknownNode && couldBeBooleanExpression(currToken)) {
        copyToken = currToken;
        copyNode = copyTree(currNode);
        CSTNode* test = parseBooleanExpression(copyNode, copyToken);

        if (test && copyToken && copyToken->getType() == R_PAREN) {
            currToken = copyToken;
            unknownNode = test;
            usedCopy = true;
        } else {
            deleteTree(copyNode);
            copyNode = nullptr;
        }
    }
    ERROR--;




    if (unknownNode == nullptr) {return nullptr;} 
    if (usedCopy && copyNode != nullptr) {
        deleteTree(currNode);   
        currNode = copyNode;       
    }
 
    currNode = currNode->link(unknownNode);



    // <R_PAREN>
    if (currToken->getType() != R_PAREN) {
       if(!ERROR) { std::cerr << "syntax error at line << " << currToken->getLineNum() << " expected (" << "\n";}
        return nullptr;
    }
    CSTNode* rParenNode = new CSTNode(R_PAREN, ")", currToken->getLineNum());
    currNode = currNode->link(rParenNode);
    if (currToken->getNext() == nullptr) { return currNode;}
    currToken = currToken->getNext();




    return currNode;

}








bool couldBeUserDefinedFunction(Token* currToken) {



    std::string tempToken = currToken->token;
    TOKEN currType = currToken->getType();


    if (currToken->getNext() == nullptr) {return false;}
    if (currToken->getNext()->getType() == L_PAREN) {
        return true;
        }

    return false;

}





// <GETCHAR_FUNCTION> ::= getchar <L_PAREN> <IDENTIFIER> <R_PAREN>
CSTNode* parseGetCharFunction(CSTNode*& currNode, Token*& currToken) {


    if (currNode == nullptr) { return nullptr;} 
    if (currToken == nullptr) {return currNode;}



    // getchar
    CSTNode* getcharNode = new CSTNode(IDENTIFIER, currToken->token, currToken->getLineNum());
    if (getcharNode == nullptr) { return nullptr;}
    currNode = currNode->link(getcharNode);

    // <L_PAREN>
    if (currToken->getType() != L_PAREN) { 
       if(!ERROR) { std::cerr << "Syntac error on line " << currToken->getLineNum() << "exprected (" << std::endl;}
        return nullptr;
    }
    CSTNode* lParenNode = new CSTNode(L_PAREN, "(", currToken->getLineNum());
    currNode = currNode->link(lParenNode);
    currToken = currToken->getNext();
    if (currToken->getNext() == nullptr) { return currNode;}


    // <IDENTIFIER>
    CSTNode* identifierNode = parseIdentifier(currNode, currToken);
    if (identifierNode == nullptr) {return nullptr;}
    currNode = currNode->link(identifierNode);



    // <R_PAREN>
    if (currToken->getType() != R_PAREN) {
       if(!ERROR) { std::cerr << "syntax error at line << " << currToken->getLineNum() << " expected (" << "\n";}
        return nullptr;
    }
    CSTNode* rParenNode = new CSTNode(R_PAREN, ")", currToken->getLineNum());
    currNode = currNode->link(rParenNode);
    if (currToken->getNext() == nullptr) { return currNode;}
    currToken = currToken->getNext();

    return currNode;
}










// <NUMERICAL_OPERAND> ::= <IDENTIFIER> | <INTEGER> | <GETCHAR_FUNCTION> | <USER_DEFINED_FUNCTION> | <SIZEOF_FUNCTION> |
//                         <IDENTIFIER> <L_BRACKET> <NUMERICAL_EXPRESSION> <R_BRACKET> | 
//                         <SINGLE_QUOTE> <CHARACTER> <SINGLE_QUOTE> | 
//                         <SINGLE_QUOTE> <ESCAPED_CHARACTER> <SINGLE_QUOTE> | 
//                         <DOUBLE_QUOTE> <CHARACTER> <DOUBLE_QUOTE> | 
//                         <DOUBLE_QUOTE> <ESCAPED_CHARACTER> <DOUBLE_QUOTE> | 
CSTNode* parseNumericalOperand(CSTNode*& currNode, Token*& currToken) { 



    if (currNode == nullptr) { return nullptr;} 
    if (currToken == nullptr) {return currNode;}

    std::string tempToken = currToken->token;
    TOKEN tempType = currToken->getType();



    // <SINGLE_QUOTE>
    if (tempType == SINGLE_QUOTE) {
        if (currToken->getNext() == nullptr) {return nullptr;}
        if (currToken->getNext()->token[0] == '\\' || currToken->getNext()->token.size() == 1) {
            CSTNode* stringNode = parseSingleQuotedString(currNode, currToken);
            if (stringNode == nullptr) {return nullptr;}
            currNode = currNode->link(stringNode);
        } else {
           if(!ERROR) { std::cerr << "Syntac error on line " << currToken->getLineNum() << "invalid single quoted string for numical operand" << std::endl;}
            return nullptr;
        }
    }


    // <DOUBLE_QUOTE>
    else if (tempType == DOUBLE_QUOTE) {
        if (currToken->getNext() == nullptr) {return nullptr;}
        if (currToken->getNext()->token == "\\" || currToken->getNext()->token.size() == 1) {
            CSTNode* stringNode = parseSingleQuotedString(currNode, currToken);
            if (stringNode == nullptr) {return nullptr;}
            currNode = currNode->link(stringNode);
        } else {
           if(!ERROR) { std::cerr << "Syntac error on line " << currToken->getLineNum() << "invalid single quoted string for numical operand" << std::endl;}
            return nullptr;
        }
    }


    // <GETCHAR_FUNCTION>
    else if (tempToken == "getchar") {
        CSTNode* getCharNode = parseGetCharFunction(currNode, currToken);
        if (getCharNode == nullptr) {return nullptr;}
        currNode = currNode->link(getCharNode);

    }



    // <SIZEOF_FUNCTION>
    else if (tempToken == "sizeof") {
        CSTNode* sizeofNode = parseSizeofFunction(currNode, currToken);
        if (sizeofNode == nullptr) {return nullptr;}
        currNode = currNode->link(sizeofNode);

    }




    // <USER_DEFINED_FUNCTION>
    else if (couldBeUserDefinedFunction(currToken)) {
        CSTNode* userNode = parseUserDefinedFunction(currNode, currToken);
        if (userNode == nullptr) {return nullptr;}
        currNode = currNode->link(userNode);
    }
    

    // <INTEGER>
    else if (std::isdigit(tempToken[0]) || tempToken[0] == '-') {
        bool isInt = true;
        for (int i = 1; i < tempToken.length(); i++) {
            if (!std::isdigit(tempToken[i])) {
                isInt = false;
            }
        }
        if (isInt) {
            CSTNode* intNode = new CSTNode(INTEGER, currToken->token, currToken->getLineNum()); 
            currNode = currNode->link(intNode);
            if (currToken->getNext() == nullptr) { return currNode;}
            currToken = currToken->getNext();
        } else {
           if(!ERROR) { std::cerr << "Syntax error on line " << currToken->getLineNum() << " Expected an int, got " << tempToken;}
            return nullptr;
        }

    }

    //<IDENTIFIER>
    else {

        CSTNode* identifierNode = parseIdentifier(currNode, currToken);
        if (identifierNode == nullptr) {return nullptr;}
        currNode = currNode->link(identifierNode);


        // <L_BRACKET> <NUMERICAL_EXPRESSION> <R_BRACKET> 
        if (currToken->getType() == L_BRACKET) {

            // <L_BRACKET>
            if (currToken->getType() != L_BRACKET) {
                if(!ERROR) {std::cerr << "syntax error at line << " << currToken->getLineNum() << " '[' should follow paramiter" << "\n";}
                return nullptr;
            }
            CSTNode* lBracketNode = new CSTNode(L_BRACKET, "[", currToken->getLineNum());
            currNode = currNode->link(lBracketNode);
            currToken = currToken->getNext();
            if (currToken->getNext() == nullptr) { return currNode;}



            // <NUMERICAL_EXPRESSION>
            CSTNode* expressionNode = parseNumericalExpression(currNode, currToken);
            if (expressionNode == nullptr) {return nullptr;}
            currNode = currNode->link(expressionNode);



            // <R_BRACKET>
            if (currToken->getType() != R_BRACKET) {
                if(!ERROR) {std::cerr << "syntax error at line << " << currToken->getLineNum() << " unclosed ]" << "\n";}
                return nullptr;
            }
            CSTNode* rBracketNode = new CSTNode(R_BRACKET, "]", currToken->getLineNum());
            currNode = currNode->link(rBracketNode);
            currToken = currToken->getNext();
            if (currToken->getNext() == nullptr) { return currNode;}
        }

    }


    return currNode;


}







bool couldBeNumericalOperand(Token* currToken) {



    Token* temp = currToken;


    std::string tempToken = currToken->token;
    TOKEN tempType = currToken->getType();



    if (tempType == L_PAREN) {
        if (currToken->getNext() != nullptr) {
            tempType = currToken->getNext()->getType();
            tempToken = currToken->getNext()->token;
        }
    }



    // <SINGLE_QUOTE>
    else if (tempType == SINGLE_QUOTE) {
        if (currToken->getNext() == nullptr) {return false;}
        if (currToken->getNext()->token == "\\" || currToken->getNext()->token.size() == 1) {
            return true;
        } 
    }


    // <DOUBLE_QUOTE>
    else if (tempType == DOUBLE_QUOTE) {
        if (currToken->getNext() == nullptr) {return false;}
        if (currToken->getNext()->token == "\\" || currToken->getNext()->token.size() == 1) {
            return true;
        } 
    }


    // <GETCHAR_FUNCTION>
    else if (tempToken == "getchar") {
        return true;
    }



    // <SIZEOF_FUNCTION>
    else if (tempToken == "sizeof") {
        return true;
    }



    // <USER_DEFINED_FUNCTION>
    else if (couldBeUserDefinedFunction(currToken)) {
        return true;
    }
    

    // <INTEGER>
    else if (std::isdigit(tempToken[0]) || tempToken[0] == '-') {
        bool isInt = true;
        if (tempToken.size() == 1) {return true;}
        for (int i = 1; i < tempToken.length(); i++) {
            if (!std::isdigit(tempToken[i])) {
                isInt = false;
            }
        }
        if (isInt) {
            return true;
        } 
    }



    // <IDENTIFIER>
    else if (tempType == IDENTIFIER) {
        return true;
    }


    return false;

}






bool couldBeNumericalExpression(Token* currToken) {

    TOKEN tempType = currToken->getType();



    // <L_PAREN>
    if (tempType == L_PAREN) {
    if (currToken->getNext() == nullptr) { return false;}
    currToken = currToken->getNext();

        // <NUMERICAL_OPERAND>
        if (!couldBeNumericalOperand(currToken)) {return false;}
        if (currToken->getNext() == nullptr) { return false;}
        currToken = currToken->getNext();


        // <R_PAREN>
        if (currToken->getType() == R_PAREN) { return true;} 


        // <NUMERICAL_OPERATOR>
        else {
            tempType = currToken->getType();
            if (tempType != MINUS && tempType != PLUS && tempType != ASTERISK && tempType != DIVIDE && tempType != MODULO && tempType != CARET) {return false;}
            if (currToken->getNext() == nullptr) { return false;}
            currToken = currToken->getNext();


            // <NUMERICAL_EXPRESSION>
            if (!couldBeNumericalExpression(currToken)) {return false;}
            if (currToken->getNext() == nullptr) { return false;}
            currToken = currToken->getNext();



            // <R_PAREN>
            if (currToken->getType() == R_PAREN) {return true;}
            if (currToken->getNext() == nullptr) { return false;}
            currToken = currToken->getNext();



            // <NUMERICAL_OPERATOR>
            tempType = currToken->getType();
            if (tempType == MINUS || tempType == PLUS || tempType == ASTERISK || tempType == DIVIDE || tempType == MODULO || tempType == CARET) {
                if (currToken->getNext() == nullptr) { return false;}
                currToken = currToken->getNext();


                // <NUMERICAL_EXPRESSION>
                if (!couldBeNumericalExpression(currToken)) {return false;}
                return true;
            }
        }
    }




    // <NUMERICAL_OPERATOR>
    else if (tempType == MINUS || tempType == PLUS || tempType == ASTERISK || tempType == DIVIDE || tempType == MODULO || tempType == CARET) {
        if (currToken->getNext() == nullptr) { return false;}
        currToken = currToken->getNext();
        

        // <NUMERICAL_EXPRESSION>
        if (!couldBeNumericalExpression(currToken)) {return false;}
        return true;
    }




    // <NUMERICAL_OPERAND>
    else {
        if (!couldBeNumericalOperand(currToken)) {return false;}
        return true;
        if (currToken->getNext() == nullptr) { return false;}
        currToken = currToken->getNext();


        // <NUMERICAL_OPERATOR>
        tempType = currToken->getType();
        if (tempType == MINUS || tempType == PLUS || tempType == ASTERISK || tempType == DIVIDE || tempType == MODULO || tempType == CARET) {
            if (currToken->getNext() == nullptr) { return false;}
            currToken = currToken->getNext();


            
            // <L_PAREN>
            if (currToken->getType() == L_PAREN) {
                if (currToken->getNext() == nullptr) { return false;}
                currToken = currToken->getNext();


                // <NUMERICAL_EXPRESSION>
                if (!couldBeNumericalExpression(currToken)) {return false;}
                if (currToken->getNext() == nullptr) { return false;}
                currToken = currToken->getNext();

                // <R_PAREN>
                if (currToken->getType() == R_PAREN) { return true;}



                // <NUMERICAL_OPERATOR>
                else {
                    tempType = currToken->getType();
                    if (tempType != MINUS && tempType != PLUS && tempType != ASTERISK && tempType != DIVIDE && tempType != MODULO && tempType != CARET) {return false;}


                    // <NUMERICAL_EXPRESSION>
                    if (!couldBeNumericalExpression(currToken)) {return false;}
                    return true;

                }
            }


            // <NUMERICAL_EXPRESSION>
            else {
                if (!couldBeNumericalExpression(currToken)) {return false;}
                return true;
            }
        }
    }

    return false;
}













bool couldBeNumericalExpressionThenBoolean(Token* currToken) {

    Token* temp = currToken;


    std::string tempToken = currToken->token;
    TOKEN currType = currToken->getType();


    if (currType == L_PAREN) {
        if (couldBeNumericalOperand(temp)) {
            if (temp->getNext() != nullptr) {
                if (temp->getNext()->getType() == R_PAREN || temp->getNext()->getType() == PLUS || temp->getNext()->getType() == MINUS || temp->getNext()->getType() == ASTERISK || 
                    temp->getNext()->getType() == DIVIDE || temp->getNext()->getType() == MODULO || temp->getNext()->getType() == CARET) {
                    if (temp->getNext()->getNext()->getNext() != nullptr) {
                        TOKEN tempType = currToken->getNext()->getNext()->getNext()->getType();
                        if (tempType == LT || tempType == GT || tempType == LT_EQUAL || tempType == GT_EQUAL || tempType == BOOLEAN_EQUAL || tempType == BOOLEAN_NOT_EQUAL || tempType == BOOLEAN_AND || tempType == BOOLEAN_OR) {
                            return true;
                        }
    
                    }

                }
            }
        }
    }


    else  {



        // <DOUBLE_QUOTE> || <SINGLE_QUOTE>
        if (currType == DOUBLE_QUOTE || currType == SINGLE_QUOTE) {
            if (currToken->getNext() == nullptr) {return false;}
            if (currToken->getNext()->token == "\\" || currToken->getNext()->token.size() == 1) {
                if (currToken->getNext()->getNext() == nullptr) {return false;}
                if (currToken->getNext()->getNext()->getType() == DOUBLE_QUOTE || currToken->getNext()->getNext()->getType() == SINGLE_QUOTE) {
                if (currToken->getNext()->getNext()->getNext() == nullptr) {return false;}
                    TOKEN tempType = currToken->getNext()->getNext()->getNext()->getType();
                    if (tempType == LT || tempType == GT || tempType == LT_EQUAL || tempType == GT_EQUAL || tempType == BOOLEAN_EQUAL || tempType == BOOLEAN_NOT_EQUAL || tempType == BOOLEAN_AND || tempType == BOOLEAN_OR) {
                        return true;
                    }
                }

            } 
        }


        // <INTEGER>
        else if (std::isdigit(tempToken[0]) || tempToken[0] == '-') {
            bool isInt = true;
            for (int i = 1; i < tempToken.length(); i++) {
                if (!std::isdigit(tempToken[i])) {
                    isInt = false;
                }
            }
            if (isInt) {
                if (currToken->getNext() == nullptr) {return false;}
                TOKEN tempType = currToken->getNext()->getType();
                if (tempType == LT || tempType == GT || tempType == LT_EQUAL || tempType == GT_EQUAL || tempType == BOOLEAN_EQUAL || tempType == BOOLEAN_NOT_EQUAL || tempType == BOOLEAN_AND || tempType == BOOLEAN_OR) {
                    return true;
                }
            } 
        }



        // <IDENTIFIER>
        else if (currToken->getType() == IDENTIFIER) {
            if (currToken->getNext() == nullptr) {return false;}
            TOKEN tempType = currToken->getNext()->getType();
            if (tempType == LT || tempType == GT || tempType == LT_EQUAL || tempType == GT_EQUAL || tempType == BOOLEAN_EQUAL || tempType == BOOLEAN_NOT_EQUAL || tempType == BOOLEAN_AND || tempType == BOOLEAN_OR) {
                return true;
            }
        }

    }


    return false;
}














// <NUMERICAL_EXPRESSION> ::= <NUMERICAL_OPERAND> | 
//                            <NUMERICAL_OPERAND> <NUMERICAL_OPERATOR> <NUMERICAL_EXPRESSION> | 
//                            <NUMERICAL_OPERAND> <NUMERICAL_OPERATOR> <L_PAREN> <NUMERICAL_EXPRESSION> <R_PAREN> <NUMERICAL_OPERATOR> <NUMERICAL_EXPRESSION> | 
//                            <NUMERICAL_OPERAND> <NUMERICAL_OPERATOR> <L_PAREN> <NUMERICAL_EXPRESSION> <R_PAREN> | 
//                            <L_PAREN> <NUMERICAL_OPERAND> <R_PAREN> | 
//                            <L_PAREN> <NUMERICAL_OPERAND> <NUMERICAL_OPERATOR> <NUMERICAL_EXPRESSION> <R_PAREN> | 
//                            <L_PAREN> <NUMERICAL_OPERAND> <NUMERICAL_OPERATOR> <NUMERICAL_EXPRESSION> <R_PAREN> | 
//                            <L_PAREN> <NUMERICAL_OPERAND> <NUMERICAL_OPERATOR> <NUMERICAL_EXPRESSION> <R_PAREN> <NUMERICAL_OPERATOR> <NUMERICAL_EXPRESSION> | 
//                            <NUMERICAL_OPERATOR> <NUMERICAL_EXPRESSION>
CSTNode* parseNumericalExpression(CSTNode*& currNode, Token*& currToken) { 


    if (currNode == nullptr) { return nullptr;} 
    if (currToken == nullptr) {return currNode;}

    TOKEN tempType = currToken->getType();



    // <L_PAREN>
    if (tempType == L_PAREN) {
        CSTNode* lParenNode = new CSTNode(L_PAREN, "(", currToken->getLineNum());
        currNode = currNode->link(lParenNode);
        if (currToken->getNext() == nullptr) { return currNode;}
        currToken = currToken->getNext();

        // <NUMERICAL_OPERAND>
        CSTNode* operandNode = parseNumericalOperand(currNode, currToken);
        if (operandNode == nullptr) {return nullptr;}
        currNode = currNode->link(operandNode);



        // <R_PAREN>
        if (currToken->getType() == R_PAREN) {
            CSTNode* rParenNode = new CSTNode(R_PAREN, ")", currToken->getLineNum());
            currNode = currNode->link(rParenNode);
            if (currToken->getNext() == nullptr) { return currNode;}
            currToken = currToken->getNext();
        } 



        // <NUMERICAL_OPERATOR>
        else {
            tempType = currToken->getType();
            if (tempType != MINUS && tempType != PLUS && tempType != ASTERISK && tempType != DIVIDE && tempType != MODULO && tempType != CARET) {
                if(!ERROR) {std::cerr << "syntax error at line << " << currToken->getLineNum() << " expected numerical operator got " << currToken->token << "\n";}
                return nullptr;
            }
            CSTNode* operatorNode = new CSTNode(tempType, currToken->token, currToken->getLineNum());
            currNode = currNode->link(operatorNode);
            if (currToken->getNext() == nullptr) { return currNode;}
            currToken = currToken->getNext();
         


            // <NUMERICAL_EXPRESSION>  // fourth call at the last n
            CSTNode* expressionNode = parseNumericalExpression(currNode, currToken);
            currNode = currNode->link(expressionNode);
            if (currToken->getNext() == nullptr) { return currNode;}
           // currToken = currToken->getNext();



            // <R_PAREN>
            if (currToken->getType() != R_PAREN) {
                if(!ERROR) {std::cerr << "syntax error at line << " << currToken->getLineNum() << " expected (" << "\n";}
                return nullptr;
            }
            CSTNode* rParenNode = new CSTNode(R_PAREN, ")", currToken->getLineNum());
            currNode = currNode->link(rParenNode);
            if (currToken->getNext() == nullptr) { return currNode;}
            currToken = currToken->getNext();



            // <NUMERICAL_OPERATOR>
            tempType = currToken->getType();
            if (tempType == MINUS || tempType == PLUS || tempType == ASTERISK || tempType == DIVIDE || tempType == MODULO || tempType == CARET) {
                CSTNode* operatorNode2 = new CSTNode(tempType, currToken->token, currToken->getLineNum());
                currNode = currNode->link(operatorNode2);
                if (currToken->getNext() == nullptr) { return currNode;}
                currToken = currToken->getNext();


                // <NUMERICAL_EXPRESSION>
                CSTNode* expressionNode2 = parseNumericalExpression(currNode, currToken);
                currNode = currNode->link(expressionNode2);
                if (currToken->getNext() == nullptr) { return currNode;}
                //currToken = currToken->getNext();
            }
        }
    }






    // <NUMERICAL_OPERATOR>
    else if (tempType == MINUS || tempType == PLUS || tempType == ASTERISK || tempType == DIVIDE || tempType == MODULO || tempType == CARET) {
        CSTNode* operatorNode = new CSTNode(tempType, currToken->token, currToken->getLineNum());
        currNode = currNode->link(operatorNode);
        if (currToken->getNext() == nullptr) { return currNode;}
        currToken = currToken->getNext();
        

        // <NUMERICAL_EXPRESSION>
        CSTNode* expressionNode = parseNumericalExpression(currNode, currToken);
        if (expressionNode == nullptr) {return nullptr;}
        currNode = currNode->link(expressionNode);
    }





    // <NUMERICAL_OPERAND>
    else {
        CSTNode* operandNode = parseNumericalOperand(currNode, currToken);
        if (operandNode == nullptr) {return nullptr;}
        currNode = currNode->link(operandNode);

        // <NUMERICAL_OPERATOR>
        tempType = currToken->getType();
        if (tempType == MINUS || tempType == PLUS || tempType == ASTERISK || tempType == DIVIDE || tempType == MODULO || tempType == CARET) {
            CSTNode* operatorNode = new CSTNode(tempType, currToken->token, currToken->getLineNum());
            currNode = currNode->link(operatorNode);
            if (currToken->getNext() == nullptr) { return currNode;}
            currToken = currToken->getNext();


            
            // <L_PAREN>
            if (currToken->getType() == L_PAREN) {
                CSTNode* lParenNode = new CSTNode(L_PAREN, "(", currToken->getLineNum());
                currNode = currNode->link(lParenNode);
                if (currToken->getNext() == nullptr) { return currNode;}
                currToken = currToken->getNext();


                // <NUMERICAL_EXPRESSION>   // first call at 2nd n (done)
                CSTNode* expressionNode = parseNumericalExpression(currNode, currToken);
                if (expressionNode == nullptr) {return nullptr;}
                currNode = currNode->link(expressionNode);



                // <R_PAREN>
                if (currToken->getType() != R_PAREN) {
                    if(!ERROR) {std::cerr << "syntax error at line << " << currToken->getLineNum() << " unclosed ')' in boolean expression" << "\n";}
                    return nullptr;
                }
                CSTNode* rParenNode = new CSTNode(R_PAREN, ")", currToken->getLineNum());
                currNode = currNode->link(rParenNode);
                if (currToken->getNext() == nullptr) { return currNode;}
                currToken = currToken->getNext();



                // <NUMERICAL_OPERATOR>
                tempType = currToken->getType();
                if (tempType == MINUS || tempType == PLUS || tempType == ASTERISK || tempType == DIVIDE || tempType == MODULO || tempType == CARET) {
                    CSTNode* operatorNode = new CSTNode(tempType, currToken->token, currToken->getLineNum());
                    currNode = currNode->link(operatorNode);
                    if (currToken->getNext() == nullptr) { return currNode;}
                    currToken = currToken->getNext();


                    // <NUMERICAL_EXPRESSION>  // third call at second (
                    CSTNode* expressionNode2 = parseNumericalExpression(currNode, currToken);
                    if (expressionNode2 == nullptr) {return nullptr;}
                    currNode = currNode->link(expressionNode2);

                }
            }




            // <NUMERICAL_EXPRESSION>  // 2nd call at the 1(done)     // fith fall at last 1
            else {
                CSTNode* expressionNode = parseNumericalExpression(currNode, currToken);
                if (expressionNode == nullptr) {return nullptr;}
                currNode = currNode->link(expressionNode);
            }
        }
    }


    return currNode;
}






// <BOOLEAN_OPERATOR> ::= <BOOLEAN_AND_OPERATOR> | <BOOLEAN_OR_OPERATOR>
CSTNode* parseBooleanOperator(CSTNode*& currNode, Token*& currToken) { 


    if (currNode == nullptr) { return nullptr;} 
    if (currToken == nullptr) {return currNode;}


    CSTNode* operatorNode;
    if (currToken->token == "&&") {
        operatorNode = new CSTNode(BOOLEAN_AND, "&&", currToken->getLineNum());
    } else if (currToken->token == "||") {
        operatorNode = new CSTNode(BOOLEAN_OR, "||", currToken->getLineNum());
    } else {
        if(!ERROR) {std::cerr << "Syntac error on line " << currToken->getLineNum() << " exped boolean operator" << "\n";}
        return nullptr;
    }
    currNode = currNode->link(operatorNode);
    if (currToken->getNext() == nullptr) { return currNode;}
    currToken = currToken->getNext();
    



    return currNode;
}






// <EXPRESSION> ::= <BOOLEAN_EXPRESSION> | <NUMERICAL_EXPRESSION>
CSTNode* parseExpression(CSTNode*& currNode, Token*& currToken) { 

    if (currNode == nullptr) { return nullptr;} 
    if (currToken == nullptr) {return currNode;}


    ERROR++;
    Token* copyToken = currToken;
    CSTNode* copyNode = copyTree(currNode);
    CSTNode* expressionNode = nullptr;


    if (couldBeBooleanExpression(copyToken)) {
        expressionNode = parseBooleanExpression(copyNode, copyToken);
    }

    if (expressionNode == nullptr) {
        // delete copy tree
        deleteTree(copyNode);
        copyToken = currToken;
        

        if (couldBeNumericalExpression(copyToken)) {
            expressionNode = parseNumericalExpression(currNode, copyToken);
        }
    } else {
        deleteTree(currNode);   
        currNode = copyNode;
        
    }
    ERROR--;    


    
    if (expressionNode == nullptr) {return nullptr;}
    currToken = copyToken;
    currNode = currNode->link(expressionNode);


    
    return currNode;


}








bool couldBeBooleanExpression(Token* currToken) {


    std::string tempToken = currToken->token;
    TOKEN tempType = currToken->getType();


    // <BOOLEAN_TRUE>  
    if (tempType == BOOLEAN_TRUE) {return true;}

    // <BOOLEAN_FALSE> 
    else if (tempType == BOOLEAN_FALSE) { return true;}


    // <BOOLEAN_NOT> 
    else if (tempType == BOOLEAN_NOT) {
        if (currToken->getNext() == nullptr) { return false;}
        currToken = currToken->getNext();


        // <BOOLEAN_NOT> <BOOLEAN_TRUE> | <BOOLEAN_NOT> <BOOLEAN_FALSE> | <BOOLEAN_NOT> <IDENTIFIER> | <BOOLEAN_NOT> <USER_DEFINED_FUNCTION> |
        CSTNode* unknownNode;
        if (currToken->getType() == BOOLEAN_TRUE) {return true;}
        else if (currToken->getType() == BOOLEAN_FALSE) {return true;}
        else if (couldBeUserDefinedFunction(currToken)) {return true;}
        else if (currToken->getType() == IDENTIFIER) {return true;}

    }


    
    //<USER_DEFINED_FUNCTION> | <USER_DEFINED_FUNCTION> <BOOLEAN_OPERATOR> <BOOLEAN_EXPRESSION> | 
    else if (couldBeUserDefinedFunction(currToken)) { return true;}



    // <NUMERICAL_EXPRESSION>
    else if (couldBeNumericalExpression(currToken)) {
        if (currToken->getNext() == nullptr) { false;}
        currToken = currToken->getNext();
            tempToken = currToken->getType();
            if (tempType == BOOLEAN_EQUAL || tempType == BOOLEAN_NOT_EQUAL || tempType == LT_EQUAL || tempType == GT_EQUAL || tempType == LT || tempType == GT || tempType == BOOLEAN_AND || tempType == BOOLEAN_OR) {
                if (currToken->getNext() && couldBeNumericalExpression(currToken->getNext())) {return true;}
            }
        }
    



    // <L_PAREN>
    else if (tempType == L_PAREN) {
        if (currToken->getNext() == nullptr) { false;}
        currToken = currToken->getNext();




        // <BOOLEAN_NOT>
        if (currToken->getType() == BOOLEAN_NOT) {
                if (currToken->getNext() == nullptr) { return false;}
                currToken = currToken->getNext();


                // <USER_DEFINED_FUNCTION>
                if (couldBeUserDefinedFunction(currToken)) {
                if (currToken->getNext() == nullptr) { return false;}
                currToken = currToken->getNext();

                // <R_PAREN>
                if (currToken->getType() != R_PAREN) {return false;}
                if (currToken->getNext() == nullptr) { return false;}
                currToken = currToken->getNext();

                return true;
            }



            // <IDENTIFIER>
            else if (currToken->getType() == IDENTIFIER){
                if (currToken->getNext() == nullptr) { return false;}
                currToken = currToken->getNext();

        
                if (currToken->getType() == R_PAREN) { return true;}


                
                // <BOOLEAN_OPERATOR> <BOOLEAN_EXPRESSION> <R_PAREN> 
                else {

    
                    // <BOOLEAN_OPERATOR>
                    tempType = currToken->getType();
                    if (tempType == BOOLEAN_AND || tempType == BOOLEAN_OR) {
                        if (!currToken->getNext()) { return false;}
                        currToken = currToken->getNext();
                        
                        // <BOOLEAN_EXPRESSION> 
                        if (!couldBeBooleanExpression(currToken)) {return false;}
                        if (!currToken->getNext()) { return false;}
                        currToken = currToken->getNext();


                        // <R_PAREN> 
                        if (currToken->getType() != R_PAREN) { return false;}
                        return true;
                    }
                }
            }
        }





        // <USER_DEFINED_FUNCTION>
        else if (couldBeUserDefinedFunction(currToken)) {
                if (!currToken->getNext()) { return false;}
                currToken = currToken->getNext();

                if (currToken->getType() == R_PAREN) { return true;}
        }





        // <NUMERICAL_OPERAND> || <IDENTIFIER>
        else{

            if (currToken->getType() == IDENTIFIER && currToken->getNext() && 
                   (currToken->getNext()->getType() == BOOLEAN_AND || currToken->getNext()->getType() == BOOLEAN_OR)) {
                
                
                // <IDENTIFIER>
                if (currToken->getType() != IDENTIFIER) {return false;}
                if (currToken->getNext() == nullptr) { false;}
                currToken = currToken->getNext();


                // <BOOLEAN_OPERATOR>
                if (currToken->getType() != BOOLEAN_AND || currToken->getType() != BOOLEAN_OR) { return false;}
                if (currToken->getNext() == nullptr) { false;}
                currToken = currToken->getNext();
               

            
                // <BOOLEAN_EXPRESSION> 
                if (!couldBeBooleanExpression(currToken)) {return false;}
                if (currToken->getNext() == nullptr) { false;}
                currToken = currToken->getNext();


                // <R_PAREN>
                if (currToken->getType() != R_PAREN) {return false;}
                return true;
            } else {


                // <NUMERICAL_OPERAND>
                if (!couldBeNumericalOperand(currToken)) {return false;}
                if (currToken->getNext() == nullptr) { false;}
                currToken = currToken->getNext();


                // <REALATIONAL_EXPRESSION>
                tempType = currToken->getType();
                if (tempType != LT && tempType != LT_EQUAL && tempType != GT && tempType != GT_EQUAL && tempType != BOOLEAN_EQUAL && tempType != BOOLEAN_NOT_EQUAL) {return false;}
                if (currToken->getNext() == nullptr) { false;}
                currToken = currToken->getNext();


                // <NUMERICAL_EXPRESSION>
                if (!couldBeNumericalExpression(currToken)) {return false;}
                if (currToken->getNext() == nullptr) { false;}
                currToken = currToken->getNext();


                // <R_PAREN>
                if (currToken->getType() != R_PAREN) { return false;}
                return true;

               }
            }
        }
    return false;
}














// <BOOLEAN_EXPRESSION> ::= <BOOLEAN_TRUE> | <BOOLEAN_FALSE> | <IDENTIFIER> | 
//                          <BOOLEAN_NOT> <BOOLEAN_TRUE> | 
//                          <BOOLEAN_NOT> <BOOLEAN_FALSE> | 
//                          <BOOLEAN_NOT> <IDENTIFIER> | 
//                          <BOOLEAN_NOT> <USER_DEFINED_FUNCTION> | 
//                          <USER_DEFINED_FUNCTION> | 
//                          <USER_DEFINED_FUNCTION> <BOOLEAN_OPERATOR> <BOOLEAN_EXPRESSION> | 
//                          <NUMERICAL_EXPRESSION> <BOOLEAN_EQUAL> <NUMERICAL_EXPRESSION> | 
//                          <NUMERICAL_EXPRESSION> <BOOLEAN_NOT_EQUAL> <NUMERICAL_EXPRESSION> | 
//                          <NUMERICAL_EXPRESSION> <LT_EQUAL> <NUMERICAL_EXPRESSION> | 
//                          <NUMERICAL_EXPRESSION> <GT_EQUAL> <NUMERICAL_EXPRESSION> | 
//                          <NUMERICAL_EXPRESSION> <LT> <NUMERICAL_EXPRESSION> | 
//                          <NUMERICAL_EXPRESSION> <GT> <NUMERICAL_EXPRESSION> | 
//                          <IDENTIFIER> <BOOLEAN_OPERATOR> <BOOLEAN_EXPRESSION> | 
//                          <L_PAREN> <USER_DEFINED_FUNCTION> <R_PAREN> | 
//                          <L_PAREN> <IDENTIFIER> <BOOLEAN_OPERATOR> <BOOLEAN_EXPRESSION> <R_PAREN> | 
//                          <L_PAREN> <NUMERICAL_OPERAND> <RELATIONAL_EXPRESSION> <NUMERICAL_OPERAND> <R_PAREN> | 
//                          <L_PAREN> <NUMERICAL_OPERAND> <RELATIONAL_EXPRESSION> <NUMERICAL_OPERAND> <R_PAREN> <BOOLEAN_OPERATOR> <BOOLEAN_EXPRESSION> | 
//                          <L_PAREN> <BOOLEAN_NOT> <IDENTIFIER> <R_PAREN> | 
//                          <L_PAREN> <BOOLEAN_NOT> <IDENTIFIER> <BOOLEAN_OPERATOR> <BOOLEAN_EXPRESSION> <R_PAREN> | 
//                          <L_PAREN> <BOOLEAN_NOT> <USER_DEFINED_FUNCTION> <R_PAREN> | 
//                          <L_PAREN> <BOOLEAN_NOT> <USER_DEFINED_FUNCTION> <R_PAREN> <BOOLEAN_OPERATOR> <BOOLEAN_EXPRESSION> | 
//                          <L_PAREN> <NUMERICAL_OPERAND> <RELATIONAL_EXPRESSION> <NUMERICAL_EXPRESSION> <R_PAREN>
CSTNode* parseBooleanExpression(CSTNode*& currNode, Token*& currToken) { 


    if (currNode == nullptr) { return nullptr;} 
    if (currToken == nullptr) {return currNode;}




    std::string tempToken = currToken->token;
    TOKEN tempType = currToken->getType();


    // <BOOLEAN_TRUE>  
    if (tempType == BOOLEAN_TRUE) {
        CSTNode* trueNode = new CSTNode(BOOLEAN_TRUE, "TRUE", currToken->getLineNum());
        currNode = currNode->link(trueNode);
        if (currToken->getNext() == nullptr) { return currNode;}
        currToken = currToken->getNext();
    }

    // <BOOLEAN_FALSE> 
    else if (tempType == BOOLEAN_FALSE) {
        CSTNode* falseNode = new CSTNode(BOOLEAN_FALSE, "FALSE", currToken->getLineNum());
        currNode = currNode->link(falseNode);
        if (currToken->getNext() == nullptr) { return currNode;}
        currToken = currToken->getNext();
    }




    // <BOOLEAN_NOT> 
    else if (tempType == BOOLEAN_NOT) {
        CSTNode* notNode = new CSTNode(BOOLEAN_NOT, "!", currToken->getLineNum());
        currNode = currNode->link(notNode);
        if (currToken->getNext() == nullptr) { return currNode;}
        currToken = currToken->getNext();


        // <BOOLEAN_NOT> <BOOLEAN_TRUE> | <BOOLEAN_NOT> <BOOLEAN_FALSE> | <BOOLEAN_NOT> <IDENTIFIER> | <BOOLEAN_NOT> <USER_DEFINED_FUNCTION> |
        tempType = currToken->getType();
        if (tempType == BOOLEAN_TRUE || tempType == BOOLEAN_FALSE) {
            CSTNode* booleanNode = new CSTNode(tempType, currToken->token, currToken->getLineNum());
            currNode = currNode->link(booleanNode);
            if (currToken->getNext() == nullptr) { return currNode;}
            currToken = currToken->getNext();

            
        }
        else if (couldBeUserDefinedFunction(currToken)) {
            CSTNode* userDefinedNode = parseUserDefinedFunction(currNode, currToken);
            if (!userDefinedNode) {return nullptr;}
            currNode = currNode->link(userDefinedNode);

            }
        else {

            CSTNode* identifierNode = parseIdentifier(currNode, currToken);
            if (!identifierNode) {return nullptr;}
            currNode = currNode->link(identifierNode);
            }
    }


    
    //<USER_DEFINED_FUNCTION> | <USER_DEFINED_FUNCTION> <BOOLEAN_OPERATOR> <BOOLEAN_EXPRESSION> | 
    else if (couldBeUserDefinedFunction(currToken)) {
        CSTNode* userDefinedNode = parseUserDefinedFunction(currNode, currToken);
        if (userDefinedNode == nullptr) {return nullptr;}
        currNode = currNode->link(userDefinedNode);
            

        tempType = currToken->getType();
        if (tempType == BOOLEAN_AND || tempType == BOOLEAN_OR) {
            CSTNode* operatorNode = new CSTNode(tempType, currToken->token, currToken->getLineNum());
            currNode = currNode->link(operatorNode);
            if (!currToken->getNext()) { return currNode;}
            currToken = currToken->getNext();

            
            // <BOOLEAN_EXPRESSION> 
            CSTNode* booleanExpressionNode = parseBooleanExpression(currNode, currToken);
            if (booleanExpressionNode == nullptr) {return nullptr;}
            currNode = currNode->link(booleanExpressionNode);
        }
    }






    // <NUMERICAL_EXPRESSION>
    else if (couldBeNumericalExpression(currToken)) {
        if (currToken->getType() == IDENTIFIER && currToken->getNext() && 
               (currToken->getNext()->getType() == BOOLEAN_AND || currToken->getNext()->getType() == BOOLEAN_OR)) {
            
            
            // <IDENTIFIER>
            CSTNode* identifierNode = parseIdentifier(currNode, currToken);
            if (identifierNode == nullptr) {return nullptr;}


            // <BOOLEAN_OPERATOR>
            tempType = currToken->getType();
            CSTNode* operatorNode = new CSTNode(tempType, currToken->token, currToken->getLineNum());
            currNode = currNode->link(operatorNode);
            if (!currToken->getNext()) { return currNode;}
            currToken = currToken->getNext();


            // <BOOLEAN_EXPRESSION> 
            CSTNode* booleanExpressionNode = parseBooleanExpression(currNode, currToken);
            if (booleanExpressionNode == nullptr) {return nullptr;}
            currNode = currNode->link(booleanExpressionNode);
        } else {


            // <NUMERICAL_EXPRESSION>
            CSTNode* expressionNode = parseNumericalExpression(currNode, currToken);
            if (expressionNode == nullptr) {return nullptr;}
            currNode = currNode->link(expressionNode);




            CSTNode* operatorNode; 
            tempType = currToken->getType();
            if (tempType == BOOLEAN_EQUAL) {operatorNode = new CSTNode(BOOLEAN_EQUAL, "==", currToken->getLineNum());}
            else if (tempType == BOOLEAN_NOT_EQUAL) {operatorNode = new CSTNode(BOOLEAN_NOT_EQUAL, "!=", currToken->getLineNum());}
            else if (tempType == LT_EQUAL) {operatorNode = new CSTNode(LT_EQUAL, "<=", currToken->getLineNum());}
            else if (tempType == GT_EQUAL) {operatorNode = new CSTNode(GT_EQUAL, ">=", currToken->getLineNum());}
            else if (tempType == LT) {operatorNode = new CSTNode(LT, "<", currToken->getLineNum());}
            else if (tempType == GT) {operatorNode = new CSTNode(GT, ">", currToken->getLineNum());} 
            else {
                if (!ERROR) {std::cerr << "syntax error at line << " << currToken->getLineNum() << " exprected an operator, got (boolean expression)" << currToken->token  << ":  " << currToken->typeToStr() << "\n";}
                return nullptr;
            }
            currNode = currNode->link(operatorNode);
            if (currToken->getNext() == nullptr) { return currNode;}
            currToken = currToken->getNext();



            // <NUMERICAL_EXPRESSION>
            CSTNode* expressionNode2 = parseNumericalExpression(currNode, currToken);
            if (expressionNode2 == nullptr) {return nullptr;}
            currNode = currNode->link(expressionNode2);

    
        }
    }





    // <L_PAREN>
    else if (tempType == L_PAREN) {
        CSTNode* lParenNode = new CSTNode(L_PAREN, "(", currToken->getLineNum());
        currNode = currNode->link(lParenNode);
        if (currToken->getNext() == nullptr) { return currNode;}
        currToken = currToken->getNext();






        // <BOOLEAN_NOT>
        if (currToken->getType() == BOOLEAN_NOT) {
            CSTNode* notNode = new CSTNode(BOOLEAN_NOT, "!", currToken->getLineNum());
            currNode = currNode->link(notNode);
            if (currToken->getNext() == nullptr) { return notNode;}
            currToken = currToken->getNext();



            // <USER_DEFINED_FUNCTION>
            if (couldBeUserDefinedFunction(currToken)) {
                CSTNode* userNode = parseUserDefinedFunction(currNode, currToken);
                if (userNode == nullptr) {return nullptr;}
                currNode = currNode->link(userNode);



                // <R_PAREN>
                CSTNode* rParenNode = new CSTNode(R_PAREN, ")", currToken->getLineNum());
                currNode = currNode->link(rParenNode);
                if (currToken->getNext() == nullptr) { return currNode;}
                currToken = currToken->getNext();



                // <BOOLEAN_OPERATOR>
                tempType = currToken->getType();
                if (tempType == BOOLEAN_AND || tempType == BOOLEAN_OR) {
                    CSTNode* operatorNode = new CSTNode(tempType, currToken->token, currToken->getLineNum());
                    currNode = currNode->link(operatorNode);
                    if (!currToken->getNext()) { return currNode;}
                    currToken = currToken->getNext();

                    
                    // <BOOLEAN_EXPRESSION> 
                    CSTNode* booleanExpressionNode = parseBooleanExpression(currNode, currToken);
                    if (booleanExpressionNode == nullptr) {return nullptr;}
                    currNode = currNode->link(booleanExpressionNode);
                }
            }



            // <IDENTIFIER>
            else {
                CSTNode* identifierNode = parseIdentifier(currNode, currToken);
                if (identifierNode == nullptr) {return nullptr;}
                currNode = currNode->link(identifierNode);

        
                if (currToken->getType() == R_PAREN) {
                    CSTNode* rParenNode2 = new CSTNode(R_PAREN, ")", currToken->getLineNum());
                    currNode = currNode->link(rParenNode2);
                    if (currToken->getNext() == nullptr) { return currNode;}
                    currToken = currToken->getNext();
                }


                
                // <BOOLEAN_OPERATOR> <BOOLEAN_EXPRESSION> <R_PAREN> 
                else {

    
                    // <BOOLEAN_OPERATOR>
                    tempType = currToken->getType();
                    if (tempType == BOOLEAN_AND || tempType == BOOLEAN_OR) {
                        CSTNode* operatorNode = new CSTNode(tempType, currToken->token, currToken->getLineNum());
                        currNode = currNode->link(operatorNode);
                        if (!currToken->getNext()) { return currNode;}
                        currToken = currToken->getNext();

                        
                        // <BOOLEAN_EXPRESSION> 
                        CSTNode* booleanExpressionNode = parseBooleanExpression(currNode, currToken);
                        if (booleanExpressionNode == nullptr) {return nullptr;}
                        currNode = currNode->link(booleanExpressionNode);



                        // <R_PAREN> 
                        if (currToken->getType() != R_PAREN) {
                            if(!ERROR) {std::cerr << "syntax error at line << " << currToken->getLineNum() << " unclosed ')' in boolean expression" << "\n";}
                            return nullptr;
                        }
                        CSTNode* rParenNode2 = new CSTNode(R_PAREN, ")", currToken->getLineNum());
                        currNode = currNode->link(rParenNode2);
                        if (currToken->getNext() == nullptr) { return currNode;}
                        currToken = currToken->getNext();

                    }
                }
            }
        }






        // <USER_DEFINED_FUNCTION>
        else if (couldBeUserDefinedFunction(currToken)) {
            CSTNode* userNode = parseUserDefinedFunction(currNode, currToken);
            if (userNode == nullptr) {return nullptr;}
            currNode = currNode->link(userNode);




            // <R_PAREN> 
            if (currToken->getType() != R_PAREN) {
                if(!ERROR) {std::cerr << "syntax error at line << " << currToken->getLineNum() << " unclosed ')' in boolean expression" << "\n";}
                return nullptr;
            }
            CSTNode* rParenNode2 = new CSTNode(R_PAREN, ")", currToken->getLineNum());
            currNode = currNode->link(rParenNode2);
            if (currToken->getNext() == nullptr) { return currNode;}
            currToken = currToken->getNext();
        }







        // <NUMERICAL_OPERAND> || <IDENTIFIER>
        else{

            if (currToken->getType() == IDENTIFIER && currToken->getNext() && 
                   (currToken->getNext()->getType() == BOOLEAN_AND || currToken->getNext()->getType() == BOOLEAN_OR)) {
                
                
                // <IDENTIFIER>
                CSTNode* identifierNode = parseIdentifier(currNode, currToken);
                if (identifierNode == nullptr) {return nullptr;}


                // <BOOLEAN_OPERATOR>
                tempType = currToken->getType();
                CSTNode* operatorNode = new CSTNode(tempType, currToken->token, currToken->getLineNum());
                currNode = currNode->link(operatorNode);
                if (!currToken->getNext()) { return currNode;}
                currToken = currToken->getNext();
               

            
                // <BOOLEAN_EXPRESSION> 
                CSTNode* booleanExpressionNode = parseBooleanExpression(currNode, currToken);
                if (booleanExpressionNode == nullptr) {return nullptr;}
                currNode = currNode->link(booleanExpressionNode);


                // <R_PAREN>
                if (currToken->getType() != R_PAREN) {
                    if(!ERROR) {std::cerr << "syntax error at line << " << currToken->getLineNum() << " unclosed ')' in boolean expression" << "\n";}
                    return nullptr;
                }
                CSTNode* rParenNode = new CSTNode(R_PAREN, ")", currToken->getLineNum());
                currNode = currNode->link(rParenNode);
                if (currToken->getNext() == nullptr) { return currNode;}
                currToken = currToken->getNext();
            } else {



                // <NUMERICAL_OPERAND>
                CSTNode* operandNode = parseNumericalOperand(currNode, currToken);
                if (operandNode == nullptr) {return nullptr;}
                currNode = currNode->link(operandNode);


                // <REALATIONAL_EXPRESSION>
                tempType = currToken->getType();
                if (tempType != GT && tempType != LT && tempType != GT_EQUAL && tempType != LT_EQUAL && tempType != BOOLEAN_EQUAL && tempType != BOOLEAN_NOT_EQUAL) {
                    if(!ERROR) {std::cerr << "syntax error at line << " << currToken->getLineNum() << " expected relatinal operator, got " << currToken->token << "\n";}
                    return nullptr;
                }
                CSTNode* relationNode = new CSTNode(tempType, currToken->token, currToken->getLineNum());
                currNode = currNode->link(relationNode);
                if (currToken->getNext() == nullptr) { return currNode;}
                currToken = currToken->getNext();





                // <NUMERICAL_EXPRESSION>
                CSTNode* expressionNode = parseNumericalExpression(currNode, currToken);
                if (expressionNode == nullptr) {return nullptr;}
                currNode = currNode->link(expressionNode);



                // <R_PAREN>
                if (currToken->getType() != R_PAREN) {
                    if(!ERROR) {std::cerr << "syntax error at line << " << currToken->getLineNum() << " expected (" << "\n";}
                    return nullptr;
                }
                CSTNode* rParenNode = new CSTNode(R_PAREN, ")", currToken->getLineNum());
                currNode = currNode->link(rParenNode);
                if (currToken->getNext() == nullptr) { return currNode;}
                currToken = currToken->getNext();



                // <BOOLEAN_OPERATOR>
                tempType = currToken->getType();
                if (tempType == BOOLEAN_AND || tempType == BOOLEAN_OR) {
                    CSTNode* operatorNode = new CSTNode(tempType, currToken->token, currToken->getLineNum());
                    currNode = currNode->link(operatorNode);
                    if (!currToken->getNext()) { return currNode;}
                    currToken = currToken->getNext();


                    // <BOOLEAN_EXPRESSION> 
                    CSTNode* booleanExpressionNode = parseBooleanExpression(currNode, currToken);
                    if (booleanExpressionNode == nullptr) {return nullptr;}
                    currNode = currNode->link(booleanExpressionNode);
                }
            }
        }
    }




    return currNode;
}



















// <INITIALIZATION_EXPRESSION> ::= <IDENTIFIER> <ASSIGNMENT_OPERATOR> <EXPRESSION> | 
//                                 <IDENTIFIER> <ASSIGNMENT_OPERATOR> <SINGLE_QUOTED_STRING> | 
//                                 <IDENTIFIER> <ASSIGNMENT_OPERATOR> <DOUBLE_QUOTED_STRING>
CSTNode* parseInitilazationExpression(CSTNode*& currNode, Token*& currToken) { 


    if (currNode == nullptr) { return nullptr;} 
    if (currToken == nullptr) {return currNode;}




    // <IDENTIFIER>
    CSTNode* identifierNode = parseIdentifier(currNode, currToken);
    if (identifierNode == nullptr) {return nullptr;}
    currNode = currNode->link(identifierNode);




    // <ASSIGNMENT_OPERATOR>
    if (currToken->getType() != ASSIGNMENT_OPERATOR) {
        if(!ERROR) {std::cerr << "Syntac error on line " << currToken->getLineNum() << " missing '=' in assignment statement" << "\n";}
        return nullptr;
    }
    CSTNode* assignmentNode = new CSTNode(ASSIGNMENT_OPERATOR, "=", currToken->getLineNum());
    currNode = currNode->link(assignmentNode);
    if (currToken->getNext() == nullptr) { return currNode;}
    currToken = currToken->getNext();




    // <SINGLE_QUOTED_STRING> | <DOUBLE_QUOTED_STRING> | <EXPRESSION>
    CSTNode* unknownNode;
    if (currToken->getType() == SINGLE_QUOTE) {
        unknownNode = parseSingleQuotedString(currNode, currToken);
    } else if (currToken->getType() == DOUBLE_QUOTE) {
        unknownNode = parseDoubleQuotedString(currNode, currToken);
    } else {
        unknownNode = parseExpression(currNode, currToken);
    }
    if (unknownNode == nullptr) {return nullptr;} 
    currNode = currNode->link(unknownNode);



    return currNode;
}





// <DOUBLE_QUOTED_STRING> ::= <DOUBLE_QUOTE> <STRING> <DOUBLE_QUOTE>
CSTNode* parseDoubleQuotedString(CSTNode*& currNode, Token*& currToken) { 



    if (currNode == nullptr) { return nullptr;} 
    if (currToken == nullptr) {return currNode;}



    // <DOUBLE_QUOTE>
    if (currToken->getType() != DOUBLE_QUOTE) {
        if(!ERROR) {std::cerr << "[-] Syntax error on line " << currToken->getLineNum() << " expected '" << "\n";}
        return nullptr;
    }
    CSTNode* doubleQuoteNode = new CSTNode(DOUBLE_QUOTE, "\"", currToken->getLineNum());
    currNode = currNode->link(doubleQuoteNode);
    if (currToken->getNext() == nullptr) { return currNode;}
    currToken = currToken->getNext();



    // <STRING>
    if (currToken->getType() != STRING) {
        if(!ERROR) {std::cerr << "[-] Syntax error on line " << currToken->getLineNum() << " expected string after '" << "\n";}
        return nullptr;
    } else if (currToken->token.back() == '\\') {
        if(!ERROR) {std::cerr << "[-] Syntax error on line " << currToken->getLineNum() << " unterminated string quote" << "\n";}
        return nullptr;
    }

    int strLineNum = currToken->getLineNum();
    CSTNode* stringNode = new CSTNode(STRING, currToken->token, currToken->getLineNum());
    currNode = currNode->link(stringNode);
    if (currToken->getNext() == nullptr) { return currNode;}
    currToken = currToken->getNext();





    // <DOUBLE_QUOTE>
    if (currToken->getType() != DOUBLE_QUOTE) {
        if(!ERROR) {std::cerr << "[-] Syntax error on line " << strLineNum << " unclosed double quote string" << "\n";}
        return nullptr;
    }
    CSTNode* doubleQuote2Node = new CSTNode(DOUBLE_QUOTE, "\"", currToken->getLineNum());
    currNode = currNode->link(doubleQuote2Node);
    if (currToken->getNext() == nullptr) { return currNode;}
    currToken = currToken->getNext();


    return currNode;
}







// <SINGLE_QUOTED_STRING> ::= <SINGLE_QUOTE> <STRING> <SINGLE_QUOTE>
CSTNode* parseSingleQuotedString(CSTNode*& currNode, Token*& currToken) { 


    if (currNode == nullptr) { return nullptr;} 
    if (currToken == nullptr) {return currNode;}




    // <SINGLE_QUOTE>
    if (currToken->getType() != SINGLE_QUOTE) {
        if(!ERROR) {std::cerr << "[-] Syntax error on line " << currToken->getLineNum() << " expected '" << "\n";}
        return nullptr;
    }
    CSTNode* singleQuoteNode = new CSTNode(SINGLE_QUOTE, "'", currToken->getLineNum());
    currNode = currNode->link(singleQuoteNode);
    if (currToken->getNext() == nullptr) { return currNode;}
    currToken = currToken->getNext();



    // <STRING>
    if (currToken->getType() != STRING) {
        if(!ERROR) {std::cerr << "[-] Syntax error on line " << currToken->getLineNum() << " expected string after '" << "\n";}
        return nullptr;
    }
    CSTNode* stringNode = new CSTNode(STRING, currToken->token, currToken->getLineNum());
    currNode = currNode->link(stringNode);
    if (currToken->getNext() == nullptr) { return currNode;}
    currToken = currToken->getNext();





    // <SINGLE_QUOTE>
    if (currToken->getType() != SINGLE_QUOTE) {
        if(!ERROR) {std::cerr << "[-] Syntax error on line " << currToken->getLineNum() << " unclosed single quote string" << "\n";}
        return nullptr;
    }
    CSTNode* singleQuote2Node = new CSTNode(SINGLE_QUOTE, "'", currToken->getLineNum());
    currNode = currNode->link(singleQuote2Node);
    if (currToken->getNext() == nullptr) { return currNode;}
    currToken = currToken->getNext();





    return currNode;




}




// <RETURN_STATEMENT> ::= return <EXPRESSION> <SEMICOLON> | return <SINGLE_QUOTED_STRING> <SEMICOLON> | return <DOUBLE_QUOTED_STRING> <SEMICOLON>
CSTNode* parseReturnStatement(CSTNode*& currNode, Token*& currToken) { 


    if (currNode == nullptr) { return nullptr;} 
    if (currToken == nullptr) {return currNode;}



    // return
    CSTNode* returnNode = new CSTNode(IDENTIFIER, "return", currToken->getLineNum());
    currNode = currNode->link(returnNode);
    if (currToken->getNext() == nullptr) { return currNode;}
    currToken = currToken->getNext();




    // <SINGLE_QUOTED_STRING> | <DOUBLE_QUOTED_STRING> | <EXPRESSION>
    CSTNode* unknownNode;
    if (currToken->getType() == SINGLE_QUOTE) {
        unknownNode = parseSingleQuotedString(currNode, currToken);
    } else if (currToken->getType() == DOUBLE_QUOTE) {
        unknownNode = parseDoubleQuotedString(currNode, currToken);
    } else {
        unknownNode = parseExpression(currNode, currToken);
    }
    if (unknownNode == nullptr) {return nullptr;} 
    currNode = currNode->link(unknownNode);



    // <SEMICOLON>
    if (currToken->getType() != SEMICOLON) {
        if(!ERROR) {std::cerr << "syntax error on line " << currToken->getLineNum() << " missing ';' " << "\n";}
        return nullptr;
    }
    CSTNode* semiColonNode = new CSTNode(SEMICOLON, ";", currToken->getLineNum());
    currNode = currNode->link(semiColonNode);
    if (currToken->getNext() == nullptr) { return currNode;}
    currToken = currToken->getNext();


    return currNode;
}






// <PRINTF_STATEMENT> ::= printf <L_PAREN> <DOUBLE_QUOTED_STRING> <R_PAREN> <SEMICOLON> | 
//                        printf <L_PAREN> <SINGLE_QUOTED_STRING> <R_PAREN> <SEMICOLON> | 
//                        printf <L_PAREN> <DOUBLE_QUOTED_STRING> <COMMA> <IDENTIFIER_AND_IDENTIFIER_ARRAY_PARAMETER_LIST> <R_PAREN> <SEMICOLON> | 
//                        printf <L_PAREN> <SINGLE_QUOTED_STRING> <COMMA> <IDENTIFIER_AND_IDENTIFIER_ARRAY_PARAMETER_LIST> <R_PAREN> <SEMICOLON>
CSTNode* parsePrintfStatement(CSTNode*& currNode, Token*& currToken) {



    if (currNode == nullptr) { return nullptr;} 
    if (currToken == nullptr) {return currNode;}


    // printf
    CSTNode* printfNode = new CSTNode(IDENTIFIER, "printf", currToken->getLineNum());
    currNode = currNode->link(printfNode);
    if (currToken->getNext() == nullptr) { return currNode;}
    currToken = currToken->getNext();



    // <L_PAREN>
    if (currToken->getType() != L_PAREN) {
        if(!ERROR) {std::cerr << "syntax error at line << " << currToken->getLineNum() << " printf statment needs '('" << "\n";}
        return nullptr;
    }
    CSTNode* lParenNode = new CSTNode(L_PAREN, "(", currToken->getLineNum());
    currNode = currNode->link(lParenNode);
    currToken = currToken->getNext();
    if (currToken->getNext() == nullptr) { return currNode;}



    // <DOUBLE_QUOTED_STRING> | <SINGLE_QUOTED_STRING>
    CSTNode* quoteStringNode;
    if (currToken->getType() == DOUBLE_QUOTE) {
        quoteStringNode = parseDoubleQuotedString(currNode, currToken);
    }
    else if (currToken->getType() == SINGLE_QUOTE) {
        quoteStringNode = parseSingleQuotedString(currNode, currToken);
    }
    if (quoteStringNode == nullptr) {return nullptr;} 
    currNode = currNode->link(quoteStringNode);


    
    // <R_PAREN>
    if (currToken->getType() == R_PAREN) {
        CSTNode* rParenNode = new CSTNode(R_PAREN, ")", currToken->getLineNum());
        currNode = currNode->link(rParenNode);
        currToken = currToken->getNext();
        if (currToken->getNext() == nullptr) { return currNode;}
        


        // <SEMICOLON>
        if (currToken->getType() != SEMICOLON) {
            if(!ERROR) {std::cerr << "syntax error on line " << currToken->getLineNum() << " midding ';' " << "\n";}
            return nullptr;
        }
        CSTNode* semiColonNode = new CSTNode(SEMICOLON, ";", currToken->getLineNum());
        currNode = currNode->link(semiColonNode);
        if (currToken->getNext() == nullptr) { return currNode;}
        currToken = currToken->getNext();
    } 



    // <COMMA>
    else if (currToken->getType() == COMMA) {
        CSTNode* commaNode = new CSTNode(COMMA, ",", currToken->getLineNum());
        currNode = currNode->link(commaNode);
        if (currToken->getNext() == nullptr) { return currNode;}
        currToken = currToken->getNext();


        // <IDENTIFIER_AND_IDENTIFIER_ARRAY_PARAMETER_LIST>
        CSTNode* identifierNode = parseIdentifierAndIdentifierArrayParameterList(currNode, currToken);
        if (identifierNode == nullptr) {return nullptr;} 
        currNode = currNode->link(identifierNode);



        // <R_PAREN>
        CSTNode* rParenNode = new CSTNode(R_PAREN, ")", currToken->getLineNum());
        currNode = currNode->link(rParenNode);
        currToken = currToken->getNext();
        if (currToken->getNext() == nullptr) { return currNode;}
        


        // <SEMICOLON>
        if (currToken->getType() != SEMICOLON) {
            if(!ERROR) {std::cerr << "syntax error on line " << currToken->getLineNum() << " midding ';' " << "\n";}
            return nullptr;
        }
        CSTNode* semiColonNode = new CSTNode(SEMICOLON, ";", currToken->getLineNum());
        currNode = currNode->link(semiColonNode);
        if (currToken->getNext() == nullptr) { return currNode;}
        currToken = currToken->getNext();


    } else {
        if(!ERROR) {std::cerr << "syntax error at line << " << currToken->getLineNum() << " expected either a ')' or ',' got " << currToken->token << "\n";}
        return nullptr;
    }


    return currNode;

}






// <SELECTION_STATEMENT> ::= if <L_PAREN> <BOOLEAN_EXPRESSION> <R_PAREN> <STATEMENT> | 
//                           if <L_PAREN> <BOOLEAN_EXPRESSION> <R_PAREN> <STATEMENT> else <STATEMENT> | 
//                           if <L_PAREN> <BOOLEAN_EXPRESSION> <R_PAREN> <BLOCK_STATEMENT> | 
//                           if <L_PAREN> <BOOLEAN_EXPRESSION> <R_PAREN> <BLOCK_STATEMENT> else <STATEMENT> | 
//                           if <L_PAREN> <BOOLEAN_EXPRESSION> <R_PAREN> <BLOCK_STATEMENT> else <BLOCK_STATEMENT> | 
//                           if <L_PAREN> <BOOLEAN_EXPRESSION> <R_PAREN> <STATEMENT> else <BLOCK_STATEMENT>
CSTNode* parseSelectionStatement(CSTNode*& currNode, Token*& currToken) {


    if (currNode == nullptr) { return nullptr;} 
    if (currToken == nullptr) {return currNode;}


    // if
    CSTNode* selectionNode = new CSTNode(IDENTIFIER, "if", currToken->getLineNum());
    currNode = currNode->link(selectionNode);
    if (currToken->getNext() == nullptr) { return currNode;}
    currToken = currToken->getNext();


    // <L_PAREN>
    if (currToken->getType() != L_PAREN) {
        if(!ERROR) {std::cerr << "syntax error at line << " << currToken->getLineNum() << " iteration statment needs '('" << "\n";}
        return nullptr;
    }
    CSTNode* lParenNode = new CSTNode(L_PAREN, "(", currToken->getLineNum());
    currNode = currNode->link(lParenNode);
    if (currToken->getNext() == nullptr) { return currNode;}
    currToken = currToken->getNext();



    // <BOOLEAN_EXPRESSION> 
    CSTNode* booleanExpressionNode = parseBooleanExpression(currNode, currToken);
    if (booleanExpressionNode == nullptr) {return nullptr;} 
    currNode = currNode->link(booleanExpressionNode);



    // <R_PAREN> 
    if (currToken->getType() != R_PAREN) {
        if(!ERROR) {std::cerr << "syntax error at line << " << currToken->getLineNum() << " unclosed ')' in selectioin statement" << "\n";}
        return nullptr;
    }
    CSTNode* rParenNode = new CSTNode(R_PAREN, ")", currToken->getLineNum());
    currNode = currNode->link(rParenNode);
    if (currToken->getNext() == nullptr) { return currNode;}
    currToken = currToken->getNext();




    // <BLOCK_STATEMENT>
    if (currToken->getType() == L_BRACE) {
        CSTNode* statementNode = parseBlockStatement(currNode, currToken);        
        if (statementNode == nullptr) {return nullptr;}
        currNode = currNode->link(statementNode);



        if (currToken->token == "else") {
            CSTNode* elseNode = new CSTNode(IDENTIFIER, "else", currToken->getLineNum());
            currNode = currNode->link(elseNode);
            if (currToken->getNext() == nullptr) { return currNode;}
            currToken = currToken->getNext();


        
            // <BLOCK_STATEMENT>
            if (currToken->getType() == L_BRACE) {
                CSTNode* statementNode = parseBlockStatement(currNode, currToken);        
                if (statementNode == nullptr) {return nullptr;}
                currNode = currNode->link(statementNode);
            }


            // <STATEMENT>
            else {
                CSTNode* statementNode = parseStatement(currNode, currToken);        
                if (statementNode == nullptr) {return nullptr;}
                currNode = currNode->link(statementNode);
            }
        }
    }





    // <STATEMENT>
    else {
        CSTNode* statementNode = parseStatement(currNode, currToken);        
        if (statementNode == nullptr) {return nullptr;}
        currNode = currNode->link(statementNode);


        if (currToken->token == "else") {
            CSTNode* elseNode = new CSTNode(IDENTIFIER, "else", currToken->getLineNum());
            currNode = currNode->link(elseNode);
            if (currToken->getNext() == nullptr) { return currNode;}
            currToken = currToken->getNext();


        
            // <BLOCK_STATEMENT>
            if (currToken->getType() == L_BRACE) {
                CSTNode* statementNode = parseBlockStatement(currNode, currToken);        
                if (statementNode == nullptr) {return nullptr;}
                currNode = currNode->link(statementNode);
            }


            // <STATEMENT>
            else {
                CSTNode* statementNode = parseStatement(currNode, currToken);        
                if (statementNode == nullptr) {return nullptr;}
                currNode = currNode->link(statementNode);
            }
        }
    }


    return currNode;
 }





// <ITERATION_STATEMENT> ::= for <L_PAREN> <INITIALIZATION_EXPRESSION> <SEMICOLON> <BOOLEAN_EXPRESSION> <SEMICOLON> <ITERATION_ASSIGNMENT> <R_PAREN> <STATEMENT> | 
//                           for <L_PAREN> <INITIALIZATION_EXPRESSION> <SEMICOLON> <BOOLEAN_EXPRESSION> <SEMICOLON> <ITERATION_ASSIGNMENT> <R_PAREN> <BLOCK_STATEMENT> | 
//                           while <L_PAREN> <BOOLEAN_EXPRESSION> <R_PAREN> <STATEMENT> | 
//                           while <L_PAREN> <BOOLEAN_EXPRESSION> <R_PAREN> <BLOCK_STATEMENT>
CSTNode* parseIterationStatement(CSTNode*& currNode, Token*& currToken) {


    if (currNode == nullptr) { return nullptr;} 
    if (currToken == nullptr) {return currNode;}

    

    // for
    if (currToken->token == "for") {

        CSTNode* iteratorNode = new CSTNode(IDENTIFIER, "for", currToken->getLineNum());
        currNode = currNode->link(iteratorNode);
        if (currToken->getNext() == nullptr) { return currNode;}
        currToken = currToken->getNext();


        // <L_PAREN>
        if (currToken->getType() != L_PAREN) {
            if(!ERROR) {std::cerr << "syntax error at line << " << currToken->getLineNum() << " iteration statment needs '('" << "\n";}
            return nullptr;
        }
        CSTNode* lParenNode = new CSTNode(L_PAREN, "(", currToken->getLineNum());
        currNode = currNode->link(lParenNode);
        if (currToken->getNext() == nullptr) { return currNode;}
        currToken = currToken->getNext();


        // <INITIALIZATION_EXPRESSION> 
        CSTNode* initNode = parseInitilazationExpression(currNode, currToken);
        if (initNode == nullptr) {return nullptr;} 
        currNode = currNode->link(initNode);



        // <SEMICOLON> 
        if (currToken->getType() != SEMICOLON) {
            if(!ERROR) {std::cerr << "syntax error on line " << currToken->getLineNum() << " midding ';' " << "\n";}
            return nullptr;
        }
        CSTNode* semiColonNode = new CSTNode(SEMICOLON, ";", currToken->getLineNum());
        currNode = currNode->link(semiColonNode);
        if (currToken->getNext() == nullptr) { return currNode;}
        currToken = currToken->getNext();


        // <BOOLEAN_EXPRESSION> 
        CSTNode* booleanExpressionNode = parseBooleanExpression(currNode, currToken);
        if (booleanExpressionNode == nullptr) {return nullptr;} 
        currNode = currNode->link(booleanExpressionNode);



        // <SEMICOLON> 
        if (currToken->getType() != SEMICOLON) {
            if(!ERROR) {std::cerr << "syntax error on line " << currToken->getLineNum() << " midding ';' " << "\n";}
            return nullptr;
        }
        CSTNode* semiColonNode2 = new CSTNode(SEMICOLON, ";", currToken->getLineNum());
        currNode = currNode->link(semiColonNode2);
        if (currToken->getNext() == nullptr) { return currNode;}
        currToken = currToken->getNext();




        // <ITERATION_ASSIGNMENT>
        CSTNode* assignmentNode = parseIterationAssignment(currNode, currToken);
        if (assignmentNode == nullptr) {return nullptr;} 
        currNode = currNode->link(assignmentNode);



        // <R_PAREN> 
        if (currToken->getType() != R_PAREN) {
            if(!ERROR) {std::cerr << "syntax error at line << " << currToken->getLineNum() << " unclosed ')' in iteration statement" << "\n";}
            return nullptr;
        }
        CSTNode* rParenNode = new CSTNode(R_PAREN, ")", currToken->getLineNum());
        currNode = currNode->link(rParenNode);
        currToken = currToken->getNext();
        if (currToken->getNext() == nullptr) { return currNode;}



        // <BLOCK_STATEMENT>
        if (currToken->getType() == L_BRACE) {
            CSTNode* statementNode = parseBlockStatement(currNode, currToken);        
            if (statementNode == nullptr) {return nullptr;}
            currNode = currNode->link(statementNode);
        }


        // <STATEMENT>
        else {
            CSTNode* statementNode = parseStatement(currNode, currToken);        
            if (statementNode == nullptr) {return nullptr;}
            currNode = currNode->link(statementNode);
        }

    }





    // while
    else if (currToken->token == "while"){

        CSTNode* iteratorNode = new CSTNode(IDENTIFIER, "while", currToken->getLineNum());
        currNode = currNode->link(iteratorNode);
        if (currToken->getNext() == nullptr) { return currNode;}
        currToken = currToken->getNext();


        // <L_PAREN>
        if (currToken->getType() != L_PAREN) {
            if(!ERROR) {std::cerr << "syntax error at line << " << currToken->getLineNum() << " iteration statment needs '('" << "\n";}
            return nullptr;
        }
        CSTNode* lParenNode = new CSTNode(L_PAREN, "(", currToken->getLineNum());
        currNode = currNode->link(lParenNode);
        if (currToken->getNext() == nullptr) { return currNode;}
        currToken = currToken->getNext();



        // <BOOLEAN_EXPRESSION> 
        CSTNode* booleanExpressionNode = parseBooleanExpression(currNode, currToken);
        if (booleanExpressionNode == nullptr) {return nullptr;} 
        currNode = currNode->link(booleanExpressionNode);



        // <R_PAREN> 
        if (currToken->getType() != R_PAREN) {
            if(!ERROR) {std::cerr << "syntax error at line << " << currToken->getLineNum() << " unclosed ')' in iteration statement" << "\n";}
            return nullptr;
        }
        CSTNode* rParenNode = new CSTNode(R_PAREN, ")", currToken->getLineNum());
        currNode = currNode->link(rParenNode);
        if (currToken->getNext() == nullptr) { return currNode;}
        currToken = currToken->getNext();



        // <BLOCK_STATEMENT>
        if (currToken->getType() == L_BRACE) {
            CSTNode* statementNode;
            statementNode = parseBlockStatement(currNode, currToken);        
            if (statementNode == nullptr) {return nullptr;}
            currNode = currNode->link(statementNode);
        }


        // <STATEMENT>
        else {
            CSTNode* statementNode;
            statementNode = parseStatement(currNode, currToken);        
            if (statementNode == nullptr) {return nullptr;}
            currNode = currNode->link(statementNode);
        }

    } else { 
        if(!ERROR) {std::cerr << "Syntac error on line " << currToken->getLineNum() << " expected 'for' or 'while' got " << currToken->token << "\n";}
        return nullptr;
    }


    return currNode;


}




// <ASSIGNMENT_STATEMENT> ::= <IDENTIFIER> <ASSIGNMENT_OPERATOR> <EXPRESSION> <SEMICOLON> | 
//                            <IDENTIFIER> <ASSIGNMENT_OPERATOR> <SINGLE_QUOTED_STRING> <SEMICOLON> | 
//                            <IDENTIFIER> <ASSIGNMENT_OPERATOR> <DOUBLE_QUOTED_STRING> <SEMICOLON> | 
//                            <IDENTIFIER> <L_BRACKET> <NUMERICAL_EXPRESSION> <R_BRACKET> <ASSIGNMENT_OPERATOR> <EXPRESSION> <SEMICOLON> | 
//                            <IDENTIFIER> <L_BRACKET> <NUMERICAL_EXPRESSION> <R_BRACKET> <ASSIGNMENT_OPERATOR> <SINGLE_QUOTE> <CHARACTER> <SINGLE_QUOTE> <SEMICOLON> | 
//                            <IDENTIFIER> <L_BRACKET> <NUMERICAL_EXPRESSION> <R_BRACKET> <ASSIGNMENT_OPERATOR> <DOUBLE_QUOTE> <CHARACTER> <DOUBLE_QUOTE> <SEMICOLON> | 
//                            <IDENTIFIER> <L_BRACKET> <NUMERICAL_EXPRESSION> <R_BRACKET> <ASSIGNMENT_OPERATOR> <SINGLE_QUOTE> <ESCAPED_CHARACTER> <SINGLE_QUOTE> <SEMICOLON> |
//                            <IDENTIFIER> <L_BRACKET> <NUMERICAL_EXPRESSION> <R_BRACKET> <ASSIGNMENT_OPERATOR> <DOUBLE_QUOTE> <ESCAPED_CHARACTER> <DOUBLE_QUOTE> <SEMICOLON>
CSTNode* parseAssignmentStatement(CSTNode*& currNode, Token*& currToken) {



    if (currNode == nullptr) { return nullptr;} 
    if (currToken == nullptr) {return currNode;}


    // <IDENTIFIER>
    CSTNode* identifierNode = parseIdentifier(currNode, currToken);
    if (identifierNode == nullptr) {return nullptr;}
    currNode = currNode->link(identifierNode);






    // <ASSIGNEMTN_OPERAOR>
    if (currToken->getType() == ASSIGNMENT_OPERATOR) {
        CSTNode* assignmentNode = new CSTNode(ASSIGNMENT_OPERATOR, "=", currToken->getLineNum());
        currNode = currNode->link(assignmentNode);
        if (currToken->getNext() == nullptr) { return currNode;}
        currToken = currToken->getNext();


        // <SINGLE_QUOTED_STRING> | <DOUBLE_QUOTED_STRING> | <EXPRESSION>
        CSTNode* unknownNode;
        if (currToken->getType() == SINGLE_QUOTE) {
            unknownNode = parseSingleQuotedString(currNode, currToken);
        } else if (currToken->getType() == DOUBLE_QUOTE) {
            unknownNode = parseDoubleQuotedString(currNode, currToken);
        }  else {
            unknownNode = parseExpression(currNode, currToken);
        }
        if (unknownNode == nullptr) {return nullptr;}
        currNode = currNode->link(unknownNode);



        // <SEMICOLON>
        if (currToken->getType() != SEMICOLON) {
            if(!ERROR) {std::cerr << "syntax error on line " << currToken->getLineNum() << " midding(assignment statment) ';' " << "\n";}
            return nullptr;
        }
        CSTNode* semiColonNode = new CSTNode(SEMICOLON, ";", currToken->getLineNum());
        currNode = currNode->link(semiColonNode);
        if (currToken->getNext() == nullptr) { return currNode;}
        currToken = currToken->getNext();
    }





    // <L_BRACKET
    else if (currToken->getType() == L_BRACKET) {
        CSTNode* lBracketNode = new CSTNode(L_BRACKET, "[", currToken->getLineNum());
        currNode = currNode->link(lBracketNode);
        currToken = currToken->getNext();
        if (currToken->getNext() == nullptr) { return currNode;}




        // <NUMERICAL_EXPRESSION>
        CSTNode* expressionNode = parseNumericalExpression(currNode, currToken);
        if (expressionNode == nullptr) {return nullptr;}
        currNode = currNode->link(expressionNode);



        // <R_BRACKET>
        if (currToken->getType() != R_BRACKET) {
            if(!ERROR) {std::cerr << "syntax error at line << " << currToken->getLineNum() << " unclosed ]" << "\n";}
            return nullptr;
        }
        CSTNode* rBracketNode = new CSTNode(R_BRACKET, "]", currToken->getLineNum());
        currNode = currNode->link(rBracketNode);
        currToken = currToken->getNext();
        if (currToken->getNext() == nullptr) { return currNode;}





        // <ASSIGNEMTN_OPERAOR>
        CSTNode* assignmentNode = new CSTNode(ASSIGNMENT_OPERATOR, "=", currToken->getLineNum());
        currNode = currNode->link(assignmentNode);
        if (currToken->getNext() == nullptr) { return currNode;}
        currToken = currToken->getNext();





        // <SINGLE_QUOTE>
        if (currToken->getType() == SINGLE_QUOTE) {
            CSTNode* singleQuoteNode = new CSTNode(SINGLE_QUOTE, "'", currToken->getLineNum());
            currNode = currNode->link(singleQuoteNode);
            if (currToken->getNext() == nullptr) { return currNode;}
            currToken = currToken->getNext();



            // <ESCAPE_CHARACTOR> | <CHARACTOR> 
            CSTNode* charNode;
            if (currToken->token.size() == 1) {
                charNode = new CSTNode(CHARACTOR, currToken->token, currToken->getLineNum());
            }

            else if (currToken->token[0] == '\\') {
                charNode = new CSTNode(ESCAPED_CHARACTOR, currToken->token, currToken->getLineNum());
            } else {
                if(!ERROR) {std::cerr << "[-] Syntax error on line " << currToken->getLineNum() << " invalid assigment into char array   " << currToken->token << "" << "\n";}
                return nullptr;
            }
            currNode = currNode->link(charNode);
            if (currToken->getNext() == nullptr) { return currNode;}
            currToken = currToken->getNext();



            // <SINGLE_QUOTE>
            if (currToken->getType() != SINGLE_QUOTE) {
                if(!ERROR) {std::cerr << "[-] Syntax error on line " << currToken->getLineNum() << " unclosed single quote string" << "\n";}
                return nullptr;
            }
            CSTNode* singleQuote2Node = new CSTNode(SINGLE_QUOTE, "'", currToken->getLineNum());
            currNode = currNode->link(singleQuote2Node);
            if (currToken->getNext() == nullptr) { return currNode;}
            currToken = currToken->getNext();


        }






        // <DOUBLE_QUOTE>
        else if (currToken->getType() == DOUBLE_QUOTE) {
            CSTNode* doubleQuoteNode = new CSTNode(DOUBLE_QUOTE, "\"", currToken->getLineNum());
            currNode = currNode->link(doubleQuoteNode);
            if (currToken->getNext() == nullptr) { return currNode;}
            currToken = currToken->getNext();



            // <ESCAPE_CHARACTOR> | <CHARACTOR> 
            CSTNode* charNode;
            if (currToken->token.size() == 1) {
                charNode = new CSTNode(CHARACTOR, currToken->token, currToken->getLineNum());
            }

            else if (currToken->token[1] == '\\') {
                charNode = new CSTNode(ESCAPED_CHARACTOR, currToken->token, currToken->getLineNum());
            }
            currNode = currNode->link(charNode);
            if (currToken->getNext() == nullptr) { return currNode;}
            currToken = currToken->getNext();





            // <DOUBLE_QUOTE>
            if (currToken->getType() != DOUBLE_QUOTE) {
                if(!ERROR) {std::cerr << "[-] Syntax error on line " << currToken->getLineNum() << " unclosed double quote string" << "\n";}
                return nullptr;
            }
            CSTNode* doubleQuote2Node = new CSTNode(DOUBLE_QUOTE, "\"", currToken->getLineNum());
            currNode = currNode->link(doubleQuote2Node);
            if (currToken->getNext() == nullptr) { return currNode;}



        }



        //<EXPRESSION>
        else {
            CSTNode* expressionNode = parseExpression(currNode, currToken);
            if (expressionNode == nullptr) {return nullptr;}
            currNode = currNode->link(expressionNode);
        }
        




        // <SEMICOLON>
        if (currToken->getType() != SEMICOLON) {
            if(!ERROR) {std::cerr << "syntax error on line " << currToken->getLineNum() << " midding(assignment statment) ';' " << "\n";}
            return nullptr;
        }
        CSTNode* semiColonNode = new CSTNode(SEMICOLON, ";", currToken->getLineNum());
        currNode = currNode->link(semiColonNode);
        if (currToken->getNext() == nullptr) { return currNode;}
        currToken = currToken->getNext();

    }



    return currNode;

 }









// <WHOLE_NUMBER> ::= (old) <DIGIT> | <DIGIT> <WHOLE_NUMBER>
//                (new)     <PLUS> <DIGIT> | <DIGIT> <WHOLE_NUMBER>
CSTNode* parseWholeNumber(CSTNode*& currNode, Token*& currToken) { 



    if (currNode == nullptr) { return nullptr;} 
    if (currToken == nullptr) {return currNode;}



    if (currToken->getType() == PLUS) {
        CSTNode* plusNode = new CSTNode(PLUS, "+", currToken->getLineNum());
        currNode = currNode->link(plusNode);
        if (currToken->getNext() == nullptr) { return currNode;}
        currToken = currToken->getNext();
    } else if (currToken->getType() == MINUS) {
        CSTNode* minusNode = new CSTNode(MINUS, "-", currToken->getLineNum());
        currNode = currNode->link(minusNode);
        if (currToken->getNext() == nullptr) { return currNode;}
        currToken = currToken->getNext();
    }


    std::string::const_iterator it = currToken->token.begin();
    bool isNumber = true;

    while (it != currToken->token.end()) {
        if (!std::isdigit(*it)) {
            isNumber = false;
        }
        ++it;
    }
    
    if (!isNumber) {
        if(!ERROR) {std::cerr << "Syntax error at line << " << currToken->getLineNum() << " epxprected a whole number, got " << currToken->token << "\n";}
        return nullptr;
    }

    CSTNode* wholeNumNode = new CSTNode(WHOLE_NUMBER, currToken->token, currToken->getLineNum());
    if (wholeNumNode == nullptr) {return nullptr;}
    currNode = currNode->link(wholeNumNode);
    if (currToken->getNext() == nullptr) { return currNode;}
    currToken = currToken->getNext();

    return currNode;

}







// <STATEMENT> ::= <DECLARATION_STATEMENT> | <ASSIGNMENT_STATEMENT> | <ITERATION_STATEMENT> | <SELECTION_STATEMENT> | <PRINTF_STATEMENT> | <RETURN_STATEMENT> | <USER_DEFINED_PROCEDURE_CALL_STATEMENT>
CSTNode* parseStatement(CSTNode*& currNode, Token*& currToken) {



    if (currNode == nullptr) { return nullptr;} 
    if (currToken == nullptr) {return currNode;}




    std::string tempStr = currToken->token;
    TOKEN tempType = currToken->getType();
    CSTNode* statementNode;

    // <DECLARATION_STATEMENT>
    if (tempStr == "char" || tempStr == "int" || tempStr == "bool") {
        statementNode = parseDeclarationStatement(currNode, currToken);
    }


    // <ITERATION_STATEMENT>
    else if (tempStr == "for" || tempStr == "while") {
        statementNode = parseIterationStatement(currNode, currToken);
    }


    // <SELECTION_STATEMENT>
    else if (tempStr == "if") {
        statementNode = parseSelectionStatement(currNode, currToken);
    }


    // <PRINTF_STATEMENT>
    else if (tempStr == "printf") {
        statementNode = parsePrintfStatement(currNode, currToken);

    }


    // <RETURN_STATEMENT>
    else if (tempStr == "return") {
        statementNode = parseReturnStatement(currNode, currToken);
    }




    // <ASSIGNMENT_STATEMENT> | <USER_DEFINED_PROCEDURE_CALL_STATEMENT>
    else if (tempType == IDENTIFIER) {
        if (currToken->getNext() != nullptr) {
            if (currToken->getNext()->getType() == ASSIGNMENT_OPERATOR) {
                statementNode = parseAssignmentStatement(currNode, currToken);
                
            }  else if (currToken->getNext()->getType() == L_PAREN) {
                statementNode = parseUserDefinedProcedureCallStatement(currNode, currToken);
                      
            }  else if (currToken->getNext()->getType() == L_BRACKET) { 
                statementNode = parseAssignmentStatement(currNode, currToken); 
            }
        } 
    } 


    if (statementNode == nullptr) {return nullptr;}
    currNode = currNode->link(statementNode);



    return currNode;



}










// <IDENTIFIER_ARRAY_LIST> ::= <IDENTIFIER> <L_BRACKET> <WHOLE_NUMBER> <R_BRACKET> | 
//                             <IDENTIFIER> <L_BRACKET> <WHOLE_NUMBER> <R_BRACKET> <COMMA> <IDENTIFIER_ARRAY_LIST> 
CSTNode* parseIdentifierArrayList(CSTNode*& currNode, Token*& currToken) {


    if (currNode == nullptr) { return nullptr;} 
    if (currToken == nullptr) {return currNode;}


    // <IDENTIFIER>
    CSTNode* identifierNode = parseIdentifier(currNode, currToken);
    if (identifierNode == nullptr) {return nullptr;}
    currNode = currNode->link(identifierNode);



    // <L_BRACKET>
    if (currToken->getType() != L_BRACKET) {
        if(!ERROR) {std::cerr << "syntax error at line " << currToken->getLineNum() << " '[' should follow paramiter" << "\n";}
        return nullptr;
    }
    CSTNode* lBracketNode = new CSTNode(L_BRACKET, "[", currToken->getLineNum());
    currNode = currNode->link(lBracketNode);
    currToken = currToken->getNext();
    if (currToken->getNext() == nullptr) { return currNode;}



    if (currToken->token[0] == '-') {
        if(!ERROR) {std::cerr << "[-] Syntax error at line  " << currToken->getLineNum() << " array declaration must be positive integer" << "\n";}
        return nullptr;
    }


    // <WHOLE_NUMBER>
    CSTNode* wholeNumberNode = parseWholeNumber(currNode, currToken);
    if (wholeNumberNode == nullptr) {return nullptr;}
    currNode = currNode->link(wholeNumberNode);




    // <R_BRACKET>
    if (currToken->getType() != R_BRACKET) {
        if(!ERROR) {std::cerr << "syntax error at line  " << currToken->getLineNum() << " unclosed ]" << "\n";}
        return nullptr;
    }
    CSTNode* rBracketNode = new CSTNode(R_BRACKET, "]", currToken->getLineNum());
    currNode = currNode->link(rBracketNode);
    currToken = currToken->getNext();
    if (currToken->getNext() == nullptr) { return currNode;}




    if (currToken->getType() == COMMA) {

        // <COMMA>
        CSTNode* commaNode = new CSTNode(COMMA, ",", currToken->getLineNum());
        currNode = currNode->link(commaNode);
        if (currToken->getNext() == nullptr) { return currNode;}
        currToken = currToken->getNext();
        

        // <IDENTIFIER_ARRAY_LIST>
        CSTNode* identifierArrayListNode = parseIdentifierArrayList(currNode, currToken);
        if (identifierArrayListNode == nullptr) {return nullptr;}
        currNode = currNode->link(identifierArrayListNode);
    }


    return currNode;

}






// <IDENTIFIER_LIST> ::= <IDENTIFIER> | <IDENTIFIER> <COMMA> <IDENTIFIER_LIST>
CSTNode* parseIdentifierList(CSTNode*& currNode, Token*& currToken) {


    if (currNode == nullptr) { return nullptr;} 
    if (currToken == nullptr) {return currNode;}


    // <IDENTIFIER>
    CSTNode* identifierNode = parseIdentifier(currNode, currToken);
    if (identifierNode == nullptr) {return nullptr;}
    currNode = currNode->link(identifierNode);

    // <COMMA>
    if (currToken->getType() == COMMA) {
        CSTNode* commaNode = new CSTNode(COMMA, ",", currToken->getLineNum());
        currNode = currNode->link(commaNode);
        if (currToken->getNext() == nullptr) { return currNode;}
        currToken = currToken->getNext();
        

        // <IDENTIFIER_LIST>
        CSTNode* identifierListNode = parseIdentifierList(currNode, currToken);
        if (identifierListNode == nullptr) {return nullptr;}
        currNode = currNode->link(identifierListNode);

    }


    return currNode;

}




bool isStartOfStatment(Token* currToken) {


    if (!currToken) return false;

    std::string tempStr = currToken->token;
    TOKEN tempType = currToken->getType();

    // <DECLARATION_STATEMENT>
    if (tempStr == "char" || tempStr == "int" || tempStr == "bool") {return true;}



    // <ITERATION_STATEMENT>
    else if (tempStr == "for" || tempStr == "while") {return true;}


    // <SELECTION_STATEMENT>
    else if (tempStr == "if") { return true;}


    // <PRINTF_STATEMENT>
    else if (tempStr == "printf") {return true;}


    // <RETURN_STATEMENT>
    else if (tempStr == "return") {return true;}




    // <ASSIGNMENT_STATEMENT>
    else if (tempType == IDENTIFIER) {
        if (currToken->getNext() != nullptr) {
            if (currToken->getNext()->getType() == ASSIGNMENT_OPERATOR) {
                return true;
            } else if (currToken->getNext()->getType() == L_PAREN) {
                return true;          
            } else if (currToken->getNext()->getType() == L_BRACKET) { 
                if (currToken->getNext()->getNext()) {
                    if (currToken->getNext()->getNext()->getType() == INTEGER) {
                        if (currToken->getNext()->getNext()->getNext()) {
                            if (currToken->getNext()->getNext()->getNext()->getType() == R_BRACKET) {
                                return true;
                            }
                        }
                    }
                }
            }
        } 
    }


    return false;


}




// <IDENTIFIER_AND_IDENTIFIER_ARRAY_LIST> ::= <IDENTIFIER_LIST> | <IDENTIFIER_ARRAY_LIST> | <IDENTIFIER_LIST> <IDENTIFIER_ARRAY_LIST> | <IDENTIFIER_ARRAY_LIST> <IDENTIFIER_LIST>
CSTNode* parseIdentifierAndIdentifierArrayList(CSTNode*& currNode, Token*& currToken) {


    if (currNode == nullptr) { return nullptr;} 
    if (currToken == nullptr) {return currNode;}




    if (currToken->getType() != IDENTIFIER) {
        if(!ERROR) {std::cerr << "Syntax error at line " << currToken->getLineNum() << " expected identifer got " << currToken->token << "\n";}
        return nullptr;
    }

    if (!currToken->getNext()) {
        if(!ERROR) {std::cerr << "Syntax error at line " << currToken->getLineNum() << " incomplete identifer statment"  << "\n";}
        return nullptr;
    }




    // <IDENTIFIER_LIST>
    if (currToken->getNext()->getType() == COMMA) {
        CSTNode* identifierListNode = parseIdentifierList(currNode, currToken);
        if (identifierListNode == nullptr) {return nullptr;}
        currNode = currNode->link(identifierListNode);


        if (currToken->getType() != IDENTIFIER || !currToken->getNext()) {
            return currNode;
        } 
        
        // possibly <IDENTIFIER_ARRAY_LIST>
        if (currToken->getNext()->getType() == L_BRACKET) {
            CSTNode* identifierArrayListNode = parseIdentifierArrayList(currNode, currToken);
            if (identifierArrayListNode == nullptr) {return nullptr;}
            currNode = currNode->link(identifierArrayListNode);
        }
    }



    // <IDENTIFIER_ARRAY_LIST>
    else if (currToken->getNext()->getType() == L_BRACKET) {
        CSTNode* identifierArrayListNode = parseIdentifierArrayList(currNode, currToken);
        if (identifierArrayListNode == nullptr) {return nullptr;}
        currNode = currNode->link(identifierArrayListNode);

        if (currToken->getType() != IDENTIFIER || !currToken->getNext()) {
            return currNode;
        } 

        // possibly <IDENTIFIER_LIST>
        if (currToken->getNext()->getType() == COMMA) {
            CSTNode* identifierListNode = parseIdentifierList(currNode, currToken);
            if (identifierListNode == nullptr) {return nullptr;}
            currNode = currNode->link(identifierListNode);

        } 

    } else {


        // <IDENTIFIER>
        CSTNode* identifierNode = parseIdentifier(currNode, currToken);
        if (identifierNode == nullptr) {return nullptr;}
        currNode = currNode->link(identifierNode);
        }


    return currNode;

}






// <DATATYPE_SPECIFIER> ::= char | bool | int
CSTNode* parseDatatypeSpecifier(CSTNode*& currNode, Token*& currToken) {


    if (currNode == nullptr) { return nullptr;} 
    if (currToken == nullptr) {return currNode;}
    


    std::string tempStr = currToken->token;
    if (tempStr != "char" && tempStr != "bool" && tempStr != "int") {
        if(!ERROR) {std::cerr << "Syntax error at line " << currToken->getLineNum() << " expected a type got " << currToken->token << "\n";}
        return nullptr;
    }

    CSTNode* specifierNode = new CSTNode(DATATYPE_SPECIFIER, currToken->token, currToken->getLineNum());
    currNode = currNode->link(specifierNode);
    if (currToken->getNext() == nullptr) { return currNode;}
    currToken = currToken->getNext();
     

    return currNode;

}






// <COMPOUND_STATEMENT> ::= <STATEMENT> | <STATEMENT> <COMPOUND_STATEMENT>
CSTNode* parseCompoundStatement(CSTNode*& currNode, Token*& currToken) {

    if (currNode == nullptr) { return nullptr;} 
    if (currToken == nullptr) {return currNode;}
   


    //  <STATEMENT>  
    CSTNode* statementNode;
    statementNode = parseStatement(currNode, currToken);        
    if (statementNode == nullptr) {return nullptr;}
    currNode = currNode->link(statementNode);


    //  posisbly more <STATEMENT>  
    while (true) {

        if (isStartOfStatment(currToken)) {
            statementNode = parseStatement(currNode, currToken);        
            if (statementNode == nullptr) {return nullptr;}
            currNode = currNode->link(statementNode);

        } else {
            break;
        }

    }


    return currNode;


}






// (I added the COMMA's)
// <PARAMETER_LIST> ::= <DATATYPE_SPECIFIER> <IDENTIFIER> | 
//                      <DATATYPE_SPECIFIER> <IDENTIFIER> <COMMA> <PARAMETER_LIST> | 
//                      <DATATYPE_SPECIFIER> <IDENTIFIER_AND_IDENTIFIER_ARRAY_PARAMETER_LIST_DECLARATION> | 
//                      <DATATYPE_SPECIFIER> <IDENTIFIER_AND_IDENTIFIER_ARRAY_PARAMETER_LIST_DECLARATION> <COMMA> <PARAMETER_LIST>
CSTNode* parseParameterList(CSTNode*& currNode, Token*& currToken) {


    if (currNode == nullptr) { return nullptr;} 
    if (currToken == nullptr) {return currNode;}



    //<DATATYPE_SPECIFIER>
    CSTNode* dataSpecifierNode = parseDatatypeSpecifier(currNode, currToken);
    if (dataSpecifierNode == nullptr) {return nullptr;}
    currNode = currNode->link(dataSpecifierNode);


    //<IDENTIFIER_AND_IDENTIFIER_ARRAY_PARAMETER_LIST_DECLARATION> |<IDENTIFIER_AND_IDENTIFIER_ARRAY_PARAMETER_LIST_DECLARATION>  <PARAMETER_LIST>
    if (currToken->getNext() && currToken->getNext()->getType() == L_BRACKET) {
        CSTNode* identifierAndNode = parseIdentifierAndIdentifierArrayParameterListDeclaration(currNode, currToken);
        if (identifierAndNode == nullptr) {return nullptr;}
        currNode = currNode->link(identifierAndNode);




        //<PARAMETER_LIST>
        if (currToken->getType() == COMMA && currToken->getNext() && (currToken->getNext()->token == "char" || currToken->getNext()->token == "bool" || currToken->getNext()->token == "int")) {
            CSTNode* commaNode = new CSTNode(COMMA, ",", currToken->getLineNum());
            currNode = currNode->link(commaNode);
            if (currToken->getNext() == nullptr) { return currNode;}
            currToken = currToken->getNext();



            CSTNode* paramListNode = parseParameterList(currNode, currToken);
            if (paramListNode == nullptr) {return nullptr;}
            currNode = currNode->link(paramListNode);
        }

    }

    




    // <IDENTIFIER> | <IDENTIFIER> <COMMA> <PARAMETER_LIST>
    else {
        if (currToken->getType() != IDENTIFIER) {
            if(!ERROR) {std::cerr << "syntax error on line " << currToken->getLineNum() << " missing identifier after datatype identifier" << "\n";}
            return nullptr;
        }
        CSTNode* identifierNode = parseIdentifier(currNode, currToken);
        if (identifierNode == nullptr) {return nullptr;}
        currNode = currNode->link(identifierNode);

    
        //<PARAMETER_LIST>
        if (currToken->getType() == COMMA && currToken->getNext() && (currToken->getNext()->token == "char" || currToken->getNext()->token == "bool" || currToken->getNext()->token == "int")) {
            CSTNode* commaNode = new CSTNode(COMMA, ",", currToken->getLineNum());
            currNode = currNode->link(commaNode);
            if (currToken->getNext() == nullptr) { return currNode;}
            currToken = currToken->getNext();



            CSTNode* paramListNode = parseParameterList(currNode, currToken);
            if (paramListNode == nullptr) {return nullptr;}
            currNode = currNode->link(paramListNode);
        }
    }




    return currNode;

}









// <IDENTIFIER> ::= <LETTER_UNDERSCORE> | <LETTER_UNDERSCORE> <INDENTIFIER_TAIL>
CSTNode* parseIdentifier(CSTNode*& currNode, Token*& currToken) {


    if (currNode == nullptr) { return nullptr;} 
    if (currToken == nullptr) {return currNode;}


    if (currToken->getType() != IDENTIFIER) {
        if(!ERROR) {std::cerr << "Syntax error on line " << currToken->getLineNum() << " expected identifier got " << currToken->token << "\n";}
        return nullptr;
    } else if (isReservedWord(currToken)) {
        if(!ERROR) {std::cerr << "[-] Syntax error on line " << currToken->getLineNum() << " \"" << currToken->token << "\" is a reserved word and cannot be name for declaration" << "\n";}
        return nullptr;
    }


    CSTNode* identifierNode = new CSTNode(IDENTIFIER, currToken->token, currToken->getLineNum());
    currNode = currNode->link(identifierNode);
    if (currToken->getNext() == nullptr) { return currNode;}
    currToken = currToken->getNext();


    return identifierNode;
}









// <BLOCK_STATEMENT> ::= <L_BRACE> <COMPOUND_STATEMENT> <R_BRACE>
CSTNode* parseBlockStatement(CSTNode*& currNode, Token*& currToken) {


    if (currNode == nullptr) { return nullptr;} 
    if (currToken == nullptr) {return currNode;}




    // <L_BRACE>
    if (currToken->getType() != L_BRACE) {
        if(!ERROR) {std::cerr << "syntax error at line << " << currToken->getLineNum() << " '{' should follow paramiter" << "\n";}
        return nullptr;
    }
    CSTNode* lBraceNode = new CSTNode(L_BRACE, "{", currToken->getLineNum());
    currNode = currNode->link(lBraceNode);
    currToken = currToken->getNext();
    if (currToken->getNext() == nullptr) { return currNode;}



    // <COMPOUNT_SYATEMENT>
    CSTNode* compoundNode = parseCompoundStatement(currNode, currToken);
    if (compoundNode == nullptr) {return nullptr;}
    currNode = currNode->link(compoundNode);
    


    // <R_BRACE>
    if (currToken->getType() != R_BRACE) {
        if(!ERROR) {std::cerr << "syntax error at line << " << currToken->getLineNum() << " unclosed '}' at line " << currToken->getLineNum() << "\n";}
        return nullptr;
    }
    CSTNode* rBraceNode = new CSTNode(R_BRACE, "}", currToken->getLineNum());
    currNode = currNode->link(rBraceNode);
    if (currToken->getNext() == nullptr) { return currNode;}
    currToken = currToken->getNext();




    return currNode;


}



//<DECLARATION_STATEMENT> ::= <DATATYPE_SPECIFIER> <IDENTIFIER> <SEMICOLON> | 
//                             <DATATYPE_SPECIFIER> <IDENTIFIER_AND_IDENTIFIER_ARRAY_LIST> <SEMICOLON>
CSTNode* parseDeclarationStatement(CSTNode*& currNode, Token*& currToken) { 

    if (currNode == nullptr) { return nullptr;} 
    if (currToken == nullptr) {return currNode;}

    //<DATATYPE_SPECIFIER>
    CSTNode* dataSpecifierNode = parseDatatypeSpecifier(currNode, currToken);
    if (dataSpecifierNode == nullptr) {return nullptr;}
    currNode = currNode->link(dataSpecifierNode);


    // <IDENTIFIER>  |  <IDENTIFIER_AND_IDENTIFIER_ARRAY_LIST>
    CSTNode* identifierNode;
    if (currToken->getType() != IDENTIFIER) {
        if(!ERROR) {std::cerr << "Syntac error on line " << currToken->getLineNum() << " expected identfier, got" << currToken->token << "\n";}
        return nullptr;
    }
    if (currToken->getNext() == nullptr) {
        identifierNode = parseIdentifier(currNode, currToken);
    } else if (currToken->getNext()->token == "[" || currToken->getNext()->token == ",") {
        identifierNode = parseIdentifierAndIdentifierArrayList(currNode, currToken);
    } else {
        identifierNode = parseIdentifier(currNode, currToken);
    }

    if (identifierNode == nullptr) {return nullptr;}
    currNode = currNode->link(identifierNode);


    // <SEMICOLON>
    if (currToken->getType() != SEMICOLON) {
        if(!ERROR) {std::cerr << "syntax error on line " << currToken->getLineNum() << " midding (declaration statment) ';' " << "\n";}
        return nullptr;
    }
    CSTNode* semiColonNode = new CSTNode(SEMICOLON, ";", currToken->getLineNum());
    currNode = currNode->link(semiColonNode);
    if (currToken->getNext() == nullptr) { return currNode;}
    currToken = currToken->getNext();

    return currNode;
}







////<FUNCTION_DECLARATION> ::= function <DATATYPE_SPECIFIER> <IDENTIFIER> <L_PAREN> <PARAMETER_LIST> <R_PAREN> < L_BRACE> <COMPOUND_STATEMENT> <R_BRACE> | 
//                             function <DATATYPE_SPECIFIER> <IDENTIFIER> <L_PAREN> void <R_PAREN> < L_BRACE> <COMPOUND_STATEMENT> <R_BRACE>
CSTNode* parseFunctionDeclaration(CSTNode*& currNode, Token*& currToken) {



    if (currNode == nullptr) { return nullptr;} 
    if (currToken == nullptr) {return currNode;}





    //<DATATYPE_SPECIFIER>
    CSTNode* dataSpecifierNode = parseDatatypeSpecifier(currNode, currToken);
    if (dataSpecifierNode == nullptr) {return nullptr;}
    currNode = currNode->link(dataSpecifierNode);



    // <IDENTIFIER> 
    if (currToken->getType() != IDENTIFIER) {
        if(!ERROR) {std::cerr << "syntax error on line " << currToken->getLineNum() << " missing identifier after datatype identifier" << "\n";}
        return nullptr;
    }
    CSTNode* identifierNode = parseIdentifier(currNode, currToken);
    if (identifierNode == nullptr) {return nullptr;}
    currNode = currNode->link(identifierNode);
    



    // <L_PAREN>
    if (currToken->getType() != L_PAREN) {
        if(!ERROR) {std::cerr << "syntax error at line << " << currToken->getLineNum() << " function declasration should be followed by '('" << "\n";}
        return nullptr;
    }
    CSTNode* lParenNode = new CSTNode(L_PAREN, "(", currToken->getLineNum());
    currNode = currNode->link(lParenNode);
    currToken = currToken->getNext();
    if (currToken->getNext() == nullptr) { return currNode;}



    // "void" or <PARAMETER_LIST>
    if (currToken->token == "void") { 
        CSTNode* paramNode = new CSTNode(IDENTIFIER, "void", currToken->getLineNum());
        currNode = currNode->link(paramNode);
        currToken = currToken->getNext();
        if (currToken->getNext() == nullptr) { return currNode;}
    } else {
        CSTNode* paramNode = parseParameterList(currNode, currToken);
        if (paramNode == nullptr) {return nullptr;}
        currNode = currNode->link(paramNode);
    }




    
    // <R_PAREN>
    if (currToken->getType() != R_PAREN) {
        if(!ERROR) {std::cerr << "syntax error at line " << currToken->getLineNum() << " unclosed ')' in function declaration: got " << currToken->token << "\n";}
        return nullptr;
    }
    CSTNode* rParenNode = new CSTNode(R_PAREN, ")", currToken->getLineNum());
    currNode = currNode->link(rParenNode);
    currToken = currToken->getNext();
    if (currToken->getNext() == nullptr) { return currNode;}



    // <L_BRACE>
    if (currToken->getType() != L_BRACE) {
        if(!ERROR) {std::cerr << "syntax error at line << " << currToken->getLineNum() << " '{' should follow paramiter" << "\n";}
        return nullptr;
    }
    CSTNode* lBraceNode = new CSTNode(L_BRACE, "{", currToken->getLineNum());
    currNode = currNode->link(lBraceNode);
    currToken = currToken->getNext();
    if (currToken->getNext() == nullptr) { return currNode;}



    // <COMPOUND_SYATEMENT>
    CSTNode* compoundNode = parseCompoundStatement(currNode, currToken);
    if (compoundNode == nullptr) {return nullptr;}
    currNode = currNode->link(compoundNode);
    


    // <R_BRACE>
    if (currToken->getType() != R_BRACE) {
        if(!ERROR) {std::cerr << "syntax error at line << " << currToken->getLineNum() << " unclosed '}' at line " << currToken->getLineNum() << "\n";}
        return nullptr;
    }
    CSTNode* rBraceNode = new CSTNode(R_BRACE, "}", currToken->getLineNum());
    currNode = currNode->link(rBraceNode);
    if (currToken->getNext() == nullptr) { return currNode;}
    currToken = currToken->getNext();




    return currNode;
}









//<PROCEDURE_DECLARATION> ::= procedure <IDENTIFIER> <L_PAREN> <PARAMETER_LIST> <R_PAREN> <L_BRACE> <COMPOUND_STATEMENT> <R_BRACE> | procedure <IDENTIFIER> <L_PAREN> void <R_PAREN> < L_BRACE> <COMPOUND_STATEMENT> <R_BRACE>
CSTNode* parseProcedureDeclaration(CSTNode*& currNode, Token*& currToken) {



    if (currNode == nullptr) { return nullptr;} 
    if (currToken == nullptr) {return currNode;}




    // <IDENTIFIER> 
    if (currToken->getType() != IDENTIFIER) {
        if(!ERROR) {std::cerr << "syntax error on line " << currToken->getLineNum() << " procedure should be followed by identifier" << "\n";}
        return nullptr;
    }
    CSTNode* identifierNode = parseIdentifier(currNode, currToken);
    if (identifierNode == nullptr) {return nullptr;}
    currNode = currNode->link(identifierNode);
    

    // <L_PAREN>
    if (currToken->getType() != L_PAREN) {
        if(!ERROR) {std::cerr << "syntax error at line << " << currToken->getLineNum() << " procedure declasration should be followed by '('" << "\n";}
        return nullptr;
    }
    CSTNode* lParenNode = new CSTNode(L_PAREN, "(", currToken->getLineNum());
    currNode = currNode->link(lParenNode);
    currToken = currToken->getNext();
    if (currToken->getNext() == nullptr) { return currNode;}



    // "void" or <PARAMETER_LIST>
    if (currToken->token == "void") { 
        CSTNode* paramNode = new CSTNode(IDENTIFIER, "void", currToken->getLineNum());
        currNode = currNode->link(paramNode);
        currToken = currToken->getNext();
        if (currToken->getNext() == nullptr) { return currNode;}
    } else {
        CSTNode* paramNode = parseParameterList(currNode, currToken);
        if (paramNode == nullptr) {return nullptr;}
        currNode = currNode->link(paramNode);
        
    }




    
    // <R_PAREN>
    if (currToken->getType() != R_PAREN) {
        if(!ERROR) {std::cerr << "syntax error at line << " << currToken->getLineNum() << " unclosed ')' in procedure declaration" << "\n";}
        return nullptr;
    }
    CSTNode* rParenNode = new CSTNode(R_PAREN, ")", currToken->getLineNum());
    currNode = currNode->link(rParenNode);
    if (currToken->getNext() == nullptr) { return currNode;}
    currToken = currToken->getNext();




    // <L_BRACE>
    if (currToken->getType() != L_BRACE) {
        if(!ERROR) {std::cerr << "syntax error at line << " << currToken->getLineNum() << " '{' should follow paramiter" << "\n";}
        return nullptr;
    }
    CSTNode* lBraceNode = new CSTNode(L_BRACE, "{", currToken->getLineNum());
    currNode = currNode->link(lBraceNode);
    if (currToken->getNext() == nullptr) { return currNode;}
    currToken = currToken->getNext();



    // empty statement
    if (currToken->getType() == R_BRACE) {
        CSTNode* rBraceNode = new CSTNode(R_BRACE, "}", currToken->getLineNum());
        currNode = currNode->link(rBraceNode);
        if (currToken->getNext() == nullptr) { return currNode;}
        currToken = currToken->getNext();

        return currNode;
    }



    // <COMPOUNT_SYATEMENT>
    CSTNode* compoundNode = parseCompoundStatement(currNode, currToken);
    if (compoundNode == nullptr) {return nullptr;}
    currNode = currNode->link(compoundNode);
    


    // <R_BRACE>
    if (currToken->getType() != R_BRACE) {
        if(!ERROR) {std::cerr << "syntax error at line << " << currToken->getLineNum() << " unclosed '}' at line " << currToken->getLineNum() << "\n";}
        return nullptr;
    }
    CSTNode* rBraceNode = new CSTNode(R_BRACE, "}", currToken->getLineNum());
    currNode = currNode->link(rBraceNode);
    if (currToken->getNext() == nullptr) { return currNode;}
    currToken = currToken->getNext();

    return currNode;
}








// <PROGRAM_TAIL> ::= <FUNCTION_DECLARATION> | 
//                    <FUNCTION_DECLARATION> <PROGRAM_TAIL> | 
//                    <PROCEDURE_DECLARATION> | 
//                    <PROCEDURE_DECLARATION> <PROGRAM_TAIL> | 
//                    <DECLARATION_STATEMENT> | 
//                    <DECLARATION_STATEMENT> <PROGRAM_TAIL>
CSTNode* parseProgramTail(CSTNode*& currNode, Token*& currToken) { 



    if (currNode == nullptr) { return nullptr;} 
    if (currToken == nullptr) {return currNode;}



    if (currToken->token == "procedure") { 
        if (currToken->getNext() == nullptr) { return currNode;}

        CSTNode* procedureNode = new CSTNode(PROCEDURE_DECLARATION, "procedure", currToken->getLineNum());    
        currNode = currNode->link(procedureNode);
        currToken = currToken->getNext();
        if (currToken->getNext() == nullptr) { return currNode;}
        CSTNode* procedureDeclarationNode = parseProcedureDeclaration(currNode, currToken);
        if (procedureDeclarationNode == nullptr) {return nullptr;}
        currNode = currNode->link(procedureDeclarationNode);
        if (currToken && currToken->getType() != R_BRACE && currToken->getType() != SEMICOLON) {
            CSTNode* programNode = parseProgramTail(currNode, currToken);
            if (!programNode) {return nullptr;}
            currNode = currNode->link(programNode);
        }
        return currNode;


    } else if (currToken->token == "function") {

    
        CSTNode* functionNode = new CSTNode(FUNCTION_DECLARATION, "function", currToken->getLineNum());    
        currNode = currNode->link(functionNode);
        if (currToken->getNext() == nullptr) { return currNode;}
        currToken = currToken->getNext();
        CSTNode*  functionDeclarationNode = parseFunctionDeclaration(currNode, currToken);
        if (functionDeclarationNode == nullptr) { return nullptr;}
        currNode = currNode->link(functionDeclarationNode);
        if (currToken && currToken->getType() != R_BRACE && currToken->getType() != SEMICOLON) {
            CSTNode* programNode = parseProgramTail(currNode, currToken);
            if (!programNode) {return nullptr;}
            currNode = currNode->link(programNode);
        }
        return currNode;



    } else if (currToken->token == "char" || currToken->token == "int" || currToken->token == "bool") {


        CSTNode* declarationStatementNode = parseDeclarationStatement(currNode, currToken);
        if (declarationStatementNode == nullptr) {return nullptr;}
        currNode = currNode->link(declarationStatementNode);
        if (currToken && currToken->getType() != R_BRACE && currToken->getType() != SEMICOLON) {
            CSTNode* programNode = parseProgramTail(currNode, currToken);
            if (!programNode) {return nullptr;}
            currNode = currNode->link(programNode);
        }
        return currNode;


    } else {
        if(!ERROR) {std::cerr << "Syntax error at line << " << currToken->getLineNum() << " Imporoper start to program" << std::endl;}
        return nullptr;
    }


}







//<MAIN_PROCEDURE> ::= procedure main <L_PAREN> void <R_PAREN> <BLOCK_STATEMENT>
CSTNode* parseMainProcedure(CSTNode*& currNode, Token*& currToken) { 

    if (currNode == nullptr) { return nullptr;} 
    if (currToken == nullptr) {return currNode;}




    
    // "main"
    CSTNode* mainNode = new CSTNode(IDENTIFIER, "main", currToken->getLineNum());
    currNode = currNode->link(mainNode);
    currToken = currToken->getNext();
    if (currToken->getNext() == nullptr) { return currNode;}



    // <L_PAREN>
    if (currToken->getType() != L_PAREN) {
        if(!ERROR) {std::cerr << "syntax error at line << " << currToken->getLineNum() << " main declasration should be followed by '('" << "\n";}
        return nullptr;
    }
    CSTNode* lParenNode = new CSTNode(L_PAREN, "(", currToken->getLineNum());
    currNode = currNode->link(lParenNode);
    currToken = currToken->getNext();
    if (currToken->getNext() == nullptr) { return currNode;}



    // "void"
    if (currToken->token != "void") {
        if(!ERROR) {std::cerr << "syntax error at line << " << currToken->getLineNum() << " procedure main must be void" << "\n";}
        return nullptr;
    }
    CSTNode* voidNode = new CSTNode(IDENTIFIER, "void", currToken->getLineNum());
    currNode = currNode->link(voidNode);
    currToken = currToken->getNext();
    if (currToken->getNext() == nullptr) { return currNode;}
    


    // <R_PAREN>
    if (currToken->getType() != R_PAREN) {
        if(!ERROR) {std::cerr << "syntax error at line << " << currToken->getLineNum() << " unclosed ')' in   main declaration" << "\n";}
        return nullptr;
    }
    CSTNode* rParenNode = new CSTNode(R_PAREN, ")", currToken->getLineNum());
    currNode = currNode->link(rParenNode);
    currToken = currToken->getNext();
    if (currToken->getNext() == nullptr) { return currNode;}




    // <BLOCK_STATEMENT>
    CSTNode* blockStatementNode = parseBlockStatement(currNode, currToken);
    if (blockStatementNode == nullptr) {return nullptr;}
    currNode = currNode->link(blockStatementNode);
    
    
    return currNode;



}






// <PROGRAM> ::= <MAIN_PROCEDURE> | <MAIN_PROCEDURE> <PROGRAM_TAIL> |<FUNCTION_DECLARATION> <PROGRAM> | <PROCEDURE_DECLARATION> <PROGRAM> | <DECLARATION_STATEMENT> <PROGRAM> 
CSTNode* parseProgram(CSTNode*& currNode,Token*& currToken) {


    if (currNode == nullptr) { return nullptr;} 
    if (currToken == nullptr) {return currNode;}


    if (currToken->token == "procedure") { 
        if (currToken->getNext() == nullptr) { return currNode;}


        if (currToken->getNext()->token == "main") {
            CSTNode* procedureMainNode = new CSTNode(MAIN_PROCEDURE, "procedure", currToken->getLineNum()); 
            currNode = currNode->link(procedureMainNode);
            currToken = currToken->getNext();
            if (currToken->getNext() == nullptr) { return currNode;}
            CSTNode* mainProcedureNode = parseMainProcedure(currNode, currToken);
            if (mainProcedureNode == nullptr) {return nullptr;}
            currNode = currNode->link(mainProcedureNode);
            if (currToken && currToken->getType() != R_BRACE && currToken->getType() != SEMICOLON) {
                CSTNode* programNode = parseProgramTail(currNode, currToken);
                if (!programNode) {return nullptr;}
                currNode = currNode->link(programNode);
            }
            return currNode;
        } else {

            CSTNode* procedureNode = new CSTNode(PROCEDURE_DECLARATION, "procedure", currToken->getLineNum());    
            currNode = currNode->link(procedureNode);
            currToken = currToken->getNext();
            if (currToken->getNext() == nullptr) { return currNode;}
            CSTNode* procedureDeclarationNode = parseProcedureDeclaration(currNode, currToken);
            if (procedureDeclarationNode == nullptr) {return nullptr;}
            currNode = currNode->link(procedureDeclarationNode);
            if (currToken && currToken->getType() != R_BRACE && currToken->getType() != SEMICOLON) {
                CSTNode* programNode = parseProgram(currNode, currToken);
                if (!programNode) {return nullptr;}
                currNode = currNode->link(programNode);
        
            }
            return currNode;
        }




    } else if (currToken->token == "function") {

    
        CSTNode* functionNode = new CSTNode(FUNCTION_DECLARATION, "function", currToken->getLineNum());    
        currNode = currNode->link(functionNode);
        if (currToken->getNext() == nullptr) { return currNode;}
        currToken = currToken->getNext();
        CSTNode*  functionDeclarationNode = parseFunctionDeclaration(currNode, currToken);
        if (functionDeclarationNode == nullptr) { return nullptr;}
        currNode = currNode->link(functionDeclarationNode);
        currNode = parseProgram(currNode, currToken);
        return currNode;


    } else if (currToken->token == "char" || currToken->token == "int" || currToken->token == "bool") {


        CSTNode* declarationStatementNode = parseDeclarationStatement(currNode, currToken);
        if (declarationStatementNode == nullptr) {return nullptr;}
        currNode = currNode->link(declarationStatementNode);
        currNode = parseProgram(currNode, currToken);
        return currNode;

    } else {
        if(!ERROR) {std::cerr << "Syntax error at line << " << currToken->getLineNum() << " Imporoper start to program" << std::endl;}
        return nullptr;
    }



   
}






// helper function to start recursize decent parsing
CSTNode* recDecParse(Token*& currToken) {

    CSTNode* cstHead = new CSTNode(BASE, "base", 0);
    cstHead->setRoot(cstHead);
    CSTNode* copyHead = cstHead;
    CSTNode* result = parseProgram(cstHead, currToken);

    if (!result) { return result;}


    return result->root;



}





