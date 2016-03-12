#include "../include/SimpleCoder.h"

Coder::Coder(string inputFileName, string outFileName): HuffmanSimple(inputFileName, outFileName)
{
    inputFile.open(inputFileName.c_str(), ifstream::in);
    outputFile.open(outFileName.c_str(), ofstream::binary);

    if(!inputFile.is_open()){cout<<"Error: file " << inputFileName << " is not opened\n"; exit(-1);}
    if(!outputFile.is_open()){cout<<"Error: file " << outFileName << " is not opened\n"; exit(-1);}

    infFile.compressDataStart += sizeof(InfFile);
    outputFile.seekp(infFile.compressDataStart);
}

Coder::~Coder()
{
    inputFile.close();
    outputFile.close();
}

void Coder::getVocabulary()
{
    // Build frequency table
    int frequencies[UniqueSymbols] = {0};
    char c = inputFile.get();

    while (inputFile.good()) {
        ++frequencies[c];   //increamate frequency of symmbol
        c = inputFile.get();
    }

    inputFile.clear(); //set pointer on the begginning
    inputFile.seekg(0, inputFile.beg); //set pointer on the begginning
/*
    const char* ptr = "tEST Test";
    while (*ptr != '\0')
        ++frequencies[*ptr++];
*/
    root = buildTree(frequencies);

    generateCodes(root, HuffCode(), codes);
}

void Coder::algorithm()
{
    char c = inputFile.get();

    unsigned char myByte = 0;
    int sizeOfByte = 8; ///TODO ask how to check it
    int mySize = 1;
    unsigned int totalSize = 0;

    saveVocabulary();
    while (inputFile.good()) {
        HuffCodeMap::const_iterator it = codes.find(c);
        if(it == codes.end())
        {
            cout << "Error: Unexpected symbol in input file, symbol '" << c << "' is not found in vocabulary" << endl;
            exit(-1);
        }

        for (HuffCode::const_iterator itb = it -> second.begin(); itb != it -> second.end(); ++itb, mySize++, totalSize++)
        {
            if(mySize > sizeOfByte){ //write to file
                outputFile.write((char *)&myByte, 1);
                mySize = 1;
                myByte = 0;
            }
            myByte |= *itb << (sizeOfByte - mySize);
        }

        c = inputFile.get();
    }
    if(mySize != 0){
        outputFile.write((char *)&myByte, 1);
    }
    infFile.compressDataSize = totalSize;
    saveInfFile();
}

void Coder::saveVocabulary()
{
    ///TODO
}

void Coder::saveInfFile()
{
    unsigned int pos = outputFile.tellp();
    outputFile.seekp(0, outputFile.beg); //set pointer on the beg
    outputFile.write(reinterpret_cast<const char *>(&infFile), sizeof(InfFile));
    outputFile.seekp(pos); //set pointer on the beg
}

void Coder::closeStreams()
{
    inputFile.close();
    outputFile.close();
}

INode* Coder::buildTree(const int (&frequencies)[UniqueSymbols])
{
    priority_queue<INode*, std::vector<INode*>, NodeCmp> trees;

    for (int i = 0; i < UniqueSymbols; ++i) //create leafnodes
    {
        if(frequencies[i] != 0)
            trees.push(new LeafNode(frequencies[i], (char)i)); //priority queue, so there are sort data by frequency. The least is first
    }

    while (trees.size() > 1) //create tree base on leafnodes
    {
        INode* childR = trees.top();
        trees.pop();

        INode* childL = trees.top();
        trees.pop();

        INode* parent = new InternalNode(childR, childL);
        trees.push(parent);
    }
    return trees.top();
}

void Coder::generateCodes(const INode* node, const HuffCode& prefix, HuffCodeMap& outCodes)
{
    if (const LeafNode* lf = dynamic_cast<const LeafNode*>(node)) //the end of tree
    {
        outCodes[lf->c] = prefix;
    }

    else if (const InternalNode* in = dynamic_cast<const InternalNode*>(node))
    {
        HuffCode leftPrefix = prefix;
        leftPrefix.push_back(false);
        in -> left -> bit = false; //set prefix bit
        generateCodes(in->left, leftPrefix, outCodes);

        HuffCode rightPrefix = prefix;
        rightPrefix.push_back(true);
        in -> right -> bit = true;  //set prefix bit
        generateCodes(in->right, rightPrefix, outCodes);
    }
}
