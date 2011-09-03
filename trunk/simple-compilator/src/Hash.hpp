#ifndef HASH_HPP_
#define HASH_HPP_

#include <cstdio>
#include <cstdlib>
#include <cstring>

typedef struct _node{
	char* key;
	char* value;
	struct _node *next;
}node;

typedef struct _hashtab{
	node** tab;
	int tamanho;
}hashtab;

hashtab *inithashtab(int tamanho);
unsigned int hash(const char* str,int tamanho);
node* search(hashtab *h,const char *key);
bool remove(hashtab *h,const char *key);
bool put(hashtab *h,const char* key,node* n);
bool put(hashtab *h,const char* key,const char* value);
void printhashtable(hashtab *h);
void cleanup(hashtab *h);


#endif /* HASH_HPP_ */
