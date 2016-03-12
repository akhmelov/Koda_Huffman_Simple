#ifndef CODER_H
#define CODER_H

#include <iostream>
#include <string>
#include <fstream>
#include <bitset>

#include "HuffmanSimple.h"

using namespace std;

class Coder: public HuffmanSimple
{
    public:
        Coder(string inputFileName, string outFileName);
        virtual ~Coder();

        void getVocabulary();
        void algorithm(); //Algorithm
        void closeStreams();
    protected:
    private:
        ifstream inputFile;
        ofstream outputFile;

        INode* buildTree(const int (&frequencies)[UniqueSymbols]);
        void generateCodes(const INode* node, const HuffCode& prefix, HuffCodeMap& outCodes);
        void saveVocabulary();
};

#endif // CODER_H
