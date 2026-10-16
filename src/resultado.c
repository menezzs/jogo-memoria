#include "resultado.h"
#include "jogo_api.h"
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


int rf05_apurar_placar(const JogoMemoria *jogo, const Placar *placar)
{
    if (placar == 0) return RESULTADO_INVALIDO;
    int p1 = placar->jogadores[0].pontos;
    int p2 = placar->jogadores[1].pontos;
    if (verificarFimJogo(p1, p2) < 0 ||
        placar->paresEncontrados != p1 + p2 ||
        placar->jogadores[0].tentativas < p1 ||
        placar->jogadores[1].tentativas < p2 ||
        placar->totalTentativas < 0 ||
        (long long)placar->totalTentativas !=
            (long long)placar->jogadores[0].tentativas +
            placar->jogadores[1].tentativas) {
        return RESULTADO_INVALIDO;
    }
    return rf05_apurar_vencedor(jogo, p1, p2);
}

EXPORTAR
int PartidaEncerrada(void)
{
    const JogoMemoria *jogo = ConsultarJogo();
    return jogo != 0 && rf05_verificar_fim(jogo) == 1;
}

EXPORTAR
int ObterVencedor(void)
{
    return rf05_apurar_placar(ConsultarJogo(), ConsultarPlacar());
}
