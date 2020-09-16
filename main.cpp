#include <iostream>
#include <algorithm>
#include <sstream>
#include "utility.h"
#include "AES.h"

int main() {

    const std::string PLAIN_TEXT = "javajavajavajava";
    const std::vector<unsigned int> USER_KEY{PLAIN_TEXT.begin(), PLAIN_TEXT.end()};
    const std::vector<unsigned int> USER_MSG = fread("../message.txt");

    unsigned int dummy_key[4][4] = {
            {0x2b, 0x28, 0xab, 0x09},
            {0x7e, 0xae, 0xf7, 0xcf},
            {0x15, 0xd2, 0x15, 0x4f},
            {0x16, 0xa6, 0x88, 0x3c}
    };

    unsigned int **key = (unsigned int **) malloc(sizeof(unsigned int) * 4);
    for (int i = 0; i < 4; ++i) {
        key[i] = (unsigned int *) malloc(sizeof(unsigned int) * 4);
    }

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            key[i][j] = dummy_key[i][j];
        }
    }

    AES aes{key, USER_MSG};
    aes.key_expansion();

    for (int i = 1; i < 11; ++i) {
        std::cout << "Round " << i-1 << std::endl;
        std::cout << console_printer(aes.key_schedule.at(i)) << std::endl;
    }

    return 0;
}

// read char from file, store it in int and convert int to hex