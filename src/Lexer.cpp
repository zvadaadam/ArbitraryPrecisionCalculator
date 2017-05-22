//
//  Lexer.cpp
//  Calculator_infinite_presicion
//
//  Created by Adam Zvada on 03.05.17.
//  Copyright © 2017 Adam Zvada. All rights reserved.
//

#ifndef Lexer_hpp
#define Lexer_hpp

#include "Lexer.hpp"


const char * LexerException::what( void ) const throw() {
    return "Lexer: Character not supported.";
}


shared_ptr<Token> Lexer::NextToken() {
    
    readCharacter();
    
    while (_inputCategorie == WHITESPACE) {
        readCharacter();
    }
    
    switch (_inputCategorie) {
        case NUMBER : {
            string integer = "";
            string floatNum = "";
            bool isFloat = false;
            
            while (_inputCategorie == NUMBER) {
                if (!isFloat) {
                    integer += _character;
                    readCharacter();
                } else {
                    floatNum += _character;
                    readCharacter();
                }
                if (_character == SymboleTable::DOT) {
                    if (isFloat) {
                        throw LexerException();
                    }
                    isFloat = true;
                    readCharacter();
                }
            }
            
            if (integer.empty()) {
                integer = "0";
            }
            if (floatNum.empty()) {
                floatNum = "0";
            }
            
            _index--;
            
            return make_shared<Number>(Number(integer, floatNum));
        }
        case OPERATION:
            
            switch (_character) {
                case SymboleTable::PLUS :
                    return make_shared<Operation>(Operation(SymboleTable::PLUS));
                case SymboleTable::MINUS : //Improve, whitespaces before unanry_minus
                    if (_index == 1) {
                        return make_shared<Operation>(Operation(SymboleTable::UNARY_MINUS));
                    }
                    _index -= 2;
                    readCharacter();
                    if (_character == SymboleTable::LPAR) {
                        _index++;
                        return make_shared<Operation>(Operation(SymboleTable::UNARY_MINUS));
                    } else {
                        _index++;
                    }
                    return make_shared<Operation>(Operation(SymboleTable::MINUS));
                case SymboleTable::MULTIPLY :
                    return make_shared<Operation>(Operation(SymboleTable::MULTIPLY));
                case SymboleTable::LPAR :
                    return make_shared<Operation>(Operation(SymboleTable::LPAR));
                case SymboleTable::RPAR :
                    return make_shared<Operation>(Operation(SymboleTable::RPAR));
                default:
                    throw SymboleTableException();
            }
            break;
        case END:
            return make_shared<Operation>(Operation(SymboleTable::END));
            //return new Operation(SymboleTable::END);
            break;
        default:
            break;
    }
    
    throw LexerException();
}

void Lexer::readCharacter() {
    
    _character = _input[_index];
    
    if (isdigit(_character)) {
        _inputCategorie = NUMBER;
    } else if (isspace(_character)) {
        _inputCategorie = WHITESPACE;
    } else if (_character == '\0') {
        _inputCategorie = END;
    } else {
        _inputCategorie = OPERATION;
    }
    
    _index++;
}

vector<shared_ptr<Token>> Lexer::AllTokens() {
    _index = 0;
    vector<shared_ptr<Token>> tokens;
    do {
        tokens.push_back(NextToken());
    } while (tokens[tokens.size()-1]->GetType() != SymboleTable::END);

    return tokens;
}

#endif /* Lexer_hpp */


