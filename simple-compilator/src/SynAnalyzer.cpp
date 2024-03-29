#include "SynAnalyzer.hpp"

int casaToken(node* tok, int tok_type) {
	if (tok->token == tok_type) {
		DEBUG(cout<< "reconheceu  " << token->value << endl);
		getToken();
		return 1;
	} else {
		cerr << "Linha " << linha_atual << ": Esperado " << tokenRep(tok_type)
				<< " mas o encontrado foi " << tok->value << endl;
		return -1;
	}
}

int casaOuSinc(node* tok, int tok_type, int first[]) {
	if (tok->token == tok_type) {
		DEBUG(cout<< "reconheceu  " << token->value << endl);
		getToken();
		return 1;
	} else {
		cerr << "Linha " << linha_atual<< " : Esperado " << tokenRep(tok_type)
				<< " mas o encontrado foi " << tok->value << endl;
		sync(first);
		return 1;
	}
}

int sync(int *syncv) {

	DEBUG(cout << "Sincronizando " << endl;)

	while (!in(syncv) && token->token != EOF) {
		getToken();
	}
	if (token->token == EOF)
		exit(1);
	else
		return 1;
}

int in(int *v){

	int *p = v;

	while(*p != FINAL_V){
		if(*p == token->token) return true;
		p++;
	}

	return false;
}

void mensagem_erro(int *esperados, int encontado) {
	int *p = esperados;
	cerr << "Linha "<< linha_atual <<": Esperado " << tokenRep(*p);
	p++;
	while (*p != FINAL_V) {
		cerr  << " ou " << tokenRep(*p);
		p++;
	}
	cerr << ",mas o encontrado foi " << tokenRep(encontado) << endl;
}

int expressao() {
	DEBUG(cout<< "entrou <expressao>" << endl);
	//<expressao> --> <expressao_simples> <expressao'>
	if (in(first_expressao)) {
		expressao_simples();
		expressao_l();
		DEBUG(cout<< "saiu <expressao>" << endl);
		return 1;
	} else {
		DEBUG(cout<< "sinc <expressao>" << endl);
		mensagem_erro(first_expressao,token->token);
		sync(follow_expressao);
		return 1;
	}
}

int expressao_l() {
	DEBUG(cout<< "<expressao_l>" << endl);
	//	<expressao'> --> < <expressao_simples>
	//			| > <expressao_simples>
	//			| <= <expressao_simples>
	//			| >= <expressao_simples>
	//			| = <expressao_simples>
	//			| <> <expressao_simples>
	//			| epsilon
	if (token->token == OP_MENOR) {
		casaToken(token, OP_MENOR);
		expressao_simples();
		return 1;
	} else if (token->token == OP_MAIOR) {
		casaToken(token, OP_MAIOR);
		expressao_simples();
		return 1;
	} else if (token->token == OP_MENOR_IGUAL) {
		casaToken(token, OP_MENOR_IGUAL);
		expressao_simples();
		return 1;
	} else if (token->token == OP_MAIOR_IGUAL) {
		casaToken(token, OP_MAIOR_IGUAL);
		expressao_simples();
		return 1;
	} else if (token->token == OP_IGUAL) {
		casaToken(token, OP_IGUAL);
		expressao_simples();
		return 1;
	} else if (token->token == OP_DIFERENTE) {
		casaToken(token, OP_DIFERENTE);
		expressao_simples();
		return 1;
	} else {
		return 1;
	}
}

int expressao_simples() {
	DEBUG(cout<< "<expressao_simples>" << endl);
	//<expressao_simples> --> <termo> <expressao_simples'>
	if (token->token == ID || token->token == NUM
			|| token->token == OP_ABRE_PARENTESES) {
		termo();
		expressao_simples_l();
		return 1;
	}
	else{
		DEBUG(cout<< "sinc <expressao_simples>" << endl);
		mensagem_erro(first_expressao_simples,token->token);
		sync(follow_expressao_simples);
		return 1;
	}
}

int expressao_simples_l() {

	DEBUG(cout<< "<expressao_siples_l>" << endl);
	//<expressao_simples'> --> + <termo> <expressao_simples'> | - <termo> <expressao_simples'> | epsilon
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
	} else{
		return 1;
	}
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
	} else {
		DEBUG(cout<< "sinc <fator>" << endl);
		mensagem_erro(first_fator,token->token);
		sync(follow_fator);
		return 1;
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
	else {
		return 1;
	}
}

int termo() {
	DEBUG(cout<< "<termo>" << endl);
	//<termo> --> <fator> <termo'>
	if (token->token == ID || token->token == NUM || token->token == OP_ABRE_PARENTESES) {
		fator();
		termo_l();
		return 1;
	} else {
		DEBUG(cout<< "sinc <termo>" << endl);
		mensagem_erro(first_termo,token->token);
		sync(follow_termo);
		return 1;
	}
}

int termo_l() {
	DEBUG(cout<< "<termo_l>" << endl);
	//<termo'> -->  * <fator> <termo'> | / <fator> <termo'> | epsilon
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
	} else {
		return 1;
	}
}

int lista_expressoes() {
	DEBUG(cout<< "<lista_expressoes>" << endl);
	//<lista_de_expressoes> --> <expressao> <lista_de_expressoes'>
	if (token->token == ID || token->token == NUM || token->token == OP_ABRE_PARENTESES) {
		expressao();
		lista_expressoes_l();
		return 1;
	} else {
		DEBUG(cout<< "sinc <lista_expressoes>" << endl);
		mensagem_erro(first_lista_expressoes,token->token);
		sync(follow_lista_expressoes);
		return 1;
	}
}

int lista_expressoes_l() {
	DEBUG(cout<< "<lista_expressoes_l>" << endl);
	//<lista_de_expressoes'> --> , <expressao> <lista_de_expressoes'> | epsilon
	if (token->token == OP_VIRGULA) {
		casaToken(token, OP_VIRGULA);
		expressao();
		lista_expressoes_l();
		return 1;
	} else {
		return 1;
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
	} else {
		DEBUG(cout<< "sinc <programa>" << endl);
		mensagem_erro(first_programa,token->token);
		sync(follow_programa);
		return 1;
	}
}

int lista_ids() {
	DEBUG(cout<< "<lista_ids>" << endl);
	//<lista_de_ids> --> id <lista_de_ids'>
	if (token->token == ID) {
		casaToken(token, ID);
		lista_ids_l();
		return 1;
	} else {
		DEBUG(cout<< "sinc <lista_ids>" << endl);
		mensagem_erro(first_lista_ids,token->token);
		sync(follow_lista_ids);
		return 1;
	}
}

int lista_ids_l() {
	DEBUG(cout<< "<lista_ids_l>" << endl);
	//<lista_de_ids'> --> , id <lista_de_ids'> | epsilon
	if (token->token == OP_VIRGULA) {
		casaToken(token, OP_VIRGULA);
		casaToken(token, ID);
		lista_ids_l();
		return 1;
	} else {
		return 1;
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
	} else {
		return 1;
	}
}

int tipo() {
	DEBUG(cout<< "<tipo>" << endl);
	//<tipo> --> <tipo_padrao> | arranjo [ num .. num ] de <tipo_padrao>
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
	} else {
		DEBUG(cout<< "sinc <tipo>" << endl);
		mensagem_erro(first_tipo,token->token);
		sync(follow_tipo);
		return 1;
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
	} else {
		DEBUG(cout<< "sinc <tipo_padrao>" << endl);
		mensagem_erro(first_tipo_padrao,token->token);
		sync(follow_tipo_padrao);
		return 1;
	}
}

int declaracoes_subprograma() {
	DEBUG(cout<< "<declaracoes_subprograma>" << endl);
	// <declaracoes_de_subprogramas> -->  <declaracao_de_subprograma> ; <declaracoes_de_subprogramas> | epsilon
	if (token->token == RW_FUNCAO || token->token == RW_PROCEDIMENTO) {
		declaracao_subprograma();
		casaToken(token, OP_PONTO_VIRGULA);
		declaracoes_subprograma();
		return 1;
	} else {
		return 1;
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
	} else {
		DEBUG(cout<< "sinc <declaracao_subprograma>" << endl);
		mensagem_erro(first_declaracao_subprograma,token->token);
		sync(follow_declaracao_subprograma);
		return 1;
	}
}

int cabecalho_subprograma() {
	DEBUG(cout<< "<cabecalho_subprograma>" << endl);
	//<cabecalho_de_subprograma> --> funcao id <argumentos> : <tipo_padrao> ; | procedimento id <argumentos> ;
	if (token->token == RW_FUNCAO) {
		casaToken(token, RW_FUNCAO);
		casaToken(token, ID);
		argumentos();
		casaToken(token, OP_DOIS_PONTOS);
		tipo_padrao();
		casaToken(token, OP_PONTO_VIRGULA);
		return 1;
	}
	else if (token->token == RW_PROCEDIMENTO) {
		casaToken(token, RW_PROCEDIMENTO);
		casaToken(token, ID);
		argumentos();
		casaToken(token, OP_PONTO_VIRGULA);
		return 1;
	} else {
		DEBUG(cout<< "sinc <cabecalho_subprograma>" << endl);
		mensagem_erro(first_cabecalho_de_subprograma,token->token);
		sync(follow_cabecalho_de_subprograma);
		return 1;
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
	} else {
		return 1;
	}
}

int lista_parametros() {
	DEBUG(cout<< "<lista_parametros>" << endl);
	//<lista_de_parametros> --> <lista_de_ids> : <tipo> <lista_de_parametros'>
	if (token->token == ID) {
		lista_ids();
		casaToken(token, OP_DOIS_PONTOS);
		tipo();
		lista_parametros_l();
		return 1;
	} else {
		DEBUG(cout<< "sinc <lista_parametros>" << endl);
		mensagem_erro(first_lista_de_parametros,token->token);
		sync(follow_lista_de_parametros);
		return 1;
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
		return 1;
	} else {
		DEBUG(cout<< "sinc <enunciado_composto>" << endl);
		mensagem_erro(first_enunciado_composto,token->token);
		sync(follow_enunciado_composto);
		return 1;
	}
}

int enunciados_opcionais() {
	DEBUG(cout<< "<enunciados_opcionais>" << endl);
	//<enunciados_opcionais> --> <lista_de_enunciados> | epsilon
	if (token->token == ID || token->token == RW_INICIO || token->token == RW_SE
			|| token->token == RW_ENQUANTO) {
		lista_enunciados();
		return 1;
	} else {
		return 1;
	}
}

int lista_enunciados() {
	DEBUG(cout<< "<lista_de_enunciados>" << endl);
	//	<lista_de_enunciados> --> <enunciado> <lista_de_enunciados'>
	if (token->token == ID || token->token == RW_INICIO
			|| token->token == RW_SE || token->token == RW_ENQUANTO) {
		enunciado();
		lista_enunciados_l();
		return -1;
	}else {
		DEBUG(cout<< "sinc <lista_de_enunciados>" << endl);
		mensagem_erro(first_lista_de_enunciados,token->token);
		sync(follow_lista_de_enunciados);
		return 1;
	}
}
int lista_enunciados_l() {
	DEBUG(cout<< "<lista_de_enunciados_l>" << endl);
	//	<lista_de_enunciados'> -->  ; <enunciado> <lista_de_enunciados'> | epsilon
	if (token->token == OP_PONTO_VIRGULA) {
		casaToken(token, OP_PONTO_VIRGULA);
		enunciado();
		lista_enunciados_l();
		return 1;
	} else {
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
		casaOuSinc(token, RW_ENTAO,first_enunciado);
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
	} else {
		DEBUG(cout<< "sinc <enunciado>" << endl);
		mensagem_erro(first_enunciado,token->token);
		sync(follow_enunciado);
		return 1;
	}
}
int enunciado_l() {
	DEBUG(cout<< "<enunciado_l>" << endl);
	//	<enunciado'> --> <variavel'> := <expressao>
	if (token->token == OP_ABRE_COLCHETE || token->token == OP_RECEBE ) {
		variavel_l();
		casaToken(token, OP_RECEBE);
		expressao();
		return 1;
	}
	//	<enunciado'> --> <chamada_de_procedimento'>
	else if (token->token == OP_ABRE_PARENTESES) {
		chamada_procedimento_l();
		return 1;
	} else {
		DEBUG(cout<< "sinc <enunciado_l>" << endl);
		mensagem_erro(first_enunciado_l,token->token);
		sync(follow_enunciado_l);
		return 1;
	}
}

int variavel_l() {
	DEBUG(cout<< "<variavel'>" << endl);
	//	<variavel'> --> [ <expressao> ] | epsilon
	if (token->token == OP_ABRE_COLCHETE) {
		casaToken(token, OP_ABRE_COLCHETE);
		expressao();
		casaToken(token, OP_FECHA_COLCHETE);
		DEBUG(cout<< "saiu <variavel'>" << endl);
		return 1;
	} else {
		DEBUG(cout<< "saiu <variavel'> epsilon" << endl);
		return 1;
	}
}

int chamada_procedimento_l() {
	DEBUG(cout<< "<chamada_de_procedimento_l>" << endl);
//  <chamada_de_procedimento'> --> ( <lista_de_expressoes> ) | epsilon
	if (token->token == OP_ABRE_PARENTESES) {
		casaToken(token, OP_ABRE_PARENTESES);
		lista_expressoes();
		casaToken(token, OP_FECHA_PARENTESES);
		return 1;
	} else {
		return 1;
	}
}
