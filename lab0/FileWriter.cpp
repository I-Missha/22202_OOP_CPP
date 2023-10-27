//
// Created by Obryv on 06.10.2023.
//

#include "FileWriter.h"
#include <utility>
#include <iostream>
using namespace std;

FileWriterTest::FileWriterTest(std::string file_name) {
    filename = std::move(file_name);
}

void FileWriterTest::createFile() {
    f.open(filename,ios::out);
}

void FileWriterTest::writeData(vector<pair<string, int>> data_vec) {
    long long counter = 0;
    for (int i = 0; i < data_vec.size(); i++) {
        counter += data_vec[i].second;
    }
    for (int i = 0; i < data_vec.size(); i++) {
        f << data_vec[i].first << ";" << data_vec[i].second << ";" << (double)data_vec[i].second / (double)counter * 100 <<"\n";
    }
}

void FileWriterTest::closeFile() {
    f.close();
}

