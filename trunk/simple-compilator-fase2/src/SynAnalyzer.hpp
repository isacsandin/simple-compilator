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
int sync(int *syncv);
int in(int v[]);

int programa();
int var_decls();
int var_decls_l();
int var_decl();
int tipo_exp();
int decls();
int decls_l();
int decl();
int exp();
int exp_l();
int termo();
int termo_l();
int fator();
int numero();


#endif /* SYNANALYZER_HPP_ */
