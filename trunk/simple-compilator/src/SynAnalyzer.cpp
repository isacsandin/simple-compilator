#include "SynAnalyzer.hpp"

int casaToken(node* tok, int tok_type) {
	if (tok->token == tok_type) {
		DEBUG(cout<< "reconheceu  " << token->value << endl);
		getToken();
		return 1;
	} else {
		cerr << "linha " << linha_atual << ": Esperado " << tokenRep(tok_type)
				<< " mas o encontrado foi " << tok->value << endl;
		return -1;
	}
}

int expressao() {
	DEBUG(cout<< "entrou <expressao>" << endl);
	//<expressao> --> <expressao_simples> <expressao'>
	if (token->token == ID || token->token == NUM
			|| token->token == OP_ABRE_PARENTESES || token->token == OP_VEZES
			|| token->token == OP_DIVIDIDO || token->token == OP_MENOR
			|| token->token == OP_MAIOR || token->token == OP_IGUAL) {

		expressao_simples();
		expressao_l();
		DEBUG(cout<< "saiu <expressao>" << endl);
		return 1;
	} else if (token->token == OP_PONTO_VIRGULA || token->token == RW_FIM
			|| token->token == RW_SENAO || token->token == RW_ENTAO
			|| token->token == RW_FACA || token->token == OP_FECHA_COLCHETE
			|| token->token == OP_FECHA_PARENTESES
			|| token->token == OP_VIRGULA) {
		return -1;
	}
	return -1;
}

int expressao_l() {
	DEBUG(cout<< "<expressao_l>" << endl);
	//<expressao'> --> < <expressao'''>
	//		| > <expressao''>
	//		| = <expressao_simples>
	//		| epsilon
	if (token->token == OP_MENOR) {
		casaToken(token, OP_MENOR);
		expressao_lll();
		return 1;
	} else if (token->token == OP_MAIOR) {
		casaToken(token, OP_MAIOR);
		expressao_ll();
		return 1;
	} else if (token->token == OP_IGUAL) {
		casaToken(token, OP_IGUAL);
		expressao_simples();
		return 1;
	} else if (token->token == OP_PONTO_VIRGULA || token->token == RW_FIM
			|| token->token == RW_SENAO || token->token == RW_ENTAO
			|| token->token == RW_FACA || token->token == OP_FECHA_COLCHETE
			|| token->token == OP_FECHA_PARENTESES
			|| token->token == OP_VIRGULA) {
		return -1;
	} else {
		return -1;
	}
}

int expressao_ll() {
	DEBUG(cout<< "<expressao_ll>" << endl);
	//<expressao''> --> = <expressao_simples> | <expressao_simples>
	if (token->token == ID || token->token == NUM
			|| token->token == OP_ABRE_PARENTESES || token->token == OP_VEZES
			|| token->token == OP_DIVIDIDO || token->token == OP_MENOR
			|| token->token == OP_MAIOR || token->token == OP_IGUAL) {

		if (token->token == OP_IGUAL) {
			casaToken(token, OP_IGUAL);
			expressao_simples();
			return 1;
		} else {
			expressao_simples();
			return 1;
		}
	} else if (token->token == OP_PONTO_VIRGULA || token->token == RW_FIM
			|| token->token == RW_SENAO || token->token == RW_ENTAO
			|| token->token == RW_FACA || token->token == OP_FECHA_COLCHETE
			|| token->token == OP_FECHA_PARENTESES
			|| token->token == OP_VIRGULA) {
		return -1;
	}
	return -1;
}
int expressao_lll() {
	DEBUG(cout<< "<expressao_lll>" << endl);
	//<expressao'''> --> = <expressao_simples> | > <expressao_simples> | <expressao_simples>
	if (token->token == ID || token->token == NUM
			|| token->token == OP_ABRE_PARENTESES || token->token == OP_VEZES
			|| token->token == OP_DIVIDIDO || token->token == OP_MENOR
			|| token->token == OP_MAIOR || token->token == OP_IGUAL) {

		if (token->token == OP_IGUAL) {
			casaToken(token, OP_IGUAL);
			expressao_simples();
			return 1;
		} else if (token->token == OP_MAIOR) {
			casaToken(token, OP_MAIOR);
			expressao_simples();
			return 1;
		} else {
			expressao_simples();
			return 1;
		}
	} else if (token->token == OP_PONTO_VIRGULA || token->token == RW_FIM
			|| token->token == RW_SENAO || token->token == RW_ENTAO
			|| token->token == RW_FACA || token->token == OP_FECHA_COLCHETE
			|| token->token == OP_FECHA_PARENTESES
			|| token->token == OP_VIRGULA) {
		return -1;
	}
	return -1;
}

