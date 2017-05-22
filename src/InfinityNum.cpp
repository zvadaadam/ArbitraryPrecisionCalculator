//
//  InfinityNum.cpp
//  Calculator_infinite_presicion
//
//  Created by Adam Zvada on 16.05.17.
//  Copyright © 2017 Adam Zvada. All rights reserved.
//

#include "InfinityNum.hpp"

string InfinityNum::GetNum() const {
    string r = (!IsNegative()) ? "" : "-";
    r += _integer;
    return (_float == "") ? r  : r + "." + _float;
}

InfinityNum InfinityNum::operator + (const InfinityNum & b) const {
    
    Operand left(GetInteger(), GetFloat(), IsNegative());
    Operand right(b.GetInteger(), b.GetFloat(), b.IsNegative());
    
    allignStrings(left, right);
    
    return sumStr(left, right);
}

InfinityNum InfinityNum::operator - (const InfinityNum & b) const {
    
    Operand left(GetInteger(), GetFloat(), IsNegative());
    Operand right(b.GetInteger(), b.GetFloat(), b.IsNegative());
    
    allignStrings(left, right);
    
    return subtractStr(left, right);
}

InfinityNum InfinityNum::operator * (const InfinityNum & b) const {
    
    Operand left(GetInteger(), GetFloat(), IsNegative());
    Operand right(b.GetInteger(), b.GetFloat(), b.IsNegative());
    
    allignStrings(left, right);
    pair<string, string> sum = {"", ""};
    if (GetInteger().size() >= b.GetInteger().size()) {
        sum = multiplyStr(left.integer, left.floatNum, right.integer, right.floatNum);
    } else {
        sum = multiplyStr(right.integer, right.floatNum, left.integer, left.floatNum);
    }
    
    trimZerosBack(sum.second);
    trimZerosFront(sum.first);
    
    return InfinityNum(sum.first, sum.second, (IsNegative() == b.IsNegative() ? false : true));
}

InfinityNum InfinityNum::sumStr(const Operand & left, const Operand & right) const {
    int carry = 0;
    string floatNum = "";
    string integer = "";
    
    bool isSolutionNegative = left > right ? left.isNegative : right.isNegative;
    
    if ((left.isNegative && !right.isNegative) || (!left.isNegative && right.isNegative)) { // - (+) + || + (+) -
        if (right.integer < left.integer || (right.integer == left.integer && (right.floatNum < left.floatNum))) {
            floatNum = subtract(left.floatNum, right.floatNum, carry, true);
            integer = subtract(left.integer, right.integer, carry, false);
        } else {
            floatNum = subtract(right.floatNum, left.floatNum, carry, true);
            integer = subtract(right.integer, left.integer, carry, false);
        }
    } else {
        floatNum = sum(left.floatNum, right.floatNum, carry, true);
        integer = sum(left.integer, right.integer, carry, false);
    }
    
    trimZerosBack(floatNum);
    trimZerosFront(integer);
    
    return InfinityNum(integer, floatNum, isSolutionNegative);
}

InfinityNum InfinityNum::subtractStr(const Operand & left, const Operand & right) const {
    
    int carry = 0;
    string floatNum = "";
    string integer = "";
    
    bool rightNegative = right.isNegative;
    
    if (left.isNegative && right.isNegative) { // - (-) - = - +
        rightNegative = false;
        if (right.integer < left.integer || (right.integer == left.integer && (right.floatNum < left.floatNum))) {
            floatNum = subtract(left.floatNum, right.floatNum, carry, true);
            integer = subtract(left.integer, right.integer, carry, false);
        } else {
            floatNum = subtract(right.floatNum, left.floatNum, carry, true);
            integer = subtract(right.integer, left.integer, carry, false);
        }
    } else if (!left.isNegative && !right.isNegative) { // + (-) + = + -
        rightNegative = true;
        if (right.integer < left.integer || (right.integer == left.integer && (right.floatNum < left.floatNum))) {
            floatNum = subtract(left.floatNum, right.floatNum, carry, true);
            integer = subtract(left.integer, right.integer, carry, false);
        } else {
            floatNum = subtract(right.floatNum, left.floatNum, carry, true);
            integer = subtract(right.integer, left.integer, carry, false);
        }
    } else if (left.isNegative && !right.isNegative) { // - (-) + = - -
        rightNegative = true;
        floatNum = sum(left.floatNum, right.floatNum, carry, true);
        integer = sum(left.integer, right.integer, carry, false);
    } else if (!left.isNegative && right.isNegative) { // + (-) - = + +
        rightNegative = false;
        floatNum = sum(left.floatNum, right.floatNum, carry, true);
        integer = sum(left.integer, right.integer, carry, false);
    }
    
    trimZerosFront(integer);
    trimZerosBack(floatNum);
    
    bool isSolutionNegative = left > right ? left.isNegative : rightNegative;
    
    if (integer == "0" && floatNum == "") {
        isSolutionNegative = false;
    }
    
    return InfinityNum(integer, floatNum, isSolutionNegative);
}

