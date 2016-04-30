#include <iostream>
#include <queue>
#include <map>
#include <climits> // for CHAR_BIT
#include <iterator>
#include <algorithm>
#include <iostream>
#include <dirent.h> //for list of files in directory

#include "include/ParametersService.h"
#include "include/SimpleCoder.h"
#include "include/SimpleDecoder.h"
#include "include/SimpleRandomSequenceGenerator.h"


using namespace std;

int main(int argc, const char* argv[])
{

    ParametersService parametersService;
	parametersService.service(argc, argv);

    cout << "Parameters specified by user:" << endl;
    if(parametersService.getOperationType() == 1U)
        cout << "\tProgram mode: code" << endl;
    else if(parametersService.getOperationType() == 2U)
        cout << "\tProgram mode: decode" << endl;
    else if(parametersService.getOperationType() == 3U)
        cout << "\tProgram mode: generate random sequence" << endl;
    cout << "\tInput file name: " << parametersService.getInputFileName() << endl;
    cout << "\tOutput file name: " << parametersService.getOutputFileName() << endl;
    cout << "\tSequence length: " << parametersService.getSequenceLength() << endl;
    cout << "\tNum of chars in alphabet: " << parametersService.getNumOfCharsInAlphabet() << endl << endl;




    ///used strategy design template
    HuffmanSimple *huffman;
    Coder coder(parametersService.getInputFileName(), parametersService.getOutputFileName());
    Decoder decoder(parametersService.getInputFileName(), parametersService.getOutputFileName());
    RandomSequenceGenerator randomSequenceGenerator(parametersService.getNumOfCharsInAlphabet(), parametersService.getSequenceLength(), parametersService.getOutputFileName());


    if(parametersService.getOperationType() == 1U){
        huffman = &coder;
    }else if(parametersService.getOperationType() == 2U){
        huffman = &decoder;
    }else if(parametersService.getOperationType() == 3U){
        return randomSequenceGenerator.generateRandomSequence();
    } else {
        cout<< "Unexpected error, type of the operation is " << parametersService.getOperationType() << endl;
        exit(-1);
    }

    huffman -> getVocabulary();
    huffman -> displayVocabulary(); //help method
    huffman -> algorithm();

    cout << "Entropy: " << huffman -> countEntropy() << endl;
    cout << "(Effectivity) n = " << huffman -> findEffective() << endl;


    if(parametersService.getOperationType() == 1U){
        //for all files in one click
        //char pathToDirectory[256] = ;
        string pathToDirectory = string("/home/akhmelov/Downloads/KODA_To_check_test_files/");
        string pathToOutputDirectory = "/home/akhmelov/home/studia/KODA/Project/Koda_Huffman_Simple/outputs/";
        ofstream outputFile;
        outputFile.open((pathToOutputDirectory + "output.txt").c_str(), ofstream::in);
        string::size_type sz;     // alias of size_t

        DIR *dir;
        struct dirent *ent;
        if ((dir = opendir (pathToDirectory.c_str())) != NULL) {
          /* print all the files and directories within directory */
          while ((ent = readdir (dir)) != NULL) {
            string fileName(ent->d_name);
            if (fileName == ".." || fileName == ".") continue; //special files in linux

            Coder coder(pathToDirectory + ent->d_name, pathToOutputDirectory + "compressed_" + fileName);
            huffman = &coder;

            huffman -> getVocabulary();
            string averageLength = huffman -> algorithm();
            double efecShannon = huffman -> countEntropy() / stod (averageLength, &sz);
            outputFile << pathToDirectory << ent->d_name << endl;    cout << pathToDirectory << ent->d_name << endl;
            outputFile << "     Średnia długość słowa bitowego: " << averageLength << endl;   cout << "     Średnia długość słowa bitowego: " << averageLength << endl;
            outputFile << "     Efektywność według Shannona (entropia / śr. długość) = " << efecShannon << endl;
            cout << "     Efektywność według Shannona (entropia / śr. długość) = " << efecShannon << endl;
            outputFile << "     Entropy: " << huffman -> countEntropy() << endl;   cout << "     Entropy: " << huffman -> countEntropy() << endl;
            outputFile << "     (Effectivity) n = " << huffman -> findEffective() << endl; cout << "     (Effectivity) n = " << huffman -> findEffective() << endl;
          }
          closedir (dir);
        } else {
          /* could not open directory */
          perror ("");
          return EXIT_FAILURE;
        }
        outputFile.close();
    }
    return 0;
}
