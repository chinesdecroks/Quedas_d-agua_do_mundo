#include <stdio.h>
#include <string.h>
#include "cachoeira.h"

Municipio* inicializar_lista_vazia(){
    return NULL; //a cabeça da lista de municipios eh nula, ou seja, lista vazia
}

int lista_municipios_vazia(Municipio* lista_municipios){
    return lista_municipios == NULL;
}

void inserir_municipio(Municipio** lista_municipios, int id, char nome[50]){
    Municipio* novo = (Municipio*) malloc(sizeof(Municipio));
    if(novo == NULL) {
        printf("A alocação de memória falhou");
        return;
    }

    novo->id_municipio = id;
    strcpy(novo->nome, nome);
    novo->lista_cachoeiras = NULL;
    novo->prox = NULL;

    //lista vazia: eh necessario modificar a cabeca
    if(*lista_municipios == NULL){
        novo->ant = NULL;
        *lista_municipios = novo;
    }
    //lista com pelo menos uma elemento: eh necessario fazer o antigo ultimo apontar para o novo
    else
    {
       Municipio* atual = *lista_municipios;
       while(atual->prox != NULL)  atual = atual->prox;

       atual->prox = novo;
       novo->ant = atual;
    }
}


Municipio* buscar_municipio(Municipio* lista_municipios, int id_mun){
    if (lista_municipios_vazia(lista_municipios)) return NULL;

    Municipio *atual = lista_municipios;
    while(atual != NULL){
        if(atual->id_municipio == id_mun){ //verficação pelo id
            return atual; //retorna o ponteiro p o municipio encontrada
        }
        atual = atual->prox;
    }
    return NULL; 
}

void alterar_municipio(Municipio* lista_municipios, int id_mun, char* novo_nome){
    if(lista_municipios_vazia(lista_municipios)) return;

    Municipio *municipio = buscar_municipio(lista_municipios, id_mun); //encontra o municipio desejado
    if(municipio != NULL){ //se ele existir, altera o nome
        strcpy(municipio->nome, novo_nome);
    }
    return;
}

void remover_municipio(Municipio** lista_municipios, int id_mun){
    if(lista_municipios_vazia(*lista_municipios)) return;
    Municipio* municipio = buscar_municipio(*lista_municipios, id_mun);
    if(municipio == NULL) return ;

    //primeiro da lista
    if (municipio->ant == NULL) {
        *lista_municipios = municipio->prox;
    }
    //ultimo da lista
    else if (municipio->prox == NULL) {
        municipio->ant->prox = NULL;
    }
    //elemento intermediário
    else {
        municipio->ant->prox = municipio->prox;
        municipio->prox->ant = municipio->ant;
    }

    //TODOS: Chamar aqui a função de remover as cachoeiras desse municipio
    liberar_cachoeiras(municipio->lista_cachoeiras);

    free(municipio);
}

void listar_municipios(Municipio* lista_municipios){
    if(lista_municipios_vazia(lista_municipios)){
        printf("Nenhum municipio cadastrado!\n");
        return;
    }

    Municipio *atual = lista_municipios;
    while(atual != NULL){
        printf("\tID: %d, Nome: %s\n", atual->id_municipio, atual->nome);
        atual = atual->prox;
    }
    printf("\n");
}

int contar_municipios(Municipio* lista_municipios){
    if(lista_municipios_vazia(lista_municipios)) return 0;

    int count = 0;
    Municipio *atual = lista_municipios;
    while(atual!=NULL){
        count++;
        atual = atual->prox;
    }
    return count;
}

//funções para cachoeiras
int inserir_cachoeira(Municipio** lista_municipios, int id_mun, int id_cach, char* nome, float altura, char* dificuldade) {
    if (lista_municipios_vazia(*lista_municipios)) {
        printf("Município inexistente\n");
        return 0;
    }

    Municipio* municipio = buscar_municipio(*lista_municipios, id_mun);
    Cachoeira* nova = (Cachoeira*) malloc(sizeof(Cachoeira));
    nova->prox = NULL;
    nova->id_cachoeira = id_cach;
    strcpy(nova->nome, nome);
    nova->altura = altura;
    strcpy(nova->dificuldade, dificuldade);

    //ainda não ha cachoeiras cadastradas
    if (municipio->lista_cachoeiras == NULL) {
        municipio->lista_cachoeiras = nova;
        nova->ant = NULL;
    }
    //ha caachoeiras, entao preciso encontrar a ultima para apontar para a nova
    else {
        Cachoeira* atual = municipio->lista_cachoeiras;
        while (atual->prox != NULL) atual = atual->prox;
        atual->prox = nova;
        nova->ant = atual;
    }
}

