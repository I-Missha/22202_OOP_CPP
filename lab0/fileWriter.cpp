//
// Created by Obryv on 06.10.2023.
//

#include "FileWriter.h"
#include <utility>
#include <iostream>
using namespace std;

FileWriter::FileWriter(std::string file_name) {
    filename = std::move(file_name);
}

void FileWriter::createFile() {
    f.open(filename,ios::out);
}

void FileWriter::writeData(vector<pair<string, int>> data_vec) {
    for (int i = 0; i < data_vec.size(); i++) {
        f << data_vec[i].first << ";" << data_vec[i].second << "\n";
    }
}

void FileWriter::closeFile() {
    f.close();
}

