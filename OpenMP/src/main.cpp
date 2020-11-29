#include <iostream>
#include <omp.h>
#include <bits/stdc++.h>
#include <iomanip>
#include <sys/time.h>
#include "AES.h"
#include "utility.h"

/**
 * Group Members are:
 *      Fahad Ansar
 *      Paramvir Singh
 */

void openMP();

int main(int argc, char *argv[])
{
    const int NUM_BLOCKS = std::stoi(argv[1]);
    const int NUM_THREADS = std::stoi(argv[2]);

    // Create a text file
    fwrite_random(std::stoi("128"), NUM_BLOCKS);

    // REad text and key
    std::vector<std::vector<unsigned int>> input_text = fread_lines("../src/random_message.txt");
    std::vector<unsigned int> key = fread_chars("../src/key.txt");

    // Save encrypted blocks in this vector
    std::vector<unsigned int **> encrypted{};
    encrypted.reserve(NUM_BLOCKS);

    for (int i = 0; i < NUM_BLOCKS; i++) 
        encrypted.push_back(nullptr);
    

    // Encryption

    double start = omp_get_wtime();

    #pragma omp parallel for num_threads(NUM_THREADS)
    for (int i = 0; i < input_text.size(); i++){
        std::pair<unsigned int **, unsigned int **> key_msg = init(key, input_text.at(i), "!28");
        encrypted[i] = encrypt(key_msg.first, key_msg.second);
    }

    double end = omp_get_wtime();

    std::cout << NUM_BLOCKS << " blocks by " << NUM_THREADS << " threads done in " << (end - start) << std::fixed << std::setprecision(5) << std::endl;

    input_text.clear();

    std::string e_str = "";
    for (int i = 0; i < NUM_BLOCKS; i++)
        e_str += hex_mtrx_to_string(encrypted[i]);
    fwrite_lines("../src/encrypted.txt", e_str);

    return 0;
}