void listar_cachoeiras_municipio(Municipio* lista_municipios, int id_mun) {
    Municipio* municipio = buscar_municipio(lista_municipios, id_mun);
    if (lista_municipios_vazia(municipio)) {
        printf("Município não cadastrado\n");
        return;
    }

    if (municipio->lista_cachoeiras == NULL) {
        printf("Não há cachoeiras cadastradas para esse município\n");
        return;
    }

    Cachoeira* atual = municipio->lista_cachoeiras;
    printf("=== Cachoeiras em %s ===\n", municipio->nome);
    do {
        printf("ID: %d, ", atual->id_cachoeira);
        printf("Nome: %s, ", atual->nome);
        printf("Altura: %.2f, ", atual->altura);
        printf("Dificuldade: %s\n", atual->dificuldade);
        atual = atual->prox;
    }while (atual != NULL);
    printf("\n");
}

int contar_cachoeiras_municipio(Municipio* lista_municipios, int id_mun) {
    Municipio* municipio = buscar_municipio(lista_municipios, id_mun);
    if (lista_municipios_vazia(municipio)) {
        printf("Lista de municípios vazia\n");
        return 0;
    }

    Cachoeira* atual = municipio->lista_cachoeiras;

    //nenhuma cachoeira
    if (atual == NULL) {
        return 0;
    }
    //ao menos uma cachoeira
    int contador = 1;
    while (atual->prox != NULL) {
        atual = atual->prox;
        contador++;
    }
    return contador;
}
Cachoeira* buscar_cachoeira(Municipio* lista_municipios, int id_mun, int id_cach) {
    if (lista_municipios_vazia(lista_municipios)) {
        printf("Lista de municípios vazia\n");
        return NULL;
    }

    Cachoeira* cachoeira = lista_municipios->lista_cachoeiras;
    if (cachoeira == NULL) {
        printf("Lista de cachoeiras vazia\n");
        return NULL;
    }

    while (cachoeira->id_cachoeira != id_cach && cachoeira->prox != NULL) cachoeira = cachoeira->prox;

    //devo verificar, pois pode ter encontrado ou simplesmente chegado no fim
    if (cachoeira->id_cachoeira == id_cach) return cachoeira;

    return NULL;
}

void remover_cachoeira(Municipio** lista_municipios, int id_mun, int id_cach) {
    if (lista_municipios_vazia(*lista_municipios)) {
        printf("Lista de municípios vazia\n");
        return;
    }

    Cachoeira* cachoeira = buscar_cachoeira(*lista_municipios, id_mun, id_cach);

    if (cachoeira == NULL) {
        printf("Lista de cachoeiras vazia\n");
        return;
    }

    //removendo elemento intermediario
    if (cachoeira->ant != NULL && cachoeira->prox != NULL) {
        cachoeira->prox->ant = cachoeira->ant;
        cachoeira->ant->prox = cachoeira->prox;
    }
    //remover no inicio
    else if (cachoeira->ant == NULL) {
        (*lista_municipios)->lista_cachoeiras = (*lista_municipios)->lista_cachoeiras->prox;
        (*lista_municipios)->lista_cachoeiras->prox->ant = NULL;
    }
    //remover no final
    else {
        cachoeira->ant->prox = NULL;
    }

    free(cachoeira);
}

void alterar_cachoeira(Municipio* lista_municipios, int id_mun, int id_cach, char* novo_nome, float nova_altura, char* nova_dificuldade) {
    if (lista_municipios_vazia(lista_municipios)) {
        printf("Lista de municípios vazia\n");
        return;
    }

    Cachoeira* cachoeira = buscar_cachoeira(lista_municipios, id_mun, id_cach);
    if (cachoeira == NULL) {
        printf("Não há cachoeiras cadastradas ou a cachoeira não existe na lista\n");
        return;
    }

    strcpy(cachoeira->nome, novo_nome);
    cachoeira->altura = nova_altura;
    strcpy(cachoeira->dificuldade, nova_dificuldade);

}

