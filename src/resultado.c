#include "resultado.h"
#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#define EXPORTAR EMSCRIPTEN_KEEPALIVE
#else
#define EXPORTAR
#endif

/*
Retorna:
-1 = dados inválidos
 0 = partida em andamento
 1 = partida encerrada
*/

EXPORTAR
int verificarFimJogo(int paresJogador1, int paresJogador2)
{
    /* Cada jogador pode encontrar de 0 a 8 pares. */
    if (paresJogador1 < 0 || paresJogador1 > TOTAL_PARES ||
        paresJogador2 < 0 || paresJogador2 > TOTAL_PARES) {
        return -1;
    }

    int totalEncontrado = paresJogador1 + paresJogador2;

    /* O tabuleiro possui apenas 8 pares. */
    if (totalEncontrado > TOTAL_PARES) {
        return -1;
    }

    return totalEncontrado == TOTAL_PARES;
}

/*
Retorna:
-2 = dados inválidos
-1 = partida em andamento
 0 = empate
 1 = jogador 1 venceu
 2 = jogador 2 venceu
*/

EXPORTAR
int apurarVencedor(int paresJogador1, int paresJogador2)
{
    int estado = verificarFimJogo(
        paresJogador1,
        paresJogador2
    );

    if (estado == -1) {
        return RESULTADO_INVALIDO;
    }

    if (estado == 0) {
        return PARTIDA_EM_ANDAMENTO;
    }

    if (paresJogador1 > paresJogador2) {
        return VITORIA_JOGADOR_1;
    }

    if (paresJogador2 > paresJogador1) {
        return VITORIA_JOGADOR_2;
    }

    return RESULTADO_EMPATE;
}
