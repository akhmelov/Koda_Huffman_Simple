#ifndef SIMPLENORMALSEQUENCEGENERATOR_H
#define SIMPLENORMALSEQUENCEGENERATOR_H

#include <string>

class NormalSequenceGenerator
{
    public:
        NormalSequenceGenerator(unsigned int sequenceLength, const std::string& outputFileName, float mean, float stdDev);

        int generateNormalSequence();

    private:
        unsigned int sequenceLength_;
        const std::string& outputFileName_;
        float mean_;
        float stdDev_;


};

#endif // SIMPLENORMALSEQUENCEGENERATOR_H
