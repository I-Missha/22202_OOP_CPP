//
// Created by Obryv on 20.10.2023.
//
#define TWO_IN_31 1 << 31
#define ONE 1
#include <iostream>
#include "BitArray.h"
// size of bitArr elements
using namespace std;

//BitArray::BitArray(int Bu){
//
//}
BitArray& BitArray::operator|=(const BitArray &b) {
    if (this->size() != b.size()) {
        throw Error("BitArrays must be the same size");
    }
    for (int i = 0; i < b.bitArr.size(); i++) {
        bitArr[i] |= b.bitArr[i];
    }
    return *this;
}

BitArray& BitArray::operator&=(const BitArray &b) {
    if (this->size() != b.size()) {
        throw Error("BitArrays must be the same size");
    }
    for (int i = 0; i < b.bitArr.size(); i++){
        bitArr[i] &= b.bitArr[i];
    }
    return *this;
}

BitArray& BitArray::operator= (const BitArray& b) {
    this->bitArr = b.bitArr;
    this->bitArrSize = b.bitArrSize;
    return *this;
}

BitArray& BitArray::operator^=(const BitArray &b) {
    if (this->size() != b.size()) {
        throw Error("BitArrays must be of the same size");
    }

    for (int i = 0; i < b.bitArr.size(); i++){
        bitArr[i] ^= b.bitArr[i];
    }
    return *this;
}

BitArray& BitArray::operator<<=(int n) {
    if (n < 0) {
        throw Error("the number of bit shifts can't be negative");
    }
    if (n / ELEMENT_SIZE != 0) {
        for (int i = 0; i < n / ELEMENT_SIZE; i++) {
            bitArr[i] = bitArr[i + n / ELEMENT_SIZE];
            bitArr[bitArr.size() - 1 - i] = 0;
        }
    }
    if (n % ELEMENT_SIZE != 0) {
        for (int j = 0; j < n % ELEMENT_SIZE; j++) {
            for (int i = 0; i < bitArr.size() - 1; i++) {
                bitArr[i] = bitArr[i] << 1;
                bitArr[i] = bitArr[i] | ((bitArr[i + 1] & TWO_IN_31) ? 1 : 0);
            }
        }
    }
    return *this;
}

BitArray& BitArray::operator>>=(int n) {
    if (n < 0) {
        throw Error("the number of bit shifts can't be negative");
    }
    if (n / ELEMENT_SIZE != 0) {
        for (int i = bitArr.size() - 1; i >= n / ELEMENT_SIZE; i--) {
            bitArr[i] = bitArr[i - n / ELEMENT_SIZE];
        }
        for (int i = n / ELEMENT_SIZE - 1; i >= 0; i--) {
            bitArr[i] = 0;
        }
    }
    if (n % ELEMENT_SIZE != 0) {
        for (int j = 0; j < n % ELEMENT_SIZE; j++) {
            for (int i = (int) bitArr.size() - 1; i > 0; i--) {
                bitArr[i] = bitArr[i] >> 1;
                bitArr[i] = bitArr[i] | ((bitArr[i - 1] & ONE) ? 1 : 0);
            }
            bitArr[0] >>= 1;
        }
    }
    return *this;
}

BitArray BitArray::operator<<(int n) const {
    if (n < 0) {
        throw Error("the number of bit shifts can't be negative");
    }
    BitArray duplicate = BitArray(*this);
    duplicate <<= n;
    return duplicate;
}

BitArray BitArray::operator>>(int n) const {
    if (n < 0) {
        throw Error("the number of bit shifts can't be negative");
    }
    BitArray duplicate = BitArray(*this);
    duplicate >>= n;
    return duplicate;
}

BitArray::BitArray() = default;
BitArray::~BitArray() = default;

BitArray::BitArray(int num_bits, uint value) {
    if (num_bits < 0) {
        throw Error("number of bits is negative");
    }
    if (num_bits < sizeof(value)) {
        throw Error("size of bit array can't be sizeof(value)");
    }
    bitArr.resize(((num_bits - 1) / ELEMENT_SIZE) + 1);
    this->bitArrSize = num_bits;
    bitArr[0] = value;
}

BitArray::BitArray(const BitArray& b) {
    this->bitArr = b.bitArr;
    this->bitArrSize = b.bitArrSize;
}



