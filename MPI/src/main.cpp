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
    const int TOTAL_BLOCKS = 12;

    // Create a text file, read text and key
    fwrite_random(std::stoi(AES_TYPE)/8, TOTAL_BLOCKS);

    std::vector<std::vector<unsigned int>> input_text = fread_lines("../src/random_message.txt");
    std::vector<unsigned int> key = fread_chars("../src/key.txt");
 

    // in 1d form
    unsigned int text[16*input_text.size()];

    int text_sz = 0;
    for (size_t i = 0; i < input_text.size(); i++) {
        for (size_t j = 0; j < input_text.at(i).size(); j++) {
            text[text_sz++] =  input_text.at(i).at(j);
        }
    }

    int comm_sz;
    int my_rank;
    
    MPI_Init(NULL, NULL);

    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    MPI_Datatype BLOCK;


    // chunksize given to each thread.
    int chunk_size = TOTAL_BLOCKS/4;
    // total number of chunk size.
    int num_blocks = 32*(chunk_size); // 32 is max len of a block. num_blocks is number of block to be worked upon by each process.

    // our derived data type that is array of chars.
    MPI_Type_contiguous(num_blocks, MPI_CHAR, &BLOCK);
    MPI_Type_commit(&BLOCK);

    // buffer for sending and receving.
    char buffer[num_blocks];
    int buff_sz;

    double s = MPI_Wtime();

    if (my_rank != 0){

        buff_sz = 0;

        // text = multiple inner block
        // inner block = block of text to be encrypted by AES
        std::vector<unsigned int> inner_block{};

        // load distribution amongst processes
        // start of that process' sub array, end of that sub array, increment
        for (int i = (my_rank-1)*chunk_size*16; i < my_rank*chunk_size*16 ; ++i) {

            inner_block.push_back(text[i]);
            
            // one chunk is ready, extract all blocks
            if(inner_block.size()%16==0){

                // encryption
                std::pair<unsigned int **, unsigned int **> key_msg = init(key, inner_block, "128");
                std::string e = hex_mtrx_to_str(encrypt(key_msg.first, key_msg.second));

                // added encrypted text to buffer
                for (int i = 0; i < e.size(); ++i){
                    buffer[buff_sz++] = e[i];
                }

                
            }

        }

        // add padding
        while(buff_sz < chunk_size*32){
            buffer[buff_sz++] = ' ';
        }

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
