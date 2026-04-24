#ifndef OBJETO_H
#define OBJETO_H

//Limite de objetos
#define MAX_OBJETOS 100

//Estrutura para representar um objeto
typedef struct {
    int id;
    double x_centro; 
    double y_profundidade; 
    double largura;
    double x_inicio;
    double x_fim;
} objeto_t;

//Variáveis globais para o TAD Objeto
extern objeto_t vobj[MAX_OBJETOS];
extern int numobj;

//Cabeçalhos das funções principais
void criaObjeto(int id, double x, double y, double largura);
void atualizaObjeto(int id, double novo_x, double novo_y);

#endif