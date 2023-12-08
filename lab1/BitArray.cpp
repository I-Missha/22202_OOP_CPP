//
// Created by Obryv on 02.12.2023.
//
//
#include <iostream>
#include "BitArray.h"
#include "Error.cpp"
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
    int newBlocks = new_num_bits / (SIZE_OF_BLOCK - 1) + 1;
    if (value) {
        if (currSize % SIZE_OF_BLOCK != 0) {
            bitArr[bitArr.size() - 1] |= MAX_BLOCK_VALUE >> (currSize % SIZE_OF_BLOCK);
        };
        bitArr.resize(newBlocks, value);
    }
    else {
        bitArr.resize(newBlocks, 0);
    }

    if (new_num_bits % SIZE_OF_BLOCK != 0) {
        bitArr[bitArr.size() - 1] &= MAX_BLOCK_VALUE << (SIZE_OF_BLOCK - new_num_bits % SIZE_OF_BLOCK);
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



