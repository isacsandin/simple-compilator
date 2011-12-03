#include "Compilador.hpp"

using namespace std;

void help(char *nome){
	cerr << "USAGE: " << nome << " -f [arquivo] "<< endl;
	exit(EXIT_FAILURE);
}

int main(int argc,char** argv) {

	if(argc < 2){
		help(argv[0]);
	}

	int opt;
	char *input = NULL;
	while ((opt = getopt (argc, argv, "f:h")) != -1) {
		switch (opt) {
			case 'f': input = optarg; break;
			case 'h': help(argv[0]); break;
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


	file = fopen(input,"r");

	if(!file){
		cerr << "Arquivo não encontrado, ou não tenho permissão de acessá-lo "<< endl;
		exit(EXIT_FAILURE);
	}

	DEBUG(cout<< "entrando no programa " << endl);

	myhash = inithashtab(201);

	getToken();
	programa();

	return EXIT_SUCCESS;
}
