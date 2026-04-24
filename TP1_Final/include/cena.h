#ifndef CENA_H
#define CENA_H

#include "objeto.h"

//Limites de cenas e segmentos oclusos
#define MAX_CENAS_ITENS 50
#define MAX_SEGMENTOS_OCLUSOS 200

//Estrutura para representar a parte visível de um objeto
typedef struct {
    int tempo; 
    int id;    
    double inicio; 
    double fim;    
} cena_item_t;

extern cena_item_t cena_v[MAX_CENAS_ITENS];
extern int numcena;

//Cabeçalhos das funções principais
void OrdenaPorY(objeto_t *vobj_ptr, int numobj_ptr);
bool objetoVisivel(objeto_t &obj);
void adicionaObj(objeto_t obj, cena_item_t *cena_ptr, int *numcena_ptr);
void geraCena(objeto_t *vobj_ptr, int numobj_ptr, cena_item_t *cena_ptr, int *numcena_ptr);

#endif