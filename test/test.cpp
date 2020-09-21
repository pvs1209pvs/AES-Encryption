#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include "test.h"
#include "utility.h"

TEST_CASE("Key expansion"){

    const std::vector<unsigned int> USER_MSG = fread("../src/message.txt");

    unsigned int USER_KEY_ARRAY[][4][4] = {
            {{0x2b, 0x28, 0xab, 0x09},
                    {0x7e, 0xae, 0xf7, 0xcf},
                    {0x15, 0xd2, 0x15, 0x4f},
                    {0x16, 0xa6, 0x88, 0x3c}},

            {{0x54, 0x73, 0x20, 0x67},
                    {0x68, 0x20, 0x4b, 0x20},
                    {0x61, 0x6d, 0x75, 0x46},
                    {0x74, 0x79, 0x6e, 0x75}},

    };

    std::vector<unsigned int **> trial_keys{};
    trial_keys.reserve(2);
    for (auto & i : USER_KEY_ARRAY) {
        trial_keys.push_back(static_to_dynamic(i));
    }

    std::vector<std::vector<unsigned int **>> expanded_key_schedules{};
    for (int i = 0; i < 2; ++i) {
        AES aes(trial_keys.at(i), USER_MSG, 128);
        expanded_key_schedules.push_back(aes.key_expansion());

    }

    key_expansion_matching(expanded_key_schedules);

}

void key_expansion_matching(std::vector<std::vector<unsigned int **>> aes_keys) {

    std::vector<std::string> answer_keys = read_answer_key();

    for (int i = 0; i < 2; ++i) {

        std::stringstream ss;
        for (int j = 0; j < aes_keys.at(i).size(); ++j) {
            ss << hex_mtrx_to_string(aes_keys.at(i).at(j));
        }

        REQUIRE(answer_keys.at(i)==ss.str());

    }

}

std::vector<std::string> read_answer_key() {

    std::vector<std::string> keys;
    std::ifstream infile{"../test/correct_key_expansion_test_file.txt", std::ios::in};

    if (infile.is_open()) {

        for (int i = 0; i < 2; ++i) {
            std::string ans_key{};
            std::getline(infile, ans_key);
            keys.push_back(ans_key);
        }

        infile.close();

    } else {
        std::cout << "couldn't open file" << std::endl;
        exit(1);
    }

    return keys;

}