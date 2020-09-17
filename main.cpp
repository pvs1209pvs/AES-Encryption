#include <iostream>
#include <algorithm>
#include "utility.h"
#include "AES.h"
#include "test.h"

int main() {

    // Initialization starts here.
    const std::string KEY_TEXT = "javajavajavajava";
    const std::vector<unsigned int> USER_KEY{KEY_TEXT.begin(), KEY_TEXT.end()};

    const std::vector<unsigned int> USER_MSG = fread("../message.txt");

    unsigned int dummy_key[4][4] = {
            {0x2b, 0x28, 0xab, 0x09},
            {0x7e, 0xae, 0xf7, 0xcf},
            {0x15, 0xd2, 0x15, 0x4f},
            {0x16, 0xa6, 0x88, 0x3c}
    };

    unsigned int **trial_key = (unsigned int **) malloc(sizeof(unsigned int) * 4);
    for (int i = 0; i < 4; ++i) {
        trial_key[i] = (unsigned int *) malloc(sizeof(unsigned int) * 4);
    }
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            trial_key[i][j] = dummy_key[i][j];
        }
    }

    // Initialization ends here.

    // with trial key
    AES aes{trial_key, USER_MSG, 128};
    AES aes1{USER_KEY, USER_MSG, 128};

    key_expansion_test(aes.key_expansion());
    return 0;
}

// read char from file, store it in int and convert int to hex