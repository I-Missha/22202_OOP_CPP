//
// Created by Obryv on 20.10.2023.
//

#ifndef LAB1_BITARRAY_H
#define LAB1_BITARRAY_H
#define ELEMENT_SIZE 32
#define uint unsigned int
#include <string>
#include <vector>
#include <climits>
#include <iostream>
#include "Error.cpp"

using namespace std;
class BitArray {
private:
    vector<unsigned int> bitArr;
    int currSize = 0;
//  store only last significant bit in the array and other zeroes (insignificant bits) we don't store
// default value is -1, significant value is missing int the array

    // increase/decrease bit array by bit shifts
    void decreaseBitArray(int num_bits);
    void increaseBitArray(int num_bits, bool value);
    int findLastSignBit();

    class Bit {
    private:
        BitArray *BitArr;
        int ind;
    public:
        Bit(BitArray *BitArray, int i);
        Bit& operator=(bool val);
    };

public:
    BitArray();
    ~BitArray();


    //construct an array that stores given number of bits
    //first sizeof(unsigned int) <32> bits we can initialize a value using value parametr.
    explicit BitArray(int num_bits, unsigned int value = 0);
    BitArray(const BitArray& b); // duplicate bitArr to this bitArr

    //return bitArr[ind] value
    int getBit(int ind) const;

    //swap values of two bit arrays
    void swap(BitArray& b);

    //overload operator =,
    BitArray& operator=(const BitArray& b);

    //resize array. expand array if necessary
    //initialize value by given value.
    void resize(int num_bits, bool value = false);
    //clear the array.
    void clear();
    // add new bit in the end of array. reallocation of memory if necessary
    void push_back(bool bit);


    // bit operations on arrays. only work if size of arrays are equal
    BitArray& operator&=(const BitArray& b);
    BitArray& operator|=(const BitArray& b);
    BitArray& operator^=(const BitArray& b);
    //bit inversion
    BitArray operator~() const;

    //bit shift.
    BitArray& operator<<=(int n);
    BitArray& operator>>=(int n);
    BitArray operator<<(int n) const;
    BitArray operator>>(int n) const;


    //sets the bit with index n to the value
    void set(int n, bool val = true);
    //fills the bit array with true
    void set();

    //sets bit with index n with false value
    void reset(int n);
    //Заполняет массив ложью.
    BitArray& reset();

    //true if array includes true bit
    bool any() const;
    //true if in the array all bits are true
    bool none() const;
    //count bits that are true
    int count() const;


    //returns the bit value by index i
    // operator[] returns class Bit. operator= of class Bit return
    Bit operator[](int i);

    // returns current size of bit array
    int size() const;
    // true if array is empty
    bool empty() const;

    // returns the content of a bit array as a string
    string to_string() const;

    BitArra();
};

bool operator==(const BitArray & a, const BitArray & b);
bool operator!=(const BitArray & a, const BitArray & b);

BitArray operator&(const BitArray& b1, const BitArray& b2);
BitArray operator|(const BitArray& b1, const BitArray& b2);
BitArray operator^(const BitArray& b1, const BitArray& b2);

#endif //LAB1_BITARRAY_H
