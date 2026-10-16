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

int rf05_verificar_fim(const JogoMemoria *jogo);

int rf05_apurar_vencedor(const JogoMemoria *jogo,
                        int paresJogador1, int paresJogador2);

ResultadoJogada rf05_escolher_carta(JogoMemoria *jogo,
                                   ControleTurnos *turnos, int posicao);

int rf05_apurar_placar(const JogoMemoria *jogo, const Placar *placar);
int PartidaEncerrada(void);
int ObterVencedor(void);

#endif
