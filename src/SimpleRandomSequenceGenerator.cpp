#include "SimpleRandomSequenceGenerator.h"
#include <fstream>
using namespace std;

RandomSequenceGenerator::RandomSequenceGenerator(unsigned int numOfCharsInAlphabet, unsigned int sequenceLength, const std::string& outputFileName) : numOfCharsInAlphabet_(numOfCharsInAlphabet), sequenceLength_(sequenceLength), outputFileName_(outputFileName){}

int RandomSequenceGenerator::generateRandomSequence()
{
    ofstream ofile(outputFileName_.c_str());
    for(unsigned int i = 0U; i != sequenceLength_; ++i)
    {
        unsigned int randomNumber = rand() % (numOfCharsInAlphabet_ );
        char ch = 'a'+randomNumber;
        ofile << ch;
    }
    ofile.close();
    return 0;
}
