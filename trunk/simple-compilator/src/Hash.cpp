#include "Hash.hpp"
#include "Utils.hpp"
#include "Constantes.hpp"

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

node *alocaNode(int token,const char* value,int value_int,node* next){
	node *n = alocaNode();
	if(n){
	n->token = token;
	n->value = strdup(value);
	n->value_int = value_int;
	n->next = next;
	}
	return n;
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

node* search(hashtab *h,int token,const char *key){
	unsigned int hi=hash(key,h->tamanho);
	node* np=h->tab[hi];

	for(;np!=NULL;np=np->next){
			if(np->token == token && !strcmp(np->value,key))
				return np;
		}

	return NULL;
}

//bool remove(hashtab *h,const char *key){
//	unsigned int hi=hash(key,h->tamanho);
//	node* np=h->tab[hi];
//	node* tmp;
//	//caso nao tenha nodos...
//	if(np == NULL) return false;
//	//caso o nodo seja o primeiro
//	if(!strcmp(np->key,key)){
//		h->tab[hi]=np->next;
//		free(np);
//		return true;
//	}
//	//caso contrario
//	else{
//		tmp = np;
//		np=np->next;
//		while(np!=NULL){
//			if(!strcmp(np->key,key)){
//					tmp->next = tmp->next->next;
//					free(np);
//					return true;
//			}
//			tmp = np;
//			np=np->next;
//			}
//	}
//	return false;
//}

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
				fprintf(f,"(%s %s %d)",tokenRep(np->token),np->value,np->value_int);
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
				free(np->value);
				free(np);
				np=t;
			}
		}
	}
}

char *tokenRep(int token){
	char *saida;
	switch(token){
		case 298: saida = "ID"; break;
		case 299: saida = "NUM"; break;
		case 300: saida = "RW_PROGRAMA"; break;
		case 301: saida = "RW_DECLARE"; break;
		case 302: saida = "RW_FIM_DECLARE"; break;
		case 303: saida = "RW_ARRANJO"; break;
		case 304: saida = "RW_DE"; break;
		case 305: saida = "RW_NUMERICO"; break;
		case 306: saida = "RW_BOOLEANO"; break;
		case 307: saida = "RW_VERDADEIRO"; break;
		case 308: saida = "RW_FALSO"; break;
		case 309: saida = "RW_PROCEDIMENTO"; break;
		case 310: saida = "RW_FUNCAO"; break;
		case 311: saida = "RW_SE"; break;
		case 312: saida = "RW_ENTAO"; break;
		case 313: saida = "RW_SENAO"; break;
		case 314: saida = "RW_ENQUANTO"; break;
		case 315: saida = "RW_FACA"; break;
		case 316: saida = "RW_RETORNE"; break;
		case 317: saida = "RW_E"; break;
		case 318: saida = "RW_OU"; break;
		case 319: saida = "RW_INICIO"; break;
		case 320: saida = "RW_FIM"; break;
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
