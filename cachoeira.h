#ifndef CACHOEIRA_H
#define CACHOEIRA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct desc_municipio DescritorM;
typedef struct desc_cachoeira DescritorC;

// OPERAÇÕES PRINCIPAIS

void inicializar_municipios(DescritorM* m);
DescritorM* criar_municipios();
int inserir_municipio(DescritorM* listaM, int id_mun, char* nome);
Municipio* buscar_municipio(DescritorM* listaM, int id_mun);
void alterar_municipio(DescritorM* listaM, int id_mun, const char* novo_nome);
int remover_municipio(DescritorM* listaM, int id_mun);
void listar_municipios(DescritorM* listaM);
int contar_municipios(DescritorM* listaM);

void inicializar_cachoeira(DescritorC* c);
DescritorC* criar_cachoeiras();
int inserir_cachoeira(Municipio* lista_municipios, int id_mun, int id_cach, const char* nome, float altura, const char* dificuldade);
Cachoeira* buscar_cachoeira(Municipio* lista_municipios, int id_mun, int id_cach);
int alterar_cachoeira(Municipio* lista_municipios, int id_mun, int id_cach, const char* novo_nome, float nova_altura, const char* nova_dificuldade);
int remover_cachoeira(Municipio* lista_municipios, int id_mun, int id_cach);
void listar_cachoeiras_municipio(Municipio* lista_municipios, int id_mun);
int contar_cachoeiras_municipio(Municipio* lista_municipios, int id_mun);


//OPERAÇÕES DE CONSULTAS E CRUZAMENTOS

/*/ 1: Lista todas as cachoeiras, independente do município
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
*/
#endif