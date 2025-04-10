
#include <iostream>
#include "Token.h"
#include <stack>
#include "CSTNode.h"
#include "STNode.h"
#include <unordered_map>
#include <unordered_set>
#include <string>


#include "part_4_functions.h"







// <PARAMETER_LIST> ::= <DATATYPE_SPECIFIER> <IDENTIFIER> | 
//                      <DATATYPE_SPECIFIER> <IDENTIFIER_AND_IDENTIFIER_ARRAY_PARAMETER_LIST_DECLARATION> | 
//                      <DATATYPE_SPECIFIER> <IDENTIFIER> <PARAMETER_LIST> | 
//                      <DATATYPE_SPECIFIER> <IDENTIFIER_AND_IDENTIFIER_ARRAY_PARAMETER_LIST_DECLARATION> <PARAMETER_LIST>
bool extractSymbolsParamiterList(STNode*& headNode, CSTNode*& currNode, std::unordered_map<int, std::unordered_set<std::string>>& varsAndScopes) { 
    int initialScope = headNode->getScope();
    int globalScope = 0;

    STNode* node = new STNode(DATA_TYPE, nullptr);
    node->setIsParam(true);
    node->setScope(initialScope);
    node->setHasParam(false);
    node->setIsArray(false);
    node->setArraySize("0");

    headNode->setParamHead(node);
    STNode* currSTNode = node;




    auto createNextParamNode = [&]() {
        STNode* newNode = new STNode(DATA_TYPE, currSTNode);
        newNode->setIsParam(true);
        newNode->setScope(initialScope);
        currSTNode->setNext(newNode);
        currSTNode = newNode;
        currSTNode->setHasParam(false);
        currSTNode->setIsArray(false);
        currSTNode->setArraySize("0");
    };



    while(currNode->getType() != R_PAREN) {

        // <DATATYPE_SPECIFIER>
        currSTNode->setDataType(currNode->value);
        currNode = currNode->getNext();  // <IDENTIFIER>


        // check if identifier is alreayd used in gloabal or local scope if not
        if (varsAndScopes[globalScope].count(currNode->value) > 0) {
            std::cerr << "Error on line " << currNode->getLineNum() << ": variable \"" << currNode->value << "\" is already defined gloablly" << "\n";
            return false;
        } else if (varsAndScopes[initialScope].count(currNode->value) > 0) {
            std::cerr << "Error on line " << currNode->getLineNum() << ": variable \"" << currNode->value << "\" is already defined locally" << "\n";
            return false;
        
        }

        varsAndScopes[initialScope].insert(currNode->value); 
        currSTNode->setName(currNode->value);


        currNode = currNode->getNext(); // <L_BRACKET> | <COMMA>

        if (currNode->getType() == L_BRACKET) {
            currSTNode->setIsArray(true);
            currNode = currNode->getNext(); // <WHOLE_NUMBER>
            currSTNode->setArraySize(currNode->value);
            currNode = currNode->getNext(); // <R_BRACKET> 
            currNode = currNode->getNext(); // <COMMA> | something else 
            
            // check if comma after
            if (currNode->getType() == COMMA) { 
                currNode = currNode->getNext(); // move past comma
                createNextParamNode(); 
            }
        }


        else if (currNode->getType() == COMMA) {
            currNode = currNode->getNext(); // move past comma
            createNextParamNode(); 
        }
    }


    return true;
}




// <IDENTIFIER_AND_IDENTIFIER_ARRAY_LIST> ::= <IDENTIFIER_LIST> | <IDENTIFIER_ARRAY_LIST> | <IDENTIFIER_LIST> <IDENTIFIER_ARRAY_LIST> | <IDENTIFIER_ARRAY_LIST> <IDENTIFIER_LIST>

