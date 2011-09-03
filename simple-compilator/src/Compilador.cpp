#include <iostream>
#include "Hash.hpp"
#include "Utils.hpp"

using namespace std;
using namespace Utils;

void reconhece(string key,string valor){
	cout << key << " " << valor << endl;
}

int main(int argc,char** argv) {

	//ifstream file("teste");

	FILE *file = fopen("/home/isac/teste","r");


	//	cout << "!!!Hello World!!!" << endl;
	//	hashtab *h = inithashtab(201);
	//	for (int var = 0; var < 600; var++) {
	//		put(h,("chave"+toString(var)).c_str(),("valor"+toString(var)).c_str());
	//	}
	//	put(h,"isac","fodinha");
	//
	//	node* n = search(h,"isac");
	//	if(n) printf("key chave1 -> %s",n->value);
	//	else printf("nao encontrei!!");
	//
	//	cin.get();
	//	printhashtable(h);
	//	cin.get();
	//	for (int var = 0; var < 500; var++) {
	//		remove(h,("chave"+toString(var)).c_str());
	//	}
	//	printhashtable(h);
	cout << "!!!Hello World!!!hhhhh" << endl;
	return 0;
}
