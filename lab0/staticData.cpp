//
// Created by Obryv on 06.10.2023.
//

#include "StaticData.h"
#include <algorithm>
#include <utility>
using namespace std;

StaticData::StaticData(unordered_map<string, int> input) {
    data_map = std::move(input);
}

void StaticData::addData(vector<pair<string, int>> vec) {
    for (int i = 0; i < vec.size(); i++) {
        data_map.try_emplace(vec[i].first, 0);
        data_map[vec[i].first] += vec[i].second;
    }
}

void StaticData::dataMapToVec() {
    unordered_map<string, int>::iterator i;
    for (i = data_map.begin(); i != data_map.end(); i++) {
        data_vec.emplace_back(i->first, i->second);
    }
    data_map.clear();
}

bool comparator(pair<string, int> p1, pair<string, int> p2){
    return p2.second < p1.second;
}

void StaticData::sortData() {
    sort(data_vec.begin(), data_vec.end(), comparator);
}

vector<pair<string, int>> StaticData::getVecData() {
    return data_vec;
}