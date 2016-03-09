#include <iostream>
#include <queue>
#include <map>
#include <climits> // for CHAR_BIT
#include <iterator>
#include <algorithm>
#include <iostream>
#include "include/Coder.h"
#include "include/ParametersService.h"

using namespace std;

#include "include/Coder.h"

int main(int argc, const char* argv[])
{

    ParametersService parametersService;
	parametersService.service(argc, argv);
    cout << "Input file name: " << parametersService.getInputFileName() << endl;
    cout << "Output file name: " << parametersService.getOutputFileName() << endl;
    if(parametersService.getOperationType() == 1U)
        cout << "Program mode: code" << endl;
    else if(parametersService.getOperationType() == 2U)
        cout << "Program mode: decode" << endl;

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
