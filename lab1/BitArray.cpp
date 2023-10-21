//
// Created by Obryv on 20.10.2023.
//

#include "BitArray.h"


//BitArray::BitArray(int Bu){
//
//}

BitArray::BitArray() = default;

BitArray::BitArray(int num_bits, unsigned long value) {
    for (int i = 0; i < num_bits / 32 + 1; i++) {
        bitArr.emplace_back(0);
    }
    if (bitArr.empty()) {
        bitArr.emplace_back(value);
    } else {
        bitArr[0] = 0;
    }
    isFull = false;
}

BitArray::BitArray(const BitArray& b) {
    int n = b.size();

}
