#ifndef SYNANALYZER_HPP_
#define SYNANALYZER_HPP_

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <set>
#include <vector>
#include "Hash.hpp"
#include "Utils.hpp"
#include "LexAnalyzer.hpp"
#include "Constantes.hpp"
#include "Globals.hpp"
#include "FirstFollow.hpp"

int casaToken(node *tok,int tok_type);
int casaOuSinc(node* tok, int tok_type, int *first);
void mensagem_erro(set<int> esperados,int encontado);
int sync(int *syncv);
int in(int v[]);

int expressao();
int expressao_simples();
int expressao_simples_l();
int expressao_l();
int expressao_ll();
int expressao_lll();
int fator();
int fator_l();
int termo();
int termo_l();
int lista_expressoes();
int lista_expressoes_l();
int lista_ids();
int lista_ids_l();
int programa();
int declaracoes();
int tipo();
int tipo_padrao();
int declaracoes_subprograma();
int declaracao_subprograma();
int cabecalho_subprograma();
int argumentos();
int lista_parametros();
int lista_parametros_l();
int enunciado_composto();
int enunciados_opcionais();
int lista_enunciados();
int lista_enunciados_l();
int enunciado();
int enunciado_l();
int variavel();
int variavel_l();
int chamada_procedimento();
int chamada_procedimento_l();


#endif /* SYNANALYZER_HPP_ */
