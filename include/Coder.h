#ifndef CODER_H
#define CODER_H

#include <iostream>
#include <string>
#include <fstream>

#include "HuffmanSimple.h"

using namespace std;

class Coder: public HuffmanSimple
{
    public:
        Coder(string inputFileName, string outFileName);
        virtual ~Coder();

        void getVocabulary();
        void displayVocabulary();
        void algorithm(); //Algorithm
    protected:
    private:
        INode* buildTree(const int (&frequencies)[UniqueSymbols]);
        void generateCodes(const INode* node, const HuffCode& prefix, HuffCodeMap& outCodes);
};

#endif // CODER_H
