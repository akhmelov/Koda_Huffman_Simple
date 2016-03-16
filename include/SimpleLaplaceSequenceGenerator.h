#ifndef SIMPLELAPLACESEQUENCEGENERATOR_H
#define SIMPLELAPLACESEQUENCEGENERATOR_H

#include <string>

class LaplaceSequenceGenerator
{
    public:
        LaplaceSequenceGenerator(unsigned int sequenceLength, const std::string& outputFileName, float location, float scale);

        int generateLaplaceSequence();

    private:
        unsigned int sequenceLength_;
        const std::string& outputFileName_;
        float location_;
        float scale_;
};

#endif // SIMPLELAPLACESEQUENCEGENERATOR_H
