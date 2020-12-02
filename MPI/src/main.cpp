#include <iostream>
#include <mpi.h>
#include <cmath>
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
    const int TOTAL_BLOCKS = 4;

    // Create a text file, read text and key
    fwrite_random(std::stoi(AES_TYPE)/8, TOTAL_BLOCKS);

    unsigned int ** text = fread_lines("../src/random_message.txt");
    std::vector<unsigned int> key = fread_chars("../src/key.txt");

    int comm_sz;
    int my_rank;
    
    MPI_Init(NULL, NULL);

    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);


    int num_blocks = TOTAL_BLOCKS/4;


    MPI_Datatype BLOCK;
    MPI_Type_contiguous(16*num_blocks, MPI_UNSIGNED, &BLOCK);
    MPI_Type_commit(&BLOCK);

    char * buffer = (char *)malloc(sizeof(char)*num_blocks*32);
    int buff_sz = 0;

//     double s = MPI_Wtime();

    if (my_rank != 0){

        for (int i = (my_rank-1)*num_blocks; i < my_rank*num_blocks ; ++i){
            
            std::vector<unsigned int> sub_text(text[i], text[i]+16);
            std::pair<unsigned int **, unsigned int **> key_msg = init(key, sub_text, "128");
            std::string e_str = hex_mtrx_to_str(encrypt(key_msg.first, key_msg.second));

            while(e_str.size() < 32){
                e_str += '\0';
            }

            for (int i = 0; i < 32; i++){
                buffer[buff_sz] = e_str[i];
                buff_sz++;
            }
        
        }

        // for (int i = 0; i < 32*num_blocks; i++){
        //     std::cout << std::hex << buffer[i];
        // }
        // std::cout << std::endl;
        
        MPI_Send(buffer, 1, BLOCK, 0, 0, MPI_COMM_WORLD);

    }
    else{

        for (int i = 1; i < comm_sz; i++) {
            MPI_Recv(buffer, 1, BLOCK, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            for (int j = 0; j < num_blocks*32; j++){
                std::cout << buffer[j];
            }
            std::cout << std::endl;
            
        }

     
    }

//     double end = MPI_Wtime();

     MPI_Finalize();

    return 0;

}
