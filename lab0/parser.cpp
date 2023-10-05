//
// Created by Obryv on 30.09.2023.
//

#include "parser.h"
#include <vector>
#include <string>
using namespace std;

parser::parser(std::string line) {
    str = std::move(line);
}

vector<pair<string, int>> parser::countWords() {
    vector<string> words;
    string word;
    str += " ";
//    make a function
    for (char i : str) {
        if (!std::isalnum(i)) {
            words.emplace_back(word);
            word.erase();
            continue;
        }
        word += i;
    }

//    make a function
    vector<pair<string, int>> pairs;
    for (int i = 0; i < words.size(); i++) {
        int counter = 1;
        string s = words[i];
        for (int j = i + 1; j < words.size(); j++){
            if (words[j] == s) {
                counter++;
            }
        }
        pairs.emplace_back(s, counter);
    }
    return pairs;
}
