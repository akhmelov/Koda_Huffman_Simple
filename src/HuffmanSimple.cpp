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
    for (HuffCodeMap::const_iterator it = codes.begin(); it != codes.end(); ++it)
    {
        cout << it->first << " ";
        copy(it->second.begin(), it->second.end(), ostream_iterator<bool>(cout));
        cout << std::endl;
    }
}
