#include <iostream>
#include <mpi.h>
#include <cmath>
#include <bits/stdc++.h>
#include <iomanip>
#include <cstdio>
#include <string>
#include <sys/time.h>
#include "AES.h"
#include "utility.h"

/**
 * OpenMPI
 * 
 * @compile: 
 *      mpic++ *.cpp
 *
 * @usage:
 *      mpirun --oversubscribe -n <num_processes+1> a.out <total_blocks> <num_processes>
 * 
 * @authors:
 *      Fahad Ansar
 *      Paramvir Singh
 */

int main(int argc, char* argv[]) {

    if(argc < 3){
        std::cout << " Usage: mpirun --oversubscribe -n <num_processes+1> a.out <total_blocks> <num_processes>" << std::endl;
        exit(1);
    }

    const int TOTAL_BLOCKS = std::stoi(argv[1]);
    const int NUM_PROCESSES = std::stoi(argv[2]);
    const int NUM_BYTES = 16;
    const int NUM_BLOCKS = TOTAL_BLOCKS/NUM_PROCESSES;

    fwrite_random(std::stoi("128")/8, TOTAL_BLOCKS);

    unsigned int ** text = fread_lines("../src/random_message.txt");
    std::vector<unsigned int> key = fread_chars("../src/key.txt");

    int comm_sz;
    int my_rank;
    
    MPI_Init(nullptr, nullptr);
    
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    MPI_Datatype Block;
    MPI_Type_contiguous(NUM_BYTES*NUM_BLOCKS, MPI_CHAR, &Block);
    MPI_Type_commit(&Block);

    char * buffer = (char *)malloc(sizeof(char)*NUM_BLOCKS*NUM_BYTES*2);
    int buff_sz = 0;

    std::vector<char> encrypted{};
    encrypted.reserve(TOTAL_BLOCKS);

    double s = MPI_Wtime();

    if (my_rank != 0){

        for (int i = (my_rank-1)*NUM_BLOCKS; i < my_rank*NUM_BLOCKS ; ++i){
            
            std::vector<unsigned int> sub_text(text[i], text[i]+NUM_BYTES);
            std::pair<unsigned int **, unsigned int **> key_msg = init(key, sub_text, "128");
            std::string e_str = hex_mtrx_to_str(encrypt(key_msg.first, key_msg.second));

            while(e_str.size() < NUM_BYTES*2)
                e_str += '\0';
            

            for (int i = 0; i < NUM_BYTES*2; i++)
                buffer[buff_sz++] = e_str[i];   
        
        }

        MPI_Send(buffer, 1, Block, 0, 0, MPI_COMM_WORLD);

    }
    else{

        for (int i = 1; i < comm_sz; i++) {

            MPI_Recv(buffer, 1, Block, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            
            for (int j = 0; j < NUM_BLOCKS*NUM_BYTES*2; j++)
                encrypted.push_back(buffer[j]);
 
        }

    }

    double end = MPI_Wtime();

    if(my_rank == 0)
        std::cout << end-s << std::endl;

    MPI_Finalize();

    return 0;

}