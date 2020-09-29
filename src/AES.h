#pragma once

#include <string>
#include <vector>
#include <map>

#define BLOCK_SIZE 128

class AES {

private:
    unsigned int **key;
    unsigned int **msg;

    unsigned int **key_gen(unsigned int **parent_key, int round_number);

    void sub_bytes(unsigned int *&col);

    void rot_word(unsigned int *&col);

public:
    AES(const std::vector<unsigned int> &k, const std::vector<unsigned int> &m);

    AES(unsigned int **k, const std::vector<unsigned int> &m);

    std::vector<unsigned int **> key_expansion();

    unsigned int **get_key();

    unsigned int **get_msg();

};

