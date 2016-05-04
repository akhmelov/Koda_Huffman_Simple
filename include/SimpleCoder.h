#ifndef CODER_H
#define CODER_H

#include <iostream>
#include <string>
#include <fstream>
#include <bitset>
#include <climits>
#include <sstream> //for convering double to string

#include "HuffmanSimple.h"

using namespace std;

class Coder: public HuffmanSimple
{
    public:
        Coder(string inputFileName, string outFileName);
        virtual ~Coder();

        void getVocabulary();
        string algorithm(); //Algorithm
        void closeStreams();
    protected:
    private:
        ifstream inputFile;
        ofstream outputFile;
        InfFile infFile;
        unsigned long int myFrequencies[UniqueSymbols]; //helps the we save the vocabulary in file

        //INode* buildTree(const int (&frequencies)[UniqueSymbols]);
        //void generateCodes(const INode* node, const HuffCode& prefix, HuffCodeMap& outCodes);
        void saveVocabulary();
        void saveInfFile();
};

#endif // CODER_H
