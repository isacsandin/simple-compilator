#ifndef LEXANALYZER_HPP_
#define LEXANALYZER_HPP_

#include <cstring>
#include <sstream>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include "Hash.hpp"
#include "Utils.hpp"
#include "Constantes.hpp"
#include "Globals.hpp"

using namespace std;

static int linha_atual=1;

int get();
int unget(char c);
void getToken();

#endif /* LEXANALYZER_HPP_ */
