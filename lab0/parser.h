//
// Created by Obryv on 30.09.2023.
//

#ifndef LAB0_PARSER_H
#define LAB0_PARSER_H

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>


using namespace std;

class parser {
private:
    string str;
public:
    explicit parser(string line);

    vector<pair<string, int>> countWords();


//    static bool isLetter(unsigned char symbol);
};

#endif //LAB0_PARSER_H
