//
// Created by Obryv on 06.10.2023.
//

#ifndef LAB0_FILEREADER_H
#define LAB0_FILEREADER_H

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class FileReader {

private:
    string file_name;
    ifstream f;

public:
    explicit FileReader(string filename);

    // can return error
    string getNext();

    void open();

    void close();

    void reset();

    bool isOpen();

    bool hasNext();
};


#endif //LAB0_FILEREADER_H
