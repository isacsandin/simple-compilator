#include "SynAnalyzer.hpp"


/**
<expressao> --> <expressao_simples> <expressao'>
<expressao'> --> < <expressao'''>
		| > <expressao''>
		| = <expressao_simples>
		| epsilon

<expressao''> --> = <expressao_simples> | <expressao_simples>
<expressao'''> --> = <expressao_simples> | > <expressao_simples> | <expressao_simples>
*/

int casaToken(node* tok,int tok_type){ return -1;}

int expressao(){
	getToken();
	if(token->token == ID ||
			token->token ==  NUM ||
			token->token == OP_ABRE_PARENTESES ||
			token->token == OP_VEZES ||
			token->token ==  OP_DIVIDIDO ||
			token->token == OP_MENOR ||
			token->token == OP_MAIOR ||
			token->token ==  OP_IGUAL){

		expressao_simples();
		expressao_l();
	}
	else if(token->token == OP_PONTO_VIRGULA ||
			token->token ==  RW_FIM ||
			token->token == RW_SENAO ||
			token->token == RW_ENTAO ||
			token->token == RW_FACA ||
			token->token == OP_FECHA_COLCHETE ||
			token->token == OP_FECHA_PARENTESES){
		return -1;
	}
		return -1;
}

int expressao_simples(){
	return -1;
}
int expressao_l(){
	if(token->token == OP_MENOR || token->token ==  OP_MAIOR || token->token == OP_IGUAL){
		switch(token->token){
			case OP_MENOR:
					getToken();
					expressao_lll();
					return 1;
			case OP_MAIOR:
					getToken();
					expressao_ll();
					return 1;
			case OP_IGUAL:
					getToken();
					expressao_simples();
					return 1;
		}
	}
	else if(token->token == OP_PONTO_VIRGULA ||
			token->token ==  RW_FIM ||
			token->token == RW_SENAO ||
			token->token == RW_ENTAO ||
			token->token == RW_FACA ||
			token->token == OP_FECHA_COLCHETE ||
			token->token == OP_FECHA_PARENTESES){
		return -1;
	}
	return -1;
}

int expressao_ll(){
	return -1;
}
int expressao_lll(){
	return -1;
}
