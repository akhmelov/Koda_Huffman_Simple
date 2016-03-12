#include <iostream>
#include <queue>
#include <map>
#include <climits> // for CHAR_BIT
#include <iterator>
#include <algorithm>
#include <iostream>

#include "include/ParametersService.h"
#include "include/SimpleCoder.h"
#include "include/SimpleDecoder.h"

using namespace std;

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
    Decoder decoder(parametersService.getInputFileName(), parametersService.getOutputFileName());

    if(parametersService.getOperationType() == 1U){
        huffman = &coder;
    }else if(parametersService.getOperationType() == 2U){
        huffman = &decoder;
    } else {
        cout<< "Unexpected error, type of the coding operation if " << parametersService.getOperationType() << endl;
        exit(-1);
    }

    huffman -> getVocabulary();
    huffman -> displayVocabulary(); //help method
    huffman -> algorithm();
    coder . closeStreams(); ///todo for test only

    decoder . root = huffman -> root;
    decoder . getVocabulary();
    //decoder . displayVocabulary(); //help method
    decoder . algorithm();

    cout << "Entropy: " << huffman -> countEntropy() << endl;
    cout << "(Effectivity) n = " << huffman -> findEffective() << endl;

    return 0;
}
