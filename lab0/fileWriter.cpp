//
// Created by Obryv on 30.09.2023.
//

#include "fileWriter.h"
#include <utility>
#include <iostream>
using namespace std;

fileWriter::fileWriter(std::string file_name) {
    filename = std::move(file_name);
}

void fileWriter::createFile() {
    f.open(filename,ios::out);
}

void fileWriter::writeData(vector<pair<string, int>> data_vec) {
    for (int i = 0; i < data_vec.size(); i++) {
        f << data_vec[i].first << " " << data_vec[i].second << "\n";
    }
}

void fileWriter::closeFile() {
    f.close();
}

