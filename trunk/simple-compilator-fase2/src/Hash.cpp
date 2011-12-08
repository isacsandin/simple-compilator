#include "Hash.hpp"


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

node *alocaNode(int tok,const char* value_str,float value,node* next){
	node *n = alocaNode();
	if(n){
	n->token = tok;
	n->value_str = strdup(value_str);
	n->value = value;
	n->initialized = false;
	n->type = TYPE_NONE;
	n->next = next;
	}
	return n;
}

void printNode(FILE *f,node* np){
	fprintf(f,"imprimindo nodo");
	fprintf(f,"(%s %s %f init:%d)",tokenRep(np->token),np->value_str,np->value,(bool)np->initialized);
	fprintf(f,"\n");
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

node* search(hashtab *h,int tok,const char *key){
	unsigned int hi=hash(key,h->tamanho);
	node* np=h->tab[hi];

	for(;np!=NULL;np=np->next){
			if(np->token == tok && !strcmp(np->value_str,key))
				return np;
		}

	return NULL;
}

node *put(hashtab *h,const char* key,node* n){
	unsigned int hi;

	node *np = search(h,n->token,key);

	if(n==NULL)
		return NULL;

	if( np == NULL){
		hi=hash(key,h->tamanho);
		n->next=h->tab[hi];
		h->tab[hi]=n;
		return n;
	}
	else
		return np;
}

void printhashtable(hashtab *h,FILE *f){
	int i;
	node* np;
	for(i=0;i<h->tamanho;i++){
		if(h->tab[i]!=NULL){
			np=h->tab[i];
			fprintf(f,"%d:",i);
			while(np!=NULL){
				if(np->type == TYPE_INT)
					fprintf(f,"(%s %s %d init:%d)",tokenRep(np->token),np->value_str,(int)np->value,np->initialized);
				else
					fprintf(f,"(%s %s %f init:%d)",tokenRep(np->token),np->value_str,np->value,np->initialized);
				np=np->next;
			}
			fprintf(f,"\n");
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
				free(np->value_str);
				free(np);
				np=t;
			}
		}
	}
}

const char *tokenRep(int token){
	const char *saida;
	switch(token){
		case 294: saida = "TYPE_NONE";break;
		case 295: saida = "TYPE_INT";break;
		case 296: saida = "TYPE_FLOAT";break;
		case 297: saida = "ID"; break;
		case 298: saida = "NUM_INT"; break;
		case 299: saida = "NUM_FLOAT"; break;
		case 300: saida = "RW_INT"; break;
		case 301: saida = "RW_FLOAT"; break;
		case 321: saida = "OP_MAIS"; break;
		case 322: saida = "OP_MENOS"; break;
		case 323: saida = "OP_VEZES"; break;
		case 324: saida = "OP_DIVIDIDO"; break;
		case 325: saida = "OP_MENOR"; break;
		case 326: saida = "OP_MAIOR"; break;
		case 327: saida = "OP_MENOR_IGUAL"; break;
		case 328: saida = "OP_MAIOR_IGUAL"; break;
		case 329: saida = "OP_IGUAL"; break;
		case 330: saida = "OP_DIFERENTE"; break;
		case 331: saida = "OP_RECEBE"; break;
		case 332: saida = "OP_ABRE_COLCHETE"; break;
		case 333: saida = "OP_FECHA_COLCHETE"; break;
		case 334: saida = "OP_ABRE_CHAVES"; break;
		case 335: saida = "OP_FECHA_CHAVES"; break;
		case 336: saida = "OP_ABRE_PARENTESES"; break;
		case 337: saida = "OP_FECHA_PARENTESES"; break;
		case 338: saida = "OP_DOIS_PONTOS"; break;
		case 339: saida = "OP_PONTO_VIRGULA"; break;
		case 340: saida = "OP_VIRGULA"; break;
		case 341: saida = "OP_PONTO"; break;
		default: saida = "FERROU"; break;
	}
	return saida;
}
