#pragma once

#include "AES.h"

void key_expansion_test( std::vector<std::vector<unsigned int **>>  aes_keys);
std::vector<std::string> read_answer_key();