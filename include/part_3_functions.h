#pragma once


#include "Token.h"
#include "CSTNode.h"
#include "STNode.h"





CSTNode* recDecParse(Token*& currToken);


CSTNode* parseProgram(CSTNode*& currNode, Token*& currToken);


CSTNode* parseMainProcedure(CSTNode*& currNode, Token*& currToken);


CSTNode* parseProgramTail(CSTNode*& currNode, Token*& currToken);
 

CSTNode* parseProcedureDeclaration(CSTNode*& currNode, Token*& currToken);


CSTNode* parseFunctionDeclaration(CSTNode*& currNode, Token*& currToken);


CSTNode* parseDeclarationStatement(CSTNode*& currNode, Token*& currToken);


CSTNode* parseBlockStatement(CSTNode*& currNode, Token*& currToken);


CSTNode* parseIdentifier(CSTNode*& currNode, Token*& currToken);


CSTNode* parseParameterList(CSTNode*& currNode, Token*& currToken);


CSTNode* parseCompoundStatement(CSTNode*& currNode, Token*& currToken);


CSTNode* parseDatatypeSpecifier(CSTNode*& currNode, Token*& currToken);


CSTNode* parseIdentifierAndIdentifierArrayList(CSTNode*& currNode, Token*& currToken);


bool isStartOfStatment(Token* currToken);


CSTNode* parseIdentifierList(CSTNode*& currNode, Token*& currToken);


CSTNode* parseIdentifierArrayList(CSTNode*& currNode, Token*& currToken);


CSTNode* parseStatement(CSTNode*& currNode, Token*& currToken);


CSTNode* parseWholeNumber(CSTNode*& currNode, Token*& currToken);


CSTNode* parseAssignmentStatement(CSTNode*& currNode, Token*& currToken);


CSTNode* parseIterationStatement(CSTNode*& currNode, Token*& currToken);


CSTNode* parseSelectionStatement(CSTNode*& currNode, Token*& currToken);


CSTNode* parsePrintfStatement(CSTNode*& currNode, Token*& currToken);


CSTNode* parseReturnStatement(CSTNode*& currNode, Token*& currToken);


CSTNode* parseSingleQuotedString(CSTNode*& currNode, Token*& currToken);


CSTNode* parseDoubleQuotedString(CSTNode*& currNode, Token*& currToken);


CSTNode* parseInitilazationExpression(CSTNode*& currNode, Token*& currToken);


CSTNode* parseBooleanExpression(CSTNode*& currNode, Token*& currToken);


bool couldBeBooleanExpression(Token* currToken);


CSTNode* parseExpression(CSTNode*& currNode, Token*& currToken);


CSTNode* pareseBooleanOperator(CSTNode*& currNode, Token*& currToken);


CSTNode* parseNumericalExpression(CSTNode*& currNode, Token*& currToken); 


bool couldBeNumericalExpressionThenBoolean(Token* currToken);


bool couldBeNumericalExpression(Token* currToken);


bool couldBeNumericalOperand(Token* currToken);


CSTNode* parseNumericalOperand(CSTNode*& currNode, Token*& currToken); 


CSTNode* parseGetCharFunction(CSTNode*& currNode, Token*& currToken);


bool couldBeUserDefinedFunction(Token* currToken);


CSTNode* parseUserDefinedFunction(CSTNode*& currNode, Token*& currToken);


void deleteTree(CSTNode* node);


CSTNode* findCopyOfNode(CSTNode* original, CSTNode* copy, CSTNode* target);


CSTNode* copyHelper(CSTNode* currNode);


CSTNode* copyTree(CSTNode* currNode);


bool isReservedWord(Token* currToken);


CSTNode* parseSizeofFunction(CSTNode*& currNode, Token*& currToken);


CSTNode* parseUserDefinedProcedureCallStatement(CSTNode*& currNode, Token*& currToken);


CSTNode* parseIdentifierAndIdentifierArrayParameterList(CSTNode*& currNode, Token*& currToken);


CSTNode* parseIdentifierAndIdentifierArrayParameterListDeclaration(CSTNode*& currNode, Token*& currToken);


CSTNode* parseIterationAssignment(CSTNode*& currNode, Token*& currToken);

