#pragma once

#include <string>
#include <vector>

class AES {

private:
    unsigned int** key;
    unsigned int** msg;

public:
    AES(const std::vector<unsigned int> &k, const std::vector<unsigned int> &m);
    ~AES();
};

