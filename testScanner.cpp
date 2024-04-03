#include "testScanner.hpp"
#include "scanner.hpp"
#include "token.hpp"

#include <iostream>
#include <stack>
#include <fstream>
#include <deque>

namespace {

    static std::deque<token::Token> _tokenList;
    static token::Token _lastToken;

}

//Opens a stream to the file, begins collecting tokens from scanner
void testScanner::start(std::string fileName) {
    _lastToken.tokenId = token::tokenIdList::idTok;

    //std::string line;
    //std:getline(inputStream, line);
    std::string tokenString;
    try {
        scanner::startStream(fileName);
    } catch(const std::exception& ex) {
        std::cerr << ex.what() << '\n';
        exit(1);
    }

    while(_lastToken.tokenId != token::EOFTok) {
        _tokenList.push_back(scanner::getNextToken());
        _lastToken = _tokenList.back();
    }
} 

//Translates tokenIds to string and prints tokens to screen
void testScanner::print() {
    std::deque<token::Token>::iterator it;
    std::string tokenIdArray[] = {"idTok", "keyTok", "opTok", "intTok", "EOFTok"};

    for(it = _tokenList.begin(); it != _tokenList.end(); it++) {
        if((*it).tokenInstance == "" && (*it).tokenId == -1)
            continue; 
        std::cout << "{ " << tokenIdArray[(*it).tokenId] << ", " << (*it).tokenInstance << ", " << (*it).lineNumber << "." << (*it).charNumber << " }" << std::endl;
    }
}