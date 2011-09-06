#include "Hash.hpp"
#include "Utils.hpp"

hashtab *inithashtab(int tamanho){
	int i;
	hashtab* h = (hashtab*)malloc(sizeof(hashtab));
	h->tab = (node**)malloc(tamanho*sizeof(node*));
	for(i=0;i<tamanho;i++)
		h->tab[i]=NULL;
	h->tamanho = tamanho;
	return h;
}

node *alocaNode(){
	return (node*)malloc(sizeof(node));
}

unsigned int hash(const char* str,int tamanho){
	unsigned int hash = 0;
	unsigned int x    = 0;
	unsigned int i    = 0;
	unsigned int len  = strlen(str);
	for(i = 0; i < len; str++, i++){
		hash = (hash << 4) + (*str);
		if((x = hash & 0xF0000000L) != 0){
			hash ^= (x >> 24);
		}
		hash &= ~x;
	}
	return hash%tamanho;
}

node* search(hashtab *h,const char *key){
	unsigned int hi=hash(key,h->tamanho);
	node* np=h->tab[hi];
	for(;np!=NULL;np=np->next){
		if(!strcmp(np->key,key))
			return np;
	}
	return NULL;
}

bool remove(hashtab *h,const char *key){
	unsigned int hi=hash(key,h->tamanho);
	node* np=h->tab[hi];
	node* tmp;
	//caso nao tenha nodos...
	if(np == NULL) return false;
	//caso o nodo seja o primeiro
	if(!strcmp(np->key,key)){
		h->tab[hi]=np->next;
		free(np);
		return true;
	}
	//caso contrario
	else{
		tmp = np;
		np=np->next;
		while(np!=NULL){
			if(!strcmp(np->key,key)){
					tmp->next = tmp->next->next;
					free(np);
					return true;
			}
			tmp = np;
			np=np->next;
			}
	}
	return false;
}

bool put(hashtab *h,const char* key,node* n){
	unsigned int hi;

	if(search(h,key) == NULL){
		hi=hash(key,h->tamanho);

		if(n==NULL)
			return false;
		n->next=h->tab[hi];
		h->tab[hi]=n;
		return true;
	}
	else
		return false;
}

bool put(hashtab *h,const char* key,const char* value){
	unsigned int hi;
	if(search(h,key) == NULL){
		hi=hash(key,h->tamanho);
		node* n = (node*)malloc(sizeof(node));
		n->key = strdup(key);
		n->value = strdup(value);
		n->next=h->tab[hi];
		h->tab[hi]=n;
		return true;
	}
	else
		return false;
}

void printhashtable(hashtab *h){
	int i;
	node* np;
	for(i=0;i<h->tamanho;i++){
		if(h->tab[i]!=NULL){
			np=h->tab[i];
			printf("%d:",i);
			while(np!=NULL){
				printf("(%s %s)",np->key,np->value);
				np=np->next;
			}
			printf("\n");
		}
	}
}

void cleanup(hashtab *h){
	int i;
	node *np,*t;
	for(i=0;i<h->tamanho;i++){
		if(h->tab[i]!=NULL){
			np=h->tab[i];
			while(np!=NULL){
				t=np->next;
				free(np->value);
				free(np);
				np=t;
			}
		}
	}
}
