using namespace std;
string lexan(FILE* file){
	char token;
	int state = 0;
	if(file){
		if(!feof(file)){
			switch (state) {
			case 0:
				token = getc(file);
				switch (token) {
				case '+':
					reconhece("OP_MAIS","+");
					return "OP_MAIS";
					break;
				case '-':
					reconhece("OP_MENOS","-");
					state = 0;
					break;
				case '*':
					reconhece("OP_ASTERISCO","*");
					state = 0;
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
					state = 0;
					break;
				case ':':
					state = 4;
					break;
				case '[':
					reconhece("OP_ABRE_COLCHETE","[");
					state = 0;
					break;
				case ']':
					reconhece("OP_FECHA_COLCHETE","]");
					state = 0;
					break;
				case '{': //comentario
					state = 5;
					break;
				case '(':
					reconhece("OP_ABRE_PARENTESES","(");
					state = 0;
					break;
				case ')':
					reconhece("OP_FECHA_PARENTESES",")");
					state = 0;
					break;
				case ';':
					reconhece("OP_PONTO_VIRGULA",";");
					state = 0;
					break;
				case ',':
					reconhece("OP_VIRGULA",",");
					state = 0;
					break;
				case '.':
					reconhece("OP_PONTO",".");
					state = 0;
					break;
			default:
				if (isdigit(token)){
					if(token == '0'){
						reconhece("NUM","0");
						state = 0;
						break;
					}
					else{
						state = 5;
						break;
					}
				}
				else if (isalpha(token)){
					state = 6;
					break;
				}
				else{
					//caractere invalido
					break;
				}
			}
			break;
			case 2:
				token = getc(file);
				switch (token) {
				case '/':
					token = getc(file);
					while(token != '\n') token = getc(file);
					state = 0;
					break;
				default:
					ungetc(token,file);
					reconhece("OP_BARRA","/");
					state = 0;
					break;
				}
				break;
				case 3:
					switch (token) {
					case '=':
						reconhece("OP_MENOR_IGUAL","<=");
						state = 0;
						break;
					case '>':
						reconhece("OP_DIFERENTE","<>");
						state = 0;
						break;
					default:
						ungetc(token,file);
						state = 0;
						break;
					}
					break;
					case 4:
						switch (token) {
						case '=':
							reconhece("OP_MAIOR_IGUAL",">=");
							state = 0;
							break;
						default:
							ungetc(token,file);
							//possivel erro
							state = 0;
							break;
						}
						break;
					case 2:
						token = getc(file);
						switch (token) {
						case '/':
							token = getc(file);
							while(token != '\n') token = getc(file);
							state = 0;
							break;
						default:
							ungetc(token,file);
							reconhece("OP_BARRA","/");
							state = 0;
							break;
						}
						break;
					case 5:
						switch (token) {
						case '=':
							reconhece("OP_RECEBE",":=");
							state = 0;
							break;
						default:
							ungetc(token,file);
							state = 0;
							break;
						}
						break;
					case 6: //numeros
						stringstream id = "";
						id << token;
						token = getc(file);
						while (isdigit(token)){
							id << token;
							token = getc(file);
						}
						break;
					default:
						break;
			}
		}
		else{
			return "EOF";
		}
	}
	return "";
}




