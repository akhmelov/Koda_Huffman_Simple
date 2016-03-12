#include "../include/SimpleDecoder.h"

Decoder::Decoder(string inputFileName, string outFileName): HuffmanSimple(inputFileName, outFileName)
{
    inputFile.open(outFileName.c_str(), ifstream::binary);
    outputFile.open(inputFileName.c_str(), ofstream::in);



    if(!inputFile.is_open()){cout<<"Error: file " << inputFileName << " is not opened\n"; exit(-1);}
    //if(!outputFile.is_open()){cout<<"Error: file " << outFileName << " is not opened\n"; exit(-1);}
}

Decoder::~Decoder()
{
    inputFile.close();
    outputFile.close();
}

void Decoder::getVocabulary()
{
    ///codes - do tej zmiennej zapisywać kod
}

void Decoder::algorithm()
{
    cout << "======= Decompression ===========>>";
    inputFile.clear(); //set pointer on the begginning
    unsigned int totalSizeFromFile = 0, totalSize = 0;
    inputFile.seekg(-sizeof(unsigned int), inputFile.end); //set pointer on the size of compression data
    inputFile.read((char *)&totalSizeFromFile, sizeof(unsigned int)); //read the size of compression data
    inputFile.seekg(0, inputFile.beg); //set pointer on the beg
    cout << "Total size is: " << totalSizeFromFile << endl;
    unsigned char myByte = 0;
    inputFile.read((char *)&myByte, 1);
    int sizeOfByte = 8;

    const INode *node = root;
    while (inputFile.good())
    {
        for (int mySize = 1; mySize < sizeOfByte + 1 && totalSize != totalSizeFromFile; mySize++, totalSize++) //pass by bits of byte
        {
            //std::bitset<8> x(myByte);
            //std::cout << x;
            //std::cout << " Present size: " << totalSize << endl;
            if(const LeafNode* lf = dynamic_cast<const LeafNode*>(node)){
                cout << "" << lf -> c << "";
                ///TODO save to file
                node = root;
                mySize--;   //in this situation we aren't iterate by byte
                totalSize--;
            } else if (const InternalNode* in = dynamic_cast<const InternalNode*>(node)){
                if((myByte >> (sizeOfByte - mySize)) & 0x01){
                    node = in -> right;
                } else {
                    node = in -> left;
                }
            } else {
                cout << "Error. Unexpected type of node" << endl;
                exit(-1);
            }
        }
        if(totalSize == totalSizeFromFile) //reached the end of compression data
            break;

        inputFile.read((char *)&myByte, 1);
    }
    cout << "<<===== Decompression =========== END " << endl;
}
