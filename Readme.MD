# Sistema de Quedas d'Água do Mundo

Este repositório contém a implementação de um sistema para gestão e organização hierárquica de municípios e suas respectivas cachoeiras em linguagem C, utilizando **Listas Duplamente Encadeadas de Listas Duplamente Encadeadas (Lista de Listas)**.

---

## 1. Introdução

### Compreensão do Problema
O objetivo do sistema é resolver o problema de armazenamento e manipulação de dados geográficos e turísticos que possuem uma relação do tipo **um-para-muitos** (um município pode conter múltiplas cachoeiras). Para isso, torna-se necessário gerir dois níveis de informação interligados, permitindo inserções, buscas, alterações, remoções e consultas estatísticas de forma dinâmica.

### Desenho da Solução e Estruturas de Dados
A solução foi projetada utilizando **Listas Duplamente Encadeadas de Listas Duplamente Encadeadas**:
* **Estrutura Principal (Externa):** Lista duplamente encadeada de municípios (`Municipio`).
* **Estrutura Secundária (Interna):** Cada nó de `Municipio` possui um ponteiro `lista_cachoeiras`, que aponta para a cabeça de uma sublista duplamente encadeada de `Cachoeira`.

A escolha por encadeamento duplo (`ant` e `prox`) em ambos os níveis garante:
* Navegação bidirecional rápida.
* Facilidade na remoção e inserção de elementos no início, meio ou fim da lista.
* Modificação simplificada de ponteiros vizinhos durante operações de isolamento de nós.

---

## 2. Documentação do Código

O projeto encontra-se modularizado nos seguintes ficheiros:
* `cachoeira.h`: Definição das estruturas de dados e protótipos das funções.
* `cachoeira.c`: Implementação da lógica de negócio, manipulação de ponteiros e gestão de memória dinâmica.
* `main.c`: Interface interativa via console (menu) para interação com o utilizador.
* `dados_cachoeiras.txt`: Ficheiro de texto para persistência inicial e leitura automatizada dos dados.

### 2.1. Funções Básicas de Manipulação (CRUD)

* **Inclusão (`inserir_municipio`, `inserir_cachoeira`)**
  * **Propósito:** Alocar memória dinamicamente (`malloc`) e anexar um novo nó no final da lista.
  * **Funcionamento:** Para cachoeiras, localiza-se primeiro o município proprietário (através do seu ID) antes de encadear o nó na sublista correspondente.

* **Busca (`buscar_municipio`, `buscar_cachoeira`)**
  * **Propósito:** Localizar um registo específico na memória através do ID.
  * **Funcionamento:** Realizam travessia linear (`while(atual != NULL)`) até encontrar o ID desejado ou atingir o fim da lista, retornando o ponteiro para o nó correspondente.

* **Alteração (`alterar_municipio`, `alterar_cachoeira`)**
  * **Propósito:** Atualizar as informações armazenadas num nó existente.
  * **Funcionamento:** Utilizam as funções de busca para recuperar o endereço do nó e sobrescrevem os campos necessários (como `nome`, `altura` e `dificuldade`).

* **Remoção (`remover_municipio`, `remover_cachoeira`)**
  * **Propósito:** Eliminar registos da memória em tempo de execução sem deixar ponteiros soltos.
  * **Funcionamento:** Reajustam os ponteiros `prox` e `ant` dos nós vizinhos. Na remoção de um município, é chamada a função auxiliar `remover_todas_cachoeiras` para desalocar primeiramente todos os nós da sublista de cachoeiras, libertando depois a memória do nó pai via `free()`.

### 2.2. Funções Adicionais e Consultas Especializadas

* **`carregar_dados_arquivo`**
  * Lê e interpreta o ficheiro `dados_cachoeiras.txt` (distinguindo linhas `M` para município e `C` para cachoeiras) e constrói automaticamente as listas na inicialização do programa.

