#include "../include/SimpleCoder.h"

Coder::Coder(string inputFileName, string outFileName): HuffmanSimple(inputFileName, outFileName)
{

}

Coder::~Coder()
{

}

void Coder::getVocabulary()
{
    // Build frequency table
    int frequencies[UniqueSymbols] = {0};
    const char* ptr = "tEST Test";
    while (*ptr != '\0')
        ++frequencies[*ptr++];

    INode* root = buildTree(frequencies);

    generateCodes(root, HuffCode(), codes);
    delete root;
}

void Coder::algorithm()
{

}

INode* Coder::buildTree(const int (&frequencies)[UniqueSymbols])
{
    priority_queue<INode*, std::vector<INode*>, NodeCmp> trees;

    for (int i = 0; i < UniqueSymbols; ++i)
    {
        if(frequencies[i] != 0)
            trees.push(new LeafNode(frequencies[i], (char)i));
    }

    while (trees.size() > 1)
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
    if (const LeafNode* lf = dynamic_cast<const LeafNode*>(node))
    {
        outCodes[lf->c] = prefix;
    }

    else if (const InternalNode* in = dynamic_cast<const InternalNode*>(node))
    {
        HuffCode leftPrefix = prefix;
        leftPrefix.push_back(false);
        generateCodes(in->left, leftPrefix, outCodes);

        HuffCode rightPrefix = prefix;
        rightPrefix.push_back(true);
        generateCodes(in->right, rightPrefix, outCodes);
    }
}
