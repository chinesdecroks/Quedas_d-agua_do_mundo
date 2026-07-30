#include <stdio.h>
#include "cachoeira.h"

int main() {
    Municipio* lista_municipios = carregar_dados_arquivo("dados_cachoeiras.txt");

    if (lista_municipios == NULL) {
        printf("⚠️ Aviso: A lista iniciou vazia (arquivo nao encontrado ou sem dados).\n");
    } else {
        printf("🎉Sucesso! %d municipio(s) carregado(s) do arquivo.\n", contar_municipios(lista_municipios));
    }

    int opcao;
    int id_mun, id_cach;
    char nome[50], dificuldade[20];
    float altura;

    do {
        exibir_menu();
        
        scanf("%d", &opcao);

        printf("\n");

        switch (opcao) {
            case 1:
                printf("=== MUNICIPIOS CADASTRADOS ===\n");
                listar_municipios(lista_municipios);
                break;

            case 2:
                printf("--- Inserir Novo Municipio ---\n");
                printf("Digite o ID do Municipio: ");
                scanf("%d", &id_mun);
                while (getchar() != '\n');

                printf("Digite o Nome do Municipio: ");
                scanf("%[^\n]", nome);
                while (getchar() != '\n');

                inserir_municipio(&lista_municipios, id_mun, nome);
                printf("✅ Municipio inserido com sucesso!\n");
                break;

            case 3:
                printf("--- Alterar Municipio ---\n");
                printf("Digite o ID do Municipio que deseja alterar: ");
                scanf("%d", &id_mun);
                while (getchar() != '\n');

                printf("Digite o novo nome: ");
                scanf("%[^\n]", nome);
                while (getchar() != '\n');

                alterar_municipio(lista_municipios, id_mun, nome);
                printf("✅ Operacao concluida.\n");
                break;

            case 4:
                printf("--- Remover Municipio ---\n");
                printf("Digite o ID do Municipio a remover: ");
                scanf("%d", &id_mun);
                remover_municipio(&lista_municipios, id_mun);
                printf("✅ Operacao concluida.\n");
                break;

            case 5:
                printf("--- Listar Cachoeiras de um Municipio ---\n");
                printf("Digite o ID do Municipio: ");
                scanf("%d", &id_mun);
                listar_cachoeiras_municipio(lista_municipios, id_mun);
                break;

            case 6:
                printf("--- Inserir Nova Cachoeira ---\n");
                printf("ID do Municipio correspondente: ");
                scanf("%d", &id_mun);
                printf("ID da Cachoeira: ");
                scanf("%d", &id_cach);
                printf("Altura (em metros): ");
                scanf("%f", &altura);
                while (getchar() != '\n');

                printf("Dificuldade (Facil/Media/Dificil): ");
                scanf("%[^\n]", dificuldade);
                while (getchar() != '\n');

                printf("Nome da Cachoeira: ");
                scanf("%[^\n]", nome);
                while (getchar() != '\n');

                inserir_cachoeira(&lista_municipios, id_mun, id_cach, nome, altura, dificuldade);
                break;

            case 7:
                printf("--- Alterar Cachoeira ---\n");
                printf("ID do Municipio: ");
                scanf("%d", &id_mun);
                printf("ID da Cachoeira: ");
                scanf("%d", &id_cach);
                printf("Nova Altura: ");
                scanf("%f", &altura);
                while (getchar() != '\n');

                printf("Nova Dificuldade: ");
                scanf("%[^\n]", dificuldade);
                while (getchar() != '\n');

                printf("Novo Nome: ");
                scanf("%[^\n]", nome);
                while (getchar() != '\n');

                alterar_cachoeira(lista_municipios, id_mun, id_cach, nome, altura, dificuldade);
                break;

            case 8:
                printf("--- Remover Cachoeira ---\n");
                printf("ID do Municipio: ");
                scanf("%d", &id_mun);
                printf("ID da Cachoeira: ");
                scanf("%d", &id_cach);
                remover_cachoeira(&lista_municipios, id_mun, id_cach);
                break;

            case 9:
                printf("=== TODAS AS CACHOEIRAS ===\n");
                listar_todas_cachoeiras(lista_municipios);
                break;

            case 10:
                printf("=== CONTAGEM DE CACHOEIRAS POR MUNICIPIO ===\n");
                contar_cachoeiras_por_municipio(lista_municipios);
                break;

            case 11:
                printf("--- Filtrar Cachoeiras por Dificuldade ---\n");
                printf("Digite a dificuldade desejada (Facil, Media ou Dificil): ");
                setbuf(stdin, NULL);
                scanf("%[^\n]", dificuldade);
                filtrar_cachoeiras_por_dificuldade(lista_municipios, dificuldade);
                break;

            case 12:
                printf("=== ESTATISTICAS GERAIS DO SISTEMA ===\n");
                gerar_estatisticas_gerais(lista_municipios);
                break;

            case 13: {
                municipio_com_menos_cachoeiras(lista_municipios);
                break;

            case 14:
                printf("Recarregando dados do arquivo 'dados_cachoeiras.txt'...\n");
                liberar_municipios(lista_municipios); // Libera a lista atual da memória antes de carregar a nova
                lista_municipios = carregar_dados_arquivo("dados_cachoeiras.txt");
                break;

            case 0:
                printf("👋🏽 Encerrando o programa... Ate logo!\n");
                break;

            default:
                printf("❌ Opcao invalida! Tente novamente.\n");
                break;
        }

    } while (opcao != 0);

    liberar_municipios(lista_municipios);

    return 0;
}