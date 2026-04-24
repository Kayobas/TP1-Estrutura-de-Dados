#include "objeto.h"

//Variáveis globais para o TAD Objeto
objeto_t vobj[MAX_OBJETOS];
int numobj = 0;

//Função para criar um objeto
void criaObjeto(int id, double x, double y, double largura) {
    if (numobj < MAX_OBJETOS) {
        vobj[numobj].id = id;
        vobj[numobj].x_centro = x;
        vobj[numobj].y_profundidade = y;
        vobj[numobj].largura = largura;
        vobj[numobj].x_inicio = x - largura / 2.0;
        vobj[numobj].x_fim = x + largura / 2.0;
        numobj++;
    }
}

//Função para atualizar um objeto
void atualizaObjeto(int id, double novo_x, double novo_y) {
    for (int i = 0; i < numobj; i++) {
        if (vobj[i].id == id) {
            vobj[i].x_centro = novo_x;
            vobj[i].y_profundidade = novo_y;
            vobj[i].x_inicio = novo_x - vobj[i].largura / 2.0;
            vobj[i].x_fim = novo_x + vobj[i].largura / 2.0;
            return;
        }
    }
}