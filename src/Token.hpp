//
//  Token.hpp
//  Calculator_infinite_presicion
//
//  Created by Adam Zvada on 03.05.17.
//  Copyright © 2017 Adam Zvada. All rights reserved.
//

#ifndef Token_hpp
#define Token_hpp

#include <stdio.h>
#include "SymboleTable.hpp"

using namespace std;

/**
 * Abstract class of Token.
 */
class Token {
public:
    
    /**
     * Destructor
     */
    virtual ~Token() = default;
    
    /**
     * @return string of Token
     */
    virtual string GetString() const = 0;
    
    /**
     * @return SymboleTable::Types get type of token
     */
    virtual SymboleTable::Types GetType() const = 0;
    
    /**
     * Prints the Token
     */
    virtual void Print() const = 0;
private:
};


#endif /* Token_hpp */
