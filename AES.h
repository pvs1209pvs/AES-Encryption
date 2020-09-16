#pragma once

#include <string>
#include <vector>

class AES {

private:
    unsigned int** key;
    unsigned int** msg;


public:
    std::vector<unsigned int **> key_schedule;

    AES(const std::vector<unsigned int> &k, const std::vector<unsigned int> &m);
    AES(unsigned int ** k, const std::vector<unsigned int> &m);
    ~AES();

    void key_expansion();
    unsigned int ** key_gen(unsigned int** parent_key, int round_number);
    void sub_bytes(unsigned int * &col);
    void rot_word(unsigned int * &col);

};

