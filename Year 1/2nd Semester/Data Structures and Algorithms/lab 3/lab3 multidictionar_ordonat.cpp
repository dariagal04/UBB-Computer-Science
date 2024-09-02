#include <iostream>
using namespace std;
#include "TestScurt.h"
#include "TestExtins.h"

int main() {
    cout << "running tests...\n";
    testAll();
    testAllExtins();
    cout << "tests are ok";
   
}
