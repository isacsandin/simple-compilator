#include "LexAnalyzer.hpp"

using namespace std;

void reconhece(string key,string valor){
	cout << key << " " << valor << endl;
}

string lexan(FILE* file){
	char token = ' ';
	stringstream tmp, resultado;
	int state = 0;
	if(file){
		if(!feof(file)){
			while(true){
				switch (state) {
				case 0:
					//cout << "estado zero" << endl;
					token = getc(file);
					switch (token) {
					case '+':
						reconhece("OP_MAIS","+");
						resultado.clear();
						state = 8;
						resultado << "OP_MAIS";
						break;
					case '-':
						reconhece("OP_MENOS","-");
						resultado.clear();
						state = 8;
						resultado << "OP_MAIS";
						break;
					case '*':
						reconhece("OP_ASTERISCO","*");
						resultado.clear();
						state = 8;
						resultado << "OP_ASTERISCO";
						break;
					case '/':
						state = 1;
						break;
					case '<':
						state = 2;
						break;
					case '>':
						state = 3;
						break;
					case '=':
						reconhece("OP_IGUAL","=");
						resultado.clear();
						state = 8;
						resultado << "OP_IGUAL";
						break;
					case ':':
						state = 4;
						break;
					case '[':
						reconhece("OP_ABRE_COLCHETE","[");
						resultado.clear();
						state = 8;
						resultado << "OP_ABRE_COLCHETE";
						break;
					case ']':
						reconhece("OP_FECHA_COLCHETE","]");
						resultado.clear();
						state = 8;
						resultado << "OP_FECHA_COLCHETE";
						break;
					case '{': //comentario
						state = 5;
						break;
					case '(':
						reconhece("OP_ABRE_PARENTESES","(");
						resultado.clear();
						state = 8;
						resultado << "OP_ABRE_PARENTESES";
						break;
					case ')':
						reconhece("OP_FECHA_PARENTESES",")");
						resultado.clear();
						state = 8;
						resultado << "OP_FECHA_PARENTESES";
						break;
					case ';':
						reconhece("OP_PONTO_VIRGULA",";");
						resultado.clear();
						state = 8;
						resultado << "OP_PONTO_VIRGULA";
						break;
					case ',':
						reconhece("OP_VIRGULA",",");
						resultado.clear();
						state = 8;
						resultado << "OP_VIRGULA";
						break;
					case '.':
						reconhece("OP_PONTO",".");
						resultado.clear();
						state = 8;
						resultado << "OP_PONTO";
						break;
				default:
					if (isdigit(token)){
						if(token == '0'){
							reconhece("NUM","0");
							resultado.clear();
							state = 8;
							resultado << "NUM:0";
							break;
						}
						else{
							state = 6;
							break;
						}
					}
					else if (isalpha(token)){
						state = 7;
						break;
					}
					else{
						resultado.clear();
						state = 8;
						resultado << "ERRO=> "+token;
						break;
					}
				}
				break;
				case 1: //comentario uma linha
					//cout << "estado um" << endl;
					token = getc(file);
					switch (token) {
					case '/':
						tmp.clear();
						token = getc(file);
						while(token != '\n'){
							tmp << token;
							token = getc(file);
						}
						cout << "COMENTARIO: " << tmp.str() << endl;
						state = 0;
						break;
					default:
						ungetc(token,file);
						reconhece("OP_BARRA","/");
						resultado.clear();
						state = 8;
						resultado << "OP_BARRA";
						break;
					}
					break;
				case 2:
					//cout << "estado dois" << endl;
					token = getc(file);
					switch (token) {
					case '=':
						reconhece("OP_MENOR_IGUAL","<=");
						resultado.clear();
						state = 8;
						resultado << "OP_MENOR_IGUAL";
						break;
					case '>':
						reconhece("OP_DIFERENTE","<>");
						resultado.clear();
						state = 8;
						resultado << "OP_DIFERENTE";
						break;
					default:
						ungetc(token,file);
						reconhece("OP_MENOR","<");
						resultado.clear();
						state = 8;
						resultado << "OP_MENOR";
						break;
					}
					break;
				case 3:
					//cout << "estado tres" << endl;
					token = getc(file);
					switch (token) {
					case '=':
						reconhece("OP_MAIOR_IGUAL",">=");
						resultado.clear();
						state = 8;
						resultado << "OP_MAIOR_IGUAL";
						break;
					default:
						ungetc(token,file);
						reconhece("OP_MAIOR",">");
						resultado.clear();
						state = 8;
						resultado << "OP_MAIOR";
						break;
					}
					break;
				case 4:
					//cout << "estado quatro" << endl;
					token = getc(file);
					switch (token) {
					case '=':
						reconhece("OP_RECEBE",":=");
						resultado.clear();
						state = 8;
						resultado << "OP_RECEBE";
						break;
					default:
						ungetc(token,file);
						resultado.clear();
						state = 8;
						resultado << "DOIS PONTOS SEM IGUAL";
						break;
					}
					break;
				case 5://comentario multiplas linhas
					//cout << "estado cinco" << endl;
					tmp.clear();
					token = getc(file);
					while (token != '}') {
						tmp << token;
						token = getc(file);
					}
					cout << "COMENTARIO: " << tmp.str() << endl;
					state = 0;
					break;
				case 6: //numeros
					//cout << "estado seis" << endl;
					tmp.clear();
					tmp << token;
					token = getc(file);
					while (isdigit(token)){
						tmp << token;
						token = getc(file);
					}
					ungetc(token,file);
					reconhece("NUM",tmp.str());
					resultado.clear();
					state = 8;
					resultado << "NUM:"+tmp.str();
					break;
				case 7: //id
					//cout << "estado sete" << endl;
					tmp << token;
					token = getc(file);
					while (isalnum(token)){
						tmp << token;
						token = getc(file);
					}
					ungetc(token,file);
					reconhece("ID",tmp.str());
					resultado.clear();
					state = 8;
					resultado << "ID:"+ tmp.str();
					break;
				case 8:
					return resultado.str();
				default:
					cout << "estado indefinido!" << endl;
					break;
				}
			}
		}
		else{
			return "EOF";
		}
	}
	else{
		cout << "erro no arquivo" << endl;
		exit(1);
	}
	return "ERRO kkk";
}




