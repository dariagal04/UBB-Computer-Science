#include <iostream>
#include "Matrice.h"
#include "TestExtins.h"
#include "TestScurt.h"

using namespace std;
int main() {

	cout << "running tests...\n";

	testAll();
	testAllExtins();

	cout << "tests are ok";
}