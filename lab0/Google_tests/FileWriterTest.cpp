//
// Created by Obryv on 13.10.2023.
//
#include "gtest/gtest.h"
#include "../FileWriter.h"

TEST (FileWriterTest, WritingData) {
    FileWriterTest FileWriter("test.csv");
    FileWriter.createFile();
    vector<pair<string, int>> test_data;

    for (int i = 0; i < 5; i++) {
        test_data.emplace_back(pair<string, int>{"1", 1});
    }

    FileWriter.writeData(test_data);
    FileWriter.closeFile();

    fstream template_file, test;
    template_file.open("C:\\Users\\Obryv\\22202_OOP_CPP\\lab0\\Google_tests\\template_file.csv");
//    cout << template_file.is_open();
    test.open("test.csv");
    for (int i = 0; i < 5; i++) {
        string tmp1, tmp2;
        getline(test, tmp1);
        getline(template_file, tmp2);
        ASSERT_EQ(tmp1, tmp2);
        tmp1.erase();
        tmp2.erase();
    }

    test.close();
    template_file.close();
}
