#include "HuffmanSimple.h"

HuffmanSimple::HuffmanSimple(string inputFileName, string outFileName)
{
    inputFile.open(inputFileName.c_str());
    outputFile.open(outFileName.c_str());
}

HuffmanSimple::~HuffmanSimple()
{
    inputFile.close();
    outputFile.close();
}

void HuffmanSimple::displayVocabulary()
{
    cout<<"DISPLAY VOCABULARY ()\n";
}
