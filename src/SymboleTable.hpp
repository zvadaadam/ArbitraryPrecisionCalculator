//
//  TokenType.hpp
//  Calculator_infinite_presicion
//
//  Created by Adam Zvada on 07.05.17.
//  Copyright © 2017 Adam Zvada. All rights reserved.
//

#ifndef TokenType_hpp
#define TokenType_hpp

#include <stdio.h>
#include <map>

using namespace std;

/**
 * 
 */
class SymboleTableException: public exception {
public:
    const char * what( void ) const noexcept {
        return "SymboleTable: Symbole type is not supported.";
    }
};

/**
 * SymboleTable represents all possible symbol which can be parsed
 */
class SymboleTable {
public:
    /**
     * Enum of all possible symbols
     */
    enum Types {NUM = 'n', PLUS = '+', MINUS = '-', UNARY_MINUS = '!', MULTIPLY = '*', LPAR = '(', RPAR = ')', DOT = '.', END = '\0'};
};

#endif /* TokenType_hpp */
