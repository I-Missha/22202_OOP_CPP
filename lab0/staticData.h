//
// Created by Obryv on 30.09.2023.
//

#ifndef LAB0_STATICDATA_H
#define LAB0_STATICDATA_H

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;


class staticData {
private:
    unordered_map<string, int> data_map;
    vector<pair<string, int>> data_vec;
public:
    explicit staticData(unordered_map<string, int>);

    void addData(vector<pair<string, int>> words);
    void dataMapToVec();
    void sortData();
    vector<pair<string, int>> getVecData();
};



#endif //LAB0_STATICDATA_H
