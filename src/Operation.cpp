//
//  Operation.cpp
//  Calculator_infinite_presicion
//
//  Created by Adam Zvada on 07.05.17.
//  Copyright © 2017 Adam Zvada. All rights reserved.
//

#include "Operation.hpp"

#define SUPER_LOW   0
#define LOW         1
#define HIGER       2
#define SUPER_HIGH  3

void Operation::Print() const {
    cout << _operaction << endl;
}

SymboleTable::Types Operation::GetType() const {
    return _type;
}

string Operation::GetString() const {
    return string(1, _operaction);
}

int Operation::GetPrecedence() const {
    return _precedence;
}

Number Operation::ApplyOperation(const Number & a, const Number & b) {
    
    switch (GetType()) {
        case SymboleTable::PLUS:
            return a + b;
        case SymboleTable::MINUS:
            return a - b;
        case SymboleTable::MULTIPLY:
            return a * b;
        default:
            throw ;
    }
}

void Operation::setPrecedence(SymboleTable::Types type) {
    switch (type) {
        case SymboleTable::PLUS:
            _precedence = LOW;
            break;
        case SymboleTable::MINUS:
            _precedence = LOW;
            break;
        case SymboleTable::UNARY_MINUS:
            _precedence = LOW;
            break;
        case SymboleTable::MULTIPLY:
            _precedence = HIGER;
            break;
        case SymboleTable::LPAR:
            _precedence = SUPER_LOW;
            break;
        case SymboleTable::RPAR:
            _precedence = SUPER_HIGH;
            break;
        default:
            break;
    }
}
