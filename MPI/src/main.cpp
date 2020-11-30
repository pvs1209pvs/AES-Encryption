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
    const int NUM_BLOCKS = 8;

    // Create a text file
    fwrite_random(std::stoi(AES_TYPE)/8, NUM_BLOCKS);

    // Read text and key
    std::vector<std::vector<unsigned int>> input_text = fread_lines("../src/random_message.txt");

    std::cout << input_text.size() << " " << input_text.at(0).size() << std::endl;
    unsigned int text [16*input_text.size()];

    int text_sz = 0;
    for (size_t i = 0; i < input_text.size(); i++) {
        for (size_t j = 0; j < input_text.at(i).size(); j++) {
            text[text_sz++] =  input_text.at(i).at(j);
        }
    }
    
    std::vector<unsigned int> key = fread_chars("../src/key.txt");

    std::pair<unsigned int **, unsigned int **> key_msg = init(key, input_text.at(0), "128");
    std::cout<< hex_mtrx_to_string(encrypt(key_msg.first, key_msg.second)) << std::endl;

    char * encrypted[NUM_BLOCKS];

    int comm_sz;
    int my_rank;
    
    MPI_Init(NULL, NULL);

    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    MPI_Datatype BLOCK;

    int chunk_size = NUM_BLOCKS/4;
    int block_array = 32*(chunk_size);
    
    MPI_Type_contiguous(block_array,MPI_CHAR,&BLOCK);
    MPI_Type_commit(&BLOCK);

    char buffer[block_array];
    int buff_sz;


    std::cout << "chunk " << chunk_size << std::endl;
    std::cout << "block " << block_array << std::endl;



    if (my_rank != 0){

        buff_sz = 0;

        for (int i = (my_rank-1)*chunk_size; i < my_rank*chunk_size ; ++i) {
            buffer[buff_sz++] = text[i];
        }

        std::cout<< my_rank << std::endl;
        for (int k = 0; k <buff_sz ; ++k) {
            std::cout << buffer[k];
        }
//        for (int i=0; i<block_array; i++)
//            buffer[i] = i;
        MPI_Send(buffer, 1, BLOCK, 0, 0, MPI_COMM_WORLD);
    }
    else{

        for (int i = 1; i < comm_sz; i++) {
            MPI_Recv(buffer, 1, BLOCK, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
//            for (int j=0; j<block_array; j++)
//                printf("%dbuffer[%d] = %d\n", i, j, buffer[j]);
        }

        fflush(stdout);
    }


    MPI_Finalize();

    return 0;

}
