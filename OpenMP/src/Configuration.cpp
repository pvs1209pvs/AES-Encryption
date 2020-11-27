#include "Configuration.h"

Configuration::Configuration(int p_block_size_bits) : BLOCK_SIZE(p_block_size_bits){
    switch (p_block_size_bits) {
        case 128:{
            N = 4;
            NUM_ROUNDS = 10;
            break;
        }
    }
}
