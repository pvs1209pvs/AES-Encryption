#pragma once

#include <string>
#include <vector>
#include <map>
#include "Configuration.h"

unsigned int **key_gen(unsigned int **parent_key, int round_number);

void sub_bytes(unsigned int *&col);

void rot_word(unsigned int *&col);

void init(const std::vector<unsigned int> &k, const std::vector<unsigned int> &m);

void init(unsigned int **&k, const std::vector<unsigned int> &m);

std::vector<unsigned int **> key_expansion();

void substitute_step(unsigned int **arr);

void shift_row_step(unsigned int **arr);

void mix_step(unsigned int **&arr);

unsigned int mix_step_helper(unsigned int x, unsigned int mix_no);

unsigned int **add_round_key(unsigned int **a, unsigned int **b);

unsigned int **round(unsigned int **state, unsigned int **round_key);

unsigned int **encrypt();