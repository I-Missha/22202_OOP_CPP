//
// Created by Obryv on 06.10.2023.
//

#ifndef LAB0_PARSER_H
#define LAB0_PARSER_H

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>


using namespace std;

class Parser {
private:
    string str;
public:
    explicit Parser(string line);

    vector<string> parse();


//    static bool isLetter(unsigned char symbol);
};


#endif //LAB0_PARSER_H
