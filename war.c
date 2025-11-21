// ============================================================================
//         PROJETO WAR ESTRUTURADO - DESAFIO DE CÓDIGO
// ============================================================================
//        
// ============================================================================
//
// OBJETIVOS:
// - Modularizar completamente o código em funções especializadas.
// - Implementar um sistema de missões para um jogador.
// - Criar uma função para verificar se a missão foi cumprida.
// - Utilizar passagem por referência (ponteiros) para modificar dados e
//   passagem por valor/referência constante (const) para apenas ler.
// - Foco em: Design de software, modularização, const correctness, lógica de jogo.
//
// ============================================================================

// Inclusão das bibliotecas padrão necessárias para entrada/saída, alocação de memória, manipulação de strings e tempo.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Estrutura que representa um território no jogo
typedef struct {
    char nome[30];   // Nome do território
    char cor[10];    // Cor do exército que domina o território
    int tropas;      // Quantidade de tropas presentes no território
} Territorio;

// Função para cadastrar os territórios
// Recebe um ponteiro para o vetor de territórios e a quantidade de territórios
void cadastrarTerritorios(Territorio* mapa, int n) {
    printf("Cadastro de Territórios\n");
    printf("=======================\n");
    for (int i = 0; i < n; i++) {
        printf("\nTerritório %d:\n", i + 1);
        printf("Digite o nome do território: ");
        scanf("%29s", mapa[i].nome); // Lê o nome do território
        printf("Digite a cor do exército: ");
        scanf("%9s", mapa[i].cor);   // Lê a cor do exército
        printf("Digite a quantidade de tropas: ");
        scanf("%d", &mapa[i].tropas); // Lê a quantidade de tropas
    }
}

// Função para exibir os dados dos territórios
// Recebe um ponteiro constante para o vetor de territórios e a quantidade de territórios
void exibirTerritorios(const Territorio* mapa, int n) {
    printf("\nDados dos Territórios:\n");
    printf("=====================\n");
    for (int i = 0; i < n; i++) {
        printf("Território %d:\n", i + 1);
        printf("Nome: %s\n", mapa[i].nome);
        printf("Cor do Exército: %s\n", mapa[i].cor);
        printf("Tropas: %d\n", mapa[i].tropas);
        printf("--------------------------\n");
    }
}

// Função que simula um ataque entre dois territórios
// Recebe ponteiros para o território atacante e defensor
void atacar(Territorio* atacante, Territorio* defensor) {
    printf("\nSimulando ataque de %s (%s) contra %s (%s)\n", atacante->nome, atacante->cor, defensor->nome, defensor->cor);
    int dado_atacante = (rand() % 6) + 1; // Simula dado do atacante (1 a 6)
    int dado_defensor = (rand() % 6) + 1; // Simula dado do defensor (1 a 6)
    printf("Dado atacante: %d\n", dado_atacante);
    printf("Dado defensor: %d\n", dado_defensor);

    if (dado_atacante > dado_defensor) {
        // Se o atacante vencer, o defensor muda de cor e perde tropas
        printf("O atacante venceu!\n");
        strcpy(defensor->cor, atacante->cor); // Atualiza cor do defensor
        defensor->tropas = atacante->tropas / 2; // Atualiza tropas do defensor
        printf("O território %s agora pertence ao exército %s.\n", defensor->nome, defensor->cor);
    } else {
        // Se o defensor vencer, o atacante perde uma tropa (se possível)
        printf("O defensor resistiu ao ataque!\n");
        if (atacante->tropas > 1) {
            atacante->tropas -= 1;
            printf("O atacante perdeu uma tropa. Tropas restantes: %d\n", atacante->tropas);
        } else {
            printf("O atacante não tem tropas suficientes para continuar atacando.\n");
        }
    }
}

// Função para liberar a memória alocada dinamicamente para o vetor de territórios
void liberarMemoria(Territorio* mapa) {
    free(mapa);
}

// Vetor de missões estratégicas
const char* missoes[] = {
    "Conquistar 3 territórios seguidos",
    "Eliminar todas as tropas da cor vermelha",
    "Ter pelo menos 2 territórios com mais de 10 tropas",
    "Conquistar um território de cada cor",
    "Ter o maior número de territórios ao final do turno"
};
const int totalMissoes = 5;

// Função que sorteia e atribui uma missão ao jogador
void atribuirMissao(char* destino, const char* missoes[], int totalMissoes) {
    int sorteio = rand() % totalMissoes;
    strcpy(destino, missoes[sorteio]);
}

// Função para exibir a missão do jogador
void exibirMissao(const char* missao) {
    printf("\nSua missão: %s\n", missao);
}

