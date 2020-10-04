#include <algorithm>
#include <iostream>
#include <bitset>
#include "AES.h"
#include "utility.h"
#include "Table.h"

AES::AES(const std::vector<unsigned int> &k, const std::vector<unsigned int> &m, Configuration cfg) : config(cfg) {

    key = (unsigned int **) malloc(sizeof(unsigned int *) * 4);
    msg = (unsigned int **) malloc(sizeof(unsigned int *) * 4);

    for (int i = 0; i < 4; ++i) {
        key[i] = (unsigned int *) malloc(sizeof(unsigned int *) * 4);
        msg[i] = (unsigned int *) malloc(sizeof(unsigned int *) * 4);
    }

    col_major_cnstrctn(key, k);
    col_major_cnstrctn(msg, m);

}

AES::AES(unsigned int **k, const std::vector<unsigned int> &m, Configuration cfg) : key{k}, config(cfg) {

    msg = (unsigned int **) malloc(sizeof(unsigned int *) * 4);

    for (int i = 0; i < 4; ++i) {
        msg[i] = (unsigned int *) malloc(sizeof(unsigned int *) * 4);
    }

    col_major_cnstrctn(msg, m);

}


/**
 * Creates round key for each round.
 *
 * @return User key and keys for each round.
 */
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
 *
 * @param parent_key Round key from the last round.
 * @param round_number Round number.
 * @return Round-key for the next round.
 */
unsigned int **AES::key_gen(unsigned int **parent_key, int round_number) {

    unsigned int **round_key = (unsigned int **) malloc(sizeof(unsigned int *) * 4);
    for (int i = 0; i < 4; ++i) {
        round_key[i] = (unsigned int *) malloc(sizeof(unsigned int) * 4);
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
 * Performs subsitution step on whole year
 *
 * @param array which where this step will be performed
 */
void AES::substitute_step(unsigned int **arr) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            arr[i][j] = sbox[arr[i][j]];
        }
    }
}


/**
 * Performs rotation step on whole array
 *
 * @param array which where this step will be performed
 */
void AES::shift_row_step(unsigned int **arr) {
    for (int i = 0; i < 4; i++) {
        std::rotate(&arr[i][0], &arr[i][0] + i, &arr[i][4]);
    }
}


/**
 * performs Key rounding step of AES
 * @param array 'a' and array 'b'
 * @return XOR of 'a' and 'b'
 */
unsigned int **AES::add_round_key(unsigned int **a, unsigned int **b) {

    unsigned int **result = (unsigned int **) malloc(sizeof(unsigned int *) * 4);

    for (int i = 0; i < 4; ++i) {
        result[i] = (unsigned int *) malloc(sizeof(unsigned int) * 4);
    }

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            result[i][j] = a[i][j] ^ b[i][j];
        }
    }

    return result;

}

/**
 * Performs Mixing step of AES
 *
 * @param array on which mixing needs to be performed
 *
 * */
void AES::mix_step(unsigned int **&arr) {

    unsigned int **new_state = (unsigned int **) malloc(sizeof(unsigned int *) * 4);
    for (int i = 0; i < 4; ++i) {
        new_state[i] = (unsigned int *) malloc(sizeof(unsigned int) * 4);
    }

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            new_state[j][i] = 0x0;
        }
    }

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            std::bitset<8> bins[4];
            for (int k = 0; k < 4; ++k) {
                bins[k] = std::bitset<8>{mix_step_helper(mix[i][k], arr[k][j])};
            }
            new_state[i][j] = (unsigned int) ((bins[0] ^ bins[1] ^ bins[2] ^ bins[3]).to_ulong());
        }
    }

    arr = new_state;

}

/**
 * Performs core functions of mixing step
 *
 * @param first int to perform calculations
 * @param second int perform calculations
 */
unsigned int AES::mix_step_helper(unsigned int mix_no, unsigned int x) {

    unsigned int result = x;

    switch (mix_no) {
        case 1: {
            result = x;
            break;
        }
        case 2: {
            result = x << 1;
            if (std::bitset<8>{x}[7]) {
                result = result ^ 0x1b;
            }
            break;
        }
        case 3: {
            std::bitset<8> b{std::bitset<8>{x}.to_string()};
            std::bitset<8> result_b{b << 1};
            if (b[7]) {
                result_b = result_b ^ std::bitset<8>{"00011011"};
            }
            result_b = result_b ^ b;
            result = (unsigned int) result_b.to_ulong();
            break;
        }
    }

    return result;
}

/**
 * one complete round of AES encryption
 * @param state on which round will be ran
 * @param key to use for current round number
 */
unsigned int **AES::round(unsigned int **state, unsigned int **round_key) {

    substitute_step(state);
    shift_row_step(state);
    mix_step(state);
    state = add_round_key(state, round_key);

    return state;

}


unsigned int **AES::get_key() {
    return key;
}

unsigned int **AES::get_msg() {
    return msg;
}

unsigned int ** AES::encrypt() {

    // key expansion
    std::vector<unsigned int **> key_schedule = key_expansion();

    // initial round
    unsigned int **encrypt_state = add_round_key(get_key(), get_msg());

    // round 0 t0 9
    for (int i = 1; i < config.NUM_ROUNDS; ++i) {
        encrypt_state = round(encrypt_state, key_schedule.at(i));
    }

    // last round
    substitute_step(encrypt_state);
    shift_row_step(encrypt_state);
    encrypt_state = add_round_key(encrypt_state, key_schedule.at(10));

    // encrypted text
    return encrypt_state;

}





