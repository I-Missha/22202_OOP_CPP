//
// Created by Obryv on 30.09.2023.
//

#ifndef LAB0_FILEWRITER_H
#define LAB0_FILEWRITER_H

#include <vector>
#include <string>
#include <fstream>
#include <unordered_map>
using namespace std;

class fileWriter {
private:
    string filename;
    fstream f;
public:
    fileWriter(string file_name);
    void createFile();
    void closeFile();
    void writeData(vector<pair<string, int>> data_vec);
};

#endif //LAB0_FILEWRITER_H
