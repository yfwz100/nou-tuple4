
#include <stack>
#include <vector>
#include <algorithm>

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

#include <string>

#include <cstdlib>
#include <cstddef>
#include <cstring>

#include "token.h"
#include "expbuilder.h"

#include "ll1expbuilder.h"
#include "rexpbuilder.h"
#include "slr1expbuilder.h"

using namespace std;

typedef istream token_stream;

int main(int argc, char* argv[])
{
    ifstream fin;
    if (argc < 2) {
        fin.open("sample.txt");
    } else {
        fin.open(argv[1]);
    }

    ExpBuilder* expbuilder = new SLR1ExpBuilder();

    expbuilder->process(fin);

    delete expbuilder;

    cout << endl << "Done!" << endl;
    fin.close();
    return EXIT_SUCCESS;
}
