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

    AES() = default;

    std::vector<unsigned int **> key_expansion();

    bool round(unsigned int **text, unsigned int **key);

    void substitute_step(unsigned int **arr);

    void rotate_step(unsigned int **arr);

    unsigned int overflow_handle(unsigned int x, unsigned int mix_no);

    void mul_mixin_consts(unsigned int **arr);

    unsigned int **add_round_key(unsigned int **a, unsigned int **b);

    unsigned int **get_key();

    unsigned int **get_msg();

};

