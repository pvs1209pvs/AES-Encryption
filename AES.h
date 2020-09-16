#pragma once

#include <string>
#include <vector>

class AES {

private:
    unsigned int** key;
    unsigned int** msg;

    void rot_word(unsigned int * &col);
    void sub_bytes(unsigned int * &col);

public:
    std::vector<unsigned int **> key_schedule;

    AES(const std::vector<unsigned int> &k, const std::vector<unsigned int> &m);
    ~AES();

    unsigned int ** key_gen(unsigned int** parent_key, int round_number);
    std::vector<unsigned int **> key_expansion();

};

