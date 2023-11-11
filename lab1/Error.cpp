//
// Created by Obryv on 09.11.2023.
//

#include <string>

#ifndef LAB1_ERROR_H
#define LAB1_ERROR_H

using namespace std;

class Error: public exception {
private:
    string errorMessage;

public:
    Error(string errorMessage) {
        this->errorMessage = errorMessage;
    }

    const char* what() const noexcept override {
        return errorMessage.c_str();
    }
};


#endif //LAB1_ERROR_H
