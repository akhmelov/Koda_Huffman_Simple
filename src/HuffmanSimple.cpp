#include "../include/HuffmanSimple.h"

#include <math.h>

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

double HuffmanSimple::countEntropy()
{
    double entropy = 0.0;
    map<char, unsigned int> charHistogramMap;
    typedef std::istreambuf_iterator<char> buf_iter;
    unsigned int numOfChars = 0U;
    for(buf_iter i(inputFile), e; i != e; ++i)
    {
        ++numOfChars;
        char c = *i;
        if(charHistogramMap.find(c) == charHistogramMap.end())
        {
            charHistogramMap.insert(pair<char, unsigned int>(c,1));
        }
        else
        {
            ++(charHistogramMap.find(c)->second);
        }
    }
    for(map<char, unsigned int>::const_iterator it = charHistogramMap.begin(); it != charHistogramMap.end(); ++it)
    {
        double propability = (double)it->second / (double)numOfChars;
        double tmpEntropy = propability * log(propability);     //logarytm o podstawie 2, nie wiem czy na pewno 2???
        entropy -= tmpEntropy;
    }
    return entropy;
}
