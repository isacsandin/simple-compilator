#ifndef COMPILADOR_HPP_
#define COMPILADOR_HPP_

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include "Hash.hpp"
#include "Utils.hpp"
#include "LexAnalyzer.hpp"
#include "SynAnalyzer.hpp"
#include "Constantes.hpp"
#include "Globals.hpp"
#include "SynAnalyzer.hpp"

extern hashtab *myhash;
extern FILE *file;
extern node *token;

#endif /* COMPILADOR_HPP_ */
