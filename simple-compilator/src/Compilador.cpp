#include <iostream>
#include "Hash.hpp"
#include "Utils.hpp"
#include "LexAnalyzer.hpp"


using namespace std;
using namespace Utils;

int main(int argc,char** argv) {

	//ifstream file("teste");

	FILE *file = fopen("/home/isac/teste","r");

	cout << "!!!Hello World!!!hhhhh" << endl;

	while(!feof(file)) lexan(file);

	cout << "!!!Hello World!!!hhhhh" << endl;
	return 0;
}