string BitArray::to_string() const {
    string str = "";
    for (int i = 0; i < bitArr.size(); i++){
        str += std::to_string(this->getBit(i));
    }
    return str;
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
    if (num_bits < 0) {
        throw Error("number of bits is negative");
    }
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

void BitArray::set(int n, bool val) {
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
}

void BitArray::set() {
    for (int i = 0; i < bitArr.size() - 1 * (bitArrSize % ELEMENT_SIZE != 0); i++) {
        bitArr[i] |= UINT_MAX;
    }
    if (bitArrSize % ELEMENT_SIZE == 0) {
        return;
    }
    int temp = UINT_MAX << (ELEMENT_SIZE - bitArrSize % ELEMENT_SIZE);
    bitArr[bitArr.size()] |= temp;
}

void BitArray::push_back(bool bit) {
    if ((bitArrSize + 1) % ELEMENT_SIZE == 0) {
        bitArr.emplace_back(0);
    }
    bitArrSize += 1;
    this->set((int)bitArrSize, bit);
}

void BitArray::reset(int n) {
    this->set(n, false);
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
    return *this;
}

void BitArray::decreaseBitArray(int num_bits) {
    int diff = (int)bitArrSize - num_bits;
    for (int i = 0; i < diff / ELEMENT_SIZE; i++){
        bitArr.pop_back();
    }
    if ((diff) % ELEMENT_SIZE != 0) {
        bitArr[bitArr.size() - 1] = (bitArr[bitArr.size() - 1] >> diff) << diff;
    }
    bitArrSize = num_bits;
}

void BitArray::increaseBitArray(int num_bits, bool value) {
//        needs to test
    // if amount of elements in bitArr is equal, we need to fill last element till achieve index num_bits
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
        return;
    }
    // filling last element
    int oldRemainder = bitArrSize % ELEMENT_SIZE;
    if (oldRemainder != 0 && value) {
        uint temp = UINT_MAX >> (ELEMENT_SIZE - oldRemainder);
        bitArr[bitArr.size() - 1] = bitArr[bitArr.size() - 1] | temp;
    }
    // filling elements in bitArr
    for (int i = 0; i < (num_bits / ELEMENT_SIZE - bitArr.size()); i++) {
        if (value) {
            bitArr.emplace_back(UINT_MAX);
        } else {
            bitArr.emplace_back(0);
        }
    }
    // filling new last element in bitArr till achieve index num_bits if it is necessary
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
    bitArrSize = num_bits;
}



int BitArray::getBit(int ind) const{
//    error
    int elementPosition = ind / ELEMENT_SIZE;
    uint bitPosition = 1 << ( 7 - ind % ELEMENT_SIZE);
    return this->bitArr[elementPosition] & bitPosition;
}

BitArray::Bit::Bit(BitArray *BitArray, int i) {
    this->BitArr = BitArray;
    this->ind = i;
}

BitArray::Bit &BitArray::Bit::operator=(bool val) {
    this->BitArr->set(ind, val);
    return *this;
}

BitArray::Bit BitArray::operator[](int i){
    if (i > bitArrSize) {
        resize(i);
    } else if (i < 0) {
        throw Error("index can't be negative");
    }
    return Bit(this, i);
}

int BitArray::count() const{
    int counter = 0;
    for (int i = 0; i < bitArr.size(); i++) {
        for (int j = 0; j < ELEMENT_SIZE; j++) {
            counter += bitArr[i] & (1 << j);
        }
    }
    return counter;
}

int BitArray::size() const{
    return bitArrSize;
}

bool BitArray::empty() const {
    return bitArrSize == 0;
}

bool operator==(const BitArray &a, const BitArray &b) {
    if (a.size() != b.size()) {
        return false;
    }
    for (int i = 0; i < a.size(); i++) {
        if (a.getBit(i) != b.getBit(i)) {
            return false;
        }
    }
    return true;
}

bool operator!=(const BitArray &a, const BitArray &b) {
    return !(a == b);
}

BitArray operator&(const BitArray &b1, const BitArray &b2) {
    if (b1.size() != b2.size()) {
        throw Error("BitArrays must be the same size");
    }
    BitArray res = BitArray(b1);
    res &= b2;
    return res;
}

BitArray operator|(const BitArray &b1, const BitArray &b2) {
    if (b1.size() != b2.size()) {
        throw Error("BitArrays must be the same size");
    }
    BitArray res = BitArray(b1);
    res |= b2;
    return res;
}

BitArray operator^(const BitArray &b1, const BitArray &b2) {
    if (b1.size() != b2.size()) {
        throw Error("BitArrays must be the same size");
    }
    BitArray res = BitArray(b1);
    res ^= b2;
    return res;
}
