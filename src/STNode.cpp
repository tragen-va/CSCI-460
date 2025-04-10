

#include "STNode.h"



std::ostream& operator<<(std::ostream& out, const STNode &t) {
    if (&t == nullptr) {
        out << "NULL" << "\n";
    } else {

        out << "STNode type: " << t.typeToStr() << "\nCSTNode Name: " << t.name << "\n";
    }

    return out;
}



std::string STNode::typeToStr() const {
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
        case FUNCTION: return "FUNCTION";
        case PROCEDURE: return "PROCEDURE";
        case DATA_TYPE: return "DATA_TYPE";
        case EXPRESSION_STATEMENT: return "EXPRESSION_STATEMENT";
        default: return "UNKNOWN_TOKEN";
    }

}








void STNode::printChain() const {
    const STNode* temp = this;
    std::cout << "**************************** " << std::endl;
    std::cout << "**     Symbol Table       **" << std::endl;
    std::cout << "**************************** " << std::endl;

    while (temp) {
        // Print main node
        std::cout << "             |" << std::endl;
        std::cout << "             v" << std::endl;
        std::cout << "Name:     " << temp->name << std::endl;
        std::cout << "Type:     " << temp->typeToStr() << std::endl;
        std::cout << "DataType: " << temp->dataType << std::endl;
        temp->isArray ? std::cout << "isArray: Yes" << std::endl : std::cout << "isArray: No" << std::endl;
        std::cout << "ArraySize: " << temp->arraySize << std::endl;
        std::cout << "Scope:    " << temp->scope << std::endl;

        // If it has parameters, print those indented
        if (temp->hasParam && temp->paramHead) {
            std::cout << "             |                                  " << std::endl;
            std::cout << "             ----------------------------------- " << std::endl;
            std::cout << "                                               | " << std::endl;
            std::cout << "                                           Parameters " << std::endl;
            const STNode* param = temp->paramHead;
            while (param) {
                std::cout << "                                               |" << std::endl;
                std::cout << "                                               v" << std::endl;
                std::cout << "                                      Param Name:     " << param->name << std::endl;
                std::cout << "                                      Param DataType: " << param->dataType << std::endl;
                param->isArray ? std::cout << "                                      isArray: Yes" << std::endl : std::cout << "                                      isArray: No" << std::endl;
                std::cout << "                                      Param arraySize: " << param->arraySize << std::endl;
                std::cout << "                                      Param Scope:    " << param->scope << std::endl;
                std::cout << "                               ------------------------------" << std::endl;
                param = param->next;
            }
            std::cout << "\n\n " << std::endl;
            
        }

        std::cout << "-------------------------------" << std::endl;

        // Move to next main node
        temp = temp->next;
    }
}






void STNode::setName(std::string _name) {
    name = _name;
}

void STNode::setType(TOKEN _type) {
    type = _type;
}

void STNode::setDataType(std::string _dataType) {
    dataType = _dataType;
}

void STNode::setIsArray(bool _isArray) {
    isArray = _isArray;
}

void STNode::setArraySize(std::string _arraySize) {
    arraySize = _arraySize;
}

void STNode::setScope(int _scope) {
    scope = _scope;
}
void STNode::setPrev(STNode* _prev) {
    prev = _prev;
}

void STNode::setIsParam(bool _isParam) {
    isParam = _isParam;
}

void STNode::setHasParam(bool _hasParam) {
    hasParam = _hasParam;
}

void STNode::setParamHead(STNode* _paramHead) {
    paramHead = _paramHead;
}

std::string STNode::getDataType() {
    return dataType;
}

int STNode::getScope() {
    return scope;
}

void STNode::setNext(STNode* _next) {
    next = _next;
}


STNode* STNode::getNext() {
    return next;
}




