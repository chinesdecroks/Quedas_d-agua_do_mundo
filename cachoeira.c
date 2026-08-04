#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cachoeira.h"

struct Cachoeira {
    int id_cachoeira;
    char nome[50];
    float altura;
    char dificuldade[20]; // Ex: "Facil", "Media", "Dificil"
    struct Cachoeira* ant;
    struct Cachoeira* prox;
};

struct Municipio {
    int id_municipio;
    char nome[50];
    struct Cachoeira* lista_cachoeiras;
    struct Municipio* ant;
    struct Municipio* prox;
} ;

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
        if (*lista_municipios != NULL) {      // se a lista ficar vazia
        (*lista_municipios)->ant = NULL; //o ant passa a ser NULL
    }
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
    return 1;
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

    printf("\nCachoeira excluida com sucesso\n");
}

void alterar_cachoeira(Municipio* lista_municipios, int id_mun, int id_cach, char* novo_nome, float nova_altura, char* nova_dificuldade) {
    if (lista_municipios_vazia(lista_municipios)) {
        printf("Lista de municípios vazia\n");
        return;
    }

    Cachoeira* cachoeira = buscar_cachoeira(lista_municipios, id_mun, id_cach);
    if (cachoeira == NULL) {
        printf("Não há cachoeiras cadastradas ou a cachoeira não existe na lista ou o município não existe\n");
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

void contar_cachoeiras_por_municipio(Municipio* lista_municipios)
{
    
    Municipio* atualM = lista_municipios; // ponteiro auxiliar para lista de municipios

    printf("\n=============================================\n");
    while (atualM != NULL) // anda na lista de municipios
    { 
        int cont = 0;
        Cachoeira* atualC = atualM->lista_cachoeiras; //cada vez que se acessa um novo municipio atualiza a lista de cachoeiras

        while (atualC != NULL)// anda na lista de cachoeiras e conta elas
        {
            cont++;
            atualC = atualC->prox;
        }

        printf("Municipio: %s\n", atualM->nome);
        printf("Cachoeiras: %d\n\n", cont);

        atualM = atualM->prox;
    }

    printf("=============================================\n");
}


void municipio_com_menos_cachoeiras(Municipio* lista_municipios)
{
    Municipio* atual = lista_municipios;
    Municipio* menor = atual;

    //pego o menor absoluto
    while(atual != NULL){
        int a = contar_cachoeiras_municipio(atual, atual->id_municipio);
        int m = contar_cachoeiras_municipio(menor, menor->id_municipio);
        if(a < m) menor = atual;
        atual = atual->prox;
    }
    atual = lista_municipios;

    //imprimo todos aqueles com a menor quantidade
    while(atual != NULL){
        if (contar_cachoeiras_municipio(atual, atual->id_municipio) == contar_cachoeiras_municipio(menor, menor->id_municipio)) {
            printf("Municipios: %s\nCachoeiras: %d\n\n", atual->nome, contar_cachoeiras_municipio(atual, atual->id_municipio));
        }
        atual = atual->prox;
    }

}

void filtrar_cachoeiras_por_dificuldade(Municipio* lista_municipios, char* dificuldade)
{

    printf("\n====================== %s ======================\n", dificuldade);
    if (lista_municipios == NULL)//verifico se a lista principal é vazia
        printf("\nA lista esta vazia\n\n");

    Municipio* auxM = lista_municipios;//ponteiro auxiliar para a lista de municipios

    
    while (auxM != NULL)// anda na lista de municipios
    {
        Cachoeira* auxC = auxM->lista_cachoeiras;// a cada novo municipio atualizo a lista de cachoeiras

        while (auxC != NULL)//anda na lista de cachoeiras
        {
            if (!strcmp(dificuldade, auxC->dificuldade))//verifica se a dificuldade informada é igual a dificuldade da cachoeira
            {
                printf("ID: %d, ", auxC->id_cachoeira);
                printf("Nome: %s, ", auxC->nome);
                printf("Altura: %.2fm, ", auxC->altura);
                printf("Dificuldade: %s\n", auxC->dificuldade);
            }

            auxC = auxC->prox;
        }

        auxM = auxM->prox;
    }
    printf("=========================================================\n");

}

void gerar_estatisticas_gerais(Municipio* lista_municipios)
{
    int contM = 0, contC = 0;

    Municipio* auxM = lista_municipios;//ponteiro auxiliar para a lista de cachoeiras

    while (auxM != NULL)//anda na lista de Municipios
    {
        Cachoeira* auxC = auxM->lista_cachoeiras;// a cada novo municipio se atualiza a lista de cachoeiras

        while (auxC != NULL)//anda na lista de Cachoeiras
        {
            contC++;//conto a quantidade de cachoeiras
            auxC = auxC->prox;
        }

        contM++;//conto a quantidade de municipios
        auxM = auxM->prox;
    }

    float media = (float) contC / contM;//calculo a media de cachoeiras por municipio

    printf("Municipios: %d\nCachoeiras: %d\nMedia de cachoeiras por municipio: %.2f\n", contM, contC, media);
}

void liberar_municipios(Municipio* listaM)
{
    if (listaM == NULL)
    {
        printf("A lista esta vazia\n");
    }

    Municipio* aux;//ponteiro auxiliar para receber o nó que será liberado

    while (listaM != NULL)//anda na lista de municipios e vai liberando todos os nós de municipio
    {
        aux = listaM->prox;
        remover_todas_cachoeiras(listaM); //remove tds as cachoeiras antes de remover o municipio
        free(listaM);
        listaM = aux; //avança para o prox municipio
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

    Cachoeira* aux;//ponteiro auxiliar para receber o nó que será liberado

    while (listaC != NULL)//anda na lista e vai liberando todas as cachoeiras
    {
        aux = listaC;
        listaC = listaC->prox;
        free(aux);
    }
}

Municipio* carregar_dados_arquivo(const char* dados_cachoeiras) {
    //Inicializa a lista principal vazia
    Municipio* lista_municipios = inicializar_lista_vazia();

    //Tenta abrir o arquivo para leitura
    FILE* arquivo = fopen(dados_cachoeiras, "r");
    if (arquivo == NULL) {
        printf("Aviso: Arquivo '%s' nao encontrado ou erro ao abrir.\n", dados_cachoeiras);
        return lista_municipios; // Retorna NULL seguro
    }
    char tipo;
    int id_mun, id_cach;
    float altura;
    char nome[50], dificuldade[20];

    // O espaço antes do %c ignora quebras de linha entre as leituras
    while (fscanf(arquivo, " %c;", &tipo) != EOF) {
        
        if (tipo == 'M') {
            // Lê: id ; Nome\n
            fscanf(arquivo, "%d;%[^\n]", &id_mun, nome);
            inserir_municipio(&lista_municipios, id_mun, nome);
        }
        else if (tipo == 'C') {
            // Lê: id_mun ; id_cach ; altura ; dificuldade ; Nome\n
            fscanf(arquivo, "%d;%d;%f;%[^;];%[^\n]", &id_mun, &id_cach, &altura, dificuldade, nome);
            inserir_cachoeira(&lista_municipios, id_mun, id_cach, nome, altura, dificuldade);
        }
    }
    fclose(arquivo);
    return lista_municipios;
}

void exibir_menu() {
    printf("\n====================================================\n");
    printf("         SISTEMA DE QUEDAS D'AGUA DO MUNDO          \n");
    printf("====================================================\n");
    printf(" [1] Listar todos os Municipios\n");
    printf(" [2] Inserir novo Municipio\n");
    printf(" [3] Alterar Municipio\n");
    printf(" [4] Remover Municipio\n");
    printf("----------------------------------------------------\n");
    printf(" [5] Listar Cachoeiras de um Municipio\n");
    printf(" [6] Inserir nova Cachoeira em um Municipio\n");
    printf(" [7] Alterar Cachoeira\n");
    printf(" [8] Remover Cachoeira\n");
    printf("----------------------------------------------------\n");
    printf(" [9] CONSULTA: Listar TODAS as Cachoeiras\n");
    printf(" [10] CONSULTA: Contar Cachoeiras por Municipio\n");
    printf(" [11] CONSULTA: Filtrar por Dificuldade\n");
    printf(" [12] CONSULTA: Estatisticas Gerais\n");
    printf(" [13] CONSULTA: Municipio com Menos Cachoeiras\n");
    printf("----------------------------------------------------\n");
    printf(" [14] Recarregar Dados do Arquivo (dados_cachoeiras.txt)\n");
    printf(" [0] Sair do Sistema\n");
    printf("====================================================\n");
    printf("Escolha uma opcao: ");
}
