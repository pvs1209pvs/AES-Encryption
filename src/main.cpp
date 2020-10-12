#include <iostream>
#include <bitset>
#include "AES.h"
#include "AESTest.h"
#include "utility.h"

int main(int argc, char *argv[]) {

    if (argc > 1) {
        return run_tests(argc, argv);
    } else {
        init(fread_chars("../src/key.txt"), fread_chars("../src/message.txt"), "128");
        std::cout << "Encrypted text " << hex_mtrx_to_string(encrypt()) << std::endl;
        return 0;
    }

}