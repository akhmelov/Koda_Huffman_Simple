#ifndef HUFFMANCODER_H
#define HUFFMANCODER_H

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class HuffmanSimple
{
    public:
        HuffmanSimple(string inputFileName, string outFileName);
        virtual ~HuffmanSimple();

        virtual void getVocabulary() = 0;
        void displayVocabulary();
        virtual void algorithm() = 0; //Algorithm

    protected:
        ifstream inputFile;
        ofstream outputFile;
    private:
};

#endif // HUFFMANCODER_H
