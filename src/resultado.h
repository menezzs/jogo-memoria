#ifndef RESULTADO_H
#define RESULTADO_H

#define TOTAL_PARES 8

#define RESULTADO_INVALIDO    -2
#define PARTIDA_EM_ANDAMENTO  -1
#define RESULTADO_EMPATE       0
#define VITORIA_JOGADOR_1       1
#define VITORIA_JOGADOR_2       2

int verificarFimJogo(int paresJogador1, int paresJogador2);
int apurarVencedor(int paresJogador1, int paresJogador2);

#endif
