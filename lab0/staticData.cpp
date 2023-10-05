//
// Created by Obryv on 30.09.2023.
//

#include "staticData.h"
#include <algorithm>
#include <utility>
using namespace std;

staticData::staticData(unordered_map<string, int> input) {
    data_map = std::move(input);
}

void staticData::addData(vector<pair<string, int>> vec) {
    for (int i = 0; i < vec.size(); i++) {
        data_map.try_emplace(vec[i].first, 0);
        data_map[vec[i].first] += vec[i].second;
    }
}

void staticData::dataMapToVec() {
    unordered_map<string, int>::iterator i;
    for (i = data_map.begin(); i != data_map.end(); i++) {
        data_vec.emplace_back(i->first, i->second);
    }
    data_map.clear();
}

bool comparator(pair<string, int> p1, pair<string, int> p2){
    return p2.second < p1.second;
}

void staticData::sortData() {
    sort(data_vec.begin(), data_vec.end(), comparator);
}

vector<pair<string, int>> staticData::getVecData() {
    return data_vec;
}