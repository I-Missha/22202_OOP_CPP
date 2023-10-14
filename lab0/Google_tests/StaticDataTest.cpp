//
// Created by Obryv on 14.10.2023.
//
#include "gtest/gtest.h"
#include "../StaticData.h"

void addStrToVec(vector<string>& words, int n){
    for (int i = n; i < 10; i++){
        words.emplace_back(to_string(i));
    }
}

TEST (StaticDataTests, workProcess) {
    StaticDataTest StaticData;

    vector<string> words;
    words.reserve(10);
    for (int i = 0; i < 10; i++) {
        addStrToVec(words, i);
    }
    StaticData.addData(words);
    StaticData.dataMapToVec();
    StaticData.sortData();
    vector<pair<string, int>> vec_test = StaticData.getVecData();

    vector<pair<string, int>> templ_vec;
    templ_vec.reserve(10);
    for (int i = 9; i > -1; i--) {
        templ_vec.emplace_back(to_string(i), i + 1);
    }

    ASSERT_EQ(vec_test, templ_vec);
}
