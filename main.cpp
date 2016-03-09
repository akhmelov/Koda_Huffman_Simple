#include <iostream>
#include <queue>
#include <map>
#include <climits> // for CHAR_BIT
#include <iterator>
#include <algorithm>
#include <iostream>
#include "include/Coder.h"
#include "include/ParametersService.h"

using namespace std;

int main(int argc, const char* argv [])
{
    ParametersService parametersService;
	parametersService.service(argc, argv);
    cout << "Input file name: " << parametersService.getInputFileName() << endl;
    cout << "Output file name: " << parametersService.getOutputFileName() << endl;
    if(parametersService.getOperationType() == 1U)
        cout << "Program mode: code" << endl;
    else if(parametersService.getOperationType() == 2U)
        cout << "Program mode: decode" << endl;


    return 0;
}
