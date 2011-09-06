#include "LexAnalyzer.hpp"

using namespace std;

void reconhece(string key,string valor){
	cout << key << " " << valor << endl;
}

char *getCorrectToken(const char* token){

	node reservadas[21]{
			{"programa","300",300},
			{"declare","301",301},
			{"fim_declare","302",302},
			{"arranjo","303",303},
			{"de","304",304},
			{"numerico","305",305},
			{"booleano","306",306},
			{"verdadeiro","307",307},
			{"falso","308",308},
			{"procedimento","309",309},
			{"funcao","310",310},
			{"se","311",311},
			{"entao","312",312},
			{"senao","313",313},
			{"enquanto","314",314},
			{"faca","315",315},
			{"retorne","316",316},
			{"e","317",317},
			{"ou","318",318},
			{"inicio","319",319},
			{"fim","320",320},

		};

	for(int i=0;i<21;i++){
		if(!strcmp(reservadas[i].key,token)){
			return reservadas[i].value;
		}
	}
	return (char*)string("299").c_str(); //identificador
}

node *lexan(FILE* file){
	char token = ' ';
	char *tok;
	stringstream tmp;
	int state = 0;
	node* n = NULL;

	if(file){
		if(!feof(file)){
			while(true){
				switch (state) {
				case 0:
					token = getc(file);
					switch (token) {
					case '+':
						n = alocaNode();
						n->key = strdup("321");
						n->value = strdup("OP_MAIS");
						n->value_int = 321;
						n->next = NULL;
						state = 8;
						break;
					case '-':
						n = alocaNode();
						n->key = strdup("322");
						n->value = strdup("OP_MENOS");
						n->value_int = 322;
						n->next = NULL;
						state = 8;
						break;
					case '*':
						n = alocaNode();
						n->key = strdup("323");
						n->value = strdup("OP_VEZES");
						n->value_int = 323;
						n->next = NULL;
						state = 8;
						break;
					case '/':
						state = 1;
						break;
					case '<':
						state = 2;
						break;
					case '>':
						state = 3;
						break;
					case '=':
						n = alocaNode();
						n->key = strdup("324");
						n->value = strdup("OP_IGUAL");
						n->value_int = 324;
						n->next = NULL;
						state = 8;
						break;
					case ':':
						state = 4;
						break;
					case '[':
						n = alocaNode();
						n->key = strdup("325");
						n->value = strdup("OP_ABRE_COLCHETE");
						n->value_int = 325;
						n->next = NULL;
						state = 8;
						break;
					case ']':
						n = alocaNode();
						n->key = strdup("326");
						n->value = strdup("OP_FECHA_COLCHETE");
						n->value_int = 326;
						n->next = NULL;
						state = 8;
						break;
					case '{': //comentario
						state = 5;
						break;
					case '(':
						n = alocaNode();
						n->key = strdup("327");
						n->value = strdup("OP_ABRE_PARENTESES");
						n->value_int = 327;
						n->next = NULL;
						state = 8;
						break;
					case ')':
						n = alocaNode();
						n->key = strdup("328");
						n->value = strdup("OP_FECHA_PARENTESES");
						n->value_int = 328;
						n->next = NULL;
						state = 8;
						break;
					case ';':
						n = alocaNode();
						n->key = strdup("329");
						n->value = strdup("OP_PONTO_VIRGULA");
						n->value_int = 329;
						n->next = NULL;
						state = 8;
						break;
					case ',':
						n = alocaNode();
						n->key = strdup("330");
						n->value = strdup("OP_VIRGULA");
						n->value_int = 330;
						n->next = NULL;
						state = 8;
						break;
					case '.':
						n = alocaNode();
						n->key = strdup("331");
						n->value = strdup("OP_PONTO");
						n->value_int = 331;
						n->next = NULL;
						state = 8;
						break;
				default:
					if (isdigit(token)){
						if(token == '0'){
							n = alocaNode();
							n->key = strdup("298");
							n->value = strdup("0");
							n->value_int = 0;
							n->next = NULL;
							state = 8;
							break;
						}
						else{
							state = 6;
							break;
						}
					}
					else if (isalpha(token)){
						state = 7;
						break;
					}
					else{
						n = NULL;
						break;
					}
				}
				break;
				case 1: //comentario uma linha
					token = getc(file);
					switch (token) {
					case '/':
						tmp.clear();
						token = getc(file);
						while(token != '\n'){
							tmp << token;
							token = getc(file);
						}
						n = alocaNode();
						n->key = strdup("297");
						n->value = strdup(tmp.str().c_str());
						n->value_int = 297;
						n->next = NULL;
						state = 8;
						break;
					default:
						ungetc(token,file);
						n = alocaNode();
						n->key = strdup("332");
						n->value = strdup("OP_BARRA");
						n->value_int = 332;
						n->next = NULL;
						state = 8;
						break;
					}
					break;
				case 2:
					token = getc(file);
					switch (token) {
					case '=':
						n = alocaNode();
						n->key = strdup("333");
						n->value = strdup("OP_MENOR_IGUAL");
						n->value_int = 333;
						n->next = NULL;
						state = 8;
						break;
					case '>':
						n = alocaNode();
						n->key = strdup("334");
						n->value = strdup("OP_DIFERENTE");
						n->value_int = 334;
						n->next = NULL;
						state = 8;
						break;
					default:
						ungetc(token,file);
						n = alocaNode();
						n->key = strdup("335");
						n->value = strdup("OP_MENOR");
						n->value_int = 335;
						n->next = NULL;
						state = 8;
						break;
					}
					break;
				case 3:
					token = getc(file);
					switch (token) {
					case '=':
						n = alocaNode();
						n->key = strdup("336");
						n->value = strdup("OP_MAIOR_IGUAL");
						n->value_int = 336;
						n->next = NULL;
						state = 8;
						break;
					default:
						ungetc(token,file);
						n = alocaNode();
						n->key = strdup("337");
						n->value = strdup("OP_MAIOR");
						n->value_int = 337;
						n->next = NULL;
						state = 8;
						break;
					}
					break;
				case 4:
					token = getc(file);
					switch (token) {
					case '=':
						n = alocaNode();
						n->key = strdup("338");
						n->value = strdup("OP_RECEBE");
						n->value_int = 338;
						n->next = NULL;
						state = 8;
						break;
					default:
						ungetc(token,file);
						n = NULL;
						state = 8;
						break;
					}
					break;
				case 5://comentario multiplas linhas
					tmp.clear();
					token = getc(file);
					while (token != '}' && !feof(file)) {
						tmp << token;
						token = getc(file);
					}
					n = alocaNode();
					n->key = strdup("297");
					n->value = strdup(tmp.str().c_str());
					n->value_int = 297;
					n->next = NULL;
					state = 8;
					break;
				case 6: //numeros
					tmp.clear();
					tmp << token;
					token = getc(file);
					while (isdigit(token)){
						tmp << token;
						token = getc(file);
					}
					ungetc(token,file);
					n = alocaNode();
					n->key = strdup("298");
					n->value = strdup(tmp.str().c_str());
					n->value_int = atoi(tmp.str().c_str());
					n->next = NULL;
					state = 8;
					break;
				case 7: //id
					tmp << token;
					token = getc(file);
					while (isalnum(token) || token == '_'){
						tmp << token;
						token = getc(file);
					}
					ungetc(token,file);
					n = alocaNode();
					tok = getCorrectToken(tmp.str().c_str());
					n->key = strdup(tok);
					n->value = strdup((tmp.str()).c_str());
					n->value_int = atoi(tok);
					n->next = NULL;
					state = 8;
					break;
				case 8:
					return n;
				default:
					return NULL;
					break;
				}
			}
		}
		else{
			return NULL;
		}
	}
	else{
		return NULL;
	}
	return NULL;
}
