#include "LexAnalyzer.hpp"

using namespace std;

int get(FILE *file){
	int c = getc(file);
	if(c == '\n') linha_atual++;
	return c;
}

int unget(char c,FILE *file){
	if(c == '\n') linha_atual--;
	return ungetc(c,file);
}

node *getCorrectToken(const char* token){

	node *n=NULL;

	struct _aa{
		char* index;
		int token_type;
	}reservadas[21]{
			{"programa",RW_PROGRAMA},
			{"declare",RW_DECLARE},
			{"fim_declare",RW_FIM_DECLARE},
			{"arranjo",RW_ARRANJO},
			{"de",RW_DE},
			{"numerico",RW_NUMERICO},
			{"booleano",RW_BOOLEANO},
			{"verdadeiro",RW_VERDADEIRO},
			{"falso",RW_FALSO},
			{"procedimento",RW_PROCEDIMENTO},
			{"funcao",RW_FUNCAO},
			{"se",RW_SE},
			{"entao",RW_ENTAO},
			{"senao",RW_SENAO},
			{"enquanto",RW_ENQUANTO},
			{"faca",RW_FACA},
			{"retorne",RW_RETORNE},
			{"e",RW_E},
			{"ou",RW_OU},
			{"inicio",RW_INICIO},
			{"fim",RW_FIM},

		};

	for(int i=0;i<21;i++){
		if(!strcmp(reservadas[i].index,token)){
			n = alocaNode();
			n->token = reservadas[i].token_type;
			n->value = strdup("");
			n->value_int = 0;
			return n;
		}
	}
	n = alocaNode();
	n->token = ID;
	n->value = strdup(token);
	n->value_int = 0;
	return n;
}

node *lexan(FILE* file){
	char token = ' ';
	stringstream tmp;
	int state = 0;
	node* n = NULL;

	if(!file || feof(file)) return NULL;

	while(true){
		switch (state) {
		case 0:
			tmp.clear();
			token = get(file);
			switch (token) {
			case '+':
				n = alocaNode(OP_MAIS,"+",0,NULL);
				state = 8;
				break;
			case '-':
				n = alocaNode(OP_MENOS,"-",0,NULL);
				state = 8;
				break;
			case '*':
				n = alocaNode(OP_VEZES,"*",0,NULL);
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
				n = alocaNode(OP_IGUAL,"=",0,NULL);
				state = 8;
				break;
			case ':':
				state = 4;
				break;
			case '[':
				n = alocaNode(OP_ABRE_COLCHETE,"[",0,NULL);
				state = 8;
				break;
			case ']':
				n = alocaNode(OP_FECHA_COLCHETE,"]",0,NULL);
				state = 8;
				break;
			case '{': //comentario
				state = 5;
				break;
			case '(':
				n = alocaNode(OP_ABRE_PARENTESES,"(",0,NULL);
				state = 8;
				break;
			case ')':
				n = alocaNode(OP_FECHA_PARENTESES,")",0,NULL);
				state = 8;
				break;
			case ';':
				n = alocaNode(OP_PONTO_VIRGULA,";",0,NULL);
				state = 8;
				break;
			case ',':
				n = alocaNode(OP_VIRGULA,",",0,NULL);
				state = 8;
				break;
			case '.':
				n = alocaNode(OP_PONTO,".",0,NULL);
				state = 8;
				break;
		default:
			if (isdigit(token)){
				if(token == '0'){
					n = alocaNode(NUM,"0",0,NULL);
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
				if (feof(file)) state = 8;
				else if (!iscntrl(token) && !isspace(token) && !isblank(token)){
					fprintf(stderr,"caractere não identificado `%c'!! na linha %d\n",token,linha_atual);
					state = 0;
					//exit(1);
				}
 				break;
			}
		}
		break;
		case 1: //comentario uma linha
			token = get(file);
			switch (token) {
			case '/':
				token = get(file);
				while(token != '\n') token = get(file);
				state = 0;
				break;
			default:
				unget(token,file);
				n = alocaNode(OP_DIVIDIDO,"/",0,NULL);
				state = 8;
				break;
			}
			break;
		case 2:
			token = get(file);
			switch (token) {
			case '=':
				n = alocaNode(OP_MENOR_IGUAL,"<=",0,NULL);
				state = 8;
				break;
			case '>':
				n = alocaNode(OP_DIFERENTE,"<>",0,NULL);
				state = 8;
				break;
			default:
				unget(token,file);
				n = alocaNode(OP_MENOR,"<",0,NULL);
				state = 8;
				break;
			}
			break;
		case 3:
			token = get(file);
			switch (token) {
			case '=':
				n = alocaNode(OP_MAIOR_IGUAL,">=",0,NULL);
				state = 8;
				break;
			default:
				unget(token,file);
				n = alocaNode(OP_MAIOR,">",0,NULL);
				state = 8;
				break;
			}
			break;
		case 4:
			token = get(file);
			switch (token) {
			case '=':
				n = alocaNode(OP_RECEBE,":=",0,NULL);
				state = 8;
				break;
			default:
				unget(token,file);
				n = alocaNode(OP_DOIS_PONTOS,":",0,NULL);
				state = 8;
				break;
			}
			break;
		case 5://comentario multiplas linhas
			token = get(file);
			while (token != '}' && !feof(file)) token = get(file);
			state = 0;
			break;
		case 6: //numeros
			tmp.clear();
			tmp << token;
			token = get(file);
			while (isdigit(token)){
				tmp << token;
				token = get(file);
			}
			unget(token,file);
			n = alocaNode(NUM,tmp.str().c_str(),atoi(tmp.str().c_str()),NULL);
			state = 8;
			break;
		case 7: //id
			tmp.clear();
			tmp << token;
			token = get(file);
			while (isalnum(token) || token == '_'){
				tmp << token;
				token = get(file);
			}
			unget(token,file);
			n = getCorrectToken(tmp.str().c_str());
			state = 8;
			break;
		case 8:
			return n;
		default:
			return NULL;
			break;
		}
	}
	return NULL;
}