bool extractSymbolsIdentifierAndIdentifierArrayList(STNode*& stNode, CSTNode*& currNode, std::unordered_map<int, std::unordered_set<std::string>>& varsAndScopes, bool isGlobal) {

    int initialScope = stNode->getScope();
    int globalScope = 0;
    STNode* currSTNode = stNode;
 

    while(currNode->getType() != SEMICOLON) {
        stNode->setIsParam(false);
        stNode->setHasParam(false);


        // <L_BRACKET> | <COMMA>
        if (currNode->getType() == L_BRACKET) {

            currSTNode->setIsArray(true);
            currNode = currNode->getNext();
            // <WHOLE_NUMBER>
            currSTNode->setArraySize(currNode->value);
            
            // check if comma 
            currNode = currNode->getNext();
            if (currNode->getType() == COMMA) {
                currNode = currNode->getNext();
            } else {
                break;
            }
        }


        else if (currNode->getType() == COMMA) {
            currSTNode->setIsArray(false);
            currSTNode->setArraySize("0");
        } else {
            break;
        }

        STNode* newNode = new STNode(DATA_TYPE, currSTNode);
        newNode->setScope(currSTNode->getScope());
        newNode->setDataType(currSTNode->getDataType());
        newNode->setIsArray(false);
        newNode->setArraySize("0");
        currSTNode->setNext(newNode);
        currSTNode = newNode;


        currNode = currNode->getNext(); // <IDENTIFIER>
        // check if identifier is alreayd used in gloabal or local scope if not
        if (varsAndScopes[globalScope].count(currNode->value) > 0) {
            std::cerr << "Error on line " << currNode->getLineNum() << ": variable \"" << currNode->value << "\" is already defined gloablly" << "\n";
            return false;
        } else if (varsAndScopes[initialScope].count(currNode->value) > 0) {
            std::cerr << "Error on line " << currNode->getLineNum() << ": variable \"" << currNode->value << "\" is already defined locally" << "\n";
            return false;
        }

        isGlobal ? varsAndScopes[globalScope].insert(currNode->value) : varsAndScopes[initialScope].insert(currNode->value); 
        currSTNode->setName(currNode->value);

        currNode = currNode->getNext();
    }

    stNode = currSTNode;
    return true;
}













// fuction
// procedure
// <DATATYPE_SPECIFIER> <IDENTIFIER> <SEMICOLON> | <DATATYPE_SPECIFIER> <IDENTIFIER_AND_IDENTIFIER_ARRAY_LIST> <SEMICOLON>
STNode* makeSymbolTable(CSTNode* cstHead) {

    if (!cstHead) {
        std::cerr << "Symbol Table cant be created from nullptr" << "\n";
        return nullptr;
    }



    STNode* stHead = new STNode(BASE, nullptr);
    STNode* stNode = stHead; // ⬅️ last node in the chain




    std::unordered_map<int, std::unordered_set<std::string>> varsAndScopes;
    int currScope = 0;
    int globalScope = 0;
    bool isGlobal = true;
    int braceCount = 0;


    // create stack and look through CST
    std::stack<CSTNode*> stk;
    stk.push(cstHead);
    while (!stk.empty()) {
        CSTNode* node = stk.top();
        stk.pop();

        

        // <FUNCTION_DECLARATION> ::= function <DATATYPE_SPECIFIER> <IDENTIFIER> <L_PAREN> <PARAMETER_LIST> <R_PAREN> <L_BRACE> <COMPOUND_STATEMENT> <R_BRACE> |
        //                            function <DATATYPE_SPECIFIER> <IDENTIFIER> <L_PAREN> void <R_PAREN> <L_BRACE> <COMPOUND_STATEMENT> <R_BRACE>
        if (node->getType() == FUNCTION_DECLARATION) {
            isGlobal = false;
            currScope += 1;
            STNode* newSTNode = new STNode(FUNCTION, nullptr);
            stNode->setNext(newSTNode);
            newSTNode->setPrev(stNode);                        
            stNode = newSTNode;


 

            stNode->setScope(currScope);
            node = node->getNext(); // <DATATYPE_SPECIFIER>
            stNode->setDataType(node->value);
            node = node->getNext();


            // check if identifier is alreayd used in gloabal or local scope if not
            if (varsAndScopes[globalScope].count(node->value) > 0) {
                std::cerr << "Error on line " << node->getLineNum() << ": variable \"" << node->value << "\" is already defined gloablly" << "\n";
                return nullptr;
            } else if (varsAndScopes[currScope].count(node->value) > 0) {
                std::cerr << "Error on line " << node->getLineNum() << ": variable \"" << node->value << "\" is already defined locally" << "\n";
                return nullptr;
            
            }


            isGlobal ? varsAndScopes[globalScope].insert(node->value) : varsAndScopes[currScope].insert(node->value); 
            stNode->setName(node->value);
            node = node->getNext();
            // <L_PAREN>
            node = node->getNext();

            // if void do nothing if parameter_list so somehting
            if (node->value == "void") {
                stNode->setHasParam(false);
            }
            else {
                stNode->setHasParam(true);
                if (!extractSymbolsParamiterList(stNode, node,  varsAndScopes)) {return nullptr;}
            } 
            stNode->setIsArray(false); 
            stNode->setArraySize("0");
        }






        // <MAIN_PROCEDURE> ::= procedure main <L_PAREN> void <R_PAREN> <BLOCK_STATEMENT>
        else if (node->getType() == MAIN_PROCEDURE) {

            isGlobal = false;
            currScope += 1;
            STNode* newSTNode = new STNode("main", PROCEDURE, stNode);            
            stNode->setNext(newSTNode);
            stNode = newSTNode;

            stNode->setDataType("NA");
            stNode->setScope(currScope);
            stNode->setIsArray(false); 
            stNode->setArraySize("0");
        }





        // <PROCEDURE_DECLARATION> ::= procedure <IDENTIFIER> <L_PAREN> <PARAMETER_LIST> <R_PAREN> <L_BRACE> <COMPOUND_STATEMENT> <R_BRACE> | 
        //                             procedure <IDENTIFIER> <L_PAREN> void <R_PAREN> <L_BRACE> <COMPOUND_STATEMENT> <R_BRACE>
        else if (node->getType() == PROCEDURE_DECLARATION) {
            isGlobal = false;
            currScope += 1;
            STNode* newSTNode = new STNode(PROCEDURE, stNode);            
            stNode->setNext(newSTNode);
            stNode = newSTNode;

            stNode->setScope(currScope);
            node = node->getNext(); // <IDENTIFIER> 
            stNode->setDataType("NA");


            // check if identifier is alreayd used in gloabal or local scope if not
            if (varsAndScopes[globalScope].count(node->value) > 0) {
                std::cerr << "Error on line " << node->getLineNum() << ": variable \"" << node->value << "\" is already defined gloablly" << "\n";
                return nullptr;
            } else if (varsAndScopes[currScope].count(node->value) > 0) {
                std::cerr << "Error on line " << node->getLineNum() << ": variable \"" << node->value << "\" is already defined locally" << "\n";
                return nullptr;
            
            }
            isGlobal ? varsAndScopes[globalScope].insert(node->value) : varsAndScopes[currScope].insert(node->value); 
            stNode->setName(node->value);


            node = node->getNext(); // <L_PAREN>
            node = node->getNext(); // <VOID> | <DATATYPE_SPECIFIER>

            // if void do nothing if parameter_list so somehting
            if (node->value == "void") {
                stNode->setHasParam(false);
            }
            else {
                stNode->setHasParam(true);
                if (!extractSymbolsParamiterList(stNode, node,  varsAndScopes)) {return nullptr;}
            } 
            stNode->setIsArray(false); 
            stNode->setArraySize("0");
        }







        // <DECLARATION_STATEMENT> ::= <DATATYPE_SPECIFIER> <IDENTIFIER> <SEMICOLON> | 
        //                             <DATATYPE_SPECIFIER> <IDENTIFIER_AND_IDENTIFIER_ARRAY_LIST> <SEMICOLON>
        else if (node->getType() == DATATYPE_SPECIFIER) {
            STNode* newSTNode = new STNode(DATA_TYPE, stNode);            
            stNode->setNext(newSTNode);
            stNode = newSTNode;
            isGlobal ? stNode->setScope(0): stNode->setScope(currScope);

            stNode->setDataType(node->value);
            node = node->getNext();
            // check if identifier is alreayd used in gloabal or local scope if not
            if (varsAndScopes[globalScope].count(node->value) > 0) {
                std::cerr << "Error on line " << node->getLineNum() << ": variable \"" << node->value << "\" is already defined gloablly" << "\n";
                return nullptr;
            } else if (varsAndScopes[currScope].count(node->value) > 0) {
                std::cerr << "Error on line " << node->getLineNum() << ": variable \"" << node->value << "\" is already defined locally" << "\n";
                return nullptr;
            
            }

            varsAndScopes[currScope].insert(node->value);
            stNode->setName(node->value);
            node = node->getNext();


            if (node->getType() != SEMICOLON) {
                if (!extractSymbolsIdentifierAndIdentifierArrayList(stNode, node, varsAndScopes, isGlobal)) {return nullptr;}
            } else {
                stNode->setIsArray(false);
                stNode->setArraySize("0");
            }
        }


        
        else {
            if (node->getType() == L_BRACE) {braceCount++;}
            else if (node->getType() == R_BRACE) {braceCount--;}


            if (braceCount == 0) { isGlobal = true;}
            else { isGlobal = false;}
        }



        // Push sibling first so child is processed next
        if (node->rightSibling)
            stk.push(node->rightSibling);
        if (node->leftChild)
            stk.push(node->leftChild);
        }



   // remove BASE node 
    STNode* returnNode = stHead->getNext();
    delete(stHead);
    return returnNode;

}






