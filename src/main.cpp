#include "AES.h"
#include "utility.h"

int main() {

        std::vector<std::vector<unsigned int>> input_text = fread_lines("../src/message.txt");
        std::vector<unsigned int> key = fread_chars("../src/key.txt");

        for(auto & text : input_text){
            init(key, text, "128");
            fwrite_lines( "../src/encryptedText.txt" , hex_mtrx_to_string(encrypt()));
        }

        return 0;

}