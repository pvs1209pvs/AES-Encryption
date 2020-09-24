#include <iostream>
#include <algorithm>
#include <gtest/gtest.h>
#include "utility.h"
#include "AES.h"

int main(int argc, char *argv[]) {

   testing::InitGoogleTest(&argc, argv);
//
//    std::vector<unsigned int> msg = fread_chars("../src/message.txt");
//    const std::vector<unsigned int> key = fread_chars("../src/key.txt");
//
//    AES aes(key, msg, 128);

    return RUN_ALL_TESTS();
}

// msg = my name is paramvir singh.
// key = javajavajava
// cipher = 8B92802C131422122999E39B713CB4B12E8C646410A03C63534F79A386004C04