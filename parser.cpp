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


/*
TODO
    * Add in Identifiers wherever the grammars say "Identifier"

*/

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
        std::cout << "ERROR: Token instance \"" << _lookahead.tokenInstance << "\" at line " << _lookahead.lineNumber 
            << " char " << _lookahead.charNumber << " did not match the expected value of \"" << terminalString << "\"" << std::endl;
        throw std::runtime_error("Mismatch Error");
    }
}

//Overloaded match function for checking tokenIds
void match(int tokenId) {
    if(_lookahead.tokenId == tokenId) {
        _lookahead = scanner::getNextToken();
    }
    else {
        std::string tokenIdArray[] = {"idTok", "keyTok", "opTok", "intTok", "EOFTok"};
        std::cout << "ERROR: The token instance \"" << _lookahead.tokenInstance << "\" of type " << tokenIdArray[_lookahead.tokenId] 
            << " at line " << _lookahead.lineNumber << " char " << _lookahead.charNumber 
            << " did not match the expected value of \"" << tokenIdArray[tokenId] << "\"" << std::endl;
        throw std::runtime_error("Mismatch Error");
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
    
    try {
        match("tape");
    }
    catch(const std::exception& ex) {
        std::cerr << ex.what() << " inside of nonterminal \"program\"" << std::endl;
        exit(1);
    }

    if(_lookahead.tokenInstance == "func") {
        func();
    }

    block();

    return;
}

//<func> -> func Identifier <block>
void func() {
    try {
        match("func");
        match(token::tokenIdList::idTok);
    }
    catch(const std::exception& ex) {
        std::cerr << ex.what() << " inside of nonterminal \"func\"" << std::endl;
        exit(1);
    }
    block();
    return;
}

//<block> -> { <vars> <stats> }
void block() {
    try {
        match("{");
        vars();
        stats();
        match("}");
    }
    catch(const std::exception& ex) {
        std::cerr << ex.what() << " inside of nonterminal \"block\"" << std::endl;
        exit(1);
    }
    return;
}

//<vars> -> empty | create Identifier ; | create Identifier := Integer ; <vars>
void vars() {
    try {
        if(_lookahead.tokenInstance == "create") {
            match("create");
            match(token::idTok);
            if(_lookahead.tokenInstance == ":=") {
                match(":=");
                match(token::tokenIdList::intTok);
                match(";");
                vars();
            }
            else 
                match(";");
            return;
        }
        else
            return;
    }
    catch(const std::exception& ex) {
        std::cerr << ex.what() << " inside of nonterminal \"vars\"" << std::endl;
        exit(1);
    }
}

//<expr> -> <N> - <expr> | <N>
void expr() {
    N();

    if(_lookahead.tokenInstance == "-") {
        try {
            match("-");
        }
        catch(const std::exception& ex) {
            std::cerr << ex.what() << " inside of nonterminal \"expr\"" << std::endl;
            exit(1);
        }
        expr();
    }
    
    return;
}

//<N> -> <A> <NPrime>
void N() {
    A();
    NPrime();
}

//<NPrime> -> empty | / <A> <NPrime> | + <A> <NPrime>
void NPrime() {
    try {
        if(_lookahead.tokenInstance == "/") {
            match("/");
            A();
            NPrime();
            return;
        }
        else if(_lookahead.tokenInstance == "+") {
            match("+");
            A();
            NPrime();
            return;
        }
        else
            return;
    }
    catch(const std::exception& ex) {
        std::cerr << ex.what() << " inside of nonterminal \"NPrime\"" << std::endl;
        exit(1);
    }
}

//<A> -> <M> * <A> | <M>
void A() {
    M();

    if(_lookahead.tokenInstance == "*") {
        try {
            match("*");
        }
        catch(const std::exception& ex) {
            std::cerr << ex.what() << " inside of nonterminal \"A\"" << std::endl;
            exit(1);
        }
        A();
    }

    return;
}

//<M> -> ^ <M> | <R>
void M() {
    if(_lookahead.tokenInstance == "^") {
        try {
            match("^");
        }
        catch(const std::exception& ex) {
            std::cerr << ex.what() << " inside of nonterminal \"M\"" << std::endl;
            exit(1);
        }
        M();
        return;
    }

    R();
    return;
}

//<R> -> ( <expr> ) | Identifier | Integer
void R() {
    try{
        if(_lookahead.tokenInstance == "(") {
            match("(");
            expr();
            match(")");
            return;
        }
        else if(_lookahead.tokenId == token::tokenIdList::idTok) {
            match(token::tokenIdList::idTok);
            return;
        }
        else if(_lookahead.tokenId == token::tokenIdList::intTok) {
            match(token::tokenIdList::intTok);
            return;
        }
        else {
            std::cerr << "Error in nonterminal R: symbol " << _lookahead.tokenInstance << "\" did not match allowed symbols."
                << "Allowed symbols are: \"(\", identifiers, and integers." << std::endl;
            exit(1);
        }
    }
    catch(const std::exception& ex) {
        std::cerr << ex.what() << " inside of nonterminal \"R\"" << std::endl;
        exit(1);
    }
}

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
    std::vector<std::string> firstSet;
    firstSet = first("block");

    //If the first set of block contains the lookahead token, then...
    if(setContainsLookahead(firstSet)) {
        block();
        return;
    }

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
    }
    else if(token == "repeat")
        loop2();
    else if(token == "set")
        assign();
    else if(token == "jump")
        gotoNonTerminal();
    else if(token == "label")
        label();
    else if(token == "pick")
        pick();
    
    match(";");
    return;
}

