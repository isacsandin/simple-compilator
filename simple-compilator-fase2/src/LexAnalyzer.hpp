#ifndef LEXANALYZER_HPP_
#define LEXANALYZER_HPP_

#include <cstring>
#include <sstream>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include "Hash.hpp"
#include "Constantes.hpp"
#include "Globals.hpp"

using namespace std;

int get();
int unget(char c);
void getToken();

#endif /* LEXANALYZER_HPP_ */
