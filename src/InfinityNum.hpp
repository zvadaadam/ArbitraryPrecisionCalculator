//
//  InfinityNum.hpp
//  Calculator_infinite_presicion
//
//  Created by Adam Zvada on 16.05.17.
//  Copyright © 2017 Adam Zvada. All rights reserved.
//

#ifndef InfinityNum_hpp
#define InfinityNum_hpp

#include <stdio.h>
#include <iostream>
#include <string>

#include "Operand.hpp"


#define BASE 10

using namespace std;

class PaddingSizeExepction : public exception {
public:
    const char * what() const throw() {
        return "Padding size is smaller than actual size";
    }
};

/**
 * InfinityNum stores arbitrary precised integer or float number and let you do operation as +,-,*
 */
class InfinityNum {
public:
    
    /**
     * Constructor fot InfinityNum
     * @param integer string
     * @param floatNum string
     * @param isNegative flag for negative number, default false
     */
    InfinityNum(const string & integer, const string & floatNum, bool isNegative = false) : _integer(integer), _float(floatNum), _isNegative(isNegative) {};
    
    /**
     * Overrided operator + for InfinityNum
     * @param b right operand number
     * @return InfinityNum returns solution of expression
     */
    InfinityNum operator + (const InfinityNum & b) const;

    /**
     * Overrided operator - for InfinityNum
     * @param b right operand number
     * @return InfinityNum returns solution of expression
     */
    InfinityNum operator - (const InfinityNum & b) const;
    
    /**
     * Overrided operator * for InfinityNum
     * @param b right operand number
     * @return InfinityNum returns solution of expression
     */
    InfinityNum operator * (const InfinityNum & b) const;
    
    /**
     * Get String form of number
     * @return string number
     */
    string GetNum() const;
    
    /**
     * Get String form of integer
     * @return string number
     */
    string GetInteger() const { return _integer; }
    
    /**
     * Get String form of float
     * @return string number
     */
    string GetFloat() const { return _float; }
    
    /**
     * Get flag for negative num
     * @return bool true -, false +
     */
    bool IsNegative() const { return _isNegative; }
    
    /**
     * Change the current number to new passed in parameters
     * @param integer string
     * @param floatNum string
     * @param isNegative flag for negative number, default false
     */
    void ChangeNumber(const string & integer, const string & floatNum, bool isNegative = false) { _integer = integer; _float = floatNum; _isNegative = isNegative; }
private:
    /**
     * Stores string integer
     */
    string _integer;
    
    /**
     * Stores string float
     */
    string _float;
    
    /**
     * Flag wheter number is negative
     */
    bool _isNegative;
    
    /**
     * Perform multiplication on passed strings
     * @param leftInteger left oprand's integer
     * @param leftFloat left oprand's float
     * @param rightInteger right oprand's integer
     * @param rightFloat right oprand's float
     * @return pair<string, string> solution
     */
    pair<string, string> multiplyStr(string & leftInteger, string & leftFloat, string & rightInteger, string & rightFloat) const;
    
    /**
     * Sum left and right operand depending on its sign.
     * @param left operand
     * @param right operand
     * @return InfinityNum solution
     */
    InfinityNum sumStr(const Operand & left, const Operand & right) const;
    
    /**
     * Subtract left and right operand depending on its sign.
     * @param left operand
     * @param right operand
     * @return InfinityNum solution
     */
    InfinityNum subtractStr(const Operand & left, const Operand & right) const;
    

    //InfinityNum multiplyStr(const Operand & left, const Operand & right) const;
    
    /**
     * Updates strings to be alligned, fills padding.
     * @param left operand
     * @param right operand
     */
    void allignStrings(Operand & left, Operand & right) const;
    
    /**
     * Updates strings to be alligned, fills padding.
     * @param b original InfinityNum
     * @param leftInteger left oprand's integer
     * @param leftFloat left oprand's float
     * @param rightInteger right oprand's integer
     * @param rightFloat right oprand's float
     */
    void allignStrings(const InfinityNum & b, string & leftInteger, string & leftFloat, string & rightInteger, string & rightFloat) const;
    
    /**
     * Fill passed string with zeros to given length, does not change the value.
     * @param str updates string
     * @param size to be string padded
     * @param isFloat flag wheter it's float number
     * @return string padded parameter
     */
    string fillPadding(const string str, unsigned int size, bool isFloat) const;
    
    /**
     * Return bigger value
     * @param a value
     * @param b value
     * @return unsigned int max value
     */
    unsigned int max(unsigned int a, unsigned int b) const { return a > b ? a : b; }
    
    /**
     * Simply sum passed strings. Does not care about operands signs.
     * @param leftNum operand
     * @param rightNum operand
     * @param carryFloat update carry, if float then it stores return value for integer
     * @param isFloat flag wheter operands are floats
     * @return string solution
     */
    string sum(const string & leftNum, const string & rightNum, int & carryFloat, bool isFloat) const;
    
    /**
     * Simply subtraction passed strings. Does not care about operands signs.
     * @param leftNum operand
     * @param rightNum operand
     * @param carry update carry, if float then it stores return value for integer
     * @param isFloat flag wheter operands are floats
     * @return string solution
     */
    string subtract(const string & leftNum, const string & rightNum, int & carry, bool isFloat) const;
    
    /**
     * Multiplication by one character
     * @param num number to be multiplied
     * @param digit for multiplication
     * @param decimal number of zeros in back of solution, muliplication by decimal*10
     * @return string solution
     */
    string multiplyByDigit(string & num, char digit, const int decimal) const;
    
    /**
     * Trimming zeros in the back of string number
     * @param str to be trimed, updates
     */
    void trimZerosBack(string & str) const;
    
    /**
     * Trimming zeros in the front of string number*
     * @param str to be trimed, updates
     */
    void trimZerosFront(string & str) const;
};


#endif /* InfinityNum_hpp */
