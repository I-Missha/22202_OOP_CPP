#include "BitArray.h"

using namespace std;

int main() {
    BitArray a(100, UINT_MAX);
    a.set();
//    a.resize(95, 1);
    a.to_string();
    return 0;
}
