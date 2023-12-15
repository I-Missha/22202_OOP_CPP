//
// Created by Obryv on 02.12.2023.
//
//
#include <iostream>
#include "BitArray.h"
#include "Error.cpp"
#include "string"
#define SIZE_OF_BLOCK 32
#define MAX_BLOCK_VALUE 0xffffffff
using namespace std;

BitArray::BitArray(int num_bits, unsigned int value) {
    if (num_bits < 0) {
        throw Error("Number of bits can't be negative");
    }
    bitArr.resize((num_bits - 1) / SIZE_OF_BLOCK  + 1);
    currSize = num_bits;
    bitArr[0] = value;
}

BitArray::BitArray(const BitArray& b) {
    bitArr = b.bitArr;
    currSize = b.currSize;
}

void BitArray::swap(BitArray& b) {
    if (b.currSize != currSize) {
        throw Error("Size of array must be equal");
    }
    for (int i = 0; i < bitArr.size() - 1; i++) {
        ::swap(bitArr[i], b.bitArr[i]);
    }
}

BitArray& BitArray::operator=(const BitArray& b) {
    bitArr = b.bitArr;
    currSize = b.currSize;
    return *this;
}

void BitArray::resize(int new_num_bits, bool value) {
    if (new_num_bits < 0) {
        throw Error("Number of bits can't be negative");
    }
    int newBlocks = (new_num_bits - 1) / SIZE_OF_BLOCK + 1;
    if (value) {
        if (currSize % SIZE_OF_BLOCK != 0) {
            bitArr[bitArr.size() - 1] |= MAX_BLOCK_VALUE >> (currSize % SIZE_OF_BLOCK);
        };
        bitArr.resize(newBlocks, UINT_MAX);
    }
    else {
        bitArr.resize(newBlocks, 0);
    }

    if (new_num_bits % SIZE_OF_BLOCK != 0) {
        bitArr[bitArr.size() - 1] &= MAX_BLOCK_VALUE >> (SIZE_OF_BLOCK - (new_num_bits % SIZE_OF_BLOCK));
    }
    currSize = new_num_bits;
}

void BitArray::clear() {
    currSize = 0;
    bitArr.clear();
}

void BitArray::push_back(bool value) {
    resize(currSize + 1, value);
}

BitArray& BitArray::operator&=(const BitArray& b) {
    if (currSize != b.currSize) {
        throw Error("Size of arrays have to be equal");
    }
    for (int i = 0; i < bitArr.size() - 1; i++) {
        bitArr[i] &= b.bitArr[i];
    }
    return *this;
}

BitArray& BitArray::operator|=(const BitArray& b) {
    if (currSize != b.currSize) {
        throw Error("Size of arrays have to be equal");
    }
    for (int i = 0; i < bitArr.size() - 1; i++) {
        bitArr[i] |= b.bitArr[i];
    }
    return *this;
}

BitArray& BitArray::operator^=(const BitArray& b) {
    if (currSize != b.currSize) {
        throw Error("Size of arrays have to be equal");
    }
    for (int i = 0; i < bitArr.size() - 1; i++) {
        bitArr[i] ^= b.bitArr[i];
    }
    if (currSize % SIZE_OF_BLOCK != 0) {
        bitArr[bitArr.size() - 1] &= MAX_BLOCK_VALUE >> (SIZE_OF_BLOCK - (currSize % SIZE_OF_BLOCK));
    }
    return *this;
}

BitArray BitArray::operator~() const {
    BitArray invertedBitArr(*this);
    for (int i = 0; i < invertedBitArr.bitArr.size() - 1; i++) {
        invertedBitArr.bitArr[i] = ~invertedBitArr.bitArr[i];
    }
    if (invertedBitArr.currSize % SIZE_OF_BLOCK != 0) {
        invertedBitArr.bitArr[invertedBitArr.bitArr.size() - 1] &=
                MAX_BLOCK_VALUE << (SIZE_OF_BLOCK - invertedBitArr.currSize % SIZE_OF_BLOCK);
    }
    return invertedBitArr;
}

BitArray& BitArray::operator>>=(int n) {
    if ( n < 0 ) {
        throw Error("Number of bit shifts can't be negative");
    }
    if ( n > currSize) {
        this->reset();
        return *this;
    }
    int blocksNum = n / SIZE_OF_BLOCK;
    if ( blocksNum > 0) {
        for (int i = bitArr.size() - 1; i >= blocksNum; i--) {
            bitArr[i] = bitArr[i - blocksNum];
        }

        for (int i = 0; i < blocksNum; i++) {
            bitArr[i] = 0;
        }
    }

    int bitsNum = n % SIZE_OF_BLOCK;
    if (bitsNum > 0) {
        for (int i = bitArr.size() - 1; i > blocksNum; i--) {
            bitArr[i] >>= bitsNum;
            bitArr[i] |= (bitArr[i - 1] << (SIZE_OF_BLOCK - n % SIZE_OF_BLOCK));
        }
        bitArr[blocksNum] >>= bitsNum;
        bitArr[bitArr.size() - 1] &= (MAX_BLOCK_VALUE << (MAX_BLOCK_VALUE - bitsNum));
    }
    return *this;
}

