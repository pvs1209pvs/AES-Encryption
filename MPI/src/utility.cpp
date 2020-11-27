#include <fstream>
#include <iostream>
#include <sstream>
#include <cstring>
#include "utility.h"
#include "AES.h"

/**
 * Reads ascii text from the file.
 * @param filename Name of the file to be read.
 * @param num_bytes Number of bytes to read from the file.
 * @return Vector containing all the ascii text of the file.
 */
std::vector<unsigned int> fread_chars(const std::string &filename) {

    std::ifstream file_reader{filename, std::ios::in};
    std::vector<unsigned int> message{};

    if (file_reader.is_open()) {

        while (!file_reader.eof()) {

            int value = file_reader.get();

            if (value == -1)continue;

            message.push_back(value);

        }

        file_reader.close();

    } else {
        std::cout << "FILE NOT OPENING" << std::endl;
        exit(1);
    }

    return message;

}

std::vector<std::vector<unsigned int>> fread_lines(const std::string &filename) {

    std::vector<unsigned int> text;
    std::vector<std::vector<unsigned int>> block_text;
    std::ifstream infile{filename, std::ios::in};

    if (infile.is_open()) {

        while (!infile.eof()) {
            unsigned int r = (unsigned int) infile.get();
            text.push_back(r);
            if (text.size() == 128) {
                block_text.push_back(text);
                text.clear();
            }
        }

        infile.close();

    } else {
        std::cout << "couldn't open file" << std::endl;
        exit(1);
    }

    return block_text;

}

/*
 * Writes encrypted text to a file 'EncryptedText.txt'
 * @param filename Name of the file to be write.
 * @param encrypted string that will be printed to a file
 * @return boolean which is a confimation flag of success
 *
 * */
bool fwrite_lines(const std::string &fname, std::string encrypted) {

    int sucessFlag = 0;
    std::ofstream fileWriter(fname, std::ios::app);

    if (fileWriter.is_open()) {
        fileWriter << encrypted;
        fileWriter.close();
        sucessFlag = 1;
    }

    return sucessFlag;
}

/**
 *
 * @param bit_blocks Number of 128bit blocks.
 */
void fwrite_random(const int &bit_blocks, const int &block_size) {

    std::ofstream fwriter{"../src/random_message.txt"};

    if (fwriter.is_open()) {

        srand(time(NULL));

        for (int i = 1; i <= bit_blocks * block_size; ++i) {
            fwriter << (char) (rand() % 94 + 32);
            if (i % bit_blocks == 0) {
              //  fwriter << '\n';
            }
        }

        fwriter.close();

    } else {
        std::cout << "fwrite_random error" << std::endl;
    }
}

/**
 * Initializes a 4*4 matrix in a column-major format.
 * @param state 4*4 matrix to be initialized.
 * @param text String that is added to the matrix.
 */
void col_major_cnstrctn(unsigned int **&state, std::vector<unsigned int> text) {

    int text_pntr = 0;

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < 4; ++j) {
            state[j][i] = text.at(text_pntr++);
        }
    }

}


/**
 * Performs xor on columns.
 * @param a First column.
 * @param b Second column.
 * @return Xor of the two columns.
 */
unsigned int *col_xor(unsigned int *a, unsigned int *b) {

    unsigned int *result = (unsigned int *) malloc(sizeof(unsigned int) * 4);

    for (int i = 0; i < 4; ++i) {
        result[i] = a[i] ^ b[i];
    }

    return result;

}

/**
 * Returns the column of the input matrix.
 * @param state Input matrix who column needs to be written.
 * @param col_number Column number that needs to be added.
 * @return Column of the input matrix.
 */
unsigned int *get_col(unsigned int **state, int col_number) {

    unsigned int *col = (unsigned int *) malloc(sizeof(unsigned int) * 4);

    for (int i = 0; i < 4; ++i) {
        col[i] = state[i][col_number];
    }

    return col;

}

/**
 * Sets the column of the state matrix.
 * @param state Input state matrix whose column needs to be created.
 * @param source_col Column that provides the value to create the column of the input matrix.
 * @param col_number Column that needs to be created.
 */
void set_col(unsigned int **&state, unsigned int *source_col, int col_number) {

    for (int i = 0; i < 4; ++i) {
        state[i][col_number] = source_col[i];
    }

}

/**
 * Creates the string representation of state matrix.
 * @param input Input state matrix.
 * @return String representation of the state matrix.
 */
std::string hex_mtrx_to_string(unsigned int **input) {

    if (input == nullptr) {
        return "nullstate";
    }

    std::stringstream ss{};

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < N; ++j) {
            ss << std::hex << input[i][j];
        }
    }

    return ss.str();

}

unsigned int **static_to_dynamic(unsigned int source[4][4]) {

    unsigned int **result = (unsigned int **) malloc(sizeof(unsigned int *) * 4);

    for (int i = 0; i < 4; ++i) {
        result[i] = (unsigned int *) malloc(sizeof(unsigned int) * N);
    }
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < 4; ++j) {
            result[i][j] = source[i][j];
        }
    }

    return result;

}

