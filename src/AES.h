#pragma once

#include <string>
#include <vector>
#include <map>
#include "Configuration.h"

extern int N;
extern int ROUNDS;

void init(const std::vector<unsigned int> &k, const std::vector<unsigned int> &m, const std::string &type);

void init(unsigned int **&k, const std::vector<unsigned int> &m);

void sub_bytes(unsigned int *const &col);

unsigned int **key_gen(unsigned int **parent_key, int round_number);

void rot_word(unsigned int *&col);

std::vector<unsigned int **> key_expansion();

void substitute_step(unsigned int **const &arr);

void shift_row_step(unsigned int **const &arr);

void mix_step(unsigned int **&arr);

unsigned int mix_step(const unsigned int &x, const unsigned int &mix_no);

unsigned int **add_round_key(const unsigned int **const &a, const unsigned int **const &b);

unsigned int **round(unsigned int **state, unsigned int **round_key);

unsigned int **encrypt();