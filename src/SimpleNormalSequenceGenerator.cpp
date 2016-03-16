#include "SimpleNormalSequenceGenerator.h"
#include <fstream>
#include <random>
#include <iostream>
using namespace std;

NormalSequenceGenerator::NormalSequenceGenerator(unsigned int sequenceLength, const std::string& outputFileName, float mean, float stdDev) : sequenceLength_(sequenceLength), outputFileName_(outputFileName), mean_(mean), stdDev_(stdDev){}

int NormalSequenceGenerator::generateNormalSequence()
{
    ofstream ofile(outputFileName_.c_str());
    normal_distribution<> d(mean_, stdDev_);
    default_random_engine gen;
    for(unsigned int i = 0U; i != sequenceLength_; ++i)
    {
        int normalNumber = round(d(gen));
        char ch = 'P'+normalNumber;
        ofile << ch;
    }
    ofile.close();
    return 0;
}
