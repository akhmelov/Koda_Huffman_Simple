#ifndef SIMPLERANDOMSEQUENCEGENERATOR_H
#define SIMPLERANDOMSEQUENCEGENERATOR_H

#include <string>

class RandomSequenceGenerator
{
    public:
        RandomSequenceGenerator(unsigned int numOfCharsInAlphabet, unsigned int sequenceLength, const std::string& outputFileName);

        int generateRandomSequence();

    private:
        unsigned int numOfCharsInAlphabet_;
        unsigned int sequenceLength_;
        const std::string& outputFileName_;
};

#endif // SIMPLERANDOMSEQUENCEGENERATOR_H