int expressao_simples() {
	DEBUG(cout<< "<expressao_simples>" << endl);
	//<expressao_simples> --> <termo> | <expressao_simples'>
	//TODO oops nem todos os caras desse first sao first dos caras das regras
	if (token->token == ID || token->token == NUM
			|| token->token == OP_ABRE_PARENTESES || token->token == OP_VEZES
			|| token->token == OP_DIVIDIDO || token->token == OP_MENOR
			|| token->token == OP_MAIOR || token->token == OP_IGUAL) {

//		if (token->token == ID || token->token == NUM
//				|| token->token == OP_ABRE_PARENTESES
//				|| token->token == OP_VEZES || token->token == OP_DIVIDIDO) { // first <termo>
//			termo();
//			return 1;
//		} else if (token->token == OP_MENOS || token->token == OP_MAIS) { // first <expressao_simples'>
//			expressao_simples_l();
//			return 1;
//		}
		termo();
		expressao_simples_l();
		return 1;
	} else if (token->token == OP_PONTO_VIRGULA || token->token == RW_FIM
			|| token->token == RW_SENAO || token->token == RW_ENTAO
			|| token->token == RW_FACA || token->token == OP_FECHA_COLCHETE
			|| token->token == OP_FECHA_PARENTESES
			|| token->token == OP_VIRGULA) {
		return -1;
	}
	return -1;
}

int expressao_simples_l() {
	DEBUG(cout<< "<expressao_siples_l>" << endl);
	//<expressao_simples'> --> + <termo> <expressao_simples'> | - <termo> <expressao_simples'>
	if (token->token == OP_MAIS || token->token == OP_MENOS) {
		if (token->token == OP_MAIS) {
			casaToken(token, OP_MAIS);
			termo();
			expressao_simples_l();
			return 1;
		} else if (token->token == OP_MENOS) {
			casaToken(token, OP_MENOS);
			termo();
			expressao_simples_l();
			return 1;
		}
	} else if (token->token == OP_PONTO_VIRGULA || token->token == RW_FIM
			|| token->token == RW_SENAO || token->token == RW_ENTAO
			|| token->token == RW_FACA || token->token == OP_FECHA_COLCHETE
			|| token->token == OP_FECHA_PARENTESES
			|| token->token == OP_VIRGULA) {
		return -1;
	}
	return -1;
}

int fator() {
	DEBUG(cout<< "<fator>" << endl);
	//<fator> --> id <fator'> | num | ( <expressao> )
	if (token->token == ID) {
		casaToken(token, ID);
		fator_l();
		return 1;
	} else if (token->token == NUM) {
		casaToken(token, NUM);
		return 1;
	} else if (token->token == OP_ABRE_PARENTESES) {
		casaToken(token, OP_ABRE_PARENTESES);
		expressao();
		casaToken(token, OP_FECHA_PARENTESES);
		return 1;
	}
	//folow
	else if (token->token == OP_PONTO_VIRGULA || token->token == RW_FIM
			|| token->token == RW_SENAO || token->token == RW_ENTAO
			|| token->token == RW_FACA || token->token == OP_FECHA_COLCHETE
			|| token->token == OP_FECHA_PARENTESES
			|| token->token == OP_VIRGULA) {
		return -1;
	} else {
		return -1;
	}
}

int fator_l() {
	DEBUG(cout<< "<fator_l>" << endl);
	//<fator'> --> ( <lista_de_expressoes> ) | epsilon
	if (token->token == OP_ABRE_PARENTESES) {
		casaToken(token, OP_ABRE_PARENTESES);
		lista_expressoes();
		casaToken(token, OP_FECHA_PARENTESES);
		return 1;
	}
	//folow
	else if (token->token == OP_PONTO_VIRGULA || token->token == RW_FIM
			|| token->token == RW_SENAO || token->token == RW_ENTAO
			|| token->token == RW_FACA || token->token == OP_FECHA_COLCHETE
			|| token->token == OP_FECHA_PARENTESES || token->token == OP_VIRGULA
			|| token->token == OP_MAIS || token->token == OP_MENOS) {
		return -1;
	}

	else {
		return -1;
	}
}

