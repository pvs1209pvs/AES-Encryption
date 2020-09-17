#include <fstream>
#include <iostream>
#include <sstream>
#include <utility>
#include <stdlib.h>
#include "test.h"
#include "utility.h"

void key_expansion_test(std::vector<std::vector<unsigned int **>> aes_keys) {

    std::vector<std::string> answer_keys = read_answer_key();

    for (int i = 0; i < 2; ++i) {

        std::stringstream ss;
        for (int j = 0; j < aes_keys.at(i).size(); ++j) {
            ss << hex_mtrx_to_string(aes_keys.at(i).at(j));
        }

        if (answer_keys.at(i) == ss.str()) {
            printf("%c[%dm Key Expansion Test %d PASSED\n", 0x1B, 32, i);
        } else {
            printf("%c[%dm Key Expansion Test %d FAILED\n", 0x1B, 31, i);
        }

    }

}

std::vector<std::string> read_answer_key() {

    std::vector<std::string> keys;
    std::ifstream infile{"../correct_key_expansion_test_file.txt", std::ios::in};

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