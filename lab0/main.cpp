#include <iostream>
#include "fileReader.h"
#include "parser.h"
#include "staticData.h"
#include "fileWriter.h"
#include <fstream>
using namespace std;

int main() {
    // создаем объект класса
    fileReader fileReader("C:\\Users\\Obryv\\CLionProjects\\lab0\\file.txt");
    // открываем файл
    fileReader.open();
    unordered_map<string, int> data;
    staticData staticData(data);
//    cout << fileReader.isOpen();
    // построчное считывание, пока не достигли конца файла
    while (fileReader.hasNext()) {
        string str = fileReader.getNext();
//        how it works??
        parser parser(str);
        vector<pair<string, int>> statistics = parser.countWords();
        staticData.addData(statistics);

    }
    staticData.dataMapToVec();
    staticData.sortData();

    fileWriter fileWriter("C:\\Users\\Obryv\\CLionProjects\\lab0\\out.csv");

    fileWriter.createFile();
    fileWriter.writeData(staticData.getVecData());
    fileWriter.closeFile();

    fileReader.close();
    return 0;
}