#include <assert.h>
#include <stdio.h>
#include "../src/resultado.h"

static const char *simbolos[16] = {
    "A", "A", "B", "B", "C", "C", "D", "D",
    "E", "E", "F", "F", "G", "G", "H", "H"
};

/* Totais apenas do teste: substituem as entradas ainda ausentes do RF04.
   Nao sao uma implementacao de pontuacao do projeto. */
static void erro(JogoMemoria *j, ControleTurnos *t)
{
    int anterior = rf03_obter_jogador(t);
    int a = -1, b = -1;
    for (int i = 0; i < 16; i++) {
        if (j->tabuleiro.cartas[i].estado != CARTA_OCULTA) continue;
        if (a == -1) a = i;
        else if (i / 2 != a / 2) { b = i; break; }
    }
    assert(a >= 0 && b >= 0);
    assert(rf05_escolher_carta(j, t, a) == PRIMEIRA_CARTA);
    assert(rf05_escolher_carta(j, t, b) == PAR_DIFERENTE);
    assert(rf03_obter_ultimo_jogador(t) == anterior);
    assert(rf03_obter_jogador(t) == 3 - anterior);
    int ultimo = rf03_obter_ultimo_jogador(t);
    assert(rf05_escolher_carta(j, t, 0) == AGUARDANDO_LIBERACAO);
    assert(rf03_obter_ultimo_jogador(t) == ultimo);
    assert(rf02_ocultar_erro(j) == 1);
}

static void partida(int paresDoPrimeiro)
{
    JogoMemoria j = {0};
    ControleTurnos t;
    int pares[2] = {0, 0};
    assert(rf02_inicializar(&j, simbolos));
    rf03_inicializar(&t);
    assert(rf05_apurar_vencedor(&j, 0, 0) == PARTIDA_EM_ANDAMENTO);
    assert(rf05_apurar_vencedor(&j, 1, 0) == RESULTADO_INVALIDO);
    assert(rf05_escolher_carta(&j, &t, -1) == JOGADA_INVALIDA);
    assert(rf03_obter_jogador(&t) == 1);

    for (int par = 0; par < 8; par++) {
        /* Na regra recebida, somente o erro passa a vez. */
        int desejado = paresDoPrimeiro == 7 ? (par == 0 ? 2 : 1) :
            (par < paresDoPrimeiro ? 1 : 2);
        if (rf03_obter_jogador(&t) != desejado) {
            erro(&j, &t);
        }
        int jogador = rf03_obter_jogador(&t);
        assert(rf05_escolher_carta(&j, &t, 2 * par) == PRIMEIRA_CARTA);
        assert(rf05_escolher_carta(&j, &t, 2 * par) == JOGADA_INVALIDA);
        assert(rf05_escolher_carta(&j, &t, 2 * par + 1) == PAR_ENCONTRADO);
        assert(rf03_obter_jogador(&t) == jogador);
        assert(rf03_obter_ultimo_jogador(&t) == jogador);
        pares[jogador - 1]++;
        assert(rf05_escolher_carta(&j, &t, 2 * par) == JOGADA_INVALIDA);
        assert(rf05_verificar_fim(&j) == (par == 7));
        int esperado = par < 7 ? PARTIDA_EM_ANDAMENTO :
            apurarVencedor(pares[0], pares[1]);
        assert(rf05_apurar_vencedor(&j, pares[0], pares[1]) == esperado);
    }
    assert(pares[0] == paresDoPrimeiro);
    assert(pares[1] == 8 - paresDoPrimeiro);
    JogoMemoria antes = j;
    ControleTurnos turnoAntes = t;
    assert(rf05_escolher_carta(&j, &t, 0) == JOGADA_INVALIDA);
    for (int i = 0; i < 16; i++) {
        assert(j.tabuleiro.cartas[i].estado == antes.tabuleiro.cartas[i].estado);
    }
    assert(t.jogadorAtual == turnoAntes.jogadorAtual);
    assert(t.ultimoJogador == turnoAntes.ultimoJogador);
    assert(rf02_inicializar(&j, simbolos));
    rf03_inicializar(&t);
    assert(rf05_verificar_fim(&j) == 0);
    assert(rf03_obter_jogador(&t) == 1);
    assert(rf05_apurar_vencedor(&j, 0, 0) == PARTIDA_EM_ANDAMENTO);
}

int main(void)
{
    assert(apurarVencedor(5, 3) == VITORIA_JOGADOR_1);
    assert(apurarVencedor(3, 5) == VITORIA_JOGADOR_2);
    assert(apurarVencedor(4, 4) == RESULTADO_EMPATE);
    assert(apurarVencedor(-1, 2) == RESULTADO_INVALIDO);
    assert(apurarVencedor(9, 0) == RESULTADO_INVALIDO);
    assert(apurarVencedor(5, 4) == RESULTADO_INVALIDO);
    assert(rf05_verificar_fim(0) == -1);
    assert(rf05_apurar_vencedor(0, 4, 4) == RESULTADO_INVALIDO);
    JogoMemoria vazio = {0};
    assert(rf05_verificar_fim(&vazio) == -1);
    for (int i = 0; i <= 8; i++) partida(i);
    puts("RF02 + RF03 + RF05: todos os testes passaram.");
    puts("RF04 ainda nao incluido: totais de pares fornecidos pelo teste.");
    return 0;
}
