#pragma once

struct Configuration{

    int BLOCK_SIZE;
    int NUM_ROUNDS;

    Configuration() = default;
    Configuration(int p_block_size_bits, int p_num_rounds);

};