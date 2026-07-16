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

// Lista Principal
typedef struct Municipio {
    int id_municipio;
    char nome[50];
    Cachoeira* lista_cachoeiras;
    struct Municipio* ant;
    struct Municipio* prox;
} Municipio;


// OPERAÇÕES PRINCIPAIS

Municipio* inicializar_lista();
int lista_municipios_vazia(Municipio* lista_municipios);
Municipio* inserir_municipio(Municipio* lista_municipios, int id_mun, const char* nome);
Municipio* buscar_municipio(Municipio* lista_municipios, int id_mun);
void alterar_municipio(Municipio* lista_municipios, int id_mun, const char* novo_nome);
Municipio* remover_municipio(Municipio* lista_municipios, int id_mun);
void listar_municipios(Municipio* lista_municipios);
int contar_municipios(Municipio* lista_municipios);

int inserir_cachoeira(Municipio* lista_municipios, int id_mun, int id_cach, const char* nome, float altura, const char* dificuldade);
Cachoeira* buscar_cachoeira(Municipio* lista_municipios, int id_mun, int id_cach);
int alterar_cachoeira(Municipio* lista_municipios, int id_mun, int id_cach, const char* novo_nome, float nova_altura, const char* nova_dificuldade);
int remover_cachoeira(Municipio* lista_municipios, int id_mun, int id_cach);
void listar_cachoeiras_municipio(Municipio* lista_municipios, int id_mun);
int contar_cachoeiras_municipio(Municipio* lista_municipios, int id_mun);


//OPERAÇÕES DE CONSULTAS E CRUZAMENTOS

// 1: Lista todas as cachoeiras, independente do município
void listar_todas_cachoeiras(Municipio* lista_municipios);

// 2: Contabiliza e exibe quantas cachoeiras existem em cada município
void contar_cachoeiras_por_municipio(Municipio* lista_municipios);

//3: Retorna o ponteiro para o município com a menor quantidade de cachoeiras
Municipio* municipio_com_menos_cachoeiras(Municipio* lista_municipios);

//1: Filtra e exibe as cachoeiras de acordo com a dificuldade buscada
void filtrar_cachoeiras_por_dificuldade(Municipio* lista_municipios, const char* dificuldade);

// 2: Gera estatísticas (Total de municípios, total de cachoeiras e média)
void gerar_estatisticas_gerais(Municipio* lista_municipios);

//Para ler o arquivo e popular as listas
Municipio* carregar_dados_arquivo(const char* nome_arquivo);

#endif