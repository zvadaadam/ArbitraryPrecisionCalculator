//
//  Calculation.hpp
//  Calculator_infinite_presicion
//
//  Created by Adam Zvada on 09.05.17.
//  Copyright © 2017 Adam Zvada. All rights reserved.
//

#ifndef Calculation_hpp
#define Calculation_hpp

#include <stdio.h>
#include <iostream>
#include <list>
#include <memory>
#include <string>

#include "Token.hpp"
#include "Operation.hpp"
#include "Number.hpp"

using namespace std;

class CalculationException : public exception {
public:
    const char * what() const throw() {
        return "Calculation error";
    }
};


/**
 * Calculation gets postfix form of arithmetic expression and calculates its solution string number.
 *
 */
class Calculation {
public:
    /**
     * Constructor for Calculation
     * @param postfixExp List of pointers to Token which stores the postfix form of arithmetic expression
     */
    Calculation(const list<shared_ptr<Token>> & postfixExp) : _postfixExp(postfixExp) {}
    
    /**
     * Removing from the postfix list a instering there calculated subexpressions
     * @return string solution number of given expression
     */
    string Calculate();
    
    /**
     * Prints the contant of postfix expression
     */
    void Print() const;
private:
    /**
     * Storage for postfix expression
     */
    list<shared_ptr<Token>> _postfixExp;
    
    /**
     * Removes number from storage 
     * @throw NotNumberException
     */
    Number removeNumber(list<shared_ptr<Token>>::iterator & it);
};

#endif /* Calculation_hpp */
