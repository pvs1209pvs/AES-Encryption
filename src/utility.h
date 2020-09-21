#pragma once

#include <vector>
#include <string>

std::vector<unsigned int> fread(const std::string &filename);

void fwrite(std::string filename, std::vector<unsigned int>);

void col_major_cnstrctn(unsigned int **&state, std::vector<unsigned int> text);

unsigned int **mtrx_multplctn(unsigned int **a, unsigned int **b);

unsigned int **mtrx_xor(unsigned int **a, unsigned int **b);

unsigned int *col_xor(unsigned int *a, unsigned int *b);

unsigned int *get_col(unsigned int **state, int col_number);

void set_col(unsigned int **&state, unsigned int *source_col, int col_number);

std::string hex_mtrx_to_string(unsigned int **&input);

unsigned int ** static_to_dynamic(unsigned int source[4][4]);