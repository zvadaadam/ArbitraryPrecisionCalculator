//
//  Calculation.cpp
//  Calculator_infinite_presicion
//
//  Created by Adam Zvada on 09.05.17.
//  Copyright © 2017 Adam Zvada. All rights reserved.
//

#include "Calculation.hpp"

string Calculation::Calculate() {
    
    list<shared_ptr<Token>>::iterator it = _postfixExp.begin();
    int index = 0;
    while (it != _postfixExp.end()) {
        index++;
        
        //Print();
        
        Operation * operation = dynamic_cast<Operation*>(it->get());
        if (operation != nullptr) {
            if (operation->GetType() == SymboleTable::UNARY_MINUS) { //erase unanry
                
                it = _postfixExp.erase(it);
                it--;
                index--;
                
                Number * num = dynamic_cast<Number*>(it->get());
                if (num == nullptr) {
                    throw CalculationException();
                }
                num->ChangeSign();
            } else {                                                //erase operand
                if (index < 3) {
                    throw CalculationException();
                }
                
                it = _postfixExp.erase(it);
                index--;
                it--;
            
                Number rightOperand = removeNumber(it);
                index--;
                it--;
            
                Number leftOperand = removeNumber(it);
            
                Number solution = operation->ApplyOperation(rightOperand, leftOperand);
                _postfixExp.insert(it, make_shared<Number>(Number(solution.GetInteger(), solution.GetFloat(), solution.IsNegative()))); //IT points down
            }
        } else {
            it++;
        }
    }
    
    
    if (_postfixExp.size() != 1) {
        throw CalculationException();;
    }
    Number * num = dynamic_cast<Number*>(_postfixExp.back().get());
    
    string solution = num->IsNegative() ? "-" : "";
    
    
    return solution.append(_postfixExp.back()->GetString());
}

void Calculation::Print() const {
    auto it = _postfixExp.begin();
    
    while (it != _postfixExp.end()) {
        cout << it->get()->GetString() << " ";
        it++;
    }
    cout << endl;
}

Number Calculation::removeNumber(list<shared_ptr<Token>>::iterator & it) {
    Number * operand = dynamic_cast<Number*>(it->get());
    if (operand == nullptr) {
        throw CalculationException();;
    }
    Number num(operand->GetInteger(), operand->GetFloat(), operand->IsNegative());
    
    it = _postfixExp.erase(it);
    
    return num;
}


