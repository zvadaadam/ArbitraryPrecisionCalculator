//
//  Parser.cpp
//  Calculator_infinite_presicion
//
//  Created by Adam Zvada on 03.05.17.
//  Copyright © 2017 Adam Zvada. All rights reserved.
//

#ifndef Parser_cpp
#define Parser_cpp

#include "Parser.hpp"



const char * ParentesisMismatchException::what( void ) const throw() {
    return "Pareser: Parentesis are unbalanced.";
}

list<shared_ptr<Token>> & Parser::GetExpPostfix() {
    return _output;
}


void Parser::ConvertToPostfix(Lexer & lexer) {
    
    vector<shared_ptr<Token>> tokens = lexer.AllTokens();
    
    for (auto & token : tokens) {
        switch (token->GetType()) {
            case SymboleTable::NUM:
                //_output.push(token);
                _output.push_back(token);
                continue;
            case SymboleTable::PLUS :
                handleOperation(token);
                continue;
            case SymboleTable::MINUS:
                handleOperation(token);
                continue;
            case SymboleTable::UNARY_MINUS:
                handleOperation(token);
                continue;
            case SymboleTable::MULTIPLY:
                handleOperation(token);
                continue;
            case SymboleTable::LPAR:
                _operators.push(token);
                continue;
            case SymboleTable::RPAR:
                if (_operators.empty() || _operators.top()->GetType() == SymboleTable::RPAR) {
                    throw ParentesisMismatchException();
                }
                while (_operators.top()->GetType() != SymboleTable::LPAR) {
                    addToOutputFromStack();
                }
                _operators.pop(); //pop the reminding LPAR
                continue;
            default:
                continue;
        }
    }
    
    //insert all remainder operators from stack to output
    while (!_operators.empty()) {
        if (_operators.top()->GetType() == SymboleTable::LPAR || _operators.top()->GetType() == SymboleTable::RPAR) {
            throw ParentesisMismatchException();
        }
        addToOutputFromStack();
    }
    
}

void Parser::handleOperation(shared_ptr<Token> token) {
    const Operation * operation = static_cast<const Operation*>(token.get());
    if (_operators.empty()) {
        _operators.push(token);
        return;
    }
    
    const Operation * stackOperation = static_cast<const Operation*>(_operators.top().get());
    
    while(operation->GetPrecedence() <= stackOperation->GetPrecedence()) {
        addToOutputFromStack();
        if (_operators.empty()) {
            break;
        }
        stackOperation = static_cast<const Operation*>(_operators.top().get());
    }

    _operators.push(token);
}

void Parser::addToOutputFromStack() {
    //_output.push(_operators.top());
    _output.push_back(_operators.top());
    _operators.pop();
}

#endif /* defined(Parser_cpp) */
