#include <iostream>
#include "Hash.hpp"
#include "Utils.hpp"
#include "LexAnalyzer.hpp"
#include "Constantes.hpp"


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


	FILE *file = fopen(input,"r");
	node *n = NULL;
	hashtab *myhash = inithashtab(201);
	while(!feof(file)){
		n = lexan(file);
		if(n){
			put(myhash,n->value,n);
			if(n->token == ID  || n->token == NUM )
				cout << tokenRep(n->token) << " " << n->value  << endl;
			else
				cout << tokenRep(n->token) << endl;
		}
	}

	printhashtable(myhash,stdout);
	return 0;
}
