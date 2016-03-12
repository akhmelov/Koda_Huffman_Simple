#ifndef HUFFMANCODER_H
#define HUFFMANCODER_H

#include <iostream>
#include <string>
#include <fstream>

#include "Structures.h"

using namespace std;

class HuffmanSimple
{
    public:
        HuffmanSimple(string inputFileName, string outFileName);
        virtual ~HuffmanSimple();

        virtual void getVocabulary() = 0;
        void displayVocabulary();
        virtual void algorithm() = 0; //Algorithm

        ///TODO entropier i dlugosc implementacja
        INode* root; //TODO change to protected
    protected:
        HuffCodeMap codes;
//        INode* root;

        string inputFileName;
        string outFileName;
    private:
};

#endif // HUFFMANCODER_H
