#include <iostream>
#include <algorithm>
#include <utility>
#include <bitset>
#include <z3.h>
#include "AES.h"
#include "utility.h"
#include "Table.h"

AES::AES(const std::vector<unsigned int> &k, const std::vector<unsigned int> &m, int bs) : BLOCK_SIZE{bs},
                                                                                           round_wrt_block_size{} {

    round_wrt_block_size.insert(std::make_pair(128, 10));
    round_wrt_block_size.insert(std::make_pair(192, 12));
    round_wrt_block_size.insert(std::make_pair(256, 14));

    key = (unsigned int **) malloc(sizeof(unsigned int *) * 4);
    msg = (unsigned int **) malloc(sizeof(unsigned int *) * 4);

    for (int i = 0; i < 4; ++i) {
        key[i] = (unsigned int *) malloc(sizeof(unsigned int *) * 4);
        msg[i] = (unsigned int *) malloc(sizeof(unsigned int *) * 4);
    }

    col_major_cnstrctn(key, k);
    col_major_cnstrctn(msg, m);

//    for (int i = 0; i < 4; ++i) {
//        for (int j = 0; j < 4; ++j) {
//            std::cout << std::hex << key[i][j] << std::endl;
//        }
//    }
}

AES::AES(unsigned int **k, const std::vector<unsigned int> &m, int bs) : BLOCK_SIZE{bs}, key{k},
                                                                         round_wrt_block_size{} {

    round_wrt_block_size.insert(std::make_pair(128, 10));
    round_wrt_block_size.insert(std::make_pair(192, 12));
    round_wrt_block_size.insert(std::make_pair(256, 14));


    msg = (unsigned int **) malloc(sizeof(unsigned int *) * 4);

    for (int i = 0; i < 4; ++i) {
        msg[i] = (unsigned int *) malloc(sizeof(unsigned int *) * 4);
    }

    col_major_cnstrctn(msg, m);

}

std::vector<unsigned int **> AES::key_expansion() {

    std::vector<unsigned int **> round_keys{};

    round_keys.push_back(key);

    for (int i = 0; i < round_wrt_block_size.at(BLOCK_SIZE); ++i) {
        round_keys.push_back(key_gen(round_keys.at(i), i));
    }

    return round_keys;

}

/**
 * Generates next round-key from the last round-key.
 * @param parent_key Round key from the last round.
 * @param round_number Round number.
 * @return Round-key for the next round.
 */

unsigned int **AES::key_gen(unsigned int **parent_key, int round_number) {

    unsigned int **round_key = (unsigned int **) malloc(sizeof(unsigned int) * 4);
    for (int i = 0; i < 4; ++i) {
        round_key[i] = (unsigned int *) calloc(4, sizeof(unsigned int));
    }

    // rotates the last column from the parent key in the upwards/left direction
    unsigned int *last_col = get_col(parent_key, 3);
    rot_word(last_col);

    // substitution from the sbox table
    sub_bytes(last_col);

    // 0 col of round key
    // parent key ^ round key ^ rcon
    set_col(round_key, col_xor(rcon[round_number], col_xor(get_col(parent_key, 0), last_col)), 0);

    // 1,2,3 col of round key
    for (int i = 1; i < 4; ++i) {
        set_col(round_key, col_xor(get_col(round_key, i - 1), get_col(parent_key, i)), i);
    }

    return round_key;

}

/**
 * Rotate the word upwards/leftwards.
 *
 * @param col word to be rotated upwards/leftwards.
 */
void AES::rot_word(unsigned int *&col) {
    std::rotate(&col[0], &col[0] + 1, &col[4]);
}

/**
 * Performs sbox substitution.
 *
 * @param col Word on which sbox substitution needs be carried out.
 */
void AES::sub_bytes(unsigned int *&col) {
    for (int i = 0; i < 4; ++i) {
        col[i] = sbox[col[i]];
    }
}

unsigned int **AES::get_key() {
    return key;
}

unsigned int **AES::get_msg() {
    return msg;
}

int AES::get_BLOCK_SIZE() {
    return this->BLOCK_SIZE;
}

std::map<int, int> AES::get_round_wrt_block_size() {
    return this->round_wrt_block_size;
}



/**
 * performs subsitution step on whole year
 *
 * @param array which where this step will be performed
 * */
void AES::substitute_step(unsigned int **&arr){
    for(int i=0; i<4; i++){
        for (int j = 0; j <4 ; j++) {
            arr[i][j] = sbox[arr[i][j]];
        }
    }
}

/**
 * performs rotation step on whole array
 *
 * @param array which where this step will be performed
 * */
void AES::rotate_step(unsigned int **&arr){
    for(int i=0; i<4; i++){
            std::rotate(&arr[i][0], &arr[i][0] + i, &arr[i][4]);
    }
}






/*
 * performs Key rounding step of AES
 *
 * @param array 'a' and array 'b'
 * @return XOR of 'a' and 'b'
 *
 * */
unsigned int** AES::key_rounding(unsigned int **a, unsigned int **b) {

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



/*
 * performs Mixing step of AES

 * @param array on which mixing needs to be performed
 *
 * */
void AES::mul_mixin_consts(unsigned int** &arr) {


}

/*
 * one complete round of AES encryption
 * @param text on which round will be ran
 * @param key to use for current round number
 *
 * */
bool AES::round_AES(unsigned int** &text, unsigned int** key){

   substitute_step(text);
   mul_mixin_consts(text);
   rotate_step(text);
   text = key_rounding(text, key);

   return true;
}
