//
//  Parser.hpp
//  Calculator_infinite_presicion
//
//  Created by Adam Zvada on 03.05.17.
//  Copyright © 2017 Adam Zvada. All rights reserved.
//

#ifndef Parser_hpp
#define Parser_hpp

#include <stack>
#include <queue>
#include <list>
#include <memory>

#include "Lexer.hpp"
#include "Operation.hpp"

/**
 * Exception of parentesis mismacth
 */
class ParentesisMismatchException: public exception {
public:
    const char * what() const throw();
};

/**
 * Parser gets tokens from Lexer. 
 * Main goal of Parser is to convert given tokens from familiary infix artihmetic for 
 * to postfix arithmetic form using Shunting-yard algorithm.
 * We get from Parser the postfix from which is just post-order of AST.
 */
class Parser {
public:
    
    /**
     * Takes all Tokens from Lexer and perfrom conversion from infix to postfix from. Update output property of Praser.
     * @param lexer instance of lexer with given input
     */
    void ConvertToPostfix(Lexer & lexer);
    
    /**
     * Get Postfix expression of ouput property.
     * @return list<shared_ptr<Token>> stores postfix expression of given lexer's input.
     */
    list<shared_ptr<Token>> & GetExpPostfix();
private:
    
    /**
     *  Stack as placeholder for operators.
     */
    stack<shared_ptr<Token>> _operators;
    /**
     *  Stores the postfix arithmetic experssion from lexer's input.
     */
    list<shared_ptr<Token>> _output;
    
    /**
     * Handling operation in shunting-yard way. Getting moved from stack to output list if precedence is in favor.
     */
    void handleOperation(shared_ptr<Token> token);
    
    /**
     * Move Token from Stack to ouput list.
     */
    void addToOutputFromStack();
};

#endif /* defined(Parser_hpp) */
