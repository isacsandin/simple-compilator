#ifndef COMPILADOR_HPP_
#define COMPILADOR_HPP_

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include "Hash.hpp"
#include "LexAnalyzer.hpp"
#include "SynAnalyzer.hpp"
#include "Constantes.hpp"
#include "Globals.hpp"
#include "SynAnalyzer.hpp"

hashtab *myhash = NULL;
FILE *file = NULL;
node *token = NULL;
int linha_atual = 1;
int col_atual = 1;

#endif /* COMPILADOR_HPP_ */
