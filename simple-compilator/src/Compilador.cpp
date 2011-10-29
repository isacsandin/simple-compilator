#include "Compilador.hpp"

using namespace std;
using namespace Utils;

int main(int argc,char** argv) {

	/*int opt;
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
	file = fopen(input,"r");*/
	file = fopen("teste","r");

	while(!feof(file)){
		printf("%c",fgetc(file));
	}
	/*
	getToken();

	while(token->token != EOF){
		cout << token->value << endl;
		getToken();
	}*/
	return 0;
}
