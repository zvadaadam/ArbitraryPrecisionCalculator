//
//  Operand.cpp
//  Calculator_infinite_presicion
//
//  Created by Adam Zvada on 20.05.17.
//  Copyright © 2017 Adam Zvada. All rights reserved.
//

#include "Operand.hpp"

bool Operand::operator > (const Operand & b) const {
    if (((integer > b.integer) || (integer == b.integer && floatNum > b.floatNum))) {
        return true;
    }
    return false;
}

bool Operand::operator == (const Operand & b) const {
    if (isNegative != b.isNegative || integer != b.integer || floatNum != b.floatNum) {
        return false;
    }
    return true;
}
