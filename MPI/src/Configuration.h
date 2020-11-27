#pragma once

struct Configuration{

    int BLOCK_SIZE;
    int NUM_ROUNDS;
    int N;

    Configuration() = default;
    Configuration(int p_block_size_bits);

};