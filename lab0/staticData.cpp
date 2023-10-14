//
// Created by Obryv on 06.10.2023.
//

#include "StaticData.h"
#include <algorithm>
#include <utility>
using namespace std;

StaticDataTest::StaticDataTest() = default;

void StaticDataTest::addData(vector<string> vec) {
    for (int i = 0; i < vec.size(); i++) {
        data_map.try_emplace(vec[i], 0);
        data_map[vec[i]] += 1;
    }
}

void StaticDataTest::dataMapToVec() {
    unordered_map<string, int>::iterator i;
    for (i = data_map.begin(); i != data_map.end(); i++) {
        data_vec.emplace_back(i->first, i->second);
    }
    data_map.clear();
}

bool comparator(pair<string, int> p1, pair<string, int> p2){
    return p2.second < p1.second;
}

void StaticDataTest::sortData() {
    sort(data_vec.begin(), data_vec.end(), comparator);
}

vector<pair<string, int>> StaticDataTest::getVecData() {
    return data_vec;
}