int termo() {
	DEBUG(cout<< "<termo>" << endl);
	//<termo> --> <fator> | <termo'>
	if (token->token == ID || token->token == NUM
			|| token->token == OP_ABRE_PARENTESES) {
		fator();
		return 1;
	} else if (token->token == OP_VEZES || token->token == OP_DIVIDIDO) {
		termo_l();
		return 1;
	}
	//folow
	else if (token->token == OP_PONTO_VIRGULA || token->token == RW_FIM
			|| token->token == RW_SENAO || token->token == RW_ENTAO
			|| token->token == RW_FACA || token->token == OP_FECHA_COLCHETE
			|| token->token == OP_FECHA_PARENTESES || token->token == OP_VIRGULA
			|| token->token == OP_MAIS || token->token == OP_MENOS) {
		return -1;
	} else {
		return -1;
	}
}

int termo_l() {
	DEBUG(cout<< "<termo_l>" << endl);
	//<termo'> -->  * <fator> <termo'> | / <fator> <termo'>
	if (token->token == OP_VEZES) {
		casaToken(token, OP_VEZES);
		fator();
		termo_l();
		return 1;
	} else if (token->token == OP_DIVIDIDO) {
		casaToken(token, OP_DIVIDIDO);
		fator();
		termo_l();
		return 1;
	}
	//folow
	else if (token->token == OP_PONTO_VIRGULA || token->token == RW_FIM
			|| token->token == RW_SENAO || token->token == RW_ENTAO
			|| token->token == RW_FACA || token->token == OP_FECHA_COLCHETE
			|| token->token == OP_FECHA_PARENTESES || token->token == OP_VIRGULA
			|| token->token == OP_MAIS || token->token == OP_MENOS) {
		return -1;
	} else {
		return -1;
	}
}

int lista_expressoes() {
	DEBUG(cout<< "<lista_expressoes>" << endl);
	//<lista_de_expressoes> --> <expressao> | <lista_de_expressoes'>
	if (token->token == ID || token->token == NUM
			|| token->token == OP_ABRE_PARENTESES || token->token == OP_VEZES
			|| token->token == OP_DIVIDIDO || token->token == OP_MENOR
			|| token->token == OP_MAIOR || token->token == OP_RECEBE) {
		expressao();
		lista_expressoes_l();
		return 1;
	}
	//folow
	else if (token->token == OP_PONTO_VIRGULA || token->token == RW_FIM
			|| token->token == RW_SENAO || token->token == RW_ENTAO
			|| token->token == RW_FACA || token->token == OP_FECHA_COLCHETE
			|| token->token == OP_FECHA_PARENTESES || token->token == OP_VIRGULA
			|| token->token == OP_MAIS || token->token == OP_MENOS) {
		return -1;
	} else {
		return -1;
	}
}

int lista_expressoes_l() {
	DEBUG(cout<< "<lista_expressoes_l>" << endl);
	//<lista_de_expressoes'> --> , <expressao> <lista_de_expressoes> | epsilon
	if (token->token == OP_VIRGULA) {
		casaToken(token, OP_VIRGULA);
		expressao();
		lista_expressoes();
		return 1;
	}
	//folow
	else if (token->token == OP_FECHA_PARENTESES) {
		return -1;
	} else {
		return -1;
	}
}

int programa() {
	DEBUG(cout<< "<programa>" << endl);
	//<programa> --> programa id; <declaracoes> <declaracoes_de_subprogramas> <enunciado_composto> .
	if (token->token == RW_PROGRAMA) {
		casaToken(token, RW_PROGRAMA);
		casaToken(token, ID);
		casaToken(token, OP_PONTO_VIRGULA);
		declaracoes();
		declaracoes_subprograma();
		enunciado_composto();
		casaToken(token, OP_PONTO);
		return 1;
	}
	//folow
	else if (token->token == EOF) {
		return -1;
	} else {
		return -1;
	}
}

int lista_ids() {
	DEBUG(cout<< "<lista_ids>" << endl);
	//<lista_de_ids> --> id | <lista_de_ids'>
	if (token->token == ID) {
		casaToken(token, ID);
		lista_ids_l();
		return 1;
	}
	//folow
	else if (token->token == OP_DOIS_PONTOS) {
		return -1;
	} else {
		return -1;
	}
}

