#ifndef SYNANALYZER_HPP_
#define SYNANALYZER_HPP_

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <set>
#include <vector>
#include "Hash.hpp"
#include "LexAnalyzer.hpp"
#include "Constantes.hpp"
#include "Globals.hpp"
#include "FirstFollow.hpp"

int casaToken(node *tok,int tok_type);
int casaOuSinc(node* tok, int tok_type, int *first);
void mensagem_erro(set<int> esperados,int encontado);
void sync(int *syncv);
bool in(int v[]);

int programa();
int var_decls();
int var_decls_l();
node* var_decl();
node* tipo_exp();
int decls();
int decls_l();
int decl();
node* exp();
node* exp_l(node*);
node* termo();
node* termo_l(node*);
node* fator();
node* numero();


#endif /* SYNANALYZER_HPP_ */
