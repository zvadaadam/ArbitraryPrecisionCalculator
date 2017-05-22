//
//  Lexer.hpp
//  Calculator_infinite_presicion
//
//  Created by Adam Zvada on 03.05.17.
//  Copyright © 2017 Adam Zvada. All rights reserved.
//

#ifndef Lexer_cpp
#define Lexer_cpp

#include <stdio.h>
#include <iostream>
#include <istream>
#include <memory>
#include <vector>

#include "Operation.hpp"
#include "SymboleTable.hpp"

#include "Token.hpp"
#include "Number.hpp"

using namespace std;

/**
 * Exeception of Lexer
 */
class LexerException: public exception {
public:
    const char * what() const throw();
};


/**
 * Lexical analyzer for arithmetic expression, which tokenize symbols such as {+,-,*,(,)} and numbers.
 */
class Lexer {
public:
    /**
     * Constructor for Lexer
     * @param input string of arithmetic expression
     */
    Lexer(string & input) : _input(input), _index(0) {}
    
    /**
     * Procces next token of given input
     * @return shared_ptr<Token> which contains upcoming Token
     */
    shared_ptr<Token> NextToken();
    
    /**
     * Gets all Tokens of given input
     * @return vector<shared_ptr<Token>> which contains all Tokens of given input
     */
    vector<shared_ptr<Token>> AllTokens();
    
private:
    /**
     * Holds given input
     */
    string _input;
    /**
     * Index of input for Lexan to keep track which token is coming next
     */
    unsigned int _index;
    /**
     * Current character from input at given index for FSM
     */
    char _character;
    
    /**
     * Character can be distributed to given categories. Stores the current category for character of given index.
     */
    enum { NUMBER, END, WHITESPACE, OPERATION } _inputCategorie;
    
    /**
     * Reads input at given index and updating character and inputCategory.
     */
    void readCharacter();                                       
};


#endif /* Lexer_cpp */
