#ifndef HUFFMANCODER_H
#define HUFFMANCODER_H

#include <iostream>
#include <string>
#include <fstream>
#include <math.h>

#include "Structures.h"

using namespace std;

class HuffmanSimple
{
    public:
        HuffmanSimple(string inputFileName, string outFileName);
        virtual ~HuffmanSimple();

        virtual void getVocabulary() = 0;
        void displayVocabulary();
        virtual string algorithm() = 0; //Algorithm

        INode* root; //TODO change to protected
        ///TODO entropier i dlugosc implementacja
        double countEntropy();
        double findEffective();
    protected:
        HuffCodeMap codes;
//        INode* root;

        string inputFileName;
        string outFileName;

        INode* buildTree(const unsigned long int (&frequencies)[UniqueSymbols]);
        void generateCodes(const INode* node, const HuffCode& prefix, HuffCodeMap& outCodes);
    private:
        ifstream inputFile;
        ofstream outputFile;
};

#endif // HUFFMANCODER_H
