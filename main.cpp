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
#include "include/SimpleRandomSequenceGenerator.h"
#include "include/SimpleNormalSequenceGenerator.h"



using namespace std;

int main(int argc, const char* argv[])
{

    ParametersService parametersService;
	parametersService.service(argc, argv);

    cout << "Parameters specified by user:" << endl;
    if(parametersService.getOperationType() == 1U)
        cout << "\tProgram mode: code" << endl;
    else if(parametersService.getOperationType() == 2U)
        cout << "\tProgram mode: decode" << endl;
    else if(parametersService.getOperationType() == 3U)
        cout << "\tProgram mode: generate random sequence" << endl;
    cout << "\tInput file name: " << parametersService.getInputFileName() << endl;
    cout << "\tOutput file name: " << parametersService.getOutputFileName() << endl;
    cout << "\tSequence length: " << parametersService.getSequenceLength() << endl;
    cout << "\tNum of chars in alphabet: " << parametersService.getNumOfCharsInAlphabet() << endl;
    cout << "\tMean: " << parametersService.getMean() << endl;
    cout << "\tStandard deviation: " << parametersService.getStdDev() << endl << endl;




    ///used strategy design template
    HuffmanSimple *huffman;
    Coder coder(parametersService.getInputFileName(), parametersService.getOutputFileName());
    Decoder decoder(parametersService.getInputFileName(), parametersService.getOutputFileName());
    RandomSequenceGenerator randomSequenceGenerator(parametersService.getNumOfCharsInAlphabet(), parametersService.getSequenceLength(), parametersService.getOutputFileName());
    NormalSequenceGenerator normalSequenceGenerator(parametersService.getSequenceLength(), parametersService.getOutputFileName(), parametersService.getMean(), parametersService.getStdDev());


    if(parametersService.getOperationType() == 1U){
        huffman = &coder;
    }else if(parametersService.getOperationType() == 2U){
        huffman = &decoder;
    }else if(parametersService.getOperationType() == 3U){
        return randomSequenceGenerator.generateRandomSequence();
    }else if(parametersService.getOperationType() == 4U){
        return normalSequenceGenerator.generateNormalSequence();
    } else {
        cout<< "Unexpected error, type of the operation is " << parametersService.getOperationType() << endl;
        exit(-1);
    }

    huffman -> getVocabulary();
    huffman -> displayVocabulary(); //help method
    huffman -> algorithm();

    cout << "Entropy: " << huffman -> countEntropy() << endl;
    cout << "(Effectivity) n = " << huffman -> findEffective() << endl;

    return 0;
}
