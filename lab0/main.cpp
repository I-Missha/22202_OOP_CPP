#include <iostream>
#include "FileReader.h"
#include "Parser.h"
#include "StaticData.h"
#include "FileWriter.h"
using namespace std;

int main() {
    // создаем объект класса
    FileReader FileReader("C:\\Users\\Obryv\\22202_OOP_CPP\\lab0\\file.txt");
    // открываем файл
    FileReader.open();
    StaticDataTest StaticData;
    // построчное считывание, пока не достигли конца файла
    while (FileReader.hasNext()) {
        string str = FileReader.getNext();
//      but how it works??
        Parser Parser(str);
        vector<string> statistics = Parser.parse();
        StaticData.addData(statistics);

    }
    StaticData.dataMapToVec();
    StaticData.sortData();

    FileWriterTest FileWriter("C:\\Users\\Obryv\\22202_OOP_CPP\\lab0\\out.csv");

    FileWriter.createFile();
    FileWriter.writeData(StaticData.getVecData());
    FileWriter.closeFile();
    FileReader.close();
    return 0;
}
