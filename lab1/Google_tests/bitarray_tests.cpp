//
// Created by Obryv on 10.11.2023.
//

#include <gtest/gtest.h>
#include "../BitArray.cpp"

#define SIZE_OF_ARRAY 1000

TEST(BitArray, ArrayContentInfo) {
    BitArray b(SIZE_OF_ARRAY, UINT_MAX);

    ASSERT_FALSE(b.empty());
    ASSERT_EQ(b.size(), SIZE_OF_ARRAY);
    ASSERT_EQ(b.getBit(0), 1);
    b.reset(3);
    ASSERT_EQ(b.getBit(3), 0);
    ASSERT_EQ(b.getBit(2), 1);
    ASSERT_TRUE(b.any());
    ASSERT_FALSE(b.none());
}

TEST(BitArray, LogicOperations) {
    BitArray b(SIZE_OF_ARRAY, UINT_MAX);
    BitArray a(SIZE_OF_ARRAY, 0);
    ASSERT_FALSE(a == b);
    ASSERT_TRUE(a != b);
}

TEST(BitArray, BitArrMethods) {
//    swap
    BitArray a(SIZE_OF_ARRAY, UINT_MAX);
    BitArray b(SIZE_OF_ARRAY, 0);
    BitArray c(SIZE_OF_ARRAY, UINT_MAX);
    BitArray d(SIZE_OF_ARRAY, 0);
    a.swap(b);
    ASSERT_TRUE(b == c);
    ASSERT_TRUE(a == d);

    b.set(1);
    ASSERT_EQ(b.getBit(1), 1);
    b.reset(1);
    ASSERT_EQ(b.getBit(1), 0);
    b.clear();

    BitArray empty;
    ASSERT_TRUE(empty == b);

    BitArray oneEl(1, 1);
    empty.push_back(1);
    ASSERT_TRUE(empty == oneEl);
}

TEST(BitArray, Resize) {
    BitArray a(SIZE_OF_ARRAY, UINT_MAX);
    BitArray templ(32, UINT_MAX);
    a.resize(32);
    ASSERT_TRUE(templ == a);
    a.resize(SIZE_OF_ARRAY, 1);

    BitArray d(992, 1);
    ASSERT_TRUE(a == d);
}

TEST(BitArray, BitOperators) {
    BitArray a(SIZE_OF_ARRAY, UINT_MAX);
    BitArray b(SIZE_OF_ARRAY, 0);

    a |= b;
    BitArray templ(SIZE_OF_ARRAY, UINT_MAX);
    ASSERT_TRUE(templ == a);
    a &= b;
    ASSERT_TRUE(a == b);
    ~templ;

    a.set();
    for (int i = 0; i < 32; i++) {
        b.set(i);
    }
    a ^= b;
    BitArray temple(32);

    temple.resize(1000, 1);
    ASSERT_TRUE(temple == a);
}

TEST(BitArray, BitShifts) {
    BitArray b(8);

    b[0] = true;
    b[3] = true;
    b[7] = true;

    b >>= 1;
    ASSERT_EQ(b.to_string(), "01001000");

    b <<= 2;
    ASSERT_EQ(b.to_string(), "00100000");
}

TEST(BitArray, BigBitShifts) {
    BitArray b(SIZE_OF_ARRAY * 10);
    b.set();

    b >>= SIZE_OF_ARRAY * 2;
    ASSERT_EQ(b.count(), SIZE_OF_ARRAY * 8);

    b <<= SIZE_OF_ARRAY * 3;
    ASSERT_EQ(b.count(), SIZE_OF_ARRAY * 7);
}

TEST(BitArray, NonMatchingOperandSize) {
    BitArray b1(SIZE_OF_ARRAY);
    BitArray b2(SIZE_OF_ARRAY * 2);

    ASSERT_THROW(b1 &= b2, Error);
    ASSERT_THROW(b1 |= b2, Error);
    ASSERT_THROW(b1 ^= b2, Error);

    ASSERT_THROW(b1 & b2, Error);
    ASSERT_THROW(b1 | b2, Error);
    ASSERT_THROW(b1 ^ b2, Error);
}
