#include <iostream>
#include <algorithm>
#include <sstream>
#include "utility.h"
#include "AES.h"
#include "Table.h"

int main() {

//    std::cout << std::hex << (0x7eu ^ 0x84u) << std::endl;
//    std::cout << std::endl;

    const std::string PLAIN_TEXT = "javajavajavajava";
    const std::vector<unsigned int> USER_KEY{PLAIN_TEXT.begin(), PLAIN_TEXT.end()};
    const std::vector<unsigned int> USER_MSG = fread("../message.txt");

    AES aes{USER_KEY, USER_MSG};

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

    unsigned int ** round_key = aes.key_gen(key, 0);

    //aes.key_schedule.push_back(aes.key_gen(key, ))
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            std::cout << std::hex << round_key[i][j] << " ";
        }
        std::cout << std::endl;
    }





    return 0;
}

// read char from file, store it in int and convert int to hex