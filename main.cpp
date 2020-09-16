#include <iostream>
#include "utility.h"
#include "AES.h"

int main() {

    const std::string KEY = "javajavajavajava";
    const std::vector<unsigned int> USER_KEY{KEY.begin(), KEY.end()};

    const std::vector<unsigned int> USER_MSG = fread("../message.txt");

    //for(int x : k) std::cout << (char)x << std::endl;

    AES aes{USER_KEY, USER_MSG};

    return 0;
}

// read char from file, store it in int and convert int to hex