int lista_ids_l() {
	DEBUG(cout<< "<lista_ids_l>" << endl);
	//<lista_de_ids'> --> , id <lista_de_ids> | epsilon
	if (token->token == OP_VIRGULA) {
		casaToken(token, OP_VIRGULA);
		casaToken(token, ID);
		lista_ids();
		return 1;
	}
	//folow
	else if (token->token == OP_DOIS_PONTOS) {
		return -1;
	} else {
		return -1;
	}
}

int declaracoes() {
	DEBUG(cout<< "<declaracoes>" << endl);
	//<declaracoes> --> declare <lista_de_ids> : <tipo>; <declaracoes> | epsilon
	if (token->token == RW_DECLARE) {
		casaToken(token, RW_DECLARE);
		lista_ids();
		casaToken(token, OP_DOIS_PONTOS);
		tipo();
		casaToken(token, OP_PONTO_VIRGULA);
		declaracoes();
		return 1;
	}
	//S(<declaracoes>) = {declare | inicio | funcao | procedimento}
	else if (token->token == RW_INICIO || token->token == RW_FUNCAO
			|| token->token == RW_PROCEDIMENTO) {
		return -1;
	} else {
		return -1;
	}
}

int tipo() {
	DEBUG(cout<< "<tipo>" << endl);
	//<tipo_padrao> | arranjo [ num .. num ] de <tipo_padrao>
	if (token->token == RW_NUMERICO) {
		casaToken(token, RW_NUMERICO);
		return 1;
	} else if (token->token == RW_BOOLEANO) {
		casaToken(token, RW_BOOLEANO);
		return 1;
	} else if (token->token == RW_ARRANJO) {
		casaToken(token, RW_ARRANJO);
		casaToken(token, OP_ABRE_COLCHETE);
		casaToken(token, NUM);
		casaToken(token, OP_PONTO);
		casaToken(token, OP_PONTO);
		casaToken(token, NUM);
		casaToken(token, OP_FECHA_COLCHETE);
		casaToken(token, RW_DE);
		tipo_padrao();
		return 1;
	}
	//folow
	else if (token->token == OP_PONTO_VIRGULA
			|| token->token == OP_FECHA_PARENTESES) {
		return -1;
	} else {
		return -1;
	}
}
int tipo_padrao() {
	DEBUG(cout<< "<tipo_padrao>" << endl);
	//<tipo_padrao> --> numerico | booleano
	if (token->token == RW_NUMERICO) {
		casaToken(token, RW_NUMERICO);
		return 1;
	} else if (token->token == RW_BOOLEANO) {
		casaToken(token, RW_BOOLEANO);
		return 1;
	}
	//folow
	else if (token->token == OP_PONTO_VIRGULA
			|| token->token == OP_FECHA_PARENTESES) {
		return -1;
	} else {
		return -1;
	}
}
int declaracoes_subprograma() {
	DEBUG(cout<< "<declaracoes_subprograma>" << endl);
	// <declaracoes_de_subprogramas> -->  <declaracao_de_subprograma> ; <declaracoes_de_subprogramas> | epsilon
	if (token->token == RW_FUNCAO || token->token == RW_PROCEDIMENTO) {
		declaracao_subprograma();
		casaToken(token,OP_PONTO_VIRGULA);
		declaracoes_subprograma();
		return 1;
	}
	//folow
	else if (token->token == RW_INICIO) {
		return -1;
	} else {
		return -1;
	}
}
int declaracao_subprograma() {
	DEBUG(cout<< "<declaracao_subprograma>" << endl);
	//<declaracao_de_subprograma> --> <cabecalho_de_subprograma> <declaracoes> <enunciado_composto>
	if (token->token == RW_FUNCAO || token->token == RW_PROCEDIMENTO) {
		cabecalho_subprograma();
		declaracoes();
		enunciado_composto();
		DEBUG(cout<< "saiu <declaracao_subprograma>" << endl);
		return 1;
	}
	//folow
	else if (token->token == RW_INICIO || token->token == OP_PONTO_VIRGULA ) {
		return -1;
	} else {
		return -1;
	}
}
int cabecalho_subprograma() {
	DEBUG(cout<< "<cabecalho_subprograma>" << endl);
	//<cabecalho_de_subprograma> --> funcao id <argumentos> : <tipo_padrao> ;
	if (token->token == RW_FUNCAO) {
		casaToken(token, RW_FUNCAO);
		casaToken(token, ID);
		argumentos();
		casaToken(token, OP_DOIS_PONTOS);
		tipo_padrao();
		casaToken(token, OP_PONTO_VIRGULA);
		return 1;
	}
	//procedimento id <argumentos> ;
	else if (token->token == RW_PROCEDIMENTO) {
		casaToken(token, RW_PROCEDIMENTO);
		casaToken(token, ID);
		argumentos();
		casaToken(token, OP_PONTO_VIRGULA);
		return 1;
	}
	//folow
	else if (token->token == RW_DECLARE) {
		return -1;
	} else {
		cerr << " condicao de erro faltam em <cabecalho_subprograma> " << endl;
		return -1;
	}
}
int argumentos() {
	DEBUG(cout<< "<argumentos>" << endl);
	//<argumentos> --> ( <lista_de_parametros> ) | epsilon
	if (token->token == OP_ABRE_PARENTESES) {
		casaToken(token, OP_ABRE_PARENTESES);
		lista_parametros();
		casaToken(token, OP_FECHA_PARENTESES);
		return 1;
	}
	//folow
	else if (token->token == OP_DOIS_PONTOS
			|| token->token == OP_PONTO_VIRGULA) {
		return -1;
	} else {
		return 1;
	}
}
int lista_parametros() {
	DEBUG(cout<< "<lista_parametros>" << endl);
	//<lista_de_parametros> --> <lista_de_ids> : <tipo>  <lista_de_parametros'>
	if (token->token == ID) {
		lista_ids();
		casaToken(token, OP_DOIS_PONTOS);
		tipo();
		lista_parametros_l();
		return 1;
	}
	//folow
	else if (token->token == OP_FECHA_PARENTESES) {
		return -1;
	} else {
		cerr << " condicao de erro faltam em <lista_parametros> " << endl;
		return -1;
	}
}
int lista_parametros_l() {
	DEBUG(cout<< "<lista_parametros_l>" << endl);
	//<lista_de_parametros'> --> ; <lista_de_ids> : <tipo> <lista_de_parametros'> | epsilon
	if (token->token == OP_PONTO_VIRGULA) {
		lista_ids();
		casaToken(token, OP_DOIS_PONTOS);
		tipo();
		lista_parametros_l();
		return 1;
	}
	//folow
	else if (token->token == OP_FECHA_PARENTESES) {
		return -1;
	} else {
		return 1;
	}
}
int enunciado_composto() {
	DEBUG(cout<< "<enunciado_composto>" << endl);
	//<enunciado_composto> --> inicio <enunciados_opcionais> fim
	if (token->token == RW_INICIO) {
		casaToken(token, RW_INICIO);
		enunciados_opcionais();
		casaToken(token, RW_FIM);
		DEBUG(cout<< "saiu <enunciado_composto>" << endl);
		return 1;
	}
	//folow
	else if (token->token == OP_PONTO_VIRGULA || token->token == RW_FIM
			|| token->token == RW_SENAO || token->token == OP_PONTO) {
		return -1;
	} else {
		cerr << " condicao de erro faltam em <enunciado_composto> " << endl;
		return -1;
	}
}
int enunciados_opcionais() {
	DEBUG(cout<< "<enunciados_opcionais>" << endl);
	//<enunciados_opcionais> --> <lista_de_enunciados> | epsilon
	if (token->token == ID || token->token == RW_INICIO || token->token == RW_SE
			|| token->token == RW_ENQUANTO) {
		lista_enunciados();
		return 1;
	}
	//folow
	else if (token->token == RW_FIM) {
		return -1;
	} else {
		return 1;
	}
}

int lista_enunciados() {
	DEBUG(cout<< "<lista_de_enunciados>" << endl);
    //	<lista_de_enunciados> --> <enunciado> <lista_de_enunciados'>
	if (token->token == ID || token->token == RW_INICIO || token->token == RW_SE
			|| token->token == RW_ENQUANTO) {
		enunciado();
		lista_enunciados_l();
		return -1;
	}
	//folow
	else if (token->token == RW_FIM) {
		return -1;
	} else {
		cerr << " condicao de erro faltam em <lista_de_enunciados> " << endl;
		return -1;
	}
}
int lista_enunciados_l() {
	DEBUG(cout<< "<lista_de_enunciados_l>" << endl);
	//	<lista_de_enunciados'> -->  ; <enunciado> <lista_de_enunciados'> | epsilon
	if (token->token == OP_PONTO_VIRGULA) {
		casaToken(token, OP_PONTO_VIRGULA);
		enunciado();
		lista_enunciados_l();
		DEBUG(cout<< "saiu <lista_de_enunciados_l>" << endl);
		return 1;
	}
	//folow
	else if (token->token == RW_FIM) {
		DEBUG(cout<< "saiu <lista_de_enunciados_l> flow " << tokenRep(token->token) << endl);
		return -1;
	} else {
		DEBUG(cout<< "saiu <lista_de_enunciados_l> epsilon" << endl);
		return 1;
	}
}
int enunciado() {
	DEBUG(cout<< "<enunciado>" << endl);
	//	<enunciado> --> id <enunciado'>
	if (token->token == ID) {
		casaToken(token, ID);
		enunciado_l();
		return 1;
	}
	//	<enunciado> --> <enunciado_composto>
	else if (token->token == RW_INICIO) {
		enunciado_composto();
		return 1;
	}
	//	<enunciado> --> se <expressao> entao <enunciado> senao <enunciado>
	else if (token->token == RW_SE) {
		casaToken(token, RW_SE);
		expressao();
		casaToken(token, RW_ENTAO);
		enunciado();
		casaToken(token, RW_SENAO);
		enunciado();
		return 1;
	}
	//	<enunciado> --> enquanto <expressao> faca <enunciado>
	else if (token->token == RW_ENQUANTO) {
		casaToken(token, RW_ENQUANTO);
		expressao();
		casaToken(token, RW_FACA);
		enunciado();
		return 1;
	}
//folow
	else if (token->token == OP_PONTO_VIRGULA || token->token == RW_FIM
			|| token->token == RW_SENAO) {
		return -1;
	} else {
		cerr << " condicao de erro faltam em <enunciado> " << endl;
		return -1;
	}
}
int enunciado_l() {
	DEBUG(cout<< "<enunciado_l>" << endl);
	//	<enunciado'> --> <variavel'> := <expressao>
	if (token->token == OP_ABRE_COLCHETE) {
		variavel_l();
		casaToken(token, OP_RECEBE);
		expressao();
		return 1;
	}
	//	<enunciado'> --> <chamada_de_procedimento'>
	else if (token->token == OP_ABRE_PARENTESES) {
		chamada_procedimento_l();
		return 1;
	}
//folow
	else if (token->token == OP_PONTO_VIRGULA || token->token == RW_FIM
			|| token->token == RW_SENAO) {
		return -1;
	} else {
		return 1;
	}
}
/*int variavel() {
	DEBUG(cout<< "<variavel>" << endl);
//	<variavel> --> id <variavel'>
	if (token->token == ID) {
		casaToken(token, ID);
		variavel_l();
		return 1;
	}
//folow
	else if (token->token == OP_DOIS_PONTOS) {
		return -1;
	} else {
		return -1;
	}
}*/
int variavel_l() {
	DEBUG(cout<< "<variavel'>" << endl);
//	<variavel'> --> [ <expressao> ] | epsilon
	if (token->token == OP_ABRE_COLCHETE) {
		casaToken(token, OP_ABRE_COLCHETE);
		expressao();
		casaToken(token, OP_FECHA_COLCHETE);
		return 1;
	}
//folow
	else if (token->token == OP_DOIS_PONTOS) {
		return -1;
	} else {
		return 1;
	}
}
/*int chamada_procedimento() {
	DEBUG(cout<< "<chamada_de_procedimento>" << endl);
//	<chamada_de_procedimento> --> id <chamada_de_procedimento'>
	if (token->token == ID) {
		casaToken(token, ID);
		chamada_procedimento_l();
		return 1;
	}
//folow
	else if (token->token == OP_PONTO_VIRGULA || token->token == RW_FIM
			|| token->token == RW_SENAO
			|| token->token == OP_FECHA_PARENTESES) {
		return -1;
	} else {
		return -1;
	}
}*/
int chamada_procedimento_l() {
	DEBUG(cout<< "<chamada_de_procedimento_l>" << endl);
//  <chamada_de_procedimento'> --> ( <lista_de_expressoes> ) | epsilon
	if (token->token == OP_ABRE_PARENTESES) {
		casaToken(token, OP_ABRE_PARENTESES);
		lista_expressoes();
		casaToken(token, OP_FECHA_PARENTESES);
		return 1;
	}
//folow
	else if (token->token == OP_PONTO_VIRGULA || token->token == RW_FIM
			|| token->token == RW_SENAO) {
		return -1;
	} else {
		return 1;
	}
}
