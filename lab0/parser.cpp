//
// Created by Obryv on 06.10.2023.
//

#include "Parser.h"
#include <vector>
#include <string>

using namespace std;

Parser::Parser(std::string line) {
    str = std::move(line);
}

vector<string> Parser::parse() {
    vector<string> words;
    string word;
    str += " ";
//    make a function
    for (char i : str) {
        if (std::isalnum(i)){
            word += i;
        } else if (!word.empty()){
            words.emplace_back(word);
            word.erase();
        }
    }

//    make a function
//    vector<pair<string, int>> pairs;
//    for (int i = 0; i < words.size(); i++) {
//        int counter = 1;
//        string s = words[i];
//        for (int j = i + 1; j < words.size(); j++){
//            if (words[j] == s) {
//                counter++;
//            }
//        }
//        pairs.emplace_back(s, counter);
//    }
    return words;
}
