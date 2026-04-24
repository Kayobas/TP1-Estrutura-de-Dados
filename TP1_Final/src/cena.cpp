#include "cena.h"
#include <iostream>
#include <cmath>

//Funções auxiliares para maximo e minimo
double custom_max(double a, double b) {
    return (a > b) ? a : b;
}

double custom_min(double a, double b) {
    return (a < b) ? a : b;
}

//Estrutura para representar um segmento ocupado
typedef struct {
    double inicio;
    double fim;
} segmento_ocupado_t;

//Limites de cenas e segmentos oclusos
#ifndef MAX_CENAS_ITENS
#define MAX_CENAS_ITENS 50
#endif

#define MAX_SEGMENTOS_OCLUSOS 200

//Variáveis globais para o TAD Cena
cena_item_t cena_v[MAX_CENAS_ITENS];
int numcena = 0;

segmento_ocupado_t espaco_ocupado[MAX_SEGMENTOS_OCLUSOS];
int num_ocupado = 0;

//Função para ordenar os objetos usando Insertion Sort
void OrdenaPorY(objeto_t *vobj_ptr, int numobj_ptr) {
    int i, j;
    objeto_t chave;

    for (i = 1; i < numobj_ptr; i++) {
        chave = vobj_ptr[i];
        j = i - 1;

        while (j >= 0 && vobj_ptr[j].y_profundidade > chave.y_profundidade) {
            vobj_ptr[j + 1] = vobj_ptr[j];
            j = j - 1;
        }
        vobj_ptr[j + 1] = chave;
    }
}

//Função para adicionar um objeto à cena
void adicionaObj(objeto_t obj, cena_item_t *cena_ptr, int *numcena_ptr) {
    if (*numcena_ptr < 50) {
        cena_ptr[*numcena_ptr].tempo = -1;
        cena_ptr[*numcena_ptr].id = obj.id;
        cena_ptr[*numcena_ptr].inicio = obj.x_inicio;
        cena_ptr[*numcena_ptr].fim = obj.x_fim;
        (*numcena_ptr)++;
    }
}

//Função para adicionar um segmento visível à cena
void adicionaSegmentoVisivel(int id, double inicio, double fim, cena_item_t *cena_ptr, int *numcena_ptr) {
    if (*numcena_ptr < MAX_CENAS_ITENS) {
        cena_ptr[*numcena_ptr].tempo = -1;
        cena_ptr[*numcena_ptr].id = id;
        cena_ptr[*numcena_ptr].inicio = inicio;
        cena_ptr[*numcena_ptr].fim = fim;
        (*numcena_ptr)++;
    }
}

//Função para processar os segmentos visíveis
void processaSegmentosVisiveis(int id, double seg_inicio, double seg_fim, 
                                cena_item_t *cena_ptr, int *numcena_ptr) {
    double segmentos[100][2];
    int num_segmentos = 1;
    segmentos[0][0] = seg_inicio;
    segmentos[0][1] = seg_fim;
    
    for (int oclusor_idx = 0; oclusor_idx < num_ocupado; oclusor_idx++) {
        segmento_ocupado_t oclusor = espaco_ocupado[oclusor_idx];
        int novos_segmentos = 0;
        double novos[100][2];
        
        for (int i = 0; i < num_segmentos; i++) {
            double inicio = segmentos[i][0];
            double fim = segmentos[i][1];
            
            if (inicio < oclusor.fim && fim > oclusor.inicio) {
                if (inicio >= oclusor.inicio && fim <= oclusor.fim) {
                    continue;
                }
                else if (inicio < oclusor.inicio && fim > oclusor.fim) {
                    if (inicio < oclusor.inicio) {
                        novos[novos_segmentos][0] = inicio;
                        novos[novos_segmentos][1] = oclusor.inicio;
                        novos_segmentos++;
                    }
                    if (fim > oclusor.fim) {
                        novos[novos_segmentos][0] = oclusor.fim;
                        novos[novos_segmentos][1] = fim;
                        novos_segmentos++;
                    }
                }
                else if (fim > oclusor.inicio && fim <= oclusor.fim) {
                    if (inicio < oclusor.inicio) {
                        novos[novos_segmentos][0] = inicio;
                        novos[novos_segmentos][1] = oclusor.inicio;
                        novos_segmentos++;
                    }
                }
                else if (inicio < oclusor.fim && inicio >= oclusor.inicio) {
                    if (fim > oclusor.fim) {
                        novos[novos_segmentos][0] = oclusor.fim;
                        novos[novos_segmentos][1] = fim;
                        novos_segmentos++;
                    }
                }
            } else {
                novos[novos_segmentos][0] = inicio;
                novos[novos_segmentos][1] = fim;
                novos_segmentos++;
            }
        }
        
        num_segmentos = novos_segmentos;
        for (int i = 0; i < num_segmentos; i++) {
            segmentos[i][0] = novos[i][0];
            segmentos[i][1] = novos[i][1];
        }
    }
    
    for (int i = 0; i < num_segmentos; i++) {
        if (segmentos[i][1] > segmentos[i][0]) {
            adicionaSegmentoVisivel(id, segmentos[i][0], segmentos[i][1], cena_ptr, numcena_ptr);
        }
    }
}

//Função para verificar se um objeto é visível
bool objetoVisivel(objeto_t &obj) {
    double visivel_inicio = obj.x_inicio;
    double visivel_fim = obj.x_fim;
    
    int numcena_antes = numcena;
    processaSegmentosVisiveis(obj.id, visivel_inicio, visivel_fim, cena_v, &numcena);
    
    if (numcena > numcena_antes) {
        for (int i = numcena_antes; i < numcena; i++) {
            if (num_ocupado < MAX_SEGMENTOS_OCLUSOS) {
                espaco_ocupado[num_ocupado].inicio = cena_v[i].inicio;
                espaco_ocupado[num_ocupado].fim = cena_v[i].fim;
                num_ocupado++;
            }
        }
        return true;
    }
    return false;
}

//Função para gerar a cena
void geraCena(objeto_t *vobj_ptr, int numobj_ptr, cena_item_t *cena_ptr, int *numcena_ptr) {
    OrdenaPorY(vobj_ptr, numobj_ptr);
    num_ocupado = 0;

    for (int i = 0; i < numobj_ptr; i++) {
        objeto_t objeto_temp = vobj_ptr[i];
        objetoVisivel(objeto_temp);
    }
}