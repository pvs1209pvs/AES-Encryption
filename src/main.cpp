#include <iostream>
#include <bitset>
#include "AES.h"
#include "AESTest.h"
#include "utility.h"

int main(int argc, char *argv[]) {

    if (argc > 1) {
        return run_tests(argc, argv);
    } else {

        unsigned int TEST_KEY[4][4] = {{0x54, 0x73, 0x20, 0x67},
                                       {0x68, 0x20, 0x4b, 0x20},
                                       {0x61, 0x6d, 0x75, 0x46},
                                       {0x74, 0x79, 0x6e, 0x75}};

        unsigned int **KEY = static_to_dynamic(TEST_KEY);
        std::vector<unsigned int> F_KEY = fread_chars("../src/key.txt");
        std::vector<unsigned int> MESSAGE = fread_chars("../src/message.txt");

        init(F_KEY, MESSAGE);

        fwrite_random(15);

        std::cout << hex_mtrx_to_string(encrypt()) << std::endl;
        // 29c3505f571420f6402299b31a2d73a

        return 0;
    }

}