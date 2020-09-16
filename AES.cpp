#include <iostream>
#include "AES.h"
#include "utility.h"

AES::AES(const std::vector<unsigned int> &k, const std::vector<unsigned int> &m)  {

    key = (unsigned int**)malloc(sizeof(unsigned int*)*4);
    msg = (unsigned int**)malloc(sizeof(unsigned int*)*4);

    for (int i = 0; i < 4; ++i) {
        key[i] = (unsigned int*)malloc(sizeof(unsigned int*)*4);
        msg[i] = (unsigned int*)malloc(sizeof(unsigned int*)*4);
    }

    col_major_cnstrctn(key, k);
    col_major_cnstrctn(msg, m);

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            std::cout << (char)msg[i][j] << " ";
        }
        std::cout << std::endl;
    }

}

AES::~AES() {
    for (int i = 0; i < 4; ++i) {
        free(key[i]);
        free(msg[i]);
    }
}