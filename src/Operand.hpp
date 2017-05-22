//
//  Operand.hpp
//  Calculator_infinite_presicion
//
//  Created by Adam Zvada on 20.05.17.
//  Copyright © 2017 Adam Zvada. All rights reserved.
//

#ifndef Operand_hpp
#define Operand_hpp

#include <stdio.h>
#include <iostream>

using namespace std;

/**
 * Helper struct for InfinityNum. Stores number and can tell which one is biger or equal.
 */
struct Operand {
    /**
     * Constructor Operand
     * @param integer string
     * @param floatNum string
     * @param isNegative true if number is negative, default is false
     */
    Operand(string integer, string floatNum, bool isNegative) : integer(integer), floatNum(floatNum), isNegative(isNegative), integerSize(integer.size()), floatSize(floatNum.size()) {}
    
    
    string integer;
    string floatNum;
    bool isNegative;
    int integerSize;
    int floatSize;
    
    /**
     * Overrided operator == can decide wheter two operands are equal.
     * @param b operand 2nd
     * @return bool equals?
     */
    bool operator == (const Operand & b) const;
    /**
     * Overrided operator > can decide whether first operand is bigger the other.
     * @param b operand 2nd
     * @return bool first is bigger the second?
     */
    bool operator > (const Operand & b) const;
};


#endif /* Operand_hpp */