// Função que verifica se a missão foi cumprida (lógica simples inicial)
int verificarMissao(const char* missao, Territorio* mapa, int tamanho) {
    // Exemplo de lógica para cada missão
    if (strcmp(missao, missoes[0]) == 0) {
        // Conquistar 3 territórios seguidos (mesma cor do jogador)
        int seguidos = 0;
        for (int i = 0; i < tamanho; i++) {
            if (i > 0 && strcmp(mapa[i].cor, mapa[i-1].cor) == 0) {
                seguidos++;
                if (seguidos >= 2) return 1;
            } else {
                seguidos = 0;
            }
        }
    } else if (strcmp(missao, missoes[1]) == 0) {
        // Eliminar todas as tropas da cor vermelha
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, "vermelha") == 0 && mapa[i].tropas > 0)
                return 0;
        }
        return 1;
    } else if (strcmp(missao, missoes[2]) == 0) {
        // Ter pelo menos 2 territórios com mais de 10 tropas
        int count = 0;
        for (int i = 0; i < tamanho; i++) {
            if (mapa[i].tropas > 10) count++;
        }
        if (count >= 2) return 1;
    } else if (strcmp(missao, missoes[3]) == 0) {
        // Conquistar um território de cada cor (azul, vermelha, verde, amarelo)
        int azul=0, vermelha=0, verde=0, amarelo=0;
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, "azul") == 0) azul = 1;
            if (strcmp(mapa[i].cor, "vermelha") == 0) vermelha = 1;
            if (strcmp(mapa[i].cor, "verde") == 0) verde = 1;
            if (strcmp(mapa[i].cor, "amarelo") == 0) amarelo = 1;
        }
        if (azul && vermelha && verde && amarelo) return 1;
    } else if (strcmp(missao, missoes[4]) == 0) {
        // Ter o maior número de territórios ao final do turno
        // Simples: verifica se a cor do jogador domina mais territórios
        // (Necessário passar a cor do jogador, aqui só exemplo)
        // Retorne 0 para não declarar vitória automática
        return 0;
    }
    return 0;
}

// Função principal do programa
int main() {
    srand(time(NULL)); // Inicializa a semente para números aleatórios

    int n;
    printf("Informe o número de territórios: ");
    scanf("%d", &n);

    // Aloca dinamicamente o vetor de territórios
    Territorio* mapa = (Territorio*)calloc(n, sizeof(Territorio));
    if (!mapa) {
        printf("Erro ao alocar memória!\n");
        return 1;
    }

    // Cadastro e exibição inicial dos territórios
    cadastrarTerritorios(mapa, n);
    exibirTerritorios(mapa, n);

    // Aloca dinamicamente a missão do jogador
    char* missao_jogador = (char*)malloc(100 * sizeof(char));
    if (!missao_jogador) {
        printf("Erro ao alocar memória para missão!\n");
        liberarMemoria(mapa);
        return 1;
    }
    atribuirMissao(missao_jogador, missoes, totalMissoes);
    exibirMissao(missao_jogador);

    // Solicita ao jogador a cor do exército que irá atacar
    char cor_jogador[10];
    printf("\nDigite sua cor de exército para atacar: ");
    scanf("%9s", cor_jogador);

    int opcao;
    do {
        // Menu de opções para ataque
        printf("\nMenu de Ataque\n");
        printf("1 - Realizar ataque\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        if (opcao == 1) {
            exibirTerritorios(mapa, n);
            int idx_atacante, idx_defensor;
            printf("Escolha o número do território atacante (da sua cor): ");
            scanf("%d", &idx_atacante);
            printf("Escolha o número do território defensor (de outra cor): ");
            scanf("%d", &idx_defensor);

            // Validação das escolhas de territórios
            if (idx_atacante < 1 || idx_atacante > n || idx_defensor < 1 || idx_defensor > n) {
                printf("Índice inválido!\n");
                continue;
            }
            if (strcmp(mapa[idx_atacante - 1].cor, cor_jogador) != 0) {
                printf("Você só pode atacar com territórios da sua cor!\n");
                continue;
            }
            if (strcmp(mapa[idx_defensor - 1].cor, cor_jogador) == 0) {
                printf("Você não pode atacar territórios da sua própria cor!\n");
                continue;
            }
            // Realiza o ataque e exibe os dados atualizados
            atacar(&mapa[idx_atacante - 1], &mapa[idx_defensor - 1]);
            exibirTerritorios(mapa, n);

            // Verifica se a missão foi cumprida após o ataque
            if (verificarMissao(missao_jogador, mapa, n)) {
                printf("\nParabéns! Você cumpriu sua missão e venceu o jogo!\n");
                break;
            }
        }
    } while (opcao != 0);

    // Libera a memória alocada antes de encerrar o programa
    liberarMemoria(mapa);
    free(missao_jogador);
    return 0;
}

// --- Implementação das Funções ---

// alocarMapa():
// Aloca dinamicamente a memória para o vetor de territórios usando calloc.
// Retorna um ponteiro para a memória alocada ou NULL em caso de falha.

// inicializarTerritorios():
// Preenche os dados iniciais de cada território no mapa (nome, cor do exército, número de tropas).
// Esta função modifica o mapa passado por referência (ponteiro).

// liberarMemoria():
// Libera a memória previamente alocada para o mapa usando free.

// exibirMenuPrincipal():
// Imprime na tela o menu de ações disponíveis para o jogador.

// exibirMapa():
// Mostra o estado atual de todos os territórios no mapa, formatado como uma tabela.
// Usa 'const' para garantir que a função apenas leia os dados do mapa, sem modificá-los.

// exibirMissao():
// Exibe a descrição da missão atual do jogador com base no ID da missão sorteada.

// faseDeAtaque():
// Gerencia a interface para a ação de ataque, solicitando ao jogador os territórios de origem e destino.
// Chama a função simularAtaque() para executar a lógica da batalha.

// simularAtaque():
// Executa a lógica de uma batalha entre dois territórios.
// Realiza validações, rola os dados, compara os resultados e atualiza o número de tropas.
// Se um território for conquistado, atualiza seu dono e move uma tropa.

// sortearMissao():
// Sorteia e retorna um ID de missão aleatório para o jogador.

// verificarVitoria():
// Verifica se o jogador cumpriu os requisitos de sua missão atual.
// Implementa a lógica para cada tipo de missão (destruir um exército ou conquistar um número de territórios).
// Retorna 1 (verdadeiro) se a missão foi cumprida, e 0 (falso) caso contrário.

// limparBufferEntrada():
// Função utilitária para limpar o buffer de entrada do teclado (stdin), evitando problemas com leituras consecutivas de scanf e getchar.
