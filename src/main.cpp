#include <iostream>



#include "Token.h"
#include "CSTNode.h"
#include "STNode.h"
#include "part_1_functions.h"
#include "part_2_functions.h"
#include "part_3_functions.h"
#include "part_4_functions.h"







int main(int argc, char* argv[]) {


    if (argc < 3) {
        std::cerr << "[-] Too few arguments: Usage ./program [inputFile] [outputFile(for part 1)] [part]" << std::endl;
        std::cerr << "[part]  - 0 = All" << std::endl;
        std::cerr << "[part]  - 1 = Remove Romments" << std::endl;
        std::cerr << "[part]  - 2 = Tokenize" << std::endl;
        std::cerr << "[part]  - 3 = CST" << std::endl;
        std::cerr << "[part]  - 4 = Symbol Table" << std::endl;
        return -1;
    }

    std::string part = (argc > 3) ? argv[3] : "0";




    // Part 1 - remove comments
    if (!parseComments(argv[1], argv[2])) return -1;
            
      
 
    // Part 2 - Tokenize
    Token* head = tokenize(argv[2]);
    if (head == nullptr) return -1; 
    if (part == "0" || part == "2") {
        while(head != nullptr) {
            std::cout << *head << std::endl;
            head = head->getNext();
        }
    }    



    // Part 3 - create concrete syntax tree
    CSTNode* cst = recDecParse(head);
    if (cst == nullptr) { return 0;}
    if (part == "0" || part == "3") {
        cst->printChain();
   } 

    
    // part 4 - create symbol table
    STNode* stHead = makeSymbolTable(cst);
    if (stHead == nullptr) { return 0;}
    if (part == "0" || part == "4") {
        stHead->printChain();
    }





    // clean up
    if (part != "0" && part != "1") {
        if (std::remove(argv[2]) != 0) {
            std::cerr << "[!] Failed to delete file: " << argv[2] << std::endl;
        }
    }



    return 0;

}








