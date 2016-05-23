#include <iostream>
#include <queue>
#include <map>
#include <climits> // for CHAR_BIT
#include <iterator>
#include <algorithm>
#include <iostream>
#include <dirent.h> //for list of files in directory
#include <time.h>

#include "include/ParametersService.h"
#include "include/SimpleCoder.h"
#include "include/SimpleDecoder.h"
#include "include/SimpleRandomSequenceGenerator.h"
#include "include/SimpleNormalSequenceGenerator.h"
#include "include/SimpleLaplaceSequenceGenerator.h"



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
        cout << "\tProgram mode: generate random (uniform distribution) sequence" << endl;
    else if(parametersService.getOperationType() == 4U)
        cout << "\tProgram mode: generate random (normal distribution) sequence" << endl;
    else if(parametersService.getOperationType() == 5U)
        cout << "\tProgram mode: generate random (Laplace distribution) sequence" << endl;
    cout << "\tInput file name: " << parametersService.getInputFileName() << endl;
    cout << "\tOutput file name: " << parametersService.getOutputFileName() << endl;
    cout << "\tSequence length: " << parametersService.getSequenceLength() << endl;
    cout << "\tNum of chars in alphabet: " << parametersService.getNumOfCharsInAlphabet() << endl;
    cout << "\tMean: " << parametersService.getMean() << endl;
    cout << "\tStandard deviation: " << parametersService.getStdDev() << endl;
    cout << "\tLocation: " << parametersService.getLocation() << endl;
    cout << "\tScale: " << parametersService.getScale() << endl << endl;




    ///used strategy design template
    HuffmanSimple *huffman;
    Coder coder(parametersService.getInputFileName(), parametersService.getOutputFileName());
    Decoder decoder(parametersService.getInputFileName(), parametersService.getOutputFileName());
    RandomSequenceGenerator randomSequenceGenerator(parametersService.getNumOfCharsInAlphabet(), parametersService.getSequenceLength(), parametersService.getOutputFileName());
    NormalSequenceGenerator normalSequenceGenerator(parametersService.getSequenceLength(), parametersService.getOutputFileName(), parametersService.getMean(), parametersService.getStdDev());
    LaplaceSequenceGenerator laplaceSequenceGenerator(parametersService.getSequenceLength(), parametersService.getOutputFileName(), parametersService.getLocation(), parametersService.getScale());


    if(parametersService.getOperationType() == 1U){
        huffman = &coder;
    }else if(parametersService.getOperationType() == 2U){
        huffman = &decoder;
    }else if(parametersService.getOperationType() == 3U){
        return randomSequenceGenerator.generateRandomSequence();
    }else if(parametersService.getOperationType() == 4U){
        return normalSequenceGenerator.generateNormalSequence();
    }else if(parametersService.getOperationType() == 5U){
        return laplaceSequenceGenerator.generateLaplaceSequence();
    } else {
        cout<< "Unexpected error, type of the operation is " << parametersService.getOperationType() << endl;
        exit(-1);
    }

    huffman -> getVocabulary();
    huffman -> displayVocabulary(); //help method

    const clock_t begin_time = clock();
    huffman -> algorithm();
    string estimatedTime(to_string(float( clock () - begin_time ) /  CLOCKS_PER_SEC));

    cout << "Entropy: " << huffman -> countEntropy() << endl;
    cout << "(Effectivity) n = " << huffman -> findEffective() << endl;
    cout << "Time = " << estimatedTime << endl;


    if(false){ //for all files in one folder
        //char pathToDirectory[256] = ;
        string pathToDirectory = string("/home/akhmelov/Downloads/KODA_Karol/test_end (copy)/");
        string pathToOutputDirectory = "/home/akhmelov/Downloads/KODA_Karol/outputs/";
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

            const clock_t begin_time = clock();
            string averageLength = huffman -> algorithm();
            string estimatedTime(to_string(float( clock () - begin_time ) /  CLOCKS_PER_SEC));

            double entropy = huffman -> countEntropy();
            double efecShannon = entropy / stod (averageLength, &sz);
            outputFile << pathToDirectory << ent->d_name << endl;    cout << pathToDirectory << ent->d_name << endl;
            outputFile << "     Średnia długość słowa bitowego: " << averageLength << endl;   cout << "     Średnia długość słowa bitowego: " << averageLength << endl;
            outputFile << "     Efektywność według Shannona (entropia / śr. długość) = " << efecShannon << endl;
            cout << "     Efektywność według Shannona (entropia / śr. długość) = " << efecShannon << endl;
            outputFile << "     Entropy: " << entropy << endl;   cout << "     Entropy: " << entropy << endl;
            outputFile << "     (Effectivity) n = " << huffman -> findEffective() << endl; cout << "     (Effectivity) n = " << huffman -> findEffective() << endl;
            outputFile << "     Time: " << estimatedTime << endl;   cout << "     Time: " << estimatedTime << endl;

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
