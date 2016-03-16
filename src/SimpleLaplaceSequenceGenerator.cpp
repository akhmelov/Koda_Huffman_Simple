#include "SimpleLaplaceSequenceGenerator.h"
#include <fstream>

#include <boost/random/laplace_distribution.hpp>
#include <boost/random/mersenne_twister.hpp>

using namespace std;

LaplaceSequenceGenerator::LaplaceSequenceGenerator(unsigned int sequenceLength, const std::string& outputFileName, float location, float scale) : sequenceLength_(sequenceLength), outputFileName_(outputFileName), location_(location), scale_(scale){}

int LaplaceSequenceGenerator::generateLaplaceSequence()
{
    boost::random::mt19937 rng;
    boost::random::laplace_distribution<> generator(location_, scale_);
    ofstream ofile(outputFileName_.c_str());
    for(unsigned int i = 0U; i != sequenceLength_; ++i)
    {
        int laplaceNumber = round(generator(rng));
        char ch = 'P'+laplaceNumber;
        ofile << ch;
    }
    ofile.close();
    return 0;
}
