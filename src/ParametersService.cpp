#include "../include/ParametersService.h"

#include <fstream>
#include <iostream>
#include <string>
#include <stdlib.h>

using namespace std;

ParametersService::ParametersService(): inputFileName_("in"), outputFileName_("out"), operationType_(0U), numOfCharsInAlphabet_(10U), sequenceLength_(1000U) {}

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

unsigned int ParametersService::getNumOfCharsInAlphabet()
{
    return numOfCharsInAlphabet_;
}

unsigned int ParametersService::getSequenceLength()
{
    return sequenceLength_;
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

    cout << "    -generate_random\tgenerate random sequence and store it in file" << endl;
    cout << "    \te.g." << endl;
    cout << "    \t./Simple_Hufman -generate_random -n 5 -l 100 -out output_file" << endl;
    cout << "          Parameters:" << endl << endl;
    cout << "            -n <integer>\tnum of chars in input alphabet. Default: 10"<< endl << endl;
    cout << "            -l <integer>\tlength of sequence to generate. Default: 1000"<< endl << endl;
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
        else if(string(argv[i]) == "-generate_random")
        {
            operationType_ = 3U;
            continue;
        }
        else if(string(argv[i]) == "-n")
        {
            ++i;
            numOfCharsInAlphabet_ = stoul(string(argv[i]),nullptr,0);
            continue;
        }
        else if(string(argv[i]) == "-l")
        {
            ++i;
            sequenceLength_ = stoul(string(argv[i]),nullptr,0);
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
        cout << "Program mode not specified, add '-code', '-decode' or 'generate_random' to parameters list." << endl;
        exit(-1);
    }
}


