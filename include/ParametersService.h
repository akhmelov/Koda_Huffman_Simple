#ifndef PARAMETERSSERVICE_H
#define PARAMETERSSERVICE_H

#include <string>

class ParametersService {
public:

    ParametersService();

    std::string getInputFileName();

    std::string getOutputFileName();

    unsigned int getOperationType();

    void service(int argc, const char* argv[]);

private:
    std::string inputFileName_;
    std::string outputFileName_;
    unsigned int operationType_;

    void printHelp();
};

#endif // PARAMETERSSERVICE_H
