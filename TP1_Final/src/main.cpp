#include <iostream>
#include <iomanip>
#include "objeto.h"
#include "cena.h"

using namespace std;

int main() {
    cout << fixed << setprecision(2);
    
    char token;
    
    //Função para ler a entrada cin com os tokens correspondentes O, M e C que são Objetos, Movimentos e Cenas respectivamente  
    while (cin >> token) {
        switch (token) {
            case 'O': {
                int id;
                double x, y, largura;
                cin >> id >> x >> y >> largura;
                criaObjeto(id, x, y, largura);
                break;
            }
            
            case 'M': {
                int tempo, id;
                double x, y;
                cin >> tempo >> id >> x >> y;
                atualizaObjeto(id, x, y);
                break;
            }
            
            case 'C': {
                int tempo;
                cin >> tempo;
                
                numcena = 0;
                geraCena(vobj, numobj, cena_v, &numcena);
                
                for (int i = 0; i < numcena - 1; i++) {
                    for (int j = i + 1; j < numcena; j++) {
                        if (cena_v[i].id > cena_v[j].id) {
                            cena_item_t temp = cena_v[i];
                            cena_v[i] = cena_v[j];
                            cena_v[j] = temp;
                        }
                    }
                }
                
                for (int i = 0; i < numcena; i++) {
                    cout << "S " << tempo << " " << cena_v[i].id
                         << " " << cena_v[i].inicio << " " << cena_v[i].fim << '\n';
                }
                break;
            }
        }
    }
    
    return 0;
}