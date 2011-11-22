#include "FirstFollow.hpp"

int first_programa[] = { RW_PROGRAMA , FINAL_V };
int first_lista_ids[] = { ID , FINAL_V };
int first_lista_ids_l[] = { OP_PONTO_VIRGULA , FINAL_V };
int first_declaracoes[] = { RW_DECLARE , FINAL_V };
int first_tipo[] = { RW_NUMERICO , RW_BOOLEANO , RW_ARRANJO, FINAL_V };
int first_tipo_padrao[] = { RW_NUMERICO , RW_BOOLEANO , FINAL_V };
int first_declaracao_subprogramas[] = { RW_FUNCAO , RW_PROCEDIMENTO , FINAL_V };
int first_declaracao_subprograma[] = { RW_FUNCAO , RW_PROCEDIMENTO , FINAL_V };
int first_cabecalho_de_subprograma[] = { RW_FUNCAO , RW_PROCEDIMENTO , FINAL_V };
int first_argumentos[] = { OP_ABRE_PARENTESES , FINAL_V };
int first_lista_de_parametros[] = { ID , FINAL_V };
int first_lista_de_parametros_l[] = { OP_PONTO_VIRGULA , FINAL_V };
int first_enunciado_composto[] = { RW_INICIO , FINAL_V };
int first_enunciados_opcionais[] = { ID , RW_INICIO , RW_SE , RW_ENQUANTO , FINAL_V };
int first_lista_de_enunciados[] = { ID , RW_INICIO , RW_SE , RW_ENQUANTO , FINAL_V };
int first_lista_de_enunciados_l[] = { OP_PONTO_VIRGULA , FINAL_V };
int first_enunciado[] = { ID , RW_INICIO , RW_SE , RW_ENQUANTO , FINAL_V };
int first_enunciado_l[] = { OP_ABRE_COLCHETE , OP_ABRE_PARENTESES , FINAL_V };
int first_variavel_l[] = { OP_ABRE_COLCHETE , OP_ABRE_PARENTESES , FINAL_V };
int first_chamada_procedimento_l[] = { OP_ABRE_PARENTESES , FINAL_V };
int first_lista_expressoes[] = { ID , NUM , OP_ABRE_PARENTESES , FINAL_V };
int first_lista_expressoes_l[] = { OP_VIRGULA , FINAL_V };
int first_expressao[] = { ID , NUM , OP_ABRE_PARENTESES , FINAL_V };
int first_expressao_l[] = { OP_MENOR , OP_MAIOR , OP_MENOR_IGUAL , OP_MAIOR_IGUAL , OP_IGUAL , OP_DIFERENTE , FINAL_V };
int first_expressao_simples[] = { ID , NUM , OP_ABRE_PARENTESES , FINAL_V };
int first_expressao_simples_l[] = { OP_MAIS , OP_MENOS , FINAL_V };
int first_termo[] = { ID , NUM , OP_ABRE_PARENTESES , FINAL_V };
int first_termo_l[] = { OP_VEZES , OP_DIVIDIDO , FINAL_V };
int first_fator[] = { ID , NUM , OP_ABRE_PARENTESES , FINAL_V };
int first_fator_l[] = { OP_ABRE_PARENTESES , FINAL_V };



int follow_programa[] = { EOF , FINAL_V };
int follow_lista_ids[] = { OP_DOIS_PONTOS , FINAL_V };
int follow_lista_ids_l[] = { OP_DOIS_PONTOS , FINAL_V };
int follow_declaracoes[] = { RW_FUNCAO, RW_PROCEDIMENTO , RW_INICIO , FINAL_V };
int follow_tipo[] = { OP_PONTO_VIRGULA , OP_VIRGULA , OP_FECHA_PARENTESES, FINAL_V };
int follow_tipo_padrao[] = { OP_PONTO_VIRGULA , OP_VIRGULA , OP_FECHA_PARENTESES , FINAL_V };
int follow_declaracoes_subprograma[] = { RW_INICIO , FINAL_V };
int follow_declaracao_subprograma[] = { OP_PONTO_VIRGULA , FINAL_V };
int follow_cabecalho_de_subprograma[] = { RW_DECLARE , FINAL_V };
int follow_argumentos[] = { OP_DOIS_PONTOS , OP_PONTO_VIRGULA , FINAL_V };
int follow_lista_de_parametros[] = { OP_FECHA_PARENTESES , FINAL_V };
int follow_lista_de_parametros_l[] = { OP_FECHA_PARENTESES , FINAL_V };
int follow_enunciado_composto[] = { OP_PONTO , OP_PONTO_VIRGULA , RW_FIM , RW_SENAO , FINAL_V };
int follow_enunciados_opcionais[] = { RW_FIM , FINAL_V };
int follow_lista_de_enunciados[] = { RW_FIM , FINAL_V };
int follow_lista_de_enunciados_l[] = { RW_FIM , FINAL_V };
int follow_enunciado[] = { OP_PONTO_VIRGULA , RW_FIM , RW_SENAO , FINAL_V };
int follow_enunciado_l[] = { OP_PONTO_VIRGULA , RW_FIM , RW_SENAO , FINAL_V };
int follow_variavel_l[] = { OP_ABRE_COLCHETE , FINAL_V };
int follow_chamada_procedimento_l[] = { OP_PONTO_VIRGULA , RW_FIM , RW_SENAO , FINAL_V };
int follow_lista_expressoes[] = { OP_FECHA_PARENTESES , FINAL_V };
int follow_lista_expressoes_l[] = { OP_FECHA_PARENTESES , FINAL_V };
int follow_expressao[] = { RW_ENTAO , RW_FACA , OP_PONTO_VIRGULA , RW_FIM , RW_SENAO , OP_FECHA_COLCHETE , OP_VIRGULA , OP_FECHA_PARENTESES , FINAL_V };
int follow_expressao_l[] = { RW_ENTAO , RW_FACA , OP_PONTO_VIRGULA , RW_FIM , RW_SENAO , OP_FECHA_COLCHETE , OP_VIRGULA , OP_FECHA_PARENTESES , FINAL_V };
int follow_expressao_simples[] = { OP_MENOR , OP_MAIOR , OP_MENOR_IGUAL , OP_MAIOR_IGUAL , OP_IGUAL , OP_DIFERENTE , RW_ENTAO , RW_FACA , OP_PONTO_VIRGULA , RW_FIM , RW_SENAO , OP_FECHA_COLCHETE , OP_VIRGULA , OP_FECHA_PARENTESES , FINAL_V };
int follow_expressao_simples_l[] = { OP_MENOR , OP_MAIOR , OP_MENOR_IGUAL , OP_MAIOR_IGUAL , OP_IGUAL , OP_DIFERENTE , RW_ENTAO , RW_FACA , OP_PONTO_VIRGULA , RW_FIM , RW_SENAO , OP_FECHA_COLCHETE , OP_VIRGULA , OP_FECHA_PARENTESES , FINAL_V };
int follow_termo[] = { OP_MAIS , OP_MENOS , OP_MENOR , OP_MAIOR , OP_MENOR_IGUAL , OP_MAIOR_IGUAL , OP_IGUAL , OP_DIFERENTE , RW_ENTAO , RW_FACA , OP_PONTO_VIRGULA , RW_FIM , RW_SENAO , OP_FECHA_COLCHETE , OP_VIRGULA , OP_FECHA_PARENTESES , FINAL_V };
int follow_termo_l[] = { OP_MAIS , OP_MENOS , OP_MENOR , OP_MAIOR , OP_MENOR_IGUAL , OP_MAIOR_IGUAL , OP_IGUAL , OP_DIFERENTE , RW_ENTAO , RW_FACA , OP_PONTO_VIRGULA , RW_FIM , RW_SENAO , OP_FECHA_COLCHETE , OP_VIRGULA , OP_FECHA_PARENTESES , FINAL_V };
int follow_fator[] = { OP_VEZES , OP_DIVIDIDO , OP_MAIS , OP_MENOS , OP_MENOR , OP_MAIOR , OP_MENOR_IGUAL , OP_MAIOR_IGUAL , OP_IGUAL , OP_DIFERENTE , RW_ENTAO , RW_FACA , OP_PONTO_VIRGULA , RW_FIM , RW_SENAO , OP_FECHA_COLCHETE , OP_VIRGULA , OP_FECHA_PARENTESES , FINAL_V };
int follow_fator_l[] = { OP_VEZES , OP_DIVIDIDO , OP_MAIS , OP_MENOS , OP_MENOR , OP_MAIOR , OP_MENOR_IGUAL , OP_MAIOR_IGUAL , OP_IGUAL , OP_DIFERENTE , RW_ENTAO , RW_FACA , OP_PONTO_VIRGULA , RW_FIM , RW_SENAO , OP_FECHA_COLCHETE , OP_VIRGULA , OP_FECHA_PARENTESES , FINAL_V };