//<in> -> cin Identifier
void in() {
    try {
        match("cin");
        match(token::idTok);
    }
    catch(const std::exception& ex) {
        std::cerr << ex.what() << " inside of nonterminal \"in\"" << std::endl;
        exit(1);
    }
    return;
}

//<out> -> cout <expr>
void out() {
    try {
        match("cout");
    }
    catch(const std::exception& ex) {
        std::cerr << ex.what() << " inside of nonterminal \"out\"" << std::endl;
        exit(1);
    }
    expr();
    return;
}

//<if> -> if [ <expr> <RO> <expr> ] then <stat>
void ifNonTerminal() {
    try {
        match("if");
        match("[");
        expr();
        RO();
        expr();
        match("]");
        match("then");
        stat();
    }
    catch(const std::exception& ex) {
        std::cerr << ex.what() << " inside of nonterminal \"ifNonTerminal\"" << std::endl;
        exit(1);
    }
    return;
}

//<pick> -> pick <expr> <pickbody>
void pick() {
    try {
        match("pick");
    }
    catch(const std::exception& ex) {
        std::cerr << ex.what() << " inside of nonterminal \"pick\"" << std::endl;
        exit(1);
    }

    expr();
    pickbody();
}

//<pickbody> -> <stat> : <stat>
void pickbody() {
    stat();

    try {
        match(":");
    }
    catch(const std::exception& ex) {
        std::cerr << ex.what() << " inside of nonterminal \"pickbody\"" << std::endl;
        exit(1);
    }

    stat();
}

//<loop1> -> while [ <expr> <RO> <expr> ] <stat>
void loop1() {
    try {
        match("while");
        match("[");
        expr();
        RO();
        expr();
        match("]");
        stat();
    }
    catch(const std::exception& ex) {
        std::cerr << ex.what() << " inside of nonterminal \"loop1\"" << std::endl;
        exit(1);
    }
    return;
}

//<loop2> -> repeat <stat> until [ <expr> <RO> <expr> ]
void loop2() {
    try{
        match("repeat");
        stat();
        match("until");
        match("[");
        expr();
        RO();
        expr();
        match("]");
    }
    catch(const std::exception& ex) {
        std::cerr << ex.what() << " inside of nonterminal \"loop2\"" << std::endl;
        exit(1);
    }
}

//<assign> -> set Identifier = <expr> | Identifier = <expr>
void assign() {
        try {
            if(_lookahead.tokenInstance == "set") {
                match("set");
            }
            match(token::idTok);
            match("=");
            expr();
        }
        catch(const std::exception& ex) {
            std::cerr << ex.what() << " inside of nonterminal \"assign\"" << std::endl;
            exit(1);
        }   
}

//<RO> -> < | > | == | ... (three tokens here) | =!=
void RO() {
    try {
        if(_lookahead.tokenInstance == "<") {
            match("<");
            return;
        }
        else if(_lookahead.tokenInstance == ">") {
            match(">");
            return;
        }
        else if(_lookahead.tokenInstance == ".") {
            match(".");
            match(".");
            match(".");
            return;
        }
        else if(_lookahead.tokenInstance == "==") {
            match("==");
            return;
        }
        else if(_lookahead.tokenInstance == "=!=") {
            match("=!=");
            return;
        }
        else {
            std::cerr << "Error in RO nonterminal: could not find matching symbol for \"" << _lookahead.tokenInstance << "\"" << std::endl;
            exit(1);
        }
    }
    catch(const std::exception& ex) {
        std::cerr << ex.what() << " inside of nonterminal \"RO\"" << std::endl;
        exit(1);
    }
}

//<label> -> label Identifier
void label() {
    try {
        match("label");
        match(token::idTok);
    }
    catch(const std::exception& ex) {
        std::cerr << ex.what() << " inside of nonterminal \"label\"" << std::endl;
        exit(1);
    }
}

//<goto> -> jump Identifier
void gotoNonTerminal() {
    try {
        match("jump");
        match(token::idTok);
    }
    catch(const std::exception& ex) {
        std::cerr << ex.what() << " inside of nonterminal \"gotoNonTerminal\"" << std::endl;
        exit(1);
    }
}