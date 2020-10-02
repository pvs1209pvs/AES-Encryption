#include <iostream>
#include "AES.h"
#include "AESTest.h"
#include "Table.h"
#include "utility.h"
#include "Configuration.h"

int main(int argc, char *argv[]) {

    int x = 7;
    x = x << 1;
    //std::cout << std::hex << x << std::endl;

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

//        std::cout << hex_mtrx_to_string(aes.get_key()) << std::endl;
//        std::cout << hex_mtrx_to_string(aes.get_msg()) << std::endl;

        std::vector<unsigned int **> key_schedule = aes.key_expansion();

        unsigned int **state = aes.add_round_key(aes.get_key(), aes.get_msg());

        aes.round(state, key_schedule.at(1));

        return 0;
    }


}

// msg = my name is paramvir singh.
// key = javajavajava
// cipher = 8B92802C131422122999E39B713CB4B12E8C646410A03C63534F79A386004C04