#pragma once

#include "Token.h"


class CSTNode {
public:
    TOKEN type;
    std::string value;
    int lineNum;

    void printHelper(int indent, bool isChild) const;


    CSTNode* leftChild;
    CSTNode* rightSibling;
    CSTNode* root;

    CSTNode(TOKEN _type, std::string _value, int _lineNum) 
        : type(_type), value(_value), lineNum(_lineNum), leftChild(nullptr), rightSibling(nullptr), root(nullptr) {}



    std::string typeToStr() const;
    CSTNode* link(CSTNode* newNode);
    
    void setRoot(CSTNode* _root);
    void setAllRoots(CSTNode* _root);


    void printChain() const;

    friend std::ostream& operator<<(std::ostream& out, const CSTNode &t);



    int getLineNum();

    CSTNode* getNext();



    TOKEN getType();



};
