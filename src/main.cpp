
//
//  Parser.hpp
//  Calculator_infinite_presicion
//
//  Created by Adam Zvada on 03.05.17.
//  Copyright © 2017 Adam Zvada. All rights reserved.
//

#include <iostream>
#include <vector>
#include <memory>
#include <fstream>


#include "Lexer.hpp"
#include "Token.hpp"
#include "Parser.hpp"
#include "Calculation.hpp"

using namespace std;

int main(int argc, const char * argv[]) {
    
    cout << "          - Arbitrary precision calculator -              " << endl;
    cout << endl;
    cout << "Type your arithmetic expression using operadns +, - and *." << endl;
    cout << endl;
    cout << "----------------------------------------------------------" << endl;    

    string exp;
    if (argc == 1) {
        //cin >> exp;
        getline(cin, exp);
    } else {
        ifstream fs( argv[1], ios::in );
        if (fs.fail()) {
            cout << "Calculator: cannot read input file." << endl;
            return 1;
        }
        getline(fs, exp);
    }
    
    Lexer lexer(exp);
    
    vector<shared_ptr<Token>> tokens;
    try {
        tokens = lexer.AllTokens();
    } catch (exception & e) {
        cout << e.what() << endl;
        return 1;
    }

    Parser parser;
    try {
        parser.ConvertToPostfix(lexer);
    } catch (exception & e) {
        cout << e.what() << endl;
        return 1;
    }
    
    Calculation calc(parser.GetExpPostfix());
    
    string solution;
    try {
        solution = calc.Calculate();
    } catch(...) {
        cout << "CALCULATION ERROR" << endl;
        return 1;
    }
    
    cout << "= " << solution << endl;
    
    
    return 0;
}
