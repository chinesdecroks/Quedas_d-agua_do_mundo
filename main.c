#include <stdio.h>
#include "cachoeira.h"

int main() {
    Municipio *municipio = inicializar_lista();
    municipio = inserir_municipio(municipio, 1, "Uberlândia");
    municipio = inserir_municipio(municipio, 2, "Uberaba");

    listar_municipios(municipio);

    remover_municipio(municipio, 2);
    listar_municipios(municipio);



    return 0;
}
