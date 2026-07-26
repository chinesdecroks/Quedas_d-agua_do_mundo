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
        novo->ant = NULL; //o anterior do primeiro é null
        *lista_municipios = novo; //nova cabeça da lista
    }
    //lista com pelo menos uma elemento: eh necessario fazer o ultimo (atual) apontar para o novo, pois insere no final
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
    Municipio* municipio = buscar_municipio(*lista_municipios, id_mun); //encontra municipio desejado
    if(municipio == NULL) return ;

    //se for o primeiro da lista
    if (municipio->ant == NULL) {
        *lista_municipios = municipio->prox; //a nova cabeça da lista passa a ser o proximo
    }
    //se for o ultimo da lista
    else if (municipio->prox == NULL) {
        municipio->ant->prox = NULL; //o anterior passa a ser o ultimo da lista
    }
    //elemento intermediário
    else {
        municipio->ant->prox = municipio->prox;
        municipio->prox->ant = municipio->ant;
    }
    
    remover_todas_cachoeiras(municipio); //remove todas as cachoeiras desse municipio

    free(municipio);
}

void remover_todas_cachoeiras(Municipio* municipio) {
    if (municipio == NULL || municipio->lista_cachoeiras == NULL) return; // Se o município não existe ou não tem cachoeiras

    Cachoeira* atual = municipio->lista_cachoeiras;

    while (atual != NULL) {
        Cachoeira* proximo = atual->prox; //salva o endereço do proximo
        free(atual);
        atual = proximo;
    }

    municipio->lista_cachoeiras = NULL; //lista_cachieiras agr está vazia
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

    Municipio* municipio = buscar_municipio(*lista_municipios, id_mun);//encontra municipio que vai receber nova cachoeira
    if(municipio == NULL){
        printf("Município não encontrado\n");
        return 0;
    }
    Cachoeira* nova = (Cachoeira*) malloc(sizeof(Cachoeira)); //aloca memória para nova cachoeira
    if(nova==NULL){
        printf("Erro de alocação de memória\n");
        return 0;
    }
    nova->prox = NULL;
    nova->id_cachoeira = id_cach;
    strcpy(nova->nome, nome);
    nova->altura = altura;
    strcpy(nova->dificuldade, dificuldade);

    //ainda não ha cachoeiras cadastradas
    if (municipio->lista_cachoeiras == NULL) {
        municipio->lista_cachoeiras = nova; //nova é a cabeça da lista
        nova->ant = NULL;
    }
    //há caachoeiras, entao preciso encontrar a ultima para apontar para a nova
    else {
        Cachoeira* atual = municipio->lista_cachoeiras; //atual aponta para cabeça da lista
        while (atual->prox != NULL) atual = atual->prox; //percorro a lista até último elemento
        atual->prox = nova;
        nova->ant = atual;
    }
}

void listar_cachoeiras_municipio(Municipio* lista_municipios, int id_mun) {
    Municipio* municipio = buscar_municipio(lista_municipios, id_mun);
    if (municipio == NULL) {
        printf("Município não encontrado\n");
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
    if (municipio == NULL) {
        printf("Município não encontrado\n");
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

    //percorre a lista de cachoeiras do município até encontrar a cachoeira com o id desejado ou chegar ao final da lista
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
        printf("Cachoeira não encontrada\n");
        return;
    }

    //removendo elemento intermediario
    if (cachoeira->ant != NULL && cachoeira->prox != NULL) {
        cachoeira->prox->ant = cachoeira->ant;
        cachoeira->ant->prox = cachoeira->prox;
    }
    //remover no inicio
    else if (cachoeira->ant == NULL) {
        if(cachoeira->prox !=NULL){
            (*lista_municipios)->lista_cachoeiras = (*lista_municipios)->lista_cachoeiras->prox; //atualiza cabeça da lista
            (*lista_municipios)->lista_cachoeiras->prox->ant = NULL;
        }
        else{
            (*lista_municipios)->lista_cachoeiras = NULL; //lista fica vazia se eu removo o primeiro elemento que é o único
        }
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

//Função do Lucas CORRIGIDA
void listar_todas_cachoeiras(Municipio* lista_municipios){
    if (lista_municipios_vazia(lista_municipios)) {
        printf("Nenhum municipio cadastrado!\n");
        return;
    }

    Municipio* municipio_atual = lista_municipios; // Começa pela cabeça da lista de municípios
    int encontrou_alguma = 0;

    while (municipio_atual != NULL) {
        // Ponteiro auxiliar para percorrer as cachoeiras desse município
        Cachoeira* cachoeira_atual = municipio_atual->lista_cachoeiras;

        if (cachoeira_atual != NULL) {
            printf("\n===================================================================\n");
            printf("=== Cachoeiras em %s ===\n", municipio_atual->nome);
            
            while (cachoeira_atual != NULL) {
                printf("  - ID: %d | Nome: %s | Altura: %.2f | Dificuldade: %s\n", 
                    cachoeira_atual->id_cachoeira, 
                    cachoeira_atual->nome, 
                    cachoeira_atual->altura, 
                    cachoeira_atual->dificuldade);
                
                cachoeira_atual = cachoeira_atual->prox; // Avança para a próxima cachoeira
            }
            printf("===================================================================\n");
            encontrou_alguma = 1;
        }

        municipio_atual = municipio_atual->prox; // Avança parao próximo município
    }

    if (!encontrou_alguma) { //se encontrou_alguma for 0, é pq passou pelo while e não encontrou nenhuma cachoeira ou município
        printf("Nenhuma cachoeira cadastrada em nenhum municipio!\n");
    }
}
