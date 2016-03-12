#include "../include/HuffmanSimple.h"

HuffmanSimple::HuffmanSimple(string inputFileName, string outFileName):
                        inputFileName(inputFileName), outFileName(outFileName)
{

}

HuffmanSimple::~HuffmanSimple()
{
    ///delete root;  ///Uncomment!!!!!!
}

void HuffmanSimple::displayVocabulary()
{
    for (HuffCodeMap::const_iterator it = codes.begin(); it != codes.end(); ++it)
    {
        cout << it->first << " ";
        cout << "[" << (int)it->first << "] ";
        copy(it -> second.begin(), it -> second.end(), ostream_iterator<bool>(cout));
        cout << std::endl;
    }
}