pair<string, string> InfinityNum::multiplyStr(string & leftInteger, string & leftFloat, string & rightInteger, string & rightFloat) const {
    
    string solution = "";
    
    string leftNum = leftInteger + leftFloat;
    string rightNum = rightInteger + rightFloat;
    
    for (int i = leftNum.length() - 1; i >= 0; i--) {
        string num = multiplyByDigit(leftNum, rightNum[i], leftNum.size() - 1 - i);
        
        int maxNumSize = max(solution.size(), num.size());
        solution = fillPadding(solution, maxNumSize, false);
        num = fillPadding(num, maxNumSize, false);
        
        int carry = 0;
        solution = sum(solution, num, carry, false);
    }
    
    trimZerosFront(solution);
    int floatDigits = leftFloat.size() + rightFloat.size();
    
    return make_pair(solution.substr(0, solution.size() - floatDigits), solution.substr(solution.size() - floatDigits, floatDigits));
}

void InfinityNum::allignStrings(Operand & left, Operand & right) const {
    unsigned int maxInteger = max(left.integerSize, right.integerSize);
    unsigned int maxFloat = max(left.floatSize, right.floatSize);
    
    left.integer = fillPadding(left.integer, maxInteger, false);
    right.integer = fillPadding(right.integer, maxInteger, false);
    
    left.floatNum = fillPadding(left.floatNum, maxFloat, true);
    right.floatNum = fillPadding(right.floatNum, maxFloat, true);
}

void InfinityNum::allignStrings(const InfinityNum & b, string & leftInteger, string & leftFloat, string & rightInteger, string & rightFloat) const {
    unsigned int maxInteger = max(GetInteger().size(), b.GetInteger().size());
    unsigned int maxFloat = max(GetFloat().size(), b.GetFloat().size());
    
    leftInteger = fillPadding(GetInteger(), maxInteger, false);
    rightInteger = fillPadding(b.GetInteger(), maxInteger, false);
    
    leftFloat = fillPadding(GetFloat(), maxFloat, true);
    rightFloat = fillPadding(b.GetFloat(), maxFloat, true);
}

string InfinityNum::fillPadding(const string str, unsigned int size, bool isFloat) const {
    string newStr = str;
    
    if (size < str.size()) {
        throw PaddingSizeExepction();
    }
    
    int paddingSize = size - str.size();
    
    for (int i = 0; i < paddingSize; i++) {
        if (!isFloat) {
            newStr.insert(newStr.begin(), '0');
        } else {
            newStr.append("0");
        }
    }
    
    return newStr;
}

string InfinityNum::sum(const string & leftNum, const string & rightNum, int & carry, bool isFloat) const {
    if (leftNum.size() != rightNum.size()) {
        cout << "Numbers not alligned!" << endl;
        throw PaddingSizeExepction();
    }
    
    string sumInteger = "";
    
    for (int i = leftNum.size() - 1; i >= 0; i--) {
        int num = (leftNum[i] - '0') + (rightNum[i] - '0') + carry;
        carry = 0;
        if (num > BASE-1) {
            carry = 1;
            num -= BASE;
        }
        
        sumInteger = to_string(num) + sumInteger ;
    }
    
    if (!isFloat && carry != 0) {
        sumInteger = to_string(carry) + sumInteger;
    }
    
    return sumInteger;
}

string InfinityNum::subtract(const string & leftNum, const string & rightNum, int & carry, bool isFloat) const {
    
    string leftF = leftNum;
    string rightF = rightNum;
    
    if (leftF.size() != rightF.size()) {
        cout << "Numbers not alligned!" << endl;
        throw PaddingSizeExepction();
    }
    
    if (leftF == rightF) return "0";
    
    string sum = "";
    for (int i = leftF.size()-1; i >= 0; i--) {
        int left = leftF[i] - '0';
        int right = rightF[i] - '0' + carry;
        int num;
        
        if (left < right) {
            left += BASE;
            num = left - right;
            carry = 1;
        } else {
            num = left - right ;
            carry = 0;
        }
        
        sum = to_string(num) + sum;
    }
    
    if (carry != 0 && !isFloat) {
        sum = to_string(carry) + sum;
    }
    
    return sum;
    
}

string InfinityNum::multiplyByDigit(string & num, char digit, const int decimal) const {
    string solution = "";
    
    for (int i = 0; i < decimal; i++) {
        solution.append("0");
    }
    
    int carry = 0;
    for (int i = num.size() - 1; i >= 0; i--) {
        int tmp = (num[i] - '0') * (digit - '0') + carry;
        
        carry = 0;
        
        if (tmp > 9) {
            carry = tmp/10;
            tmp -= carry*10;
        }
        
        solution = to_string(tmp) + solution;
    }
    
    if (carry != 0) {
        solution = to_string(carry) + solution;
    }
    
    return solution;
}

void InfinityNum::trimZerosBack(string & str) const {
    int i = str.size() - 1;
    while (str[i] == '0') {
        str.pop_back();
        i--;
    }
}

void InfinityNum::trimZerosFront(string & str) const {
    while (str[0] == '0') {
        if (str.size() == 1) {
            break;
        }
        str.erase(str.begin());
    }
}
