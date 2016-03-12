#include "../include/SimpleDecoder.h"

Decoder::Decoder(string inputFileName, string outFileName): HuffmanSimple(inputFileName, outFileName)
{
    inputFile.open(outFileName.c_str(), ifstream::binary);
    outputFile.open(inputFileName.c_str(), ofstream::in);

    if(!inputFile.is_open()){cout<<"Error: file " << inputFileName << " is not opened\n"; exit(-1);}
    if(!outputFile.is_open()){cout<<"Error: file " << outFileName << " is not opened\n"; exit(-1);}
}

Decoder::~Decoder()
{
    inputFile.close();
    outputFile.close();
}

void Decoder::getVocabulary()
{
    getInfFile();

    inputFile.seekg(infFile.wordsStart); //set to start data words

    int sizeOfByte = sizeof(unsigned int) * 8; //size of unsigned int in bits
    vector<HuffmanWordFile> worlds; //respresent worlds
    if(infFile.sizeOfWord != sizeof(HuffmanWordFile)){
        cout << endl << "Error: Unexpected error, the file to decompress isn't appropriate, maybe it's a wrong file or it was create on another OS";
        exit(-1);
    }

    for(int n = 0; n < infFile.countWords; n++){
        HuffmanWordFile word;
        inputFile.read((char *)&word, infFile.sizeOfWord);
        cout << "Word -> c: " << word.c << " (" << word.sizeOfCode << ") ";

        unsigned int myByte = word.code;
        for (int mySize = 1; mySize < sizeOfByte + 1 && mySize != word.sizeOfCode + 1; mySize++) //pass by bits of byte
        {
            if((myByte >> (sizeOfByte - mySize)) & 0x01){
                cout << "1";
            } else {
                cout << "0";
            }
        }
        cout << endl;
    }
}

void Decoder::algorithm()
{
    inputFile.seekg(infFile.compressDataStart); //set to start data compress
    unsigned int totalSizeFromFile = infFile.compressDataSize, totalSize = 0;
    unsigned char myByte = 0;
    inputFile.read((char *)&myByte, 1);
    int sizeOfByte = 8;
cout << "Word: ";
    const INode *node = root;
    while (inputFile.good())
    {
        for (int mySize = 1; mySize < sizeOfByte + 1 && totalSize != totalSizeFromFile; mySize++, totalSize++) //pass by bits of byte
        {
            //std::bitset<8> x(myByte);
            //std::cout << x;
            //std::cout << " Present size: " << totalSize << endl;
            if(const LeafNode* lf = dynamic_cast<const LeafNode*>(node)){
                cout << lf -> c;
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
cout << endl;
}

void Decoder::getInfFile()
{
    unsigned int pos = inputFile.tellg();
    inputFile.seekg(0, outputFile.beg); //set pointer on the beg
    inputFile.read((char *)&infFile, sizeof(InfFile)); //read the size of compression data
    inputFile.seekg(pos); //set pointer on the beg
}
