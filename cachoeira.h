#ifndef CACHOEIRA_H
#define CACHOEIRA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Cachoeira {
    int id_cachoeira;
    char nome[50];
    float altura;
    char dificuldade[20]; // Ex: "Facil", "Media", "Dificil"
    struct Cachoeira* ant;
    struct Cachoeira* prox;
} Cachoeira;

typedef struct Municipio {
    int id_municipio;
    char nome[50];
    struct Cachoeira* lista_cachoeiras;
    struct Municipio* ant;
    struct Municipio* prox;
} Municipio;

// OPERAÇÕES PRINCIPAIS
Municipio* inicializar_lista_vazia(); //ok
int lista_municipios_vazia(Municipio* lista_municipios); //ok
void inserir_municipio(Municipio** lista_municipios, int id_mun, char* nome); //ok
Municipio* buscar_municipio(Municipio* lista_municipios, int id_mun); //ok
void alterar_municipio(Municipio* lista_municipios, int id_mun, char* novo_nome); //ok
void remover_municipio(Municipio** lista_municipios, int id_mun); //ok
void listar_municipios(Municipio* lista_municipios); //ok
int contar_municipios(Municipio* lista_municipios); //ok
void liberar_municipios(Municipio* listaM);

int inserir_cachoeira(Municipio** lista_municipios, int id_mun, int id_cach, char* nome, float altura, char* dificuldade); //ok
Cachoeira* buscar_cachoeira(Municipio* lista_municipios, int id_mun, int id_cach); //ok
void alterar_cachoeira(Municipio* lista_municipios, int id_mun, int id_cach, char* novo_nome, float nova_altura, char* nova_dificuldade);
void remover_cachoeira(Municipio** lista_municipios, int id_mun, int id_cach); //ok
void listar_cachoeiras_municipio(Municipio* lista_municipios, int id_mun); //ok
int contar_cachoeiras_municipio(Municipio* lista_municipios, int id_mun); //ok
void liberar_cachoeiras(Cachoeira* listaC);


//OPERAÇÕES DE CONSULTAS E CRUZAMENTOS

// 1: Lista todas as cachoeiras, independente do município
void listar_todas_cachoeiras(Municipio* lista_municipios);
// 2: Contabiliza e exibe quantas cachoeiras existem em cada município
void contar_cachoeiras_por_municipio(Municipio* lista_municipios);
//3: Retorna o ponteiro para o município com a menor quantidade de cachoeiras
Municipio* municipio_com_menos_cachoeiras(Municipio* lista_municipios);
//1: Filtra e exibe as cachoeiras de acordo com a dificuldade buscada
void filtrar_cachoeiras_por_dificuldade(Municipio* lista_municipios, char* dificuldade);
// 2: Gera estatísticas (Total de municípios, total de cachoeiras e média)
void gerar_estatisticas_gerais(Municipio* lista_municipios);

//Para ler o arquivo e popular as listas
Municipio* carregar_dados_arquivo(const char* nome_arquivo);



#endif