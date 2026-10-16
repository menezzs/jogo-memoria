#include "pontuacao.h"
#include "rf02.h"

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#else
#define EMSCRIPTEN_KEEPALIVE
#endif

static Placar placar;

void rf04_inicializar(Placar *p) {
    int i;
    if (!p) {
        return;
    }
    for (i = 0; i < 2; i++) {
        p->jogadores[i].pontos = 0;
        p->jogadores[i].tentativas = 0;
    }
    p->totalTentativas = 0;
    p->paresEncontrados = 0;
}

int rf04_registrar(Placar *p, int jogador, int resultado) {
    if (!p || jogador < 1 || jogador > 2 || p->paresEncontrados >= 8 ||
        (resultado != PAR_ENCONTRADO && resultado != PAR_DIFERENTE)) {
        return 0;
    }
    p->jogadores[jogador - 1].tentativas++;
    p->totalTentativas++;
    if (resultado == PAR_ENCONTRADO) {
        p->jogadores[jogador - 1].pontos++;
        p->paresEncontrados++;
    }
    return 1;
}

EMSCRIPTEN_KEEPALIVE
void IniciarPontuacao(void) {
    rf04_inicializar(&placar);
}

int RegistrarTentativa(int jogador, int resultado) {
    return rf04_registrar(&placar, jogador, resultado);
}

EMSCRIPTEN_KEEPALIVE
int ObterPontos(int jogador) {
    return jogador >= 1 && jogador <= 2 ? placar.jogadores[jogador - 1].pontos : -1;
}

EMSCRIPTEN_KEEPALIVE
int ObterTentativas(int jogador) {
    return jogador >= 1 && jogador <= 2 ? placar.jogadores[jogador - 1].tentativas : -1;
}

EMSCRIPTEN_KEEPALIVE
int ObterTotalTentativas(void) {
    return placar.totalTentativas;
}

EMSCRIPTEN_KEEPALIVE
int ObterParesEncontrados(void) {
    return placar.paresEncontrados;
}

const Placar *ConsultarPlacar(void) {
    return &placar;
}
