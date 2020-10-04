#pragma once

#include <string>
#include <vector>
#include <map>

#include "Configuration.h"

class AES {

private:
    unsigned int **key;
    unsigned int **msg;
    Configuration config;

    unsigned int **key_gen(unsigned int **parent_key, int round_number);

    void sub_bytes(unsigned int *&col);

    void rot_word(unsigned int *&col);


public:
    AES(const std::vector<unsigned int> &k, const std::vector<unsigned int> &m, Configuration cfg);

    AES(unsigned int **k, const std::vector<unsigned int> &m, Configuration cfg);

    AES() = default;

    std::vector<unsigned int **> key_expansion();

    void substitute_step(unsigned int **arr);

    void shift_row_step(unsigned int **arr);

    void mix_step(unsigned int **&arr);

    unsigned int mix_step_helper(unsigned int x, unsigned int mix_no);

    unsigned int **add_round_key(unsigned int **a, unsigned int **b);

    unsigned int** round(unsigned int **state, unsigned int **round_key);

    unsigned int **get_key();

    unsigned int **get_msg();

};

