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
    ASSERT_TRUE(b.any());
    ASSERT_FALSE(b.none());
}

