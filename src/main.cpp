#include <iostream>
#include <bitset>
#include "AES.h"
#include "AESTest.h"
#include "utility.h"

int main(int argc, char *argv[]) {


    if (argc > 1) {
        return run_tests(argc, argv);
    } else {


        std::vector<unsigned int> KEY = fread_chars("../src/key.txt");
        std::vector<unsigned int> MESSAGE = fread_chars("../src/message.txt");

        init(KEY, MESSAGE, "128");
        encrypt();

        return 0;
    }

}