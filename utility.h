#pragma once

#include <vector>
#include <string>

std::vector<unsigned int> fread(const std::string& filename);
void fwrite(std::string filename, std::vector<unsigned int>);

void col_major_cnstrctn(unsigned int ** &state, std::vector<unsigned int> text);

unsigned int** mtrx_multplctn(unsigned int ** a, unsigned int ** b);
unsigned int ** mtrx_xor(unsigned int** a, unsigned int** b);