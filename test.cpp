#include <fstream>
#include <iostream>
#include <sstream>
#include <utility>
#include "test.h"
#include "utility.h"

#define RED_COLOR "\033[1;31m \u001b[1m"
#define GREEN_COLOR "\u001b[32m \u001b[1m"
#define RESET_COLOR "\033[0m \u001b[1m"

void key_expansion_test(std::vector<unsigned int **> keys) {

    std::string aes_key_expns = seg_to_block(std::move(keys));
    aes_key_expns = aes_key_expns.substr(0, aes_key_expns.length()-1);

    std::string file_keys{};
    std::ifstream infile{"../correct_key_expansion_test_file.txt", std::ios::in};

    if (infile.is_open()) {
        std::getline(infile, file_keys);
        infile.close();
    } else {
        std::cout << "file not opening" << std::endl;
        exit(1);
    }

    if(aes_key_expns == file_keys ){
        printf(GREEN_COLOR "Key Expansion PASSED" RESET_COLOR);
    }
    else{
        printf(RED_COLOR "Key Expansion FAILED" RESET_COLOR);
    }

}

std::string seg_to_block(std::vector<unsigned int **> keys) {

    std::stringstream block{};

    for (int i = 1; i < keys.size(); ++i) {
        unsigned int **round_key = keys.at(i);
        block << console_printer(round_key);
    }

    return block.str();

}