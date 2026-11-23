#include "rf02.h"

static int posicao_valida(int posicao) {
    return posicao >= 0 && posicao < RF02_TOTAL_CARTAS;
}

static int simbolos_iguais(const char *primeiro, const char *segundo) {
    int i = 0;

    if (primeiro == 0 || segundo == 0) {
        return 0;
    }

    while (primeiro[i] != '\0' && segundo[i] != '\0' &&
           primeiro[i] == segundo[i]) {
        i++;
    }

    return primeiro[i] == segundo[i];
}

static void limpar_jogada(Jogada *jogada) {
    jogada->primeira = -1;
    jogada->segunda = -1;
    jogada->aguardando = 0;
}

int rf02_inicializar(JogoMemoria *jogo, const char *const simbolos[]) {
    int i;

    if (jogo == 0 || simbolos == 0) {
        return 0;
    }

    for (i = 0; i < RF02_TOTAL_CARTAS; i++) {
        if (simbolos[i] == 0) {
            return 0;
        }
    }

    for (i = 0; i < RF02_TOTAL_CARTAS; i++) {
        jogo->tabuleiro.cartas[i].simbolo = simbolos[i];
        jogo->tabuleiro.cartas[i].estado = CARTA_OCULTA;
    }

    limpar_jogada(&jogo->jogada);
    return 1;
}

ResultadoJogada rf02_escolher_carta(JogoMemoria *jogo, int posicao) {
    Carta *primeira;
    Carta *segunda;

    if (jogo == 0 || !posicao_valida(posicao)) {
        return JOGADA_INVALIDA;
    }

    if (jogo->jogada.aguardando) {
        return AGUARDANDO_LIBERACAO;
    }

    if (jogo->tabuleiro.cartas[posicao].estado != CARTA_OCULTA) {
        return JOGADA_INVALIDA;
    }

    if (jogo->jogada.primeira == -1) {
        jogo->jogada.primeira = posicao;
        jogo->tabuleiro.cartas[posicao].estado = CARTA_VISIVEL;
        return PRIMEIRA_CARTA;
    }

    jogo->jogada.segunda = posicao;
    primeira = &jogo->tabuleiro.cartas[jogo->jogada.primeira];
    segunda = &jogo->tabuleiro.cartas[posicao];
    segunda->estado = CARTA_VISIVEL;

    if (simbolos_iguais(primeira->simbolo, segunda->simbolo)) {
        primeira->estado = CARTA_ENCONTRADA;
        segunda->estado = CARTA_ENCONTRADA;
        limpar_jogada(&jogo->jogada);
        return PAR_ENCONTRADO;
    }

    jogo->jogada.aguardando = 1;
    return PAR_DIFERENTE;
}

ResultadoJogada rf02_jogar_par(JogoMemoria *jogo, int linha1, int coluna1,
                             int linha2, int coluna2) {
    int primeira;
    int segunda;

    if (jogo == 0 || linha1 < 1 || linha1 > RF02_LADO_TABULEIRO ||
        coluna1 < 1 || coluna1 > RF02_LADO_TABULEIRO ||
        linha2 < 1 || linha2 > RF02_LADO_TABULEIRO ||
        coluna2 < 1 || coluna2 > RF02_LADO_TABULEIRO) {
        return JOGADA_INVALIDA;
    }

    if (jogo->jogada.aguardando) {
        return AGUARDANDO_LIBERACAO;
    }

    primeira = (linha1 - 1) * RF02_LADO_TABULEIRO + coluna1 - 1;
    segunda = (linha2 - 1) * RF02_LADO_TABULEIRO + coluna2 - 1;

    if (jogo->jogada.primeira != -1 || primeira == segunda ||
        jogo->tabuleiro.cartas[primeira].estado != CARTA_OCULTA ||
        jogo->tabuleiro.cartas[segunda].estado != CARTA_OCULTA) {
        return JOGADA_INVALIDA;
    }

    rf02_escolher_carta(jogo, primeira);
    return rf02_escolher_carta(jogo, segunda);
}

int rf02_ocultar_erro(JogoMemoria *jogo) {
    if (jogo == 0 || !jogo->jogada.aguardando ||
        !posicao_valida(jogo->jogada.primeira) ||
        !posicao_valida(jogo->jogada.segunda)) {
        return 0;
    }

    jogo->tabuleiro.cartas[jogo->jogada.primeira].estado = CARTA_OCULTA;
    jogo->tabuleiro.cartas[jogo->jogada.segunda].estado = CARTA_OCULTA;
    limpar_jogada(&jogo->jogada);
    return 1;
}
