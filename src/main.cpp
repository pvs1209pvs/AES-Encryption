#include <iostream>
#include <bitset>
#include "AES.h"
#include "AESTest.h"
#include "Table.h"
#include "utility.h"
#include "Configuration.h"

int main(int argc, char *argv[]) {

    if (argc > 1) {
        return run_tests(argc, argv);
    } else {

        unsigned int TEST_KEY[4][4] = {{0x54, 0x73, 0x20, 0x67},
                                       {0x68, 0x20, 0x4b, 0x20},
                                       {0x61, 0x6d, 0x75, 0x46},
                                       {0x74, 0x79, 0x6e, 0x75}};

        unsigned int **KEY = static_to_dynamic(TEST_KEY);
        std::vector<unsigned int> MESSAGE = fread_chars("../src/message.txt");

        AES aes(KEY, MESSAGE, Configuration(128, 10));

        std::cout << hex_mtrx_to_string(aes.encrypt()) << std::endl;
        // 29c3505f571420f6402299b31a2d73a

        return 0;
    }


}

// msg = my name is paramvir singh.
// key = javajavajava
// cipher = 8B92802C131422122999E39B713CB4B12E8C646410A03C63534F79A386004C04