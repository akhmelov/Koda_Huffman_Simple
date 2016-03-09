#include "../include/HuffmanCoder.h"

HuffmanCoder::HuffmanCoder(string inputFileName, string outFileName)
{
    inputFile.open(inputFileName.c_str());
    outputFile.open(outFileName.c_str());
}

HuffmanCoder::~HuffmanCoder()
{
    inputFile.close();
    outputFile.close();
}

void HuffmanCoder::displayVocabulary()
{
    cout<<"DISPLAY VOCABULARY ()\n";
}
