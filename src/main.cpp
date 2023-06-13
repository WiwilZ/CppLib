#include "Bit.h"
#include "Concept.h"
#include "Trait.h"
#include "Endian.h"
#include "Utils.h"
#include "Macro.h"
#include <compare>
#include <iostream>


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
