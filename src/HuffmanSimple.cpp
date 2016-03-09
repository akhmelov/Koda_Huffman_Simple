#include "../include/HuffmanSimple.h"

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
    for (HuffCodeMap::const_iterator it = codes.begin(); it != codes.end(); ++it)
    {
        std::cout << it->first << " ";
        std::copy(it->second.begin(), it->second.end(),
                  std::ostream_iterator<bool>(std::cout));
        std::cout << std::endl;
    }
}
