#pragma once

#include <string>
#include <vector>
#include <map>

class AES {

private:
    unsigned int **key;
    unsigned int **msg;
    const int BLOCK_SIZE; // in bits
    std::map<int, int> round_wrt_block_size;

    unsigned int **key_gen(unsigned int **parent_key, int round_number);

    void sub_bytes(unsigned int *&col);

    void rot_word(unsigned int *&col);

public:
    AES(const std::vector<unsigned int> &k, const std::vector<unsigned int> &m, int bs);

    AES(unsigned int **k, const std::vector<unsigned int> &m, int bs);

    std::vector<unsigned int **> key_expansion();

    unsigned int **get_key();

    unsigned int **get_msg();
};

