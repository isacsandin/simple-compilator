#include "FirstFollow.hpp"

int first_programa[] = { RW_INT ,RW_FLOAT, FINAL_V };
int first_var_decls[] = { RW_INT ,RW_FLOAT, FINAL_V };
int first_var_decls_l[] = { OP_PONTO_VIRGULA , FINAL_V };
int first_var_decl[] = { RW_INT ,RW_FLOAT, FINAL_V };
int first_tipo_exp[] = { RW_INT ,RW_FLOAT, FINAL_V };
int first_decls[] = { ID , FINAL_V };
int first_decls_l[] = { OP_PONTO_VIRGULA , FINAL_V };
int first_decl[] = { ID , FINAL_V };
int first_exp[] = { OP_ABRE_PARENTESES , NUM_INT , NUM_FLOAT , ID , FINAL_V };
int first_exp_l[] = { OP_MAIS , OP_MENOS , FINAL_V };
int first_termo[] = { OP_ABRE_PARENTESES , NUM_INT , NUM_FLOAT , ID , FINAL_V };
int first_termo_l[] = { OP_VEZES , OP_DIVIDIDO , FINAL_V };
int first_fator[] = { OP_ABRE_PARENTESES , NUM_INT , NUM_FLOAT , ID , FINAL_V };
int first_numero[] = { NUM_INT , NUM_FLOAT , FINAL_V };

int follow_programa[] = { EOF , FINAL_V };
int follow_var_decls[] = { OP_VIRGULA , FINAL_V };
int follow_var_decls_l[] = { OP_VIRGULA , FINAL_V };
int follow_var_decl[] = { OP_PONTO_VIRGULA , OP_VIRGULA , OP_DOIS_PONTOS , FINAL_V };
int follow_tipo_exp[] = { OP_DOIS_PONTOS , FINAL_V };
int follow_decls[] = { OP_VIRGULA , FINAL_V };
int follow_decls_l[] = { OP_VIRGULA , FINAL_V };
int follow_decl[] = { OP_PONTO_VIRGULA , OP_VIRGULA , FINAL_V };
int follow_exp[] = { OP_PONTO_VIRGULA , OP_VIRGULA , OP_FECHA_PARENTESES , FINAL_V };
int follow_exp_l[] = { OP_PONTO_VIRGULA , OP_VIRGULA , OP_FECHA_PARENTESES , FINAL_V };
int follow_termo[] = { OP_MAIS , OP_MENOS , OP_PONTO_VIRGULA , OP_VIRGULA , OP_FECHA_PARENTESES , FINAL_V };
int follow_termo_l[] = { OP_MAIS , OP_MENOS , OP_PONTO_VIRGULA , OP_VIRGULA , OP_FECHA_PARENTESES , FINAL_V };
int follow_fator[] = { OP_VEZES , OP_DIVIDIDO , OP_MAIS , OP_MENOS , OP_PONTO_VIRGULA , OP_VIRGULA , OP_FECHA_PARENTESES , FINAL_V };
int follow_numero[] = { OP_VEZES , OP_DIVIDIDO , OP_MAIS , OP_MENOS , OP_PONTO_VIRGULA , OP_VIRGULA , OP_FECHA_PARENTESES , FINAL_V };
