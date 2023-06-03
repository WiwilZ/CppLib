#include <iostream>
#include "Macro.h"
#include "Bit.h"

using namespace std;


int main(int argc, char **argv) {
#ifdef MSVC_COMPILER
    cout << "MSVC" << endl;
#endif

#ifdef CLANG_COMPILER
    cout << "CLANG" << endl;
#endif

#ifdef GCC_COMPILER
    cout << "GCC" << endl;
#endif


    return 0;
}
