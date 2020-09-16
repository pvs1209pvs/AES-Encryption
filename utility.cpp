#include "utility.h"
#include <fstream>
#include <iostream>

std::vector<unsigned int> fread(const std::string& filename){

    std::ifstream file_reader{filename, std::ios::in};
    std::vector<unsigned int> message{};

    if(file_reader.is_open()) {

        while(!file_reader.eof()){
            int value = file_reader.get();
            if(value==-1)continue;
            message.push_back(value);
        }

        file_reader.close();

    }
    else{
        exit(1);
    }

    return message;

}

/**
 * Initializes a 4*4 matrix in a column-major format.
 * @param state 4*4 matrix to be initialized.
 * @param text String that is added to the matrix.
 */
void col_major_cnstrctn(unsigned int ** &state, std::vector<unsigned int> text){

    int text_pntr = 0;

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            state[j][i] = text.at(text_pntr++);
        }
    }

}

unsigned int ** mtrx_xor(unsigned int** a, unsigned int** b){

    unsigned int ** result = (unsigned int**)malloc(sizeof(unsigned int*)*4);

    for (int i = 0; i < 4; ++i) {
        result[0] = (unsigned int*)malloc(sizeof(unsigned int)*4);
    }

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            result[i][j] = a[i][j] ^ b[i][j];
        }
    }

    return result;

}

unsigned int * col_xor(unsigned int* a, unsigned int* b){

    unsigned int * result = (unsigned int*)malloc(sizeof(unsigned int)*4);

    for (int i = 0; i < 4; ++i) {
        result[i] = a[i] ^ b[i];
    }
    return result;

}

unsigned int * get_col(unsigned int ** state,int col_number){

    unsigned int * col = (unsigned int *)malloc(sizeof(unsigned int)*4);

    for (int i = 0; i < 4; ++i) {
        col[i] = state[i][col_number];
    }

    return col;

}

void set_col(unsigned int ** &state, unsigned int * source_col, int col_number){

    for (int i = 0; i < 4; ++i) {
//        if(col_number==0)
//        std::cout << i << "," << col_number << " " << std::hex << source_col[i] << std::endl;
        state[i][col_number] = source_col[i];
    }


}