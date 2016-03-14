#ifndef PARAMETERSSERVICE_H
#define PARAMETERSSERVICE_H

#include <string>

class ParametersService {
public:

    ParametersService();

    std::string getInputFileName();

    std::string getOutputFileName();

    unsigned int getOperationType();

    unsigned int getSequenceLength();

    unsigned int getNumOfCharsInAlphabet();

    void service(int argc, const char* argv[]);

private:
    std::string inputFileName_;
    std::string outputFileName_;
    unsigned int operationType_;
    unsigned int numOfCharsInAlphabet_;
    unsigned int sequenceLength_;

    void printHelp();
};

#endif // PARAMETERSSERVICE_H
