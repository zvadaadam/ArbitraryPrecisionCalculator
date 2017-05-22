//
//  Operation.hpp
//  Calculator_infinite_presicion
//
//  Created by Adam Zvada on 07.05.17.
//  Copyright © 2017 Adam Zvada. All rights reserved.
//

#ifndef Operation_hpp
#define Operation_hpp

#include <stdio.h>
#include <iostream>
#include "Token.hpp"
#include "Number.hpp"
#include "SymboleTable.hpp"

using namespace std;

/**
 * Exception for unknown operation
 */
class NotSupportedOperationException : public exception {
public:
    const char * what() const throw() {
        return "Operation is not supported or application does not make sence.";
    }

};

/**
 * Operation extending from abstract Token. Holds operation and precedence from arithmetic expression.
 */
class Operation : public Token {
public:
    
    /**
     *  Constructor initilize type of operation and precendence
     * @param type Type of operation
     */
    Operation(SymboleTable::Types type) : _type(type), _operaction(type)  { setPrecedence(type); }
    
    /**
     *  Prints character of operation
     */
    virtual void Print() const;
    
    /**
     * @return SymboleTable::Types of operation
     */
    virtual SymboleTable::Types GetType() const;
    
    /**
     * @return string of operation
     */
    virtual string GetString() const;
    
    /**
     * @return value of precedence
     */
    int GetPrecedence() const;
    
    /**
     * @return Number of applied operation on given numbers
     * @param a number left operand
     * @param b number right operand
     # @throw NotSupportedOperationException if the operation is not supported or does not make sence
     */
    Number ApplyOperation(const Number & a, const Number & b);
private:
    /**
     *  type of operation
     */
    SymboleTable::Types _type;
    /**
     * operation in char
     */
    char _operaction;
    /**
     * precedence of this operation
     */
    int _precedence;
    
    /**
     * sets precedence for given operation
     * @param type of operation
     */
    void setPrecedence(SymboleTable::Types type);
};

#endif /* Operation_hpp */
