//
//  Number.cpp
//  Calculator_infinite_presicion
//
//  Created by Adam Zvada on 08.05.17.
//  Copyright © 2017 Adam Zvada. All rights reserved.
//

#include "Number.hpp"

string Number::GetString() const {
    return _integer + ((_float == "") ? "" : "." + _float);
}

string Number::GetInteger() const {
    return _integer;
}

string Number::GetFloat() const {
    return _float;
}

void Number::ChangeSign() {
    _isNegative = !_isNegative;
}

bool Number::IsNegative() const {
    return _isNegative;
}

SymboleTable::Types Number::GetType() const {
    return SymboleTable::NUM;
}

void Number::Print() const {
    cout << _number << endl;
}


Number Number::operator + (const Number & b) const {
    
    InfinityNum left(b.GetInteger(), b.GetFloat(), b.IsNegative());
    InfinityNum right(GetInteger(), GetFloat(), IsNegative());
    
    InfinityNum solution = left + right;
    
    return Number(solution.GetInteger(), solution.GetFloat(), solution.IsNegative());
}


Number Number::operator - (const Number & b) const {
    InfinityNum left(b.GetInteger(), b.GetFloat(), b.IsNegative());
    InfinityNum right(GetInteger(), GetFloat(), IsNegative());
    
    InfinityNum solution = left - right;
    
    return Number(solution.GetInteger(), solution.GetFloat(), solution.IsNegative());

}

Number Number::operator * (const Number & b) const {
    InfinityNum left(b.GetInteger(), b.GetFloat(), b.IsNegative());
    InfinityNum right(GetInteger(), GetFloat(), IsNegative());
    
    InfinityNum solution = left * right;
    
    return Number(solution.GetInteger(), solution.GetFloat(), solution.IsNegative());
    
}



