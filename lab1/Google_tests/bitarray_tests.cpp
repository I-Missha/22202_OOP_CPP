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

