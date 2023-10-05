//
// Created by Obryv on 30.09.2023.
//

#ifndef LAB0_FILEREADER_H
#define LAB0_FILEREADER_H


#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class fileReader {

private:
    string file_name;
    ifstream f;

public:
    explicit fileReader(string filename);

    // can return error
    string getNext();

    void open();

    void close();

    void reset();

    bool isOpen();

    bool hasNext();
};


#endif //LAB0_FILEREADER_H
