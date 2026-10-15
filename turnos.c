#include "turnos.h"
#include "rf02.h"

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#else
#define EMSCRIPTEN_KEEPALIVE
#endif

static ControleTurnos controle = {1, 0};

static int controle_valido(const ControleTurnos *turnos) {
    return turnos && (turnos->jogadorAtual == 1 || turnos->jogadorAtual == 2);
}

void rf03_inicializar(ControleTurnos *turnos) {
    if (turnos) {
        turnos->jogadorAtual = 1;
        turnos->ultimoJogador = 0;
    }
}

int rf03_obter_jogador(const ControleTurnos *turnos) {
    return controle_valido(turnos) ? turnos->jogadorAtual : 0;
}

int rf03_obter_ultimo_jogador(const ControleTurnos *turnos) {
    return controle_valido(turnos) ? turnos->ultimoJogador : 0;
}

int rf03_processar_resultado(ControleTurnos *turnos, int resultado) {
    if (!controle_valido(turnos)) {
        return 0;
    }

    if (resultado == PAR_ENCONTRADO || resultado == PAR_DIFERENTE) {
        turnos->ultimoJogador = turnos->jogadorAtual;
        if (resultado == PAR_DIFERENTE) {
            turnos->jogadorAtual = 3 - turnos->jogadorAtual;
        }
    } else if (resultado != JOGADA_INVALIDA && resultado != PRIMEIRA_CARTA &&
               resultado != AGUARDANDO_LIBERACAO) {
        return 0;
    }

    return turnos->jogadorAtual;
}

EMSCRIPTEN_KEEPALIVE
void IniciarTurnos(void) {
    rf03_inicializar(&controle);
}

EMSCRIPTEN_KEEPALIVE
int ObterJogadorAtual(void) {
    return rf03_obter_jogador(&controle);
}

EMSCRIPTEN_KEEPALIVE
int ObterJogadorDaUltimaJogada(void) {
    return rf03_obter_ultimo_jogador(&controle);
}

EMSCRIPTEN_KEEPALIVE
int ProcessarResultadoJogada(int resultado) {
    return rf03_processar_resultado(&controle, resultado);
}
