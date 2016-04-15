#include "../include/SimpleCoder.h"

Coder::Coder(string inputFileName, string outFileName): HuffmanSimple(inputFileName, outFileName), myFrequencies({0})
{
    inputFile.open(inputFileName.c_str(), ifstream::in);
    outputFile.open(outFileName.c_str(), ofstream::binary);

    if(!inputFile.is_open()){cout<<"Error: file " << inputFileName << " is not opened\n"; exit(-1);}
    if(!outputFile.is_open()){cout<<"Error: file " << outFileName << " is not opened\n"; exit(-1);}

    //set information about format of the compression file
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
    unsigned long int frequencies[UniqueSymbols] = {0};
    unsigned char c = inputFile.get();

    while (inputFile.good()) {
        ++myFrequencies[c];
        ++frequencies[c];   //increamate frequency of symmbol
        c = inputFile.get();
    }

    inputFile.clear(); //set pointer on the begginning
    inputFile.seekg(0, inputFile.beg); //set pointer on the begginning

    root = buildTree(frequencies);

    generateCodes(root, HuffCode(), codes);

    //save vocabulary in file
    saveVocabulary();
}

void Coder::algorithm()
{
    //srednia dlugosc slowa bitowego
    int frequencyOutputWord[UCHAR_MAX] = {0};
    int lengthOutputWord[UCHAR_MAX] = {0};
    int sizeOutputWord = 0;
    int totalCountOutputWords = 0;
    //end srednia dlugosc slowa bitowego

    unsigned char c = inputFile.get();

    unsigned char myByte = 0;
    int sizeOfByte = 8; ///TODO ask how to check it
    int mySize = 1;
    unsigned int totalSize = 0;

    while (inputFile.good()) {
        HuffCodeMap::const_iterator it = codes.find(c);
        if(it == codes.end())
        {
            cout << "Error: Unexpected symbol in input file, symbol '" << c << "' is not found in vocabulary" << endl;
            exit(-1);
        }

        for (HuffCode::const_iterator itb = it -> second.begin(); itb != it -> second.end(); ++itb, mySize++, totalSize++)
        {
            //srednia dlugosc slowa bitowego
            sizeOutputWord += 1;
            //end srednia dlugosc slowa bitowego

            if(mySize > sizeOfByte){ //write to file
                outputFile.write((char *)&myByte, 1);
                mySize = 1;
                myByte = 0;
            }
            myByte |= *itb << (sizeOfByte - mySize);
        }

        //srednia dlugosc slowa bitowego
        frequencyOutputWord[c] += 1;
        lengthOutputWord[c] = sizeOutputWord;
        totalCountOutputWords += 1;
        sizeOutputWord = 0;
        //end srednia dlugosc slowa bitowego

        c = inputFile.get();
    }
    if(mySize != 0){
        outputFile.write((char *)&myByte, 1);

        //srednia dlugosc slowa bitowego
        frequencyOutputWord[c] += 1;
        lengthOutputWord[c] = sizeOutputWord;
        totalCountOutputWords += 1;
        //end srednia dlugosc slowa bitowego
    }
    infFile.compressDataSize = totalSize;
    saveInfFile();

    double middleSumOutputWords = 0;
    for(int i = 0; i < UCHAR_MAX; i++){
        cout << "frequencyOutputWord[" << i << "]: " << frequencyOutputWord[i] << " lengthOutputWord[" << i << "]: " << lengthOutputWord[i] << endl;
        middleSumOutputWords += (double)((double)frequencyOutputWord[i] / (double)totalCountOutputWords) * (double)lengthOutputWord[i];
    }
    cout << "Średnia długość słowa bitowego: " << middleSumOutputWords / 8 << endl;
}

void Coder::saveVocabulary() //saves vocabulary into files
{
    vector<HuffmanWordFile> words; //respresent worlds

    infFile.wordsStart = outputFile.tellp();

    for (int i = 0; i < UniqueSymbols; ++i) //create leafnodes
    {
        if(myFrequencies[i] != 0){
            HuffmanWordFile word;
            word.c = i;
            word.frequency = myFrequencies[i];
            outputFile.write(reinterpret_cast<const char *>(&word), sizeof(HuffmanWordFile));
            words.push_back(word);
        }
    }

    infFile.sizeOfWord = sizeof(HuffmanWordFile);
    infFile.countWords = words.size();

    infFile.compressDataStart += sizeof(HuffmanWordFile) * words.size();

    saveInfFile();
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
