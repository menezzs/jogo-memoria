#include <stdio.h>
#include <locale.h>
#include "rf02.h"
#include "turnos.h"
#include "pontuacao.h"
#include "resultado.h"

void Embaralhar(void);
const char *ReturnCart(int posicao);
int EstadoDaCarta(int posicao);
int RealizarJogada(int linha1, int coluna1, int linha2, int coluna2);
int OcultarErro(void);

static void mostrar_tabuleiro(void) {
    int i;
    for (i = 0; i < 16; i++) {
        if (EstadoDaCarta(i) == CARTA_OCULTA) {
            printf("[%8d]", i + 1);
        } else {
            printf("[%8s]", ReturnCart(i));
        }
        if ((i + 1) % 4 == 0) {
            printf("\n");
        }
    }
    printf("Jogador 1: %d pares, %d tentativas\n", ObterPontos(1), ObterTentativas(1));
    printf("Jogador 2: %d pares, %d tentativas\n", ObterPontos(2), ObterTentativas(2));
}

static int limpar_linha(void) {
    int caractere = getchar();
    while (caractere != '\n' && caractere != EOF) {
        caractere = getchar();
    }
    return caractere;
}

int main(void) {
    int a;
    int b;
    int resultado;
    int vencedor;
    int continuar = 1;
    int lidos;
    setlocale(LC_ALL, "Portuguese");
    printf("JOGO DA MEMORIA - DOIS JOGADORES\n");
    while (continuar == 1) {
        Embaralhar();
        while (!PartidaEncerrada()) {
            mostrar_tabuleiro();
            printf("Vez do jogador %d. Escolha duas posicoes de 1 a 16: ", ObterJogadorAtual());
            lidos = scanf("%d %d", &a, &b);
            if (lidos == EOF) {
                printf("\nEntrada encerrada.\n");
                return 0;
            }
            if (lidos != 2) {
                printf("Digite dois numeros inteiros.\n");
                if (limpar_linha() == EOF) {
                    return 0;
                }
            } else if (a < 1 || a > 16 || b < 1 || b > 16) {
                printf("Posicoes invalidas. A vez foi mantida.\n");
            } else {
                resultado = RealizarJogada((a - 1) / 4 + 1, (a - 1) % 4 + 1,
                                          (b - 1) / 4 + 1, (b - 1) % 4 + 1);
                if (resultado == PAR_ENCONTRADO) {
                    printf("Par correto.\n");
                } else if (resultado == PAR_DIFERENTE) {
                    mostrar_tabuleiro();
                    printf("Cartas diferentes. Pressione Enter para oculta-las e passar a vez.\n");
                    if (limpar_linha() == EOF || getchar() == EOF) {
                        return 0;
                    }
                    OcultarErro();
                } else {
                    printf("Escolha duas cartas ocultas diferentes.\n");
                }
            }
        }
        mostrar_tabuleiro();
        vencedor = ObterVencedor();
        if (vencedor == 0) {
            printf("Empate: quatro pares para cada jogador.\n");
        } else {
            printf("Jogador %d venceu com %d pares.\n", vencedor, ObterPontos(vencedor));
        }
        printf("Nova partida? Digite 1 para sim ou 0 para sair: ");
        if (scanf("%d", &continuar) != 1) {
            continuar = 0;
        }
    }
    return 0;
}
