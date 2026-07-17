#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cachoeira.h"

typedef struct Cachoeira 
{
    int id_cachoeira;
    char nome[50];
    float altura;
    char dificuldade[20]; // Ex: "Facil", "Media", "Dificil"
} Cachoeira;

typedef struct no_cachoeira
{
    Cachoeira c;
    struct no_cachoeira* ant;
    struct no_cachoeira* prox;
} NoC;

// Lista Principal
typedef struct Municipio 
{
    int id_municipio;
    char nome[50];
    DescritorC* lista_cachoeiras;
} Municipio;

typedef struct no_municipio
{
    Municipio m;
    struct no_municipio* ant;
    struct no_municipio* prox;
} NoM;

struct desc_municipio
{
    NoM* inicio;
    NoM* fim;
    int tam;
};

struct desc_cachoeira
{
    NoC* inicio;
    NoC* fim;
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

    if (m != NULL)
        inicializar_municipios(m);

    return m;
}

DescritorC* criar_cachoeiras()
{
    DescritorC* c = (DescritorC*)malloc(sizeof(DescritorC));
    
    if (c != NULL)
        inicializar_cachoeira(c);

    return c;
}

int lista_municipios_vazia(DescritorM* listaM)
{
    return listaM == NULL || listaM->tam == 0;
}

Municipio scan_municipio()
{
    Municipio m;
    printf("Digite o ID do municipio: ");
    scanf("%d", &m.id_municipio);
    getchar();

    printf("Digite o nome do municipio: ");
    scanf("%[^\n]", m.nome);
    getchar();

    m.lista_cachoeiras = criar_cachoeiras();

    return m;
}

NoM* novo_municipio()
{
    NoM *novo = (NoM*)malloc(sizeof(NoM)); //aloca memória para o novo
    
    if(novo == NULL) 
        return novo; //retorna a lista original

    //=========Dados do Municipio ==========
    novo->m = scan_municipio();
    novo->prox = NULL;
    novo->ant = NULL;

    return novo;
}

int inserir_municipio(DescritorM* listaM)
{
    NoM* novo = novo_municipio(), *aux = listaM->fim;

    if (novo == NULL)
        return 0;

    // Verifica se tem ID repetido
    if(buscar_municipio(listaM, novo->m.id_municipio) != NULL)
    {
        free(novo);
        return 0;
    }

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

NoM* buscar_municipio(DescritorM* listaM, int id_mun)
{
    if (lista_municipios_vazia(listaM)) return NULL;

    NoM *atual = listaM->inicio;
    while(atual != NULL)
    {
        if(atual->m.id_municipio == id_mun) //verficação pelo id
        { 
            return atual; //retorna o ponteiro p o municipio encontrada
        }

        atual = atual->prox;
    }
    return NULL; 
}

void alterar_municipio(DescritorM* listaM, int id_mun, char* novo_nome)
{
    if(lista_municipios_vazia(listaM)) return;

    NoM *municipio = buscar_municipio(listaM, id_mun); //encontra o municipio desejado
    if(municipio != NULL)//se ele existir, altera o nome
    { 
        strcpy(municipio->m.nome, novo_nome);
    }
    return;
}

int remover_municipio(DescritorM* listaM, int id_mun)
{
    if(lista_municipios_vazia(listaM)) return 0;

    NoM *municipio = buscar_municipio(listaM, id_mun);
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
    printf("\n===============================================\n");
    if(lista_municipios_vazia(listaM)){
        printf("Nenhum municipio cadastrado!\n");
        return;
    }

    NoM *atual = listaM->inicio;
    while(atual != NULL){
        printf("\tID: %d, Nome: %s\n", atual->m.id_municipio, atual->m.nome);
        atual = atual->prox;
    }
    printf("==================================================\n");
}

int contar_municipios(DescritorM* listaM){
    return listaM->tam;
}

Cachoeira scan_cachoeira()
{
    Cachoeira c;
    printf("\nDigite o ID da cachoeira: ");
    scanf("%d", &c.id_cachoeira);
    getchar();

    printf("\nDigite o nome da cachoeira: ");
    scanf("%[^\n]", c.nome);
    getchar();

    printf("\nDigite a altura da cachoeira: ");
    scanf("%f", &c.altura);
    getchar();

    printf("\nDigite a dificuldade da cachoeira: ");
    scanf("%[^\n]", c.dificuldade);

    return c;
}

NoC* nova_cachoeira()
{
    NoC *novo = (NoC*)malloc(sizeof(NoC)); //aloca memória para o novo
    
    if(novo == NULL) 
        return novo; //retorna a lista original

    //=========Dados da Cachoeira ==========
    novo->c = scan_cachoeira();
    novo->prox = NULL;
    novo->ant = NULL;

    return novo;
}

int inserir_cachoeira(DescritorM* listaM, int id_mun)
{
    NoM* municipio = buscar_municipio(listaM, id_mun);

    if (municipio == NULL)
        return -1;

    DescritorC *aux = municipio->m.lista_cachoeiras;
    NoC* novo = nova_cachoeira(), *temp = aux->fim; 
    


    if (novo == NULL)
        return 0;

    //========== Adicionar Nó ==============
    if (aux->tam == 0)
    {
        aux->inicio = novo;
        aux->fim = novo;
    } else
    {
        temp->prox = novo;
        novo->ant = temp;
        aux->fim = novo;
    }

    aux->tam++;

    return 1;


}