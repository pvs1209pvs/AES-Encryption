#include <iostream>
#include <omp.h>
#include "AES.h"
#include "utility.h"

/**
 * Group Members are:
 *      Fahad Ansar
 *      Paramvir Singh
 */

const int NUM_BLOCKS = 200000;
const std::string AES_TYPE = "128";
const int NUM_THREADS = 2;

int main() {

    // text file with random text
    fwrite_random(std::stoi(AES_TYPE), NUM_BLOCKS);


    // read plain text and key

    std::vector<std::vector<unsigned int>> input_text = fread_lines("../src/random_message.txt");
    std::vector<unsigned int> key = fread_chars("../src/key.txt");
   
    std::vector<std::string> encrypted{};
    encrypted.reserve(NUM_BLOCKS);

    for (int i = 0; i < NUM_BLOCKS; i++){
        encrypted.push_back("");
    }
    

    // encryption

    #pragma omp parallel for num_threads(NUM_THREADS)
    for (int i = 0; i < input_text.size(); i++){
        std::pair<unsigned int **, unsigned int **> key_msg = init(key, input_text.at(i), AES_TYPE);
        encrypted[i] = hex_mtrx_to_string(encrypt(key_msg.first, key_msg.second));
    }

    std::cout << "\nEncrypted message saved in encrypted.txt" << std::endl;

    return 0;

}