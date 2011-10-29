#ifndef HASH_HPP_
#define HASH_HPP_

typedef struct _node{
	int token;
	char* value;
	int value_int;
	struct _node *next;
}node;

typedef struct _hashtab{
	node** tab;
	int tamanho;
}hashtab;

hashtab *inithashtab(int tamanho);

node *alocaNode();

node *alocaNode(int tok,const char* value,int value_int,node* next);

unsigned int hash(const char* str,int tamanho);

node* search(hashtab *h,int tok,const char *key);

node *put(hashtab *h,const char* key,node* n);

void printhashtable(hashtab *h,FILE *f);

char *tokenRep(int tok);

void cleanup(hashtab *h);


#endif /* HASH_HPP_ */