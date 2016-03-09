#ifndef CODER_H
#define CODER_H

#include <iostream>
#include <string>
#include <fstream>

#include "HuffmanCoder.h"

using namespace std;

class Coder: public HuffmanCoder
{
    public:
        Coder(string inputFileName, string outFileName);
        virtual ~Coder();

        void getVocabulary();
        void displayVocabulary();
        void algorithm(); //Algorithm
    protected:
    private:

};

#endif // CODER_H
