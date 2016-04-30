#ifndef DECODER_H
#define DECODER_H

#include <bitset>
#include "../include/HuffmanSimple.h"

class Decoder: public HuffmanSimple
{
    public:
        Decoder(string inputFileName, string outFileName);
        virtual ~Decoder();

        void getVocabulary();
        void displayVocabulary();
        string algorithm(); //Algorithm
    protected:
    private:
        ifstream inputFile;
        ofstream outputFile;
        InfFile infFile;

        void getInfFile();
};

#endif // DECODER_H
