#include <stdio.h>
#include "cachoeira.h"

int main(){
    Municipio* lmun = inicializar_lista_vazia();
    inserir_municipio(&lmun, 1, "Uberlândia");

    inserir_cachoeira(&lmun, 1, 1, "Água brilhante", 9, "Fácil");
    inserir_cachoeira(&lmun, 1, 2, "Pedra solta", 14, "Díficil");
    inserir_cachoeira(&lmun, 1, 3, "Pedra lascada", 20, "Díficil");
    listar_cachoeiras_municipio(lmun, 1);

    alterar_cachoeira(lmun, 1, 2, "Cristalina", 20, "Difícil");
    listar_cachoeiras_municipio(lmun, 1);

    return 0;
}