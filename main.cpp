#include <iostream>
#include <queue>
#include <map>
#include <climits> // for CHAR_BIT
#include <iterator>
#include <algorithm>

using namespace std;

#include "include/Coder.h"

int main(int argc, char* argv[])
{

    int operationType = 1; ///TODO
    string inputFile = "testToCompress.txt"; ///TODO
    string outputFile = "testToDecompress.txt"; ///TODO

    ///used strategy design template
    HuffmanCoder *huffmanCoder;
    Coder coder(inputFile, outputFile);
    ///TODO
    //Decoder decoder; ///TODO

    if(operationType == 1){
        huffmanCoder = &coder;
    }

    huffmanCoder -> getVocabulary();
    huffmanCoder -> displayVocabulary();
    huffmanCoder -> algorithm();



    return 0;
}
