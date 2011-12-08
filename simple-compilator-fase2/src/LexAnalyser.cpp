#include "LexAnalyzer.hpp"

using namespace std;

int get(){
	int c = getc(file);
	if(c == '\n'){
		linha_atual++;
	}
	return c;
}

int unget(char c){
	if(c == '\n') linha_atual--;
	return ungetc(c,file);
}

node *getCorrectToken(const char* tok){
	node *n=NULL;

	struct _aa{
		const char* index;
		int token_type;
		int type;
	}reservadas[2]{
			{"int",RW_INT,TYPE_INT},
			{"float",RW_FLOAT,TYPE_FLOAT},
		};

	for(int i=0;i<2;i++){
		if(!strcmp(reservadas[i].index,tok)){
			n = alocaNode();
			n->token = reservadas[i].token_type;
			n->value_str = strdup(tokenRep(reservadas[i].token_type));
			n->value = 0;
			n->type = reservadas[i].type;
			return n;
		}
	}
	n = alocaNode();
	n->token = ID;
	n->value_str = strdup(tok);
	n->value = 0.0;
	n->initialized = false;
	n->type = TYPE_NONE;
	return n;
}

void getToken(){
	char tok= ' ';
	stringstream tmp;
	int state = 0;
	node* n = NULL;
	bool is_int = true;
	while(true){
		switch (state) {
		case 0:
			tmp.clear();
			tok = get();
			switch (tok) {
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
				n = alocaNode(OP_DIVIDIDO,"/",0,NULL);
				state = 8;
				break;
			case ':':
				state = 4;
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
		default:
			if (isdigit(tok)){
				if(tok == '0'){
					n = alocaNode(NUM_INT,"0",0,NULL);
					state = 8;
					break;
				}
				else{
					state = 6;
					break;
				}
			}
			else if (isalpha(tok)){
				state = 7;
				break;
			}
			else{
				n = alocaNode(EOF,"$",0,NULL);
				if (feof(file)) state = 8;
				else if (!iscntrl(tok) && !isspace(tok) && !isblank(tok)){
					fprintf(stderr,"caractere não identificado `%c' na linha %d\n",tok,linha_atual);
					state = 0;
					//exit(1);
				}
 				break;
			}
		}
		break;
		case 4:
			tok = get();
			switch (tok) {
			case '=':
				n = alocaNode(OP_RECEBE,":=",0,NULL);
				state = 8;
				break;
			default:
				unget(tok);
				n = alocaNode(OP_DOIS_PONTOS,":",0,NULL);
				state = 8;
				break;
			}
			break;
		case 6: //numeros
			is_int = true;
			tmp.clear();
			tmp << tok;
			tok = get();
			while (isdigit(tok)){
				tmp << tok;
				tok = get();
			}
			if (tok == '.'){
				is_int = false;
				tmp << tok;
				tok = get();
				while (isdigit(tok)){
					tmp << tok;
					tok = get();
				}
			}
			unget(tok);
			if(is_int){
				n = alocaNode(NUM_INT,tmp.str().c_str(),atoi(tmp.str().c_str()),NULL);
				n->type = TYPE_INT;
				n->initialized = true;
			}
			else{
				n = alocaNode(NUM_FLOAT,tmp.str().c_str(),atof(tmp.str().c_str()),NULL);
				n->type = TYPE_FLOAT;
				n->initialized = true;
			}
			state = 8;
			break;
		case 7: //id
			tmp.clear();
			tmp << tok;
			tok = get();
			while (isalnum(tok) || tok == '_'){
				tmp << tok;
				tok = get();
			}
			unget(tok);
			n = getCorrectToken(tmp.str().c_str());
			state = 8;
			break;
		case 8:
			if(n->token == EOF){
				token = n;
				return;
			}
			token = n;
			return;

		default:
			token = alocaNode(EOF,"$",0,NULL);
			return;
		}
	}
	token = alocaNode(EOF,"$",0,NULL);
	return;
}
