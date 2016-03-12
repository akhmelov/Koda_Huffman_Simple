#ifndef STRUCTURES_H_INCLUDED
#define STRUCTURES_H_INCLUDED

#include <iostream>
#include <queue>
#include <map>
#include <climits> // for CHAR_BIT
#include <iterator>
#include <algorithm>

const int UniqueSymbols = 1 << CHAR_BIT;

typedef std::vector<bool> HuffCode;
typedef std::map<char, HuffCode> HuffCodeMap;

struct InfFile {
    unsigned int compressDataSize;
    unsigned int compressDataStart;

    InfFile(): compressDataSize(0), compressDataStart(0) {}
};

class INode
{
    public:
        const int f;
        bool bit;

        virtual ~INode() {}

    protected:
        INode(int f) : f(f) {}
};

class InternalNode : public INode
{
    public:
        INode *const left;
        INode *const right;

        InternalNode(INode* c0, INode* c1) : INode(c0->f + c1->f), left(c0), right(c1) {
            left -> bit = false;
            right -> bit = true;
        }
        ~InternalNode()
        {
            delete left; //bit == 0
            delete right; //bit == 1
        }
};

class LeafNode : public INode
{
    public:
        const char c;

        LeafNode(int f, char c) : INode(f), c(c) {}
};

struct NodeCmp //the class for priority queue
{
    bool operator()(const INode* lhs, const INode* rhs) const { return lhs->f > rhs->f; }
};


#endif // STRUCTURES_H_INCLUDED
