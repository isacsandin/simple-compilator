#ifndef SYNANALYZER_HPP_
#define SYNANALYZER_HPP_

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include "Hash.hpp"
#include "Utils.hpp"
#include "LexAnalyzer.hpp"
#include "Constantes.hpp"
#include "Globals.hpp"

extern hashtab *myhash;
extern FILE *file;
extern node *token;;


int casaToken(node *tok,int tok_type);
int expressao();
int expressao_simples();
int expressao_l();
int expressao_ll();
int expressao_lll();


#endif /* SYNANALYZER_HPP_ */