* **`listar_todas_cachoeiras`**
  * Percorre toda a estrutura de municípios e as suas respetivas sublistas, exibindo uma listagem completa de todas as cachoeiras registadas no sistema, independentemente do município.

* **`contar_cachoeiras_por_municipio`**
  * Itera sobre cada município da lista principal, conta quantos nós existem na sublista de cachoeiras correspondente e exibe o total individualizado por município.

* **`filtrar_cachoeiras_por_dificuldade`**
  * Percorre toda a estrutura de listas encadeadas e exibe apenas as cachoeiras que coincidem com a dificuldade especificada (`Facil`, `Media` ou `Dificil`).

* **`gerar_estatisticas_gerais`**
  * Calcula métricas do sistema, como o número total de municípios, o total global de cachoeiras e a média de cachoeiras por município.

* **`municipio_com_menos_cachoeiras`**
  * Analisa todas as sublistas e identifica qual município possui o menor número de quedas d'água registadas,retornando o ponteiro para o nó correspondente.

---

## 3. Exemplos de Uso

Abaixo estão demonstrados cenários reais de execução do sistema, incluindo as entradas fornecidas pelo utilizador e as respetivas saídas geradas no terminal.

### Exemplo 1: Leitura de Ficheiro e Listagem de Municípios

**Entrada (Opção 1 no menu principal):**

(PRINT)

**Saída obtida:**

(PRINT)

### Exemplo 2: Consulta de Cachoeiras por Município

**Entrada (Opção 5 no menu principal):**

(PRINT)

**Saída obtida:**

(PRINT)

### Exemplo 3: Filtragem por Dificuldade

**Entrada (Opção 11 no menu principal):**

(PRINT)

**Saída obtida:**

(PRINT)

---

## 4. Conclusão

A realização deste projeto permitiu à nossa equipa consolidar conceitos fundamentais de Estruturas de Dados e alocação dinâmica em linguagem C. A construção de uma arquitetura bidimensional baseada em **Listas Duplamente Encadeadas de Listas** trouxe um aprendizado prático valioso, mas também nos impôs desafios significativos durante o desenvolvimento.

### Desafios Enfrentados pelo Grupo

1. **Gestão de Ponteiros e Tratamento de Casos de Borda:**
   O principal desafio técnico do grupo foi garantir a integridade dos ponteiros (`ant` e `prox`) em operações de remoção e inserção. Identificámos dificuldades iniciais ao lidar com os casos limite, tais como a remoção do primeiro elemento da lista (onde a cabeça da lista precisa de ser atualizada) ou do único elemento existente, evitando ponteiros "órfãos" (*dangling pointers*).

2. **Prevenção de Vazamentos de Memória (*Memory Leaks*):**
   Durante a implementação da eliminação de municípios, percebemos que não bastava desalocar o nó do município. Tivemos de desenvolver a lógica auxiliar `remover_todas_cachoeiras` para varrer e libertar primeiro toda a sublista de cachoeiras associadas antes de libertar a memória do município pai. Acompanhar a memória alocada com `malloc` e garantir o correspondente `free` exigiu testes minuciosos de depuração.

3. **Persistência de Dados e Leitura de Ficheiros:**
   A integração com o ficheiro `dados_cachoeiras.txt` apresentou desafios no parsing das linhas via `fscanf`. O grupo precisou de tratar cuidadosamente a limpeza do *buffer* de entrada (`getchar()`) e a correspondência dos delimitadores (como o caractere `;` e as quebras de linha `\n`) para que os registos de municípios (`M`) e cachoeiras (`C`) fossem interpretados e encadeados na ordem correta.

### Principais Lições Aprendidas

Esta experiência reforçou para a nossa equipa a importância do planeamento e da modularização do código. Aprendemos na prática que a escolha adequada de estruturas de dados simplifica a solução de problemas complexos e que o rigor na manipulação de memória é crucial para construir programas estáveis, seguros e eficientes em C.
