#include <algorithm>

#include <utility>
#include <bitset>
#include "AES.h"
#include "utility.h"
#include "Table.h"

AES::AES(const std::vector<unsigned int> &k, const std::vector<unsigned int> &m) {


    key = (unsigned int **) malloc(sizeof(unsigned int *) * 4);
    msg = (unsigned int **) malloc(sizeof(unsigned int *) * 4);

    for (int i = 0; i < 4; ++i) {
        key[i] = (unsigned int *) malloc(sizeof(unsigned int *) * 4);
        msg[i] = (unsigned int *) malloc(sizeof(unsigned int *) * 4);
    }

    col_major_cnstrctn(key, k);
    col_major_cnstrctn(msg, m);

}

AES::AES(unsigned int **k, const std::vector<unsigned int> &m) : key{k}{


    msg = (unsigned int **) malloc(sizeof(unsigned int *) * 4);

    for (int i = 0; i < 4; ++i) {
        msg[i] = (unsigned int *) malloc(sizeof(unsigned int *) * 4);
    }

    col_major_cnstrctn(msg, m);

}

std::vector<unsigned int **> AES::key_expansion() {

    std::vector<unsigned int **> round_keys{};

    round_keys.push_back(key);

    for (int i = 0; i < 10; ++i) {
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

/**
 * performs subsitution step on whole year
 *
 * @param array which where this step will be performed
 * */
void AES::substitute_step(unsigned int **arr){
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
void AES::rotate_step(unsigned int **arr){
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
unsigned int** AES::add_round_key(unsigned int **a, unsigned int **b) {

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
void AES::mix_step(unsigned int** arr) {

    for(int i = 0; i<4; i++) {
        for (int j = 0; j < 4; j++) {
            for(int k = 0; k<4; k++) {
                unsigned int temp = overflow_handle(mix[k][j],arr[i][k]);
                arr[i][j] ^= temp;
            }
        }
    }
}

/*
 * performs core functions of mixing step

 * @param first int to perform calculations
 * @param second int perform calculations
 *
 * */
unsigned int mix_step_helper(unsigned int x, unsigned int mix_no){

    if(mix_no==1){
        return x;
    }else if(mix_no==2){
        return x<<1 ^ 0x1b;
    } else if(mix_no==3){
        int oldX = x;
        return x<<1 ^ 0x1b ^ oldX;
    }
}

/*
 * one complete round of AES encryption
 * @param text on which round will be ran
 * @param key to use for current round number
 *
 * */
bool AES::round(unsigned int** text, unsigned int** key){

   substitute_step(text);
   rotate_step(text);
   mul_mixin_consts(text);
   text = add_round_key(text, key);

   return true;
}


unsigned int **AES::get_key() {
    return key;
}

unsigned int **AES::get_msg() {
    return msg;
}


unsigned int AES::overflow_handle(unsigned int x, unsigned int mix_no) {
    return 0;
}

