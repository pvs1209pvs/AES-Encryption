#pragma once

#include <string>
#include <vector>
#include <map>

class AES {

private:
    unsigned int **key;
    unsigned int **msg;
    const int BLOCK_SIZE; // in bits
    std::map<int, int> round_wrt_block_size; // number of rounds wrt to block size

    unsigned int **key_gen(unsigned int **parent_key, int round_number);

    void sub_bytes(unsigned int *&col);

    void rot_word(unsigned int *&col);

public:
    AES(const std::vector<unsigned int> &k, const std::vector<unsigned int> &m, int bs);

    AES(unsigned int **k, const std::vector<unsigned int> &m, int bs);

    std::vector<unsigned int **> key_expansion();

    unsigned int **get_key();

    unsigned int **get_msg();

    int get_BLOCK_SIZE();

    std::map<int, int> get_round_wrt_block_size();

    void substituteStep();

    void rotateStep();

    void MixStep();

    void key_round_step();

    void substitute_step(unsigned int **&arr);

    void rotate_step(unsigned int **&arr);

    unsigned int **mix_step(unsigned int **a, unsigned int **b);

    unsigned int **key_rounding(unsigned int **a, unsigned int **b);

    unsigned int overflow_handle(unsigned int x, unsigned int mixNo);

    void mul_mixin_consts(unsigned int **&arr);

    bool round_AES(unsigned int **&text, unsigned int **key);
};