BitArray& BitArray::operator<<=(int n) {
    if ( n < 0 ) {
        throw Error("Number of bit shifts can't be negative");
    }
    if ( n > currSize) {
        this->reset();
        return *this;
    }
    int blocksNum = n / SIZE_OF_BLOCK;
    if ( blocksNum > 0) {
        for (int i = 0; i < bitArr.size() - blocksNum; i++) {
            bitArr[i] = bitArr[i + blocksNum];
        }

        for (int i = bitArr.size() - 1; i >= bitArr.size() - blocksNum; i--) {
            bitArr[i] = 0;
        }
    }

    int bitsNum = n % SIZE_OF_BLOCK;
    if (bitsNum > 0) {
        for (int i = 0; i < bitArr.size() - blocksNum; i++) {
            bitArr[i] <<= bitsNum;
            bitArr[i] |= (bitArr[i + 1] >> (SIZE_OF_BLOCK - n % SIZE_OF_BLOCK));
        }
        bitArr[bitArr.size() - blocksNum - 1] <<= bitsNum;
    }
    return *this;
}

BitArray BitArray::operator>>(int n) const{
    if (n < 0) {
        throw Error("Number of bit shifts can't be negative");
    }
    BitArray shiftedBitArr(*this);
    shiftedBitArr >>= n;
    return shiftedBitArr;
}

BitArray BitArray::operator<<(int n) const{
    if (n < 0) {
        throw Error("Number of bit shifts can't be negative");
    }
    BitArray shiftedBitArr(*this);
    shiftedBitArr <<= n;
    return shiftedBitArr;
}

void BitArray::set(int n) {
    if (n < 0) {
        throw Error("Index must be positive");
    }
    bitArr[n / (SIZE_OF_BLOCK )] |= (unsigned int)1 << (SIZE_OF_BLOCK - n % SIZE_OF_BLOCK);
}

void BitArray::reset(int n) {
    if (n < 0) {
        throw Error("Index must be positive");
    }
    bitArr[n / (SIZE_OF_BLOCK)] &= ~((unsigned int)1 << (SIZE_OF_BLOCK - n % SIZE_OF_BLOCK));
}

BitArray& BitArray::set() {
    for (int i = 0; i < bitArr.size() - 1; i++) {
        bitArr[i] = MAX_BLOCK_VALUE;
    }

    if (currSize % SIZE_OF_BLOCK > 0) {
       bitArr[bitArr.size() - 1] = MAX_BLOCK_VALUE >> (SIZE_OF_BLOCK - currSize % SIZE_OF_BLOCK);
    }

    return *this;
}

BitArray& BitArray::reset() {
    for (int i = 0; i < bitArr.size() - 1; i++) {
        bitArr[i] = 0;
    }
    return *this;
}

bool BitArray::any() const{
    for (int i = 0; i < bitArr.size() - 1; i++) {
        if (bitArr[i]) {
            return true;
        }
    }
    return false;
}

bool BitArray::none() const{
    for (int i = 0; i < bitArr.size() - 1; i++) {
        if (!bitArr[i]) {
            return false;
        }
    }
    return true;
}

int BitArray::count() const{
    int count = 0;
    for (int i = 0; i < bitArr.size() - 1; i++) {
        count += __builtin_popcountll(bitArr[i]);
    }
    return count;
}

int BitArray::size() const{
    return currSize;
}

bool BitArray::empty() const {
    return currSize == 0;
}

BitArray::Bit::Bit(BitArray& b, int index) : bitArray(b) {
    ind = index;
}

BitArray::Bit &BitArray::Bit::operator=(bool val) {
    if (val) {
        bitArray.set(ind);
    } else {
        bitArray.reset(ind);
    }
    return *this;
}

BitArray::Bit BitArray::operator[](int ind) {
    if (ind < 0 ){
        throw Error("Index must be positive");
    }
    if (ind > currSize) {
        this->resize(ind);
    }
    Bit bit(*this, ind);
    return bit;
}

int BitArray::getBit(int ind) const{
    return ((bitArr[ind / SIZE_OF_BLOCK]) >> (SIZE_OF_BLOCK - ind % SIZE_OF_BLOCK)) & 1;
}

BitArray::Bit::operator bool() {
    return this->bitArray.getBit(this->ind);
}

string BitArray::to_string()  {
    string str = "";
    for (int i = 0; i < currSize + 1; i++) {
        str += (*this)[i] ? "1" : "0";
    }
    return str;
}

bool operator==(const BitArray& a, const BitArray& b) {
    if (a.size() != b.size()) {
        return false;
    }

    return a.bitArr == b.bitArr;
}

bool operator!=(const BitArray& a, const BitArray& b) {
    if (a.size() != b.size()) {
        return true;
    }

    return a.bitArr != b.bitArr;
}

BitArray operator&(const BitArray& b1, const BitArray& b2) {
    if (b1.size() != b2.size()) {
        throw Error("BitArray operands must be of the same size");
    }

    BitArray newBitarray(b1);
    newBitarray &= b2;
    return newBitarray;
}

BitArray operator|(const BitArray& b1, const BitArray& b2) {
    if (b1.size() != b2.size()) {
        throw Error("BitArray operands must be of the same size");
    }

    BitArray newBitarray(b1);
    newBitarray |= b2;
    return newBitarray;
}

BitArray operator^(const BitArray& b1, const BitArray& b2) {
    if (b1.size() != b2.size()) {
        throw Error("BitArray operands must be of the same size");
    }

    BitArray newBitarray(b1);
    newBitarray ^= b2;
    return newBitarray;
}