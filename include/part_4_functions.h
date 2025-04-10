#pragma once



#include "CSTNode.h"
#include "STNode.h"
#include <unordered_map>
#include <unordered_set>
#include <string>





bool extractSymbolsParamiterList(STNode*& headNode, CSTNode*& currNode, std::unordered_map<int, std::unordered_set<std::string>>& varsAndScopes);


bool extractSymbolsIdentifierAndIdentifierArrayList(STNode*& stNode, CSTNode*& currNode, std::unordered_map<int, std::unordered_set<std::string>>& varsAndScopes, bool isGlobal);

STNode* makeSymbolTable(CSTNode* cstHead);
