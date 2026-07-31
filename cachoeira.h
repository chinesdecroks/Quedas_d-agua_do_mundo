#ifndef CACHOEIRA_H
#define CACHOEIRA_H


typedef struct Cachoeira Cachoeira;
typedef struct Municipio Municipio;

// OPERAÇÕES PRINCIPAIS
Municipio* inicializar_lista_vazia(); //ok
int lista_municipios_vazia(Municipio* lista_municipios); //ok
void inserir_municipio(Municipio** lista_municipios, int id_mun, char* nome); //ok
Municipio* buscar_municipio(Municipio* lista_municipios, int id_mun); //ok
void alterar_municipio(Municipio* lista_municipios, int id_mun, char* novo_nome); //ok
void remover_municipio(Municipio** lista_municipios, int id_mun); //ok
void remover_todas_cachoeiras(Municipio* municipio);
void listar_municipios(Municipio* lista_municipios); //ok
int contar_municipios(Municipio* lista_municipios); //ok

int inserir_cachoeira(Municipio** lista_municipios, int id_mun, int id_cach, char* nome, float altura, char* dificuldade); //ok
Cachoeira* buscar_cachoeira(Municipio* lista_municipios, int id_mun, int id_cach); //ok
void alterar_cachoeira(Municipio* lista_municipios, int id_mun, int id_cach, char* novo_nome, float nova_altura, char* nova_dificuldade); //ok
void remover_cachoeira(Municipio** lista_municipios, int id_mun, int id_cach); //ok
void listar_cachoeiras_municipio(Municipio* lista_municipios, int id_mun); //ok
int contar_cachoeiras_municipio(Municipio* lista_municipios, int id_mun); //ok


//OPERAÇÕES DE CONSULTAS E CRUZAMENTOS

// 1: Lista todas as cachoeiras, independente do município
void listar_todas_cachoeiras(Municipio* lista_municipios);
// 2: Contabiliza e exibe quantas cachoeiras existem em cada município
void contar_cachoeiras_por_municipio(Municipio* lista_municipios);
//3: Retorna o ponteiro para o município com a menor quantidade de cachoeiras
void municipio_com_menos_cachoeiras(Municipio* lista_municipios);
//1: Filtra e exibe as cachoeiras de acordo com a dificuldade buscada
void filtrar_cachoeiras_por_dificuldade(Municipio* lista_municipios, char* dificuldade);
// 2: Gera estatísticas (Total de municípios, total de cachoeiras e média)
void gerar_estatisticas_gerais(Municipio* lista_municipios);

//Para ler o arquivo e popular as listas
Municipio* carregar_dados_arquivo(const char* nome_arquivo);

//Para exibir menu de opções para o usuário
void exibir_menu();

void liberar_municipios(Municipio* listaM);
void liberar_cachoeiras(Cachoeira* listaC);

#endif
