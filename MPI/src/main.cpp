#include <iostream>
#include <mpi.h>
#include <bits/stdc++.h>
#include <iomanip>
#include <cstdio>
#include <sys/time.h>
#include "AES.h"
#include "utility.h"

/**
 * TODO: each process' answer is not long enough, fix that.
 * TODO: make master process combine the result of all the slave processes.
 * TODO: make the code work with any number of processes.
 */

/**
 * OpenMPI
 *
 * Group Members are:
 *      Fahad Ansar
 *      Paramvir Singh
 */


int main(int argc, char* argv[]) {
    
    const std::string AES_TYPE = "128";
    const int TOTAL_BLOCKS = 80000;

    // Create a text file, read text and key
    fwrite_random(std::stoi(AES_TYPE)/8, TOTAL_BLOCKS);

    unsigned int * text = fread_lines("../src/random_message.txt");
    std::vector<unsigned int> key = fread_chars("../src/key.txt");

    int comm_sz;
    int my_rank;
    
    MPI_Init(NULL, NULL);

    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    MPI_Datatype BLOCK;

    int chunk_size = TOTAL_BLOCKS/4;
    int num_blocks = 32*(chunk_size); // 32 is max len of a block. num_blocks is number of block to be worked upon by each process.

    MPI_Type_contiguous(num_blocks, MPI_CHAR, &BLOCK);
    MPI_Type_commit(&BLOCK);

    // buffer for sending and receving.
    char buffer[num_blocks];
    int buff_sz;

    std::vector<char[num_blocks]> encrypted{};

    double s = MPI_Wtime();

    if (my_rank != 0){

        buff_sz = 0;

        std::vector<unsigned int> inner_block{};

        for (int i = (my_rank-1)*chunk_size*16; i < my_rank*chunk_size*16 ; ++i) {

            inner_block.push_back(text[i]);
            
            if(inner_block.size()%16==0){

                std::pair<unsigned int **, unsigned int **> key_msg = init(key, inner_block, "128");
                std::string e = hex_mtrx_to_str(encrypt(key_msg.first, key_msg.second));

                for (int i = 0; i < e.size(); ++i){
                    buffer[buff_sz++] = e[i];
                }
 
            }

        }

        // add padding
        while(buff_sz < chunk_size*32){
            buffer[buff_sz++] = ' ';
        }
        std::cout << buff_sz << std::endl;

        //std::cout << my_rank << " Send" << std::endl;
        // for (int i = 0; i < buff_sz; i++){
        //     std::cout << buffer[i];
        // }
        // std::cout << std::endl;
        
        // to save space
        inner_block.clear();
    
        MPI_Send(buffer, 1, BLOCK, 0, 0, MPI_COMM_WORLD);
    }
    else{

        for (int i = 1; i < comm_sz; i++) {
            MPI_Recv(buffer, 1, BLOCK, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            
            //std::cout << i << " Recv " << std::endl;
            for (int i = 0; i < 32; ++i){
                std::cout << buffer[i];
            }
            std::cout << std::endl;

        }

        fflush(stdout);
    }

    double end = MPI_Wtime();

    MPI_Finalize();

    if(my_rank == 0)
        std::cout << end-s << std::endl;

    return 0;

}
