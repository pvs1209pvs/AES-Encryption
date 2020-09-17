#pragma once

#include "AES.h"

void key_expansion_test(std::vector<unsigned int **> keys);
std::string seg_to_block(std::vector<unsigned int **> keys);