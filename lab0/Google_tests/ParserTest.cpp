//
// Created by Obryv on 06.10.2023.
//
#include <gtest/gtest.h>
#include "../Parser.h"
#include <vector>
#include <string>

bool isPairEqual(pair<string, int> p1, pair<string, int> p2) {
    return (p1.first == p2.first) && (p1.second == p2.second);
}

bool isVecEqual(vector<pair<string, int>> vec1, vector<pair<string, int>> vec2) {
    if (vec1.size() != vec2.size()) {
        return false;
    }

    for (int i = 0; i < vec1.size(); i++) {
        if (!isPairEqual(vec1[i], vec2[i])) {
            return false;
        }
    }
    return true;
}

TEST(ParserTests, OneLetter) {
    Parser Parser("1");
//    vector<pair<string, int>> vec = Parser.countWords();
    vector<string> vec_template = {"1"};
    ASSERT_EQ(Parser.parse(), vec_template);
}

TEST(ParserTests, NewLine) {
    Parser Parser("1 sj sj sj od od \n sd");
//    vector<pair<string, int>> vec = Parser.countWords();
    vector<string> vec_template = {"1", "sj", "sj", "sj", "od", "od", "sd"};
    ASSERT_EQ(Parser.parse(), vec_template);
}
