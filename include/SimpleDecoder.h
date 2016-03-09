#ifndef DECODER_H
#define DECODER_H

#include <HuffmanSimple.h>


class Decoder: public HuffmanSimple
{
    public:
        Decoder(string inputFileName, string outFileName);
        virtual ~Decoder();

        void getVocabulary();
        void displayVocabulary();
        void algorithm(); //Algorithm
    protected:
    private:
};

#endif // DECODER_H
