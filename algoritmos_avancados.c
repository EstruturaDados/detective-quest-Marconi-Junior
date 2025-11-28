// ===== DETECTIVE QUEST =====

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura da sala
typedef struct sala {
    char nome[50]; // Nome da sala
    struct sala *esquerda; // Caminho à esquerda
    struct sala *direita; // Caminho à direita
} Sala;

// Cria dinamicamente uma sala com o nome informado
Sala* criarSala(const char *nome) {
    Sala *nova = (Sala*) malloc(sizeof(Sala));
    if (!nova) {
        printf("Erro ao alocar memória para a sala!\n");
        exit(1);
    }
    strcpy(nova->nome, nome);
    nova->esquerda = NULL;
    nova->direita = NULL;
    return nova;
}

// Permite o jogador navegar pela árvore binária da mansão
void explorarSalas(Sala *atual) {
    char opcao;

    while (1) {
        printf("\nVocê está em: %s\n", atual->nome);

        if (!atual->esquerda && !atual->direita) { // A exploração termina ao chegar em um nó-folha
            printf("Este é um cômodo sem saídas. A exploração terminou!\n");
            return;
        }

        printf("Escolha o caminho:\n");
        if (atual->esquerda) printf("  (e) Ir para a esquerda -> %s\n", atual->esquerda->nome);
        if (atual->direita)  printf("  (d) Ir para a direita  -> %s\n", atual->direita->nome);
        printf("  (s) Sair\n");
        printf("Opção: ");

        scanf(" %c", &opcao);

        if (opcao == 'e' || opcao == 'E') {
            if (atual->esquerda)
                atual = atual->esquerda;
            else
                printf("Não há caminho à esquerda!\n");
        }
        else if (opcao == 'd' || opcao == 'D') {
            if (atual->direita)
                atual = atual->direita;
            else
                printf("Não há caminho à direita!\n");
        }
        else if (opcao == 's' || opcao == 'S') {
            printf("Exploração encerrada pelo jogador.\n");
            return;
        }
        else {
            printf("Opção inválida! Tente novamente.\n");
        }
    }
}

// Monta manualmente o mapa da mansão (árvore binária) e inicia a exploração
int main() {

    // Criando as salas
    Sala *hall        = criarSala("Hall de Entrada");
    Sala *salaEstar   = criarSala("Sala de Estar");
    Sala *cozinha     = criarSala("Cozinha");
    Sala *biblioteca  = criarSala("Biblioteca");
    Sala *jardim      = criarSala("Jardim");
    Sala *porao       = criarSala("Porão");
    Sala *quarto      = criarSala("Quarto de Hóspede");

    hall->esquerda = salaEstar;
    hall->direita  = cozinha;

    salaEstar->esquerda = biblioteca;
    salaEstar->direita  = jardim;

    cozinha->direita = porao;
    porao->direita   = quarto;

    printf("\n===================================\n");
    printf("         DETECTIVE QUEST\n");
    printf("===================================\n");
    printf("\n----- Mapa da Mansão -----\n");
    printf("Explore a mansão partindo do Hall de Entrada!\n");

    explorarSalas(hall);
 
    return 0;
}

// Árvore da mansão
//
//                  Hall
//                 /    \
//       Sala de Estar   Cozinha
//           /     \        \
//   Biblioteca   Jardim     Porão
//                       \
//                       Quarto
