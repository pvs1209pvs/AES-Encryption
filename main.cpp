#include <iostream>
#include <algorithm>
#include "utility.h"
#include "AES.h"
#include "test.h"

int main() {

    // Initialization starts here.
    const std::string KEY_TEXT = "javajavajavajava";
    const std::vector<unsigned int> USER_KEY{KEY_TEXT.begin(), KEY_TEXT.end()};

    const std::vector<unsigned int> USER_MSG = fread("../message.txt", 16);
    // Initialization ends here.

    // Testing starts here
    // Laid out in col-major format
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
    for (int i = 0; i < 2; ++i) {
        trial_keys.push_back(static_to_dynamic(USER_KEY_ARRAY[i]));
    }

    // Test runs
    std::vector<std::vector<unsigned int **>> expanded_key_schedules{};
    for (int i = 0; i < 2; ++i) {
        AES aes(trial_keys.at(i), USER_MSG, 128);
        expanded_key_schedules.push_back(aes.key_expansion());

    }

    key_expansion_test(expanded_key_schedules);

    // Test ends here

    return 0;
}

// msg = my name is paramvir singh.
// key = javajavajava
// cipher = 8B92802C131422122999E39B713CB4B12E8C646410A03C63534F79A386004C04