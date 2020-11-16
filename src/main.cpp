#include <iostream>
#include "AES.h"
#include "utility.h"

/**
 * Group Members are
 *      Paramvir Singh
 *      Fahad Ansar
 */

int main() {


    // aes type selector

    std::string aes_type{};
    int aes_type_user_option{};

    do {
        std::cout << "Select AES type" << std::endl;
        std::cout << "(0) - 128 " << std::endl;
        std::cout << "(1) - 192 " << std::endl;
        std::cout << "(2) - 256 " << std::endl;
        std::cin >> aes_type_user_option;
    } while (aes_type_user_option < 0 || aes_type_user_option > 2);

    switch (aes_type_user_option) {
        case 0:
            aes_type = "128";
            break;
        case 1:
            aes_type = "192";
            break;
        case 2:
            aes_type = "256";
            break;
    }


    // input file selector

    int num_blocks{};
    do{
        std::cout << "Enter the number of blocks to be encrypted" << std::endl;
        std::cin >> num_blocks;
    }while(num_blocks < 0);

    fwrite_random(std::stoi(aes_type), num_blocks);


    // read plain text and key

    std::vector<std::vector<unsigned int>> input_text = fread_lines("../src/random_message.txt");
    std::vector<unsigned int> key = fread_chars("../src/key.txt");


    // encryption

    for (auto &text : input_text) {
        init(key, text, aes_type);
        fwrite_lines("../src/encryptedText.txt", hex_mtrx_to_string(encrypt()));
    }

    std::cout << "\nText message encrypted, check encrypted.txt for the encrypted text." << std::endl;

    return 0;

}