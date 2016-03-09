#include "ParametersService.h"

#include <fstream>
#include <iostream>
#include <stdlib.h>

using namespace std;

ParametersService::ParametersService(): inputFileName_("in"), outputFileName_("out"), operationType_(0U) {}

string ParametersService::getOutputFileName()
{
    return outputFileName_;
}

string ParametersService::getInputFileName()
{
    return inputFileName_;
}

unsigned int ParametersService::getOperationType()
{
    return operationType_;
}

void ParametersService::printHelp()
{
    cout << "Help:" << endl << endl;
    cout << "    -code\tcode file" << endl;
    cout << "    \te.g." << endl;
    cout << "    \t./Simple_Hufman -code -in input_file -out output_file" << endl;
    cout << "          Parameters:" << endl << endl;
    cout << "            -in <file_name>\tinput file name. Default: in"<< endl << endl;
    cout << "            -out <file_name>\toutput file name. Default: out"<< endl << endl;

    cout << "    -decode\tdecode file" << endl;
    cout << "    \te.g." << endl;
    cout << "    \t./Simple_Hufman -code -in input_file -out output_file" << endl;
    cout << "          Parameters:" << endl << endl;
    cout << "            -in <file_name>\tinput file name. Default: in"<< endl << endl;
    cout << "            -out <file_name>\toutput file name. Default: out"<< endl << endl;
}

void ParametersService::service(int argc, const char* argv[])
{
    if(argc == 1)
    {
        printHelp();
        exit(-1);
    }
    for(int i = 0; i < argc; ++i)
    {
        if(string(argv[i]) == "-code")
        {
            operationType_ = 1U;
            continue;
        }
        else if(string(argv[i]) == "-decode")
        {
            operationType_ = 2U;
            continue;
        }
        else if(string(argv[i]) == "-in")
        {
            ++i;
            ifstream fileCheck(string(argv[i]).c_str());
            if(!fileCheck)	//check if file exists
            {
                cout << string(argv[i]) << ": no such file" << endl;
                exit(-1);
            }
            else
            {
                inputFileName_ = string(argv[i]);
            }
            fileCheck.close();
            continue;
        }
        else if(string(argv[i]) == "-out")
        {
            ++i;
            outputFileName_ = string(argv[i]);
            continue;
        }
    }
    if(operationType_ == 0U)
    {
        cout << "Program mode not specified, add '-code' or '-decode' to parameters list." << endl;
        exit(-1);
    }
}


