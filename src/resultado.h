#ifndef RESULTADO_H
#define RESULTADO_H

#include "rf02.h"
#include "turnos.h"
#include "pontuacao.h"

#define TOTAL_PARES 8

#define RESULTADO_INVALIDO    -2
#define PARTIDA_EM_ANDAMENTO  -1
#define RESULTADO_EMPATE       0
#define VITORIA_JOGADOR_1       1
#define VITORIA_JOGADOR_2       2

int verificarFimJogo(int paresJogador1, int paresJogador2);
int apurarVencedor(int paresJogador1, int paresJogador2);

/* -1: tabuleiro invalido; 0: em andamento; 1: encerrado. */
int rf05_verificar_fim(const JogoMemoria *jogo);

/* Confere os totais do RF04 com as cartas encontradas no RF02. */
int rf05_apurar_vencedor(const JogoMemoria *jogo,
                        int paresJogador1, int paresJogador2);

/* Chamar no lugar de rf02_escolher_carta para integrar RF02 e RF03.
   Nao chamar rf03_processar_resultado novamente para a mesma selecao.
   A pontuacao do RF04 deve ser atualizada pelo chamador apos o retorno. */
ResultadoJogada rf05_escolher_carta(JogoMemoria *jogo,
                                   ControleTurnos *turnos, int posicao);

int rf05_apurar_placar(const JogoMemoria *jogo, const Placar *placar);
/* Funções sem ponteiros para a interface e o console. */
int PartidaEncerrada(void);
int ObterVencedor(void);

#endif
