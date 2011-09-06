#include <iostream>
#include "Hash.hpp"
#include "Utils.hpp"
#include "LexAnalyzer.hpp"


using namespace std;
using namespace Utils;

int main(int argc,char** argv) {

	//ifstream file("teste");

	FILE *file = fopen("/home/isac/teste","r");
	node *n = NULL;
	hashtab *h = inithashtab(201);
	while(!feof(file)){
		n = lexan(file);
		if(n){
			cout << "key: " << n->key << " value: "  << n->value <<  " value_int: " << n->value_int << endl;
			put(h,n->key,n);
		}
	}
	return 0;
}
