//
// Created by Obryv on 06.10.2023.
//

#include "FileReader.h"
#include <string>
using namespace std;

FileReader::FileReader(string filename) {
    file_name = std::move(filename);
}

void FileReader::open() {
    f.open(file_name);
}

string FileReader::getNext() {
    string new_line;
    getline(f, new_line);
    return new_line;
}

void FileReader::close() {
    f.close();
}

void FileReader::reset() {
    f.clear();
    f.seekg(0);
}

bool FileReader::hasNext() {
    return f.peek() != EOF;
}

bool FileReader::isOpen() {
    return f.is_open();
}
