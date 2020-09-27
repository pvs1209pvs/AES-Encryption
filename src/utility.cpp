#include "utility.h"
#include <fstream>
#include <iostream>
#include <sstream>

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

std::vector<std::string> fread_lines(const std::string &filename, int num_lines) {

    std::vector<std::string> keys;
    std::ifstream infile{filename, std::ios::in};

    if (infile.is_open()) {

        for (int i = 0; i < num_lines; ++i) {
            std::string ans_key{};
            std::getline(infile, ans_key);
            keys.push_back(ans_key);
        }

        infile.close();

    } else {
        std::cout << "couldn't open file" << std::endl;
        exit(1);
    }

    return keys;

}

/**
 * Initializes a 4*4 matrix in a column-major format.
 * @param state 4*4 matrix to be initialized.
 * @param text String that is added to the matrix.
 */
void col_major_cnstrctn(unsigned int **&state, std::vector<unsigned int> text) {

    int text_pntr = 0;

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            state[j][i] = text.at(text_pntr++);
        }
    }

}

unsigned int **mtrx_xor(unsigned int **a, unsigned int **b) {

    unsigned int **result = (unsigned int **) malloc(sizeof(unsigned int *) * 4);

    for (int i = 0; i < 4; ++i) {
        result[0] = (unsigned int *) malloc(sizeof(unsigned int) * 4);
    }

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            result[i][j] = a[i][j] ^ b[i][j];
        }
    }

    return result;

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

    std::stringstream ss;

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            ss << std::hex << input[j][i];
        }
    }

    return ss.str();

}

unsigned int ** static_to_dynamic(unsigned int source[4][4]){

    unsigned int **result = (unsigned int **) malloc(sizeof(unsigned int*) * 4);

    for (int i = 0; i < 4; ++i) {
        result[i] = (unsigned int *) malloc(sizeof(unsigned int) * 4);
    }
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            result[i][j] = source[i][j];
        }
    }

    return result;

}