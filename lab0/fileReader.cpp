//
// Created by Obryv on 30.09.2023.
//

#include "fileReader.h"
#include <string>
using namespace std;

fileReader::fileReader(string filename) {
    file_name = std::move(filename);
}

void fileReader::open() {
    f.open(file_name);
}

string fileReader::getNext() {
    string new_line;
    getline(f, new_line);
    return new_line;
}

void fileReader::close() {
    f.close();
}

void fileReader::reset() {
    f.clear();
    f.seekg(0);
}

bool fileReader::hasNext() {
    return f.peek() != EOF;
}

bool fileReader::isOpen() {
    return f.is_open();
}