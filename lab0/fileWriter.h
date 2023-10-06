//
// Created by Obryv on 06.10.2023.
//

#ifndef LAB0_FILEWRITER_H
#define LAB0_FILEWRITER_H

#include <vector>
#include <string>
#include <fstream>
#include <unordered_map>
using namespace std;

class FileWriter {
private:
    string filename;
    fstream f;
public:
    FileWriter(string file_name);
    void createFile();
    void closeFile();
    void writeData(vector<pair<string, int>> data_vec);
};

#endif //LAB0_FILEWRITER_H
