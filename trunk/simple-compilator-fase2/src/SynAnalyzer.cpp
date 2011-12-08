#include "SynAnalyzer.hpp"

int casaToken(node* tok, int tok_type) {
	if (tok->token == tok_type) {
		DEBUG(cout<< "reconheceu  " << token->value_str << endl);
		getToken();
		return 1;
	} else {
		cerr << "Linha " << linha_atual << ": Esperado " << tokenRep(tok_type)
				<< " mas o encontrado foi " << tok->value_str << endl;
		return -1;
	}
}

int casaOuSinc(node* tok, int tok_type, int first[]) {
	if (tok->token == tok_type) {
		DEBUG(cout<< "reconheceu  " << token->value_str << endl);
		getToken();
		return 1;
	} else {
		cerr << "Linha " << linha_atual<< " : Esperado " << tokenRep(tok_type)
				<< " mas o encontrado foi " << tok->value_str << endl;
		sync(first);
		return 1;
	}
}

void sync(int *syncv) {

	DEBUG(cout << "Sincronizando " << endl;)

	while (!in(syncv) && token->token != EOF) {
		getToken();
	}
	if (token->token == EOF)
		exit(1);
	else
		DEBUG(cout << "next token " << tokenRep(token->token) << endl;)
		cin.get();
		return;
}

