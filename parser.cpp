#include "parser.hpp"
#include "token.hpp"
#include "scanner.hpp"

#include <stdexcept>
#include <vector>
#include <stack>
#include <iostream>
#include <algorithm>

namespace {

    static std::stack<token::Token> _productionStack;
    static token::Token _lookahead;

}

//Prototypes
void program();
void func();
void block();
void vars();
void expr();
void N();
void NPrime();
void A();
void M();
void R();
void stats();
void mStat();
void stat();
void in();
void out();
void ifNonTerminal();
void pick();
void pickbody();
void loop1();
void loop2();
void assign();
void RO();
void label();
void gotoNonTerminal();

void parser::parse() {
    _lookahead = scanner::getNextToken();

    program();

    std::cout << "Okay :)" << std::endl;
    /*try {
        program();
    }
    catch(const std::exception& ex) {
        std::cerr << ex.what() << '\n';
        exit(1);
    }*/
}

//Fetches the next lookahead if the token instance matches the expected value. Exits with an error otherwise
void match(std::string terminalString) {
    if(_lookahead.tokenInstance == terminalString) {
        _lookahead = scanner::getNextToken();
    }
    else {
        std::cerr << "ERROR: Token instance \"" << _lookahead.tokenInstance << "\" at line " << _lookahead.lineNumber 
            << " char " << _lookahead.charNumber << " did not match the expected value of \"" << terminalString << "\"" << std::endl;
        exit(1);
    }
}

//Overloaded match function for checking tokenIds
void match(int tokenId) {
    if(_lookahead.tokenId == tokenId) {
        _lookahead = scanner::getNextToken();
    }
    else {
        std::string tokenIdArray[] = {"idTok", "keyTok", "opTok", "intTok", "EOFTok"};
        std::cerr << "ERROR: The token instance \"" << _lookahead.tokenInstance << "\" of type " << tokenIdArray[_lookahead.tokenId] 
            << " at line " << _lookahead.lineNumber << " char " << _lookahead.charNumber 
            << " did not match the expected value of \"" << tokenIdArray[tokenId] << "\"" << std::endl;
        exit(1);
    }
}

//Takes the string name of a nonterminal returns a vector containing the first set of that nonterminal
std::vector<std::string> first(std::string nonterminal) {
    std::vector<std::string> set;
    if(nonterminal == "stat") {
        set = {"cin", "cout", "{", "if", "while", "repeat", "set", "jump", "label", "pick"};
    }
    if(nonterminal == "block") {
        set = {"{"};
    }
    return set;
}

bool setContainsLookahead(std::vector<std::string> set) {
    if(std::find(set.begin(), set.end(), _lookahead.tokenInstance) != set.end())
        return true;

    return false;
}

//<program> -> <vars> tape <func> <block> | <vars> tape <block>
void program() {
    vars();
    match("tape");

    if(_lookahead.tokenInstance == "func") {
        func();
    }

    block();

    return;
}

//<func> -> func Identifier <block>
void func() {
  match("func");
  block();
  return;
}

//<block> -> { <vars> <stats> }
void block() {
    match("{");
    vars();
    stats();
    match("}");
    return;
}

//<vars> -> empty | create Identifier ; | create Identifier := Integer ; <vars>
void vars() {
    if(_lookahead.tokenInstance == "create") {
        match("create");
        if(_lookahead.tokenId == token::tokenIdList::opTok) {
            match(":=");
            match(token::tokenIdList::intTok);
            match(";");
            vars();
        }
        return;
    }
    else
        return;
}

//<expr> -> <N> - <expr> | <N>
void expr();

//<N> -> <A> <NPrime>
void N();

//<NPrime> -> empty | / <A> <NPrime> | + <A> <NPrime>
void NPrime();

//<A> -> <M> * <A> | <M>
void A();

//<M> -> ^ <M> | <R>
void M();

//<R> -> ( <expr> ) | Identifier | Integer
void R();

//<stats> -> <stat> <mStat>
void stats() {
    stat();
    mStat();
    return;
}

//<mStat> -> empty | <stat> <mStat>
void mStat() {
    std::vector<std::string> firstSet;
    firstSet = first("stat");

    if(setContainsLookahead(firstSet)) {
        stat();
        mStat();
        return;
    }
    else
        return;
}

//<stat> -> <in> ; | <out> ; | <block> | <if> ; | <loop1> ; | <loop2> ; | <assign> ; |
//<goto> ; | <label> ; | <pick> ;
void stat() {
    /*std::vector<std::string> firstSet;
    firstSet = first("block");

    //If the first set of block contains the lookahead token, then...
    if(setContainsLookahead(firstSet)) {
        block();
        return;
    }*/

    std::string token = _lookahead.tokenInstance;

    if(token == "cin") {
        in();
    }
    else if(token == "cout") {
        out();
    }
    else if(token == "if") {
        ifNonTerminal();
    }
    else if(token == "while") {
        loop1();
    }/*
    else if(token == "repeat")
        loop2();
    else if(token == "set")
        assign();
    else if(token == "jump")
        gotoNonTerminal();
    else if(token == "label")
        label();
    else if(token == "pick")
        pick();*/
    
    match(";");
    return;
}

//<in> -> cin Identifier
void in() {
    match("cin");
    return;
}

//<out> -> cout <expr>
void out();

//<if> -> if [ <expr> <RO> <expr> ] then <stat>
void ifNonTerminal();

//<pick> -> pick <expr> <pickbody>
void pick();

//<pickbody> -> <stat> : <stat>
void pickbody();

//<loop1> -> while [ <expr> <RO> <expr> ] <stat>
void loop1();

//<loop2> -> repeat <stat> until [ <expr> <RO> <expr> ]
void loop2();

//<assign> -> set Identifier = <expr> | Identifier = <expr>
void assign();

//<RO> -> < | > | == | ... (three tokens here) | =!=
void RO();

//<label> -> label Identifier
void label();

//<goto> -> jump Identifier
void gotoNonTerminal();