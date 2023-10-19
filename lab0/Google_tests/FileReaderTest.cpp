//
// Created by Obryv on 13.10.2023.
//
#include "gtest/gtest.h"
#include "../FileReader.h"
#include <string>
#include <fstream>
#include <vector>

TEST(FileReaderTests, gettingNext) {
    fstream file;
    FileReader FileReader("C:\\Users\\Obryv\\22202_OOP_CPP\\lab0\\file.txt");
    FileReader.open();
    file.open("C:\\Users\\Obryv\\22202_OOP_CPP\\lab0\\file.txt");
    vector<string> vec;
    while (FileReader.hasNext()) {
        vec.emplace_back(FileReader.getNext());
    }
    FileReader.reset();
    vector<string> template_vec;
    while (file.peek() != EOF) {
        string temp_str;
        getline(file, temp_str);
        template_vec.emplace_back(temp_str);
    }
    file.close();
    FileReader.close();
    ASSERT_EQ(vec, template_vec);
}
