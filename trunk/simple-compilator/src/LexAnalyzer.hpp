#ifndef LEXANALYZER_HPP_
#define LEXANALYZER_HPP_

using namespace std;

static int linha_atual=1;

int get();
int unget(char c);
void getToken();

#endif /* LEXANALYZER_HPP_ */
