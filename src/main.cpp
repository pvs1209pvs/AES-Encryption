#include <iostream>
#include <bitset>
#include "AES.h"
#include "utility.h"

int main(int argc, char *argv[]) {

        std::vector<std::vector<unsigned int>> inputText = fread_lines("../src/message.txt");
        std::vector<unsigned int> key = fread_chars("../src/key.txt");


        for(int i=0; i<inputText.size(); ++i){
            init(key, inputText.at(i), "128");
            fwrite_lines( "../src/EncryptedText.txt" , hex_mtrx_to_string(encrypt()));
        }

        return 0;


}