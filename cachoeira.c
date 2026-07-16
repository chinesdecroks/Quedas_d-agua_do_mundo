#include <stdio.h>
#include <string.h>
#include "cachoeira.h"

Municipio* inicializar_lista(){
    return NULL; 
}

Municipio* inserir_municipio(Municipio* lista_municipios, int id_mun, const char* nome){
    Municipio *novo = (Municipio*)malloc(sizeof(Municipio)); //aloca memória para o novo
    if(novo == NULL) return lista_municipios; //retirna a lista original

    novo->id_municipio = id_mun;
    strcpy(novo->nome, nome);
    novo->lista_cachoeiras = NULL;
    novo->prox = NULL; //será NULL pq é o último da lista

    if(lista_municipios == NULL){ //se a lista estiver vazia
        novo->ant = NULL;
        return novo; //novo agr é o inicio da lista
    }

    Municipio *atual = lista_municipios; //ponteiro para inicio da lista
    while(atual->prox != NULL){ //vai percorrer até o ultimo
        atual = atual->prox;
    }
    atual->prox = novo;
    novo->ant = atual;

    return lista_municipios; //retorna o inicio da lista atualizada
}

Municipio* buscar_municipio(Municipio* lista_municipios, int id_mun){
    if (lista_municipios == NULL) return NULL;

    Municipio *atual = lista_municipios;
    while(atual != NULL){
        if(atual->id_municipio == id_mun){
            return atual; //retorna o ponteiro p o municipio encontrada
        }
        atual = atual->prox;
    }
    return NULL; 
}

void alterar_municipio(Municipio* lista_municipios, int id_mun, const char* novo_nome){
    if(lista_municipios == NULL) return;

    Municipio *municipio = buscar_municipio(lista_municipios, id_mun);
    if(municipio != NULL){
        strcpy(municipio->nome, novo_nome);
    }
    return;
}

Municipio* remover_municipio(Municipio* lista_municipios, int id_mun){
    if(lista_municipios == NULL) return NULL;

    Municipio *municipio = buscar_municipio(lista_municipios, id_mun);
    if(municipio == NULL) return lista_municipios;

    if(municipio->ant != NULL){ //se não for o primeiro da lista
        municipio->ant->prox = municipio->prox;
    }
    else{
        lista_municipios = lista_municipios->prox; 
    }
    
    if(municipio->prox != NULL){ //se não for o último da lista
        municipio->prox->ant = municipio->ant;
    }
    //TODOS: Chamar aqui a função de remover as cachoeiras desse municipio
    free(municipio);
    return lista_municipios;
}