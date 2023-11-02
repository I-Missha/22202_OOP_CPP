//
// Created by Obryv on 20.10.2023.
//
#define TWO_IN_31 2147483648
#define ONE 1
#include <iostream>
#include "BitArray.h"
// size of bitArr elements
using namespace std;

//BitArray::BitArray(int Bu){
//
//}
BitArray& BitArray::operator|=(const BitArray &b) {
//    error
    for (int i = 0; i < b.bitArr.size(); i++) {
        bitArr[i] |= b.bitArr[i];
    }
    return *this;
}

BitArray& BitArray::operator&=(const BitArray &b) {
//    error
    for (int i = 0; i < b.bitArr.size(); i++){
        bitArr[i] &= b.bitArr[i];
    }
    return *this;
}

BitArray& BitArray::operator^=(const BitArray &b) {
    for (int i = 0; i < b.bitArr.size(); i++){
        bitArr[i] ^= b.bitArr[i];
    }
    return *this;
}

BitArray& BitArray::operator<<=(int n) {
    for (int j = 0; j < n; j++) {
        for (int i = 0; i < bitArr.size() - 1; i++) {
            bitArr[i] = bitArr[i] << 1;
            bitArr[i] = bitArr[i] | ((bitArr[i + 1] & TWO_IN_31) ? 1 : 0);
        }
    }
    return *this;
}

BitArray& BitArray::operator>>=(int n) {
    for (int j = 0; j < n; j++) {
        for (int i = (int)bitArr.size() - 1; i > 1; i--) {
            bitArr[i] = bitArr[i] >> 1;
            bitArr[i] = bitArr[i] | ((bitArr[i - 1] & ONE) ? 1 : 0);
        }
        bitArr[0] >>= 1;
    }
    return *this;
}

BitArray BitArray::operator<<(int n) const {
    BitArray duplicate = BitArray(*this);
    duplicate <<= n;
    return duplicate;
}

BitArray BitArray::operator>>(int n) const {
    BitArray duplicate = BitArray(*this);
    duplicate >>= n;
    return duplicate;
}

BitArray::BitArray() = default;
BitArray::~BitArray() = default;

BitArray::BitArray(int num_bits, unsigned int value) {
//    value = num, but num_bits is less than ELEMENT_SIZE
    int flag = 0;
    if (num_bits % ELEMENT_SIZE != 0) {
        flag = 1;
    }
    for (int i = 0; i < num_bits / ELEMENT_SIZE + flag; i++) {
        bitArr.emplace_back(0);
    }
    if (num_bits >= ELEMENT_SIZE ) {
        bitArr[0] = value;
    }
    bitArrSize = num_bits;
}

BitArray::BitArray(const BitArray& b) {
    for (int i = 0; i < b.bitArr.size(); i++) {
        bitArr.emplace_back(0);
    }
    *this |= b;
}


// rewrite
string BitArray::to_string() const {
    for (int i = 0; i < bitArr.size(); i++){
        cout << bitArr[i];
    }
    return std::__cxx11::string();
}

void BitArray::swap(BitArray& b) {
//    error
    for (int i = 0; i < bitArr.size(); i++) {
        uint temp = bitArr[i];
        bitArr[i] = b.bitArr[i];
        b.bitArr[i] = temp;
    }

}

void BitArray::resize(int num_bits, bool value) {
    if (num_bits == bitArrSize) {
        return;
    }
    if (num_bits > bitArrSize) {
        increaseBitArray(num_bits, value);
    } else {
        decreaseBitArray(num_bits);
    }
}

void BitArray::clear() {
    bitArr.clear();
    bitArrSize = 0;
}

BitArray& BitArray::set(int n, bool val) {
    if (n > bitArrSize) {
        resize(n, false);
    }
    int indexInVec = n / ELEMENT_SIZE;
    int indexInVecElement = n % ELEMENT_SIZE;
    if (val) {
        bitArr[indexInVec] = bitArr[indexInVec] | (1 << (ELEMENT_SIZE - indexInVecElement));
    } else {
        bitArr[indexInVec] = bitArr[indexInVec] & ~(1 << (ELEMENT_SIZE - indexInVecElement));
    }
    return *this;
}

BitArray& BitArray::set() {
    for (int i = 0; i < bitArr.size() - 1 * (bitArrSize % ELEMENT_SIZE != 0); i++) {
        bitArr[i] |= UINT_MAX;
    }
    if (bitArrSize % ELEMENT_SIZE == 0) {
        return *this;
    }
    int temp = UINT_MAX << (ELEMENT_SIZE - bitArrSize % ELEMENT_SIZE);
    bitArr[bitArr.size()] |= temp;
    return *this;
}

void BitArray::push_back(bool bit) {
    if ((bitArrSize + 1) % ELEMENT_SIZE == 0) {
        bitArr.emplace_back(0);
    }
    bitArrSize += 1;
    this->set((int)bitArrSize, bit);
}

BitArray& BitArray::reset(int n) {
    this->set(n, 0);
    return *this;
}

BitArray& BitArray::reset() {
    for (int i = 0; i < bitArr.size(); i++) {
        bitArr[i] &= 0;
    }
    return *this;
}

bool BitArray::any() const {
    for (int i = 0; i < bitArr.size(); i++) {
        if (bitArr[i]) {
            return true;
        }
    }
    return false;
}

bool BitArray::none() const {
    return !this->any();
}

BitArray BitArray::operator~() const {
    BitArray duplicate = BitArray(*this);
    for (int i = 0; i < duplicate.bitArr.size() - 1; i++) {
        duplicate.bitArr[i] = ~duplicate.bitArr[i];
    }
    int remainder = duplicate.bitArrSize % ELEMENT_SIZE;
    if (!remainder) {
        return duplicate;
    }
    for (int i = duplicate.bitArrSize - duplicate.bitArrSize % ELEMENT_SIZE + 1; i < duplicate.bitArrSize; i++) {
        duplicate.reset(i);
    }
}

void BitArray::decreaseBitArray(int num_bits) {
    for (int i = 0; i < num_bits / ELEMENT_SIZE; i++){
        bitArr.pop_back();
    }
    if ((bitArrSize - num_bits) % ELEMENT_SIZE != 0) {
        uint temp = UINT_MAX << (bitArrSize - num_bits) % ELEMENT_SIZE;
        bitArr[bitArr.size() - 1] = bitArr[bitArr.size() - 1] & temp;
    }
    bitArrSize = num_bits;
}

void BitArray::increaseBitArray(int num_bits, bool value) {
//        needs to test
    if (num_bits / ELEMENT_SIZE - bitArr.size() == 0 && bitArrSize % ELEMENT_SIZE != 0) {
        if (!value) {
            bitArrSize = num_bits;
            return;
        }
        int newRemainder = num_bits % ELEMENT_SIZE;
        int oldRemainder = bitArrSize % ELEMENT_SIZE;
        uint temp = UINT_MAX >> (ELEMENT_SIZE - (newRemainder - oldRemainder));
        temp = temp << (ELEMENT_SIZE - newRemainder);
        bitArr[bitArr.size() - 1] = bitArr[bitArr.size() - 1] | temp;
        bitArrSize = num_bits;
    }
    int oldRemainder = bitArrSize % ELEMENT_SIZE;
    if (oldRemainder != 0 && value) {
        uint temp = UINT_MAX >> (ELEMENT_SIZE - oldRemainder);
        bitArr[bitArr.size() - 1] = bitArr[bitArr.size() - 1] | temp;
    }
    for (int i = 0; i < (num_bits / ELEMENT_SIZE - bitArr.size()); i++) {
        if (value) {
            bitArr.emplace_back(UINT_MAX);
        } else {
            bitArr.emplace_back(0);
        }
    }
    bitArrSize = num_bits;
    int newRemainder = num_bits % ELEMENT_SIZE;
    if (newRemainder == 0) {
        return;
    }
    bitArr.emplace_back(0);
    if (value) {
        uint temp = UINT_MAX << (ELEMENT_SIZE - newRemainder);
//            cout << "\n" << temp << "\n";
        bitArr[bitArr.size() - 1] = bitArr[bitArr.size() - 1] | temp;
    }
}

BitArray::Bit::Bit(vector<unsigned int> *arr, int i) {
    this->bitArr = arr;
    this->size = i;
}

BitArray::Bit &BitArray::Bit::operator=(const BitArray::Bit &b) {

}


