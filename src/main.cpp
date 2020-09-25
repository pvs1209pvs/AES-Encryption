#include <iostream>
#include <algorithm>
#include <gtest/gtest.h>
#include "utility.h"
#include "AES.h"

#define NUM_TEST_CASES 2

TEST(AESTest, KeyExpansion) {

    std::vector<unsigned int> MSG = fread_chars("../src/message.txt");

    // Custom keys
    unsigned int KEY_HEX_MTRX[][4][4] = {
            {{0x2b, 0x28, 0xab, 0x09},
                    {0x7e, 0xae, 0xf7, 0xcf},
                    {0x15, 0xd2, 0x15, 0x4f},
                    {0x16, 0xa6, 0x88, 0x3c}},

            {{0x54, 0x73, 0x20, 0x67},
                    {0x68, 0x20, 0x4b, 0x20},
                    {0x61, 0x6d, 0x75, 0x46},
                    {0x74, 0x79, 0x6e, 0x75}},

    };

    // Converts static arrays to pointer arrays
    std::vector<unsigned int **> TRIAL_KEYS{};

    TRIAL_KEYS.reserve(NUM_TEST_CASES);
    for (auto &i : KEY_HEX_MTRX) {
        TRIAL_KEYS.push_back(static_to_dynamic(i));
    }

    // Expanded keys are stored in a inline format.
    std::vector<std::string> expanded_keys_inline{};
    std::vector<std::vector<unsigned int **>> expanded_key_schedules{};

    for (int i = 0; i < NUM_TEST_CASES; ++i) {

        AES aesTesting(TRIAL_KEYS.at(i), MSG, 128);
        expanded_key_schedules.push_back(aesTesting.key_expansion());

        std::string inline_key{};
        for (int j = 0; j < aesTesting.get_round_wrt_block_size().at(aesTesting.get_BLOCK_SIZE())+1; ++j) {
            inline_key += hex_mtrx_to_string(expanded_key_schedules.at(i).at(j));
        }

        expanded_keys_inline.push_back(inline_key);

    }

    std::vector<std::string> answer_keys = fread_lines("../test/correct_key_expansion_test_file.txt");

    for (int i = 0; i < NUM_TEST_CASES; ++i) {
        EXPECT_EQ(expanded_keys_inline.at(i), answer_keys.at(i));
    }

}

int main(int argc, char *argv[]) {

    if(strcmp(argv[1], "runtest")==0){
        testing::InitGoogleTest(&argc, argv);
        return RUN_ALL_TESTS();
    }
    else{

        std::cout << "ell" << std::endl;
        return 0;
    }



}

// msg = my name is paramvir singh.
// key = javajavajava
// cipher = 8B92802C131422122999E39B713CB4B12E8C646410A03C63534F79A386004C04