void listar_todas_cachoeiras(Municipio* lista_municipios)
{

    while (lista_municipios != NULL)
    {
        while (lista_municipios->lista_cachoeiras != NULL)
        {
            printf("\n===================================================================\n");

            listar_cachoeiras_municipio(lista_municipios, lista_municipios->id_municipio);

            printf("\n===================================================================\n");

            lista_municipios->lista_cachoeiras = lista_municipios->lista_cachoeiras->prox;

        }

        lista_municipios = lista_municipios->prox;

    }
}

void contar_cachoeiras_por_municipio(Municipio* lista_municipios)
{
    
    printf("\n=============================================\n");
    while (lista_municipios != NULL)
    { 
        int cont = 0;

        while (lista_municipios->lista_cachoeiras != NULL)
        {
            cont++;
            lista_municipios->lista_cachoeiras = lista_municipios->lista_cachoeiras;
        }

        printf("Municipio: %s\n", lista_municipios->nome);
        printf("Cachoeiras: %d\n\n", cont);
    }

    printf("=============================================\n");
}


Municipio* municipio_com_menos_cachoeiras(Municipio* lista_municipios)
{
    Municipio *aux = lista_municipios, *menorM = aux;
    int menor = contar_cachoeiras_municipio(menorM, menorM->id_municipio);

    while (aux != NULL)
    {
        
        int cachoeiras = contar_cachoeiras_municipio(lista_municipios, aux->id_municipio);

        if (menor > cachoeiras)
        {
            menorM = aux;
            menor = cachoeiras;
        }

        aux = aux->prox;

    }

    return menorM;
}

void filtrar_cachoeiras_por_dificuldade(Municipio* lista_municipios, char* dificuldade)
{

    printf("\n====================== %s ======================\n", dificuldade);
    if (lista_municipios == NULL)
        printf("\nA lista esta vazia\n\n");

    Municipio* aux = lista_municipios;

    
    while (aux != NULL)
    {
        while (aux->lista_cachoeiras != NULL)
        {
            if (!strcmp(dificuldade, aux->lista_cachoeiras->dificuldade));
            {
                printf("ID: %d, ", aux->lista_cachoeiras->id_cachoeira);
                printf("Nome: %s, ", aux->lista_cachoeiras->nome);
                printf("Altura: %.2fm, ", aux->lista_cachoeiras->altura);
                printf("Dificuldade: %s\n", aux->lista_cachoeiras->dificuldade);
            }

            aux->lista_cachoeiras = aux->lista_cachoeiras->prox;
        }

        aux = aux->prox;
    }
    printf("=========================================================\n");

}

void gerar_estatisticas_gerais(Municipio* lista_municipios)
{
    int contM = 0, contC = 0;

    while (lista_municipios != NULL)
    {
        while (lista_municipios->lista_cachoeiras != NULL)
        {
            contC++;
            lista_municipios->lista_cachoeiras = lista_municipios->lista_cachoeiras->prox;
        }

        contM++;
        lista_municipios = lista_municipios->prox;
    }

    float media = (float) contC / contM;

    printf("Municipios: %d\nCachoeiras: %d\nMedia de cachoeiras por municipio: %f\n", contM, contC, media);
}

void liberar_municipios(Municipio* listaM)
{
    if (listaM == NULL)
    {
        printf("A lista esta vazia\n");
    }

    Municipio* aux;

    while (listaM != NULL)
    {
        aux = listaM;
        listaM = listaM->prox;
        remover_municipio(&listaM, aux->id_municipio);
    }

    printf("\nLista de municipios liberada com sucesso!!!\n");
}

void liberar_cachoeiras(Cachoeira* listaC)
{
    if (listaC == NULL)
    {
        printf("A lista esta vazia\n");
        return;
    }

    Cachoeira* aux;

    while (listaC != NULL)
    {
        aux = listaC;
        listaC = listaC->prox;
        free(aux);
    }
}