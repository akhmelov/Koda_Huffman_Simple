#include "../include/HuffmanSimple.h"

HuffmanSimple::HuffmanSimple(string inputFileName, string outFileName):
                        inputFileName(inputFileName), outFileName(outFileName)
{
    inputFile.open(inputFileName.c_str(), ifstream::in);
    outputFile.open(outFileName.c_str(), ofstream::binary);

    if(!inputFile.is_open()){cout<<"Error: file " << inputFileName << " is not opened\n"; exit(-1);}
    if(!outputFile.is_open()){cout<<"Error: file " << outFileName << " is not opened\n"; exit(-1);}
}

HuffmanSimple::~HuffmanSimple()
{
    inputFile.close();
    outputFile.close();
    delete root;
}

void HuffmanSimple::displayVocabulary()
{
    for (HuffCodeMap::const_iterator it = codes.begin(); it != codes.end(); ++it)
    {
        cout << it->first << " ";
        cout << "[" << (int)it->first << "] ";
        copy(it -> second.begin(), it -> second.end(), ostream_iterator<bool>(cout));
        cout << std::endl;
    }
}


INode* HuffmanSimple::buildTree(const int (&frequencies)[UniqueSymbols])
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

void HuffmanSimple::generateCodes(const INode* node, const HuffCode& prefix, HuffCodeMap& outCodes)
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

double HuffmanSimple::countEntropy()
{
    double entropy = 0.0;
    map<char, unsigned int> charHistogramMap;
    typedef std::istreambuf_iterator<char> buf_iter;
    unsigned int numOfChars = 0U;
    for(buf_iter i(inputFile), e; i != e; ++i)
    {
        ++numOfChars;
        char c = *i;
        if(charHistogramMap.find(c) == charHistogramMap.end())
        {
            charHistogramMap.insert(pair<char, unsigned int>(c,1));
        }
        else
        {
            ++(charHistogramMap.find(c)->second);
        }
    }
    for(map<char, unsigned int>::const_iterator it = charHistogramMap.begin(); it != charHistogramMap.end(); ++it)
    {
        double propability = (double)it->second / (double)numOfChars;
        double tmpEntropy = propability * log(propability);     //logarytm o podstawie 2, nie wiem czy na pewno 2???
        entropy -= tmpEntropy;
    }
    return entropy;
}

double HuffmanSimple::findEffective()
{
    double effective = 0;
    unsigned int posIn = inputFile.tellg();
    unsigned int posOut = outputFile.tellp();
    inputFile.seekg(0, inputFile.end); //set pointer on the beg
    outputFile.seekp(0, outputFile.end); //set pointer on the beg
    effective = ((double)outputFile.tellp() / (double)inputFile.tellg());
    inputFile.seekg(posIn); //set pointer on the beg
    outputFile.seekp(posOut); //set pointer on the beg
    return effective;
}


