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
		DEBUG(cout << "next token " << tokenRep(token->token) << endl;)
		cin.get();
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


int programa() {
	DEBUG(cout<< "<programa>" << endl);
	//<programa> -> <var-decls> , <decls> , <exp> ,
	if (in(first_programa)) {
		var_decls();
		casaToken(token, OP_VIRGULA);
		decls();
		casaToken(token, OP_VIRGULA);
		exp();
		casaToken(token, OP_VIRGULA);
		return 1;
	} else {
		DEBUG(cout<< "sinc <programa>" << endl);
		mensagem_erro(first_programa,token->token);
		sync(follow_programa);
		return 1;
	}
}

int var_decls() {
	DEBUG(cout<< "entrou <var_decls>" << endl);
	//<var-decls> -> <var-decl> <var-decls-l>
	if (in(first_var_decls)) {
		var_decl();
		var_decls_l();
		DEBUG(cout<< "saiu <var_decls>" << endl);
		return 1;
	} else {
		DEBUG(cout<< "sinc <var_decls>" << endl);
		mensagem_erro(first_var_decls,token->token);
		sync(follow_var_decls);
		return 1;
	}
}

int var_decls_l() {
	DEBUG(cout<< "entrou <var_decls_l>" << endl);
	//<var-decls-l> -> ; <var-decl> <var-decls-l>  |  epsilon
	if (token->token == OP_PONTO_VIRGULA ) {
		casaToken(token,OP_PONTO_VIRGULA);
		var_decl();
		var_decls_l();
		DEBUG(cout<< "saiu <var_decls_l>" << endl);
		return 1;
	} else {
		DEBUG(cout<< "epsilon <var_decls_l>" << endl);
		return 1;
	}
}

int var_decl() {
	DEBUG(cout<< "entrou <var_decl>" << endl);
	//<var-decl> -> <tipo-exp> : id
	if (in(first_var_decl)) {
		tipo_exp();
		casaToken(token,OP_DOIS_PONTOS);
		casaToken(token,ID);
		DEBUG(cout<< "saiu <var_decl>" << endl);
		return 1;
	} else {
		DEBUG(cout<< "sinc <var_decl>" << endl);
		mensagem_erro(first_var_decl,token->token);
		sync(follow_var_decl);
		return 1;
	}
}

int tipo_exp() {
	DEBUG(cout<< "entrou <tipo_exp>" << endl);
	//<tipo-exp> -> int | float
	if (token->token == RW_INT) {
		casaToken(token,RW_INT);
		DEBUG(cout<< "saiu <tipo_exp>" << endl);
		return 1;
	}else if (token->token == RW_FLOAT) {
		casaToken(token,RW_FLOAT);
		DEBUG(cout<< "saiu <tipo_exp>" << endl);
		return 1;
	} else {
		DEBUG(cout<< "sinc <tipo_exp>" << endl);
		mensagem_erro(first_tipo_exp,token->token);
		sync(follow_tipo_exp);
		return 1;
	}
}

int decls() {
	DEBUG(cout<< "entrou <decls>" << endl);
	//<decls> -> <decl> <decls-l>
	if (in(first_decls)) {
		decl();
		decls_l();
		DEBUG(cout<< "saiu <decls>" << endl);
		return 1;
	} else {
		DEBUG(cout<< "sinc <decls>" << endl);
		mensagem_erro(first_decls,token->token);
		sync(follow_decls);
		return 1;
	}
}

int decls_l() {
	DEBUG(cout<< "entrou <decls_l>" << endl);
	//<decls-l> -> ; <decl> <decls-l> | epsilon
	if (token->token == OP_PONTO_VIRGULA) {
		casaToken(token,OP_PONTO_VIRGULA);
		decl();
		decls_l();
		DEBUG(cout<< "saiu <decls_l>" << endl);
		return 1;
	} else {
		return 1;
	}
}

int decl() {
	DEBUG(cout<< "entrou <decl>" << endl);
	//<decl> -> id := <exp>
	if (token->token == ID) {
		casaToken(token,ID);
		casaToken(token,OP_RECEBE);
		exp();
		DEBUG(cout<< "saiu <decl>" << endl);
		return 1;
	} else {
		DEBUG(cout<< "sinc <decl>" << endl);
		mensagem_erro(first_decl,token->token);
		sync(follow_decl);
		return 1;
	}
}

int exp() {
	DEBUG(cout<< "entrou <exp>" << endl);
	//<exp> -> <termo> <exp-l>
	if (in(first_exp)) {
		termo();
		exp_l();
		DEBUG(cout<< "saiu <exp>" << endl);
		return 1;
	} else {
		DEBUG(cout<< "sinc <exp>" << endl);
		mensagem_erro(first_exp,token->token);
		sync(follow_exp);
		return 1;
	}
}

int exp_l() {
	DEBUG(cout<< "entrou <exp>" << endl);
	//<exp> -> <termo> <exp-l>
	if (token->token == OP_MAIS) {
		casaToken(token,OP_MAIS);
		termo();
		exp_l();
		DEBUG(cout<< "saiu <exp>" << endl);
		return 1;
	}else if (token->token == OP_MENOS) {
		casaToken(token,OP_MENOS);
		termo();
		exp_l();
		DEBUG(cout<< "saiu <exp>" << endl);
		return 1;
	}else {
		return 1;
	}
}

int termo() {
	DEBUG(cout<< "entrou <termo>" << endl);
	//<termo> -> <fator> <termo-l>
	if (in(first_termo)) {
		fator();
		termo_l();
		DEBUG(cout<< "saiu <termo>" << endl);
		return 1;
	} else {
		DEBUG(cout<< "sinc <termo>" << endl);
		mensagem_erro(first_termo,token->token);
		sync(follow_termo);
		return 1;
	}
}

int termo_l() {
	DEBUG(cout<< "entrou <exp_l>" << endl);
	//<termo-l> -> *<fator> <termo-l> | / <fator> <termo-l> | epsilon
	if (token->token == OP_VEZES) {
		casaToken(token,OP_VEZES);
		fator();
		termo_l();
		DEBUG(cout<< "saiu <exp_l>" << endl);
		return 1;
	}else if (token->token == OP_DIVIDIDO) {
		casaToken(token,OP_DIVIDIDO);
		fator();
		termo_l();
		DEBUG(cout<< "saiu <exp_l>" << endl);
		return 1;
	}else {
		return 1;
	}
}

int fator() {
	DEBUG(cout<< "entrou <fator>" << endl);
	//<fator> -> (<exp>) | <numero> | id
	if (token->token == OP_ABRE_PARENTESES) {
		casaToken(token,OP_ABRE_PARENTESES);
		exp();
		casaToken(token,OP_FECHA_PARENTESES);
		DEBUG(cout<< "saiu <fator>" << endl);
		return 1;
	}else if (token->token == NUM_INT || token->token == NUM_FLOAT) {
		numero();
		DEBUG(cout<< "saiu <fator>" << endl);
		return 1;
	}else if (token->token == ID) {
		casaToken(token,ID);
		DEBUG(cout<< "saiu <fator>" << endl);
		return 1;
	} else {
		DEBUG(cout<< "sinc <fator>" << endl);
		mensagem_erro(first_fator,token->token);
		sync(follow_fator);
		return 1;
	}
}

int numero() {
	DEBUG(cout<< "entrou <numero>" << endl);
	//<numero> -> numInt | numFloat
	if (token->token == NUM_INT) {
		casaToken(token,NUM_INT);
		DEBUG(cout<< "saiu <numero>" << endl);
		return 1;
	}else if (token->token == NUM_FLOAT) {
		casaToken(token,NUM_FLOAT);
		DEBUG(cout<< "saiu <numero>" << endl);
		return 1;
	}else {
		DEBUG(cout<< "sinc <numero>" << endl);
		mensagem_erro(first_numero,token->token);
		sync(follow_numero);
		return 1;
	}
}
