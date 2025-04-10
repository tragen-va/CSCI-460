

#include "CSTNode.h"


std::ostream& operator<<(std::ostream& out, const CSTNode &t) {
    if (&t == nullptr) {
        out << "NULL" << "\n";
    } else {

        out << "CSTNode type: " << t.typeToStr() << "\nCSTNode Value: " << t.value << "\n";
    }

    return out;
}



std::string CSTNode::typeToStr() const {
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
        case DATATYPE_SPECIFIER: return "DATATYPE_SPECIFIER";
        case EXPRESSION_STATEMENT: return "EXPRESSION_STATEMENT";
        default: return "UNKNOWN_TOKEN";
    }

}




void CSTNode::printHelper(int indent, bool isChild) const {
    for (int i = 0; i < indent; ++i) std::cout << "  ";

    
    std::cout << (isChild ? "↳ " : "→ ") << value << "\n";

    
    if (leftChild) {
        leftChild->printHelper(indent + 1, true);
    }

    
    if (rightSibling) {
        rightSibling->printHelper(indent, false);
    }
}






void CSTNode::printChain() const {

    if(type == BASE) {
        if (leftChild) {
            leftChild->printHelper(0, true);
        } else if (rightSibling) {
            rightSibling->printHelper(0, false);
        } else {
            std::cout << "CST is empty" << "\n";
        }
        return;
    }

    printHelper(0, true);
}



CSTNode* CSTNode::link(CSTNode* newNode) {

    if (newNode == nullptr) {
        return nullptr;
    }

    if (newNode == this) {
        return newNode;
    }


    newNode->setRoot(root);
    //masterNode->printChain();



    if (lineNum == newNode->lineNum) {
        rightSibling = newNode;
        return newNode;
    } else if (lineNum < newNode->lineNum) {
        leftChild = newNode;
        return newNode;
    } 

    return newNode;

}




void CSTNode::setRoot(CSTNode* _root) {
        
        
        root = _root;
    }


void CSTNode::setAllRoots(CSTNode* _root) {
    this->root = _root;
    if (leftChild) leftChild->setAllRoots(_root);
    if (rightSibling) rightSibling->setAllRoots(_root);
}




int CSTNode::getLineNum() {
    return lineNum;
}

CSTNode* CSTNode::getNext() {
    if (rightSibling) {
        return rightSibling;
    }
    else if (leftChild) {
        return leftChild;
    }
    else {
        return nullptr;
    }
}



TOKEN CSTNode::getType() {
    return type;
}







