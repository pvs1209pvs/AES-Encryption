#include "AESTest.h"
#include "Table.h"

int main(int argc, char *argv[]) {

    if(argc > 1){
        return run_tests(argc, argv);
    }
    else{
        return 0;
    }



}

// msg = my name is paramvir singh.
// key = javajavajava
// cipher = 8B92802C131422122999E39B713CB4B12E8C646410A03C63534F79A386004C04