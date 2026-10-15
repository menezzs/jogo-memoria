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
    if (paresJogador1 < 0 || paresJogador1 > TOTAL_PARES ||
        paresJogador2 < 0 || paresJogador2 > TOTAL_PARES) {
        return -1;
    }

    int totalEncontrado = paresJogador1 + paresJogador2;

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

/* O RF02 deve inicializar o jogo com 16 cartas formando 8 pares.
   O ponteiro deve apontar para uma estrutura inicializada. */
static int contar_cartas_encontradas(const JogoMemoria *jogo)
{
    if (jogo == 0) {
        return -1;
    }

    int encontradas = 0;
    for (int i = 0; i < RF02_TOTAL_CARTAS; i++) {
        const Carta *carta = &jogo->tabuleiro.cartas[i];
        if (carta->simbolo == 0 ||
            (carta->estado != CARTA_OCULTA &&
             carta->estado != CARTA_VISIVEL &&
             carta->estado != CARTA_ENCONTRADA)) {
            return -1;
        }
        if (carta->estado == CARTA_ENCONTRADA) {
            encontradas++;
        }
    }

    /* O RF02 sempre marca as duas cartas de um par juntas. */
    return encontradas % 2 == 0 ? encontradas : -1;
}

EXPORTAR
int rf05_verificar_fim(const JogoMemoria *jogo)
{
    int encontradas = contar_cartas_encontradas(jogo);
    if (encontradas < 0) {
        return -1;
    }
    return encontradas == RF02_TOTAL_CARTAS;
}

EXPORTAR
int rf05_apurar_vencedor(const JogoMemoria *jogo,
                        int paresJogador1, int paresJogador2)
{
    int encontradas = contar_cartas_encontradas(jogo);
    int resultado = apurarVencedor(paresJogador1, paresJogador2);

    if (encontradas < 0 || resultado == RESULTADO_INVALIDO) {
        return RESULTADO_INVALIDO;
    }

    /* Os totais devem vir do RF04 depois de contabilizar a jogada. */
    if (paresJogador1 + paresJogador2 != encontradas / 2) {
        return RESULTADO_INVALIDO;
    }

    return resultado;
}

ResultadoJogada rf05_escolher_carta(JogoMemoria *jogo,
                                   ControleTurnos *turnos, int posicao)
{
    if (rf03_obter_jogador(turnos) == 0 ||
        rf05_verificar_fim(jogo) != 0) {
        return JOGADA_INVALIDA;
    }

    ResultadoJogada resultado = rf02_escolher_carta(jogo, posicao);
    rf03_processar_resultado(turnos, resultado);
    return resultado;
}
