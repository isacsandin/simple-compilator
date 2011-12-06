#ifndef HASH_HPP_
#define HASH_HPP_
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "Constantes.hpp"

typedef struct _node{
	int token;
	char* value_str;
	float value;
	bool initialized;
	int type;
	struct _node *next;
}node;

typedef struct _hashtab{
	node** tab;
	int tamanho;
}hashtab;

hashtab *inithashtab(int tamanho);

node *alocaNode();

node *alocaNode(int tok,const char* value_str,float value,node* next);

unsigned int hash(const char* str,int tamanho);

node* search(hashtab *h,int tok,const char *key);

node *put(hashtab *h,const char* key,node* n);

void printhashtable(hashtab *h,FILE *f);

const char *tokenRep(int tok);

void cleanup(hashtab *h);


#endif /* HASH_HPP_ */
