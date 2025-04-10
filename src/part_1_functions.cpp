
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <unistd.h>


#include "Token.h"

#include "part_1_functions.h"







/*
*    takes an input c-style file and removes all comments replacing them with blank space
*/
bool parseComments(char* inFileName, char* outFileName) {

    enum States {PROGRAM, F_SLASH, LINE_COMMENT, BLOCK_COMMENT, B_SLASH, ASTERISK, UN_TERMINATED, QUOTE, ESCAPE};

    //- initilize and check files
    std::ifstream inFile(inFileName);
    std::ofstream outFile(outFileName);
    if (!inFile) {
        std::cerr << "Unable to open: " << inFileName << std::endl;
        return false;
    } else if (!outFile) {
        std::cerr << "Unable to open: " << outFileName << std::endl;
        return false;
    }


    int currLine = 1;
    int comStartLine = 0;
    char ch = 0;
    int buffLimit = 4096;      
    States currState = PROGRAM;
    std::ostringstream buffer;

    //- retrive input char by char from file
    while (inFile.get(ch)) {



        switch (currState) {

        //- normal non-comment code
        case PROGRAM: // S/0
            switch (ch) {
            case '/':
                currState = F_SLASH;
                break;
            case '*':
                currState = ASTERISK;
                buffer << ch;
                break;
            case '\n':
                currLine += 1;
                buffer << ch;
                break;
            case '"':
                currState = QUOTE;
                buffer << ch;
                break;
            default:
                currState = PROGRAM;
                buffer << ch;
                break;
            }
            break;


        //- possibly start of line comment
        case F_SLASH:   //1
            switch(ch) {
            case '/':
                currState = LINE_COMMENT;
                comStartLine = currLine;
                buffer << "  ";
                break;
            case '*':
                currState = BLOCK_COMMENT;
                comStartLine = currLine;
                buffer << "  ";
                break;
            case '\n':
                currLine += 1;
                buffer << ch;
                break;
            default:
                currState = PROGRAM;
                buffer << '/';
                buffer << ch;
                break;
            }
            break;


        //- line comment
        case LINE_COMMENT: //2
            switch(ch) {
            case '\n':
                currLine += 1;
                currState = PROGRAM;
                buffer << '\n';
                break;
            default:
                buffer << ' ';
                break;
            }
            break;


        //- block comment
        case BLOCK_COMMENT: //3
            switch(ch) {
            case '*':
                currState = B_SLASH;
                buffer << ' ';
                break;
            case '\n':
                currLine += 1;
                currState = B_SLASH;
                buffer << '\n';
                break;
            default:
                currState = BLOCK_COMMENT;
                buffer << ' ';
                break;
            }
            break;


        //- possibly end of block comment
        case B_SLASH: //4
            switch(ch) {
            case '*':
                currState = B_SLASH;
                buffer << ' ';
                break;
            case '/':
                currState = PROGRAM;
                buffer << ' ';
                break;
            case '\n':
                currLine += 1;
                currState = B_SLASH;
                buffer << '\n';
                break;
            default:
                currState = BLOCK_COMMENT;
                buffer << ' ';
                break;
            }
            break;


        //- possibly end of block comment with no start
        case ASTERISK: //5
            switch(ch) {
            case '/':
                currState = UN_TERMINATED;
                break;
            case '\n':
                currLine += 1;
                buffer << '\n';
                break;
            default:
                currState = PROGRAM;
                buffer << ch;
                break;
            }
            break;


        //- end of block comment with no start    '*/'
        case UN_TERMINATED: //6
            std::cerr << "[-] Error: Program contains C-style, unterminated comment on line " << currLine << std::endl;
            return false;
        



        //- start of quote
        case QUOTE: //7
            switch(ch) {
            case '\\':
                currState = ESCAPE;
                buffer << '\\';
                break;
            case '\n':
                currLine += 1;
                buffer << '\n';
                break;
            case '"':
                currState = PROGRAM;
                buffer << ch;
                break;
            default:
                currState = QUOTE;
                buffer << ch;
                break;
            }
            break;

        //- possibly start of escaped charactor
        case ESCAPE: //8
            switch(ch) {
            case '\\':
                currState = ESCAPE;
                buffer << '\\';
                break;
            case '\n':
                currLine += 1;
                buffer << '\n';
                break;
            default:
                currState = QUOTE;
                buffer << ch;
                break;
            }
            break;



        //- unexpected unacounted for input
        default:
            std::cerr << "Syntax Error on line: " << currLine << std::endl;
            break;

        }

        //- check buffer size and ouput and clar it if exceeds limit
        if (buffer.tellp() >= buffLimit) {  
            outFile << buffer.str();  
            buffer.str("");           
            buffer.clear();         
        }

    }

    if (currState == BLOCK_COMMENT || currState == B_SLASH) {
        std::cerr << "[-] Error: Program contains C-style, unterminated comment on line " << comStartLine << std::endl;
        inFile.close();
        outFile.close();
        return false;
    }





    //- final write to file and close
    outFile << buffer.str();
    inFile.close();
    outFile.close();
    return true;

}







