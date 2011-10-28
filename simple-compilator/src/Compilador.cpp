#include <iostream>
#include <cstdio>
#include <cstdlib>
#include "Hash.hpp"
#include "Utils.hpp"
#include "LexAnalyzer.hpp"
#include "Constantes.hpp"
#include "Globals.hpp"
#include "Compilador.hpp"

using namespace std;
using namespace Utils;

int main(int argc,char** argv) {

	int opt;
	char *input = NULL;
	while ((opt = getopt (argc, argv, "f:")) != -1) {
		switch (opt) {
			case 'f': input = optarg; break;
			case '?':
					if ((optopt == 'f'))
						cerr << "Option -"<< optopt << " requires an argument." << endl;
					else if (isprint (optopt))
						cerr << "Unknown option `-"<< optopt <<"' .\n"<< endl;
					else
						cerr << "Unknown option character `-"<< optopt <<"'.\n"<< endl;
					return 1;
			default:
				abort ();
				break;
		}
	}

//	hashtab *myhash;
//	FILE *file;
//	node *token;


	file = fopen(input,"r");
	myhash = inithashtab(201);
	cout << file << endl;
	cout << myhash << endl;

	getToken();

	cout << file << endl;
	cout << myhash << endl;

	cout << "hahaha" << endl;

	cout << token->value << endl;

	cout << "hahaha" << endl;

	while(token->token != EOF){
		cout << token->value << endl;
		getToken();
	}
	return 0;
}
