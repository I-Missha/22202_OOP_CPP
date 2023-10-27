//
// Created by Obryv on 06.10.2023.
//

#ifndef LAB0_STATICDATA_H
#define LAB0_STATICDATA_H

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

class StaticDataTest {
private:
    unordered_map<string, int> data_map;
    vector<pair<string, int>> data_vec;
    void dataMapToVec();
    void sortData();
public:
    explicit StaticDataTest();
    void addData(vector<string> words);
    vector<pair<string, int>> getVecData();
};

#endif //LAB0_STATICDATA_H
