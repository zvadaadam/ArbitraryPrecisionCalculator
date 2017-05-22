//
//  Number.hpp
//  Calculator_infinite_presicion
//
//  Created by Adam Zvada on 08.05.17.
//  Copyright © 2017 Adam Zvada. All rights reserved.
//

#ifndef Number_hpp
#define Number_hpp

#include <stdio.h>
#include <iostream>
#include "Token.hpp"

#include "InfinityNum.hpp"

using namespace std;

/**
 * Number is extending from abstract Token. Stores number either integer or float with sign.
 */
class Number : public Token {
public:
    /**
     * Constructor Number
     * @param num integer string
     * @param isNegative true if number is negative, default is false
     */
    Number(const string & num, bool isNegative = false) : _number(num), _integer(num),_float("0"), _isNegative(isNegative) {}
    
    /**
     * Constructor Number
     * @param integer string
     * @param floatNum string
     * @param isNegative true if number is negative, default is false
     */
    Number(const string integer, const string floatNum, bool isNegative = false) : _integer(integer), _float(floatNum), _isNegative(isNegative) {}
    
    /**
     * @return string number
     */
    virtual string GetString() const;
    
    /**
     * @return string integer part
     */
    string GetInteger() const;
    
    /**
     * @return string float part
     */
    string GetFloat() const;
    
    /**
     * Inverse the sign of number
     */
    void ChangeSign();
    
    /**
     * @return bool true if is negative sign
     */
    bool IsNegative() const;
    
    /**
     * @return SymboleTable::Types number type
     */
    virtual SymboleTable::Types GetType() const;
    
    /**
     * Prints the number
     */
    virtual void Print() const;
    
    /**
     * Overriden operator + for numbers
     * @param b Number for addition
     * @return Number solution addition with parameter number
     */
    Number operator + (const Number & b) const;
    
    /**
     * Overriden operator - for numbers
     * @param b Number for substraction
     * @return Number solution substraction with parameter number
     */

    Number operator - (const Number & b) const;
    
    /**
     * Overriden operator * for numbers
     * @param b Number for multiplication
     * @return Number solution multiplication with parameter number
     */

    Number operator * (const Number & b) const;
private:
    /**
     * Number is deprecated
     */
    string _number;
    
    /**
     * Stores the integer part of number
     */
    string _integer;
    /**
     * Stores the floating part of number
     */
    string _float;
    
    /**
     * Flag if number is negative
     */
    bool _isNegative;
    
};

#endif /* Number_hpp */
