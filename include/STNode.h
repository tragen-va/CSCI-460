#pragma once

#include "Token.h"



class STNode {
public:

    std::string name;
    TOKEN type;
    std::string dataType;
    bool isArray;
    std::string arraySize;
    int scope;
    STNode* prev;
    STNode* next;
    bool isParam;
    bool hasParam;
    STNode* paramHead;
    



    STNode(std::string _name, TOKEN _type, std::string _dataType, bool _isArray, int _scope, STNode* _prev, STNode* _next)
        : name(_name), type(_type), dataType(_dataType), isArray(_isArray), scope(_scope), prev(_prev) {}


    STNode(TOKEN _type, STNode* _prev) : type(_type), prev(_prev) {
        
        name = "";
        dataType = "";
        isArray = false;
        arraySize = "";
        scope = 0;
        next = nullptr;
        isParam = false;
        hasParam = false;
        paramHead = nullptr;
    }


    STNode(std::string _name, TOKEN _type, STNode* _prev) : name(_name), type(_type), prev(_prev) {
        dataType = "";
        isArray = false;
        arraySize = "";
        scope = 0;
        next = nullptr;
        isParam = false;
        hasParam = false;
        paramHead = nullptr;

    }


    std::string typeToStr() const;
    

    void printChain() const;

    friend std::ostream& operator<<(std::ostream& out, const STNode &t);



    void setName(std::string _name);

    void setType(TOKEN _type);

    void setDataType(std::string _dataType);

    void setIsArray(bool _isArray);

    void setArraySize(std::string _arraySize);

    void setScope(int _scope);

    void setPrev(STNode* _prev);

    void setIsParam(bool _isParam);

    void setHasParam(bool _hasParam);

    void setParamHead(STNode* _paramHead);


    std::string getDataType();
    int getScope();

    void setNext(STNode* _next);
    STNode* getNext();




};

