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

    ///used strategy design template
    HuffmanSimple *huffman;
    Coder coder(parametersService.getInputFileName(), parametersService.getOutputFileName());
    ///TODO
    //Decoder decoder; ///TODO

    if(parametersService.getOperationType() == 1U){
        huffman = &coder;
    }else if(parametersService.getOperationType() == 2U){
        huffman = &coder;
    } else {
        cout<< "Unexpected error, type of the coding operation if " << parametersService.getOperationType() << endl;
        exit(-1);
    }

    huffman -> getVocabulary();
    huffman -> displayVocabulary(); //help method
    huffman -> algorithm();

    return 0;
}
