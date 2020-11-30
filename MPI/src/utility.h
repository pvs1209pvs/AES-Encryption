#pragma once

#include <vector>
#include <string>

std::vector<unsigned int> fread_chars(const std::string &filename);

std::vector<std::vector<unsigned int>> fread_lines(const std::string &filename);

// TODO write the output in char representation or in 64 base.
bool fwrite_lines(const std::string &fname, std::string encrypted);

void fwrite_random(const int &bit_blocks, const int &block_size);

void col_major_cnstrctn(unsigned int **&state, std::vector<unsigned int> text);

unsigned int *col_xor(unsigned int *a, unsigned int *b);

unsigned int *get_col( unsigned int **state,  int col_number);

void set_col(unsigned int **&state, unsigned int *source_col, int col_number);

std::string hex_mtrx_to_str(unsigned int **input);

unsigned int ** static_to_dynamic(unsigned int source[4][4]);