#include <stdio.h>
#include <string.h>
#include "cachoeira.h"

typedef struct Cachoeira 
{
    int id_cachoeira;
    char nome[50];
    float altura;
    char dificuldade[20]; // Ex: "Facil", "Media", "Dificil"
    struct Cachoeira* ant;
    struct Cachoeira* prox;
} Cachoeira;

// Lista Principal
typedef struct Municipio 
{
    int id_municipio;
    char nome[50];
    DescritorC* lista_cachoeiras;
    struct Municipio* ant;
    struct Municipio* prox;
} Municipio;

struct desc_municipio
{
    Municipio* inicio;
    Municipio* fim;
    int tam;
};

struct desc_cachoeira
{
    Cachoeira* inicio;
    Cachoeira* fim;
    int tam;
};

void inicializar_municipios(DescritorM* m)
{
    m->inicio = NULL;
    m->fim = NULL;
    m->tam = 0;
}

void inicializar_cachoeira(DescritorC* c)
{
    c->inicio = NULL;
    c->fim = NULL;
    c->tam = 0;
}

DescritorM* criar_municipios()
{
    DescritorM* m = (DescritorM*)malloc(sizeof(DescritorM));
    return m;
}

DescritorC* criar_cachoeiras()
{
    DescritorC* c = (DescritorC*)malloc(sizeof(DescritorC));
    return c;
}

int lista_municipios_vazia(DescritorM* lista_municipios)
{
    return lista_municipios->tam == 0;
}

Municipio* novo_municipio(int id_mun, char* nome)
{
    Municipio *novo = (Municipio*)malloc(sizeof(Municipio)); //aloca memória para o novo
    
    if(novo == NULL) 
        return novo; //retorna a lista original

    //=========Dados do Municipio ==========
    novo->id_municipio = id_mun; 
    strcpy(novo->nome, nome);
    novo->lista_cachoeiras = criar_cachoeiras();
    inicializar_cachoeira(novo->lista_cachoeiras);

    novo->prox = NULL;
    novo->ant = NULL;

    return novo;
}

int inserir_municipio(DescritorM* listaM, int id_mun, char* nome)
{
    Municipio* novo = novo_municipio(id_mun, nome), *aux = listaM->fim;

    if (novo == NULL)
        return 0;

    //========== Adicionar Nó ==============
    if (listaM->tam == 0)
    {
        listaM->inicio = novo;
        listaM->fim = novo;
    } else
    {
        aux->prox = novo;
        novo->ant = aux;
        listaM->fim = novo;
    }

    listaM->tam++;

    return 1;


}

Municipio* buscar_municipio(DescritorM* listaM, int id_mun)
{
    if (lista_municipios_vazia(listaM)) return NULL;

    Municipio *atual = listaM->inicio;
    while(atual != NULL){
        if(atual->id_municipio == id_mun){ //verficação pelo id
            return atual; //retorna o ponteiro p o municipio encontrada
        }
        atual = atual->prox;
    }
    return NULL; 
}

void alterar_municipio(DescritorM* listaM, int id_mun, const char* novo_nome)
{
    if(lista_municipios_vazia(listaM)) return;

    Municipio *municipio = buscar_municipio(listaM, id_mun); //encontra o municipio desejado
    if(municipio != NULL)//se ele existir, altera o nome
    { 
        strcpy(municipio->nome, novo_nome);
    }
    return;
}

int remover_municipio(DescritorM* listaM, int id_mun)
{
    if(lista_municipios_vazia(listaM)) return 0;

    Municipio *municipio = buscar_municipio(listaM, id_mun);
    if(municipio == NULL) return 0;

    if (municipio->ant == NULL && municipio->prox == NULL)
    {
        listaM->inicio = NULL;
        listaM->fim = NULL;
    } else if (municipio->prox == NULL)
    {
        listaM->fim = municipio->ant;
        municipio->ant->prox = municipio->prox;
    } else if (municipio->ant == NULL)
    {
        listaM->inicio = municipio->prox;
        municipio->prox->ant = municipio->ant;
    } else 
    {
        municipio->prox->ant = municipio->ant;
        municipio->ant->prox = municipio->prox;
    }

    free(municipio);
    listaM->tam--;
    return 1;
}

void listar_municipios(DescritorM* listaM)
{
    if(lista_municipios_vazia(listaM)){
        printf("Nenhum municipio cadastrado!\n");
        return;
    }

    Municipio *atual = listaM->inicio;
    while(atual != NULL){
        printf("\tID: %d, Nome: %s\n", atual->id_municipio, atual->nome);
        atual = atual->prox;
    }
}

int contar_municipios(DescritorM* listaM){
    return listaM->tam;
}