bool in(int *v){

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

template<typename T>
const char *toStr(T source){
	stringstream ss; ss << source;
	return ss.str().c_str();
}

node* programa() {
	DEBUG(cout<< "<programa>" << endl);
	//<programa> -> <var-decls> , <decls> , <exp> ,
	node *n=NULL;
	if (in(first_programa)) {
		var_decls();
		casaToken(token, OP_VIRGULA);
		cout << "tabela símbolos inicial "<< endl;
		printhashtable(myhash,stdout);
		decls();
		casaToken(token, OP_VIRGULA);
		cout << "tabela símbolos intermediaria "<< endl;
		printhashtable(myhash,stdout);
		n = exp();
		n->token = ID;
		n->value_str = strdup("<exp>");
		n->initialized = true;
		printNode(stdout,n);
		casaToken(token, OP_VIRGULA);
		return n;
	} else {
		DEBUG(cout<< "sinc <programa>" << endl);
		mensagem_erro(first_programa,token->token);
		sync(follow_programa);
		return NULL;
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

node* var_decl() {
	DEBUG(cout<< "entrou <var_decl>" << endl);
	//<var-decl> -> <tipo-exp> : id
	node* n = NULL;
	if (in(first_var_decl)) {
		n = tipo_exp();
		casaToken(token,OP_DOIS_PONTOS);
		if(search(myhash,token->token,token->value_str)){
			cerr <<  "linha "<< linha_atual<<": variável " << token->value_str << " já declarada anteriormente!" << endl;
			exit(EXIT_FAILURE);
		}
		DEBUG(cout<< "variável "<< token->value_str << " tipo " << n->type << endl);
		token->type = n->type;
		token->initialized = false;
		n = put(myhash,token->value_str,token); //colocando na hash
		casaToken(token,ID);
		DEBUG(cout<< "saiu <var_decl>" << endl);
		return n;
	} else {
		DEBUG(cout<< "sinc <var_decl>" << endl);
		mensagem_erro(first_var_decl,token->token);
		sync(follow_var_decl);
		return NULL;
	}
}

node* tipo_exp() {
	DEBUG(cout<< "entrou <tipo_exp>" << endl);
	//<tipo-exp> -> int | float
	node* n = NULL;
	if (token->token == RW_INT) {
		n = token;
		casaToken(token,RW_INT);
		DEBUG(cout<< "saiu <tipo_exp>" << endl);
		return n;
	}else if (token->token == RW_FLOAT) {
		n = token;
		casaToken(token,RW_FLOAT);
		DEBUG(cout<< "saiu <tipo_exp>" << endl);
		return n;
	} else {
		DEBUG(cout<< "sinc <tipo_exp>" << endl);
		mensagem_erro(first_tipo_exp,token->token);
		sync(follow_tipo_exp);
		return n;
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
	node* n1 = NULL;
	node* n2 = NULL;
	if (token->token == ID) {
		n1 = search(myhash,token->token,token->value_str);
		if (!n1){
			cerr << "linha "<< linha_atual<<": Erro variável "<< token->value_str <<" não declarada!" << endl;
			exit(EXIT_FAILURE);
		}
		casaToken(token,ID);
		casaToken(token,OP_RECEBE);
		n2 = exp();
		if (n1->type == TYPE_INT && n2->type == TYPE_FLOAT){
			cerr << "linha:"<< linha_atual<<": Warning perda de precisão na atribuição! "<< endl;
			n1->value = (int)n2->value;
			n1->initialized = true;
		}
		else{
			n1->value = n2->value;
			n1->initialized = true;
		}
		DEBUG(cout<< "saiu <decl>" << endl);
		return 1;
	} else {
		DEBUG(cout<< "sinc <decl>" << endl);
		mensagem_erro(first_decl,token->token);
		sync(follow_decl);
		return 1;
	}
}

node* exp() {
	DEBUG(cout<< "entrou <exp>" << endl);
	//<exp> -> <termo> <exp-l>
	node *n=NULL;
	if (in(first_exp)) {
		n = termo();
		//printNode(stdout,n);
		cout << endl;
		n = exp_l(n);
		//printNode(stdout,n);
		DEBUG(cout<< "saiu <exp>" << endl);
		return n;
	} else {
		DEBUG(cout<< "sinc <exp>" << endl);
		mensagem_erro(first_exp,token->token);
		sync(follow_exp);
		return NULL;
	}
}

node* exp_l(node *n) {
	DEBUG(cout<< "entrou <exp>" << endl);
	//<exp-l> -> + <termo> <exp-l> | - <termo> <exp-l> | epsilon
	node *n2 = NULL;
	node *n3 = alocaNode();
	n3->value_str = strdup("<expl>");
	n3->token = ID;
	if (token->token == OP_MAIS) {
		casaToken(token,OP_MAIS);
		n2 = termo();
		if (!n->initialized){
			cerr << "linha:"<< linha_atual<<": Warning 1 variável "<< n->value_str <<"  não inicializada, assumindo valor 0! "<< endl;
		}
		if (!n2->initialized){
			cerr << "linha:"<< linha_atual<<": Warning 2 variável "<< n2->value_str <<"  não inicializada, assumindo valor 0! "<< endl;
		}
		n3->value = n->value + n2->value;
		if(n->type == TYPE_FLOAT || n2->type == TYPE_FLOAT) n3->type = TYPE_FLOAT;
		else n3->type = TYPE_INT;
		n3->initialized = true;
		n2 = exp_l(n3);
		DEBUG(cout<< "saiu <exp>" << endl);
		return n2;
	}else if (token->token == OP_MENOS) {
		casaToken(token,OP_MENOS);
		n2 = termo();
		if (!n->initialized){
			cerr << "linha:"<< linha_atual<<": Warning 3 variável "<< n->value_str <<"  não inicializada, assumindo valor 0! "<< endl;
		}
		if (!n2->initialized){
			cerr << "linha:"<< linha_atual<<": Warning 4 variável "<< n2->value_str <<"  não inicializada, assumindo valor 0! "<< endl;
		}
		n3->value = n->value - n2->value;
		if(n->type == TYPE_FLOAT || n2->type == TYPE_FLOAT) n3->type = TYPE_FLOAT;
		else n3->type = TYPE_INT;
		n3->initialized = true;
		n2 = exp_l(n3);
		DEBUG(cout<< "saiu <exp>" << endl);
		return n2;
	}else {
		//cout << "imprimindo epslon expl"<< endl;
		//printNode(stdout,n);
		return n;
	}
}

node* termo() {
	DEBUG(cout<< "entrou <termo>" << endl);
	//<termo> -> <fator> <termo-l>
	node *n = NULL;
	if (in(first_termo)) {
		n = fator();
		n = termo_l(n);
		DEBUG(cout<< "saiu <termo>" << endl);
		return n;
	} else {
		DEBUG(cout<< "sinc <termo>" << endl);
		mensagem_erro(first_termo,token->token);
		sync(follow_termo);
		return NULL;
	}
}

node* termo_l(node *n) {
	DEBUG(cout<< "entrou <exp_l>" << endl);
	//<termo-l> -> * <fator> <termo-l> | / <fator> <termo-l> | epsilon
	node *n2 = NULL;
	node n3;
	if (token->token == OP_VEZES) {
		casaToken(token,OP_VEZES);
		n2 = fator();
		if (!n->initialized){
			cerr << "linha:"<< linha_atual<<": Warning 5 variável "<< n->value_str <<"  não inicializada, assumindo valor 0! "<< endl;
		}
		if (!n2->initialized){
			cerr << "linha:"<< linha_atual<<": Warning 6 variável "<< n2->value_str <<"  não inicializada, assumindo valor 0! "<< endl;
		}
		n3.value = n->value * n2->value;
		if(n->type == TYPE_FLOAT || n2->type == TYPE_FLOAT) n3.type = TYPE_FLOAT;
		else n3.type = TYPE_INT;
		n3.initialized = true;
		n2 = termo_l(&n3);
		DEBUG(cout<< "saiu <termo_l>" << endl);
		return n2;
	}else if (token->token == OP_DIVIDIDO) {
		casaToken(token,OP_DIVIDIDO);
		n2 = fator();
		if (!n->initialized){
			cerr << "linha:"<< linha_atual<<": Warning 7 variável "<< n->value_str <<"  não inicializada, assumindo valor 0! "<< endl;
		}
		if (!n2->initialized){
			cerr << "linha:"<< linha_atual<<": Warning 8 variável "<< n2->value_str <<"  não inicializada, assumindo valor 0! "<< endl;
		}
		n3.value = n->value / n2->value;
		if(n->type == TYPE_FLOAT || n2->type == TYPE_FLOAT) n3.type = TYPE_FLOAT;
		else n3.type = TYPE_INT;
		n3.initialized = true;
		n2 = termo_l(&n3);
		DEBUG(cout<< "saiu <exp_l>" << endl);
		return n2;
	}else {
		return n;
	}
}

node* fator() {
	DEBUG(cout<< "entrou <fator>" << endl);
	//<fator> -> (<exp>) | <numero> | id
	node *n = NULL;
	if (token->token == OP_ABRE_PARENTESES) {
		casaToken(token,OP_ABRE_PARENTESES);
		n = exp();
		casaToken(token,OP_FECHA_PARENTESES);
		DEBUG(cout<< "saiu <fator>" << endl);
		return n;
	}else if (token->token == NUM_INT || token->token == NUM_FLOAT) {
		n = numero();
		DEBUG(cout<< "saiu <fator>" << endl);
		return n;
	}else if (token->token == ID) {
		n = search(myhash,token->token,token->value_str);
		if(!n){
			cerr << "linha:"<< linha_atual<<": Erro variável "<< n->value_str <<"  não declarada!  "<< endl;
			exit(0);
		}
		casaToken(token,ID);
		DEBUG(cout<< "saiu <fator>" << endl);
		return n;
	} else {
		DEBUG(cout<< "sinc <fator>" << endl);
		mensagem_erro(first_fator,token->token);
		sync(follow_fator);
		return NULL;
	}
}

node* numero() {
	DEBUG(cout<< "entrou <numero>" << endl);
	//<numero> -> numInt | numFloat
	node* n = NULL;
	if (token->token == NUM_INT) {
		n = token;
		casaToken(token,NUM_INT);
		DEBUG(cout<< "saiu <numero>" << endl);
		return n;
	}else if (token->token == NUM_FLOAT) {
		n = token;
		casaToken(token,NUM_FLOAT);
		DEBUG(cout<< "saiu <numero>" << endl);
		return n;
	}else {
		DEBUG(cout<< "sinc <numero>" << endl);
		mensagem_erro(first_numero,token->token);
		sync(follow_numero);
		return NULL;
	}
}
