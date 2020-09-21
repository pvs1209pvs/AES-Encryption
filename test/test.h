#pragma once

#include "AES.h"

void run_test();
void key_expansion_matching(std::vector<std::vector<unsigned int **>>  aes_keys);
std::vector<std::string> read_answer_key();