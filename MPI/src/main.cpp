#include <iostream>
#include <mpi.h>
#include <bits/stdc++.h>
#include <iomanip>
#include <cstdio>
#include <sys/time.h>
#include "AES.h"
#include "utility.h"

/**
 * OpenMPI
 *
 * Group Members are:
 *      Fahad Ansar
 *      Paramvir Singh
 */


int main(int argc, char* argv[]) {

    const std::string AES_TYPE = "128";
    const int NUM_BLOCKS = 4;

    // Create a text file
    fwrite_random(std::stoi(AES_TYPE), NUM_BLOCKS);

    // Read text and key
    std::vector<std::vector<unsigned int>> input_text = fread_lines("../src/random_message.txt");
    std::vector<unsigned int> key = fread_chars("../src/key.txt");

    char * encrypted[NUM_BLOCKS];

    const int MAX_STRING = 96;

    char block_buffer[MAX_STRING];
    int comm_sz;
    int my_rank;


    MPI_Init(NULL, NULL);

    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    if(my_rank != 0){

        std::pair<unsigned int *, unsigned int *> key_msg = init(key, input_text.at(my_rank-1), AES_TYPE);
        std::string s = hex_mtrx_to_string(encrypt(key_msg.first, key_msg.second)).c_str();

        strcpy(block_buffer, s.c_str());

        MPI_Send(block_buffer, strlen(block_buffer)+1, MPI_CHAR, 0, 0, MPI_COMM_WORLD);

    }
    else{

        for (int i = 1; i < comm_sz; ++i){
            MPI_Recv(block_buffer, MAX_STRING, MPI_CHAR, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            encrypted[i-1] = block_buffer;
            printf("%s \n", encrypted[i-1]);
        }

    }


    MPI_Finalize();

    return 0;

}
