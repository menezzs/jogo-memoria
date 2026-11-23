#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "../src/jogo_api.h"
#include "../src/resultado.h"

static int jogar(int a, int b)
{
    return RealizarJogada(a / 4 + 1, a % 4 + 1, b / 4 + 1, b % 4 + 1);
}

static void errar(void)
{
    int a = -1, b = -1;
    for (int i = 0; i < 16; i++) {
        if (EstadoDaCarta(i) != CARTA_OCULTA) continue;
        if (a == -1) a = i;
        else if (strcmp(ReturnCart(a), ReturnCart(i)) != 0) { b = i; break; }
    }
    assert(a >= 0 && b >= 0);
    int autor = ObterJogadorAtual();
    int antes = ObterTentativas(autor);
    int pontos = ObterPontos(autor);
    assert(jogar(a, b) == PAR_DIFERENTE);
    assert(ObterJogadorDaUltimaJogada() == autor);
    assert(ObterJogadorAtual() == 3 - autor);
    assert(ObterTentativas(autor) == antes + 1);
    assert(ObterPontos(autor) == pontos);
    assert(jogar(a, b) == AGUARDANDO_LIBERACAO);
    assert(ObterTentativas(autor) == antes + 1);
    assert(OcultarErro() == 1);
    assert(EstadoDaCarta(a) == CARTA_OCULTA);
    assert(EstadoDaCarta(b) == CARTA_OCULTA);
}

static void partida(int alvo)
{
    int pares[8][2], usados[16] = {0}, total = 0;
    Embaralhar();
    assert(ObterJogadorAtual() == 1);
    assert(ObterJogadorDaUltimaJogada() == 0);
    assert(ObterTotalTentativas() == 0);
    assert(ObterParesEncontrados() == 0);
    assert(ObterPontos(1) == 0 && ObterPontos(2) == 0);
    assert(ObterTentativas(1) == 0 && ObterTentativas(2) == 0);
    assert(PartidaEncerrada() == 0);
    assert(ObterVencedor() == PARTIDA_EM_ANDAMENTO);
    for (int i = 0; i < 16; i++) {
        assert(EstadoDaCarta(i) == CARTA_OCULTA);
        assert(ReturnCart(i)[0] != '\0');
        if (usados[i]) continue;
        int ocorrencias = 0, parceiro = -1;
        for (int k = 0; k < 16; k++) {
            if (strcmp(ReturnCart(i), ReturnCart(k)) == 0) {
                ocorrencias++;
                if (k != i) parceiro = k;
            }
        }
        assert(ocorrencias == 2 && parceiro >= 0);
        usados[i] = usados[parceiro] = 1;
        pares[total][0] = i;
        pares[total++][1] = parceiro;
    }
    assert(total == 8);
    assert(EscolherCarta(-1) == JOGADA_INVALIDA);
    assert(EscolherCarta(16) == JOGADA_INVALIDA);
    assert(RealizarJogada(0, 1, 1, 2) == JOGADA_INVALIDA);
    assert(jogar(0, 0) == JOGADA_INVALIDA);
    assert(ObterTotalTentativas() == 0 && ObterJogadorAtual() == 1);

    for (int i = 0; i < 8; i++) {
        int desejado = alvo == 7 ? (i == 0 ? 2 : 1) : (i < alvo ? 1 : 2);
        if (ObterJogadorAtual() != desejado) errar();
        int autor = ObterJogadorAtual();
        int tentativas = ObterTentativas(autor);
        int pontos = ObterPontos(autor);
        int a = pares[i][0], b = pares[i][1];
        if (i % 2 == 0) {
            assert(EscolherCarta(a) == PRIMEIRA_CARTA);
            assert(ObterTentativas(autor) == tentativas);
            assert(EscolherCarta(a) == JOGADA_INVALIDA);
            assert(EscolherCarta(b) == PAR_ENCONTRADO);
        } else {
            assert(jogar(a, b) == PAR_ENCONTRADO);
        }
        assert(ObterPontos(autor) == pontos + 1);
        assert(ObterTentativas(autor) == tentativas + 1);
        assert(ObterJogadorAtual() == autor);
        assert(ObterJogadorDaUltimaJogada() == autor);
        assert(ObterParesEncontrados() == i + 1);
        assert(EstadoDaCarta(a) == CARTA_ENCONTRADA);
        assert(EstadoDaCarta(b) == CARTA_ENCONTRADA);
        assert(jogar(a, b) == JOGADA_INVALIDA);
        assert(ObterPontos(autor) == pontos + 1);
        assert(ObterTentativas(autor) == tentativas + 1);
        assert(PartidaEncerrada() == (i == 7));
        if (i < 7) assert(ObterVencedor() == PARTIDA_EM_ANDAMENTO);
    }
    int esperado = alvo > 4 ? VITORIA_JOGADOR_1 :
                   alvo < 4 ? VITORIA_JOGADOR_2 : RESULTADO_EMPATE;
    assert(ObterPontos(1) == alvo && ObterPontos(2) == 8 - alvo);
    assert(ObterVencedor() == esperado);
    int tentativas = ObterTotalTentativas(), turno = ObterJogadorAtual();
    assert(EscolherCarta(0) == JOGADA_INVALIDA);
    assert(jogar(0, 1) == JOGADA_INVALIDA);
    assert(ObterTotalTentativas() == tentativas);
    assert(ObterJogadorAtual() == turno);
    assert(ObterVencedor() == esperado);
    printf("[OK] Partida completa %d x %d: %s\n", alvo, 8 - alvo,
           esperado == 0 ? "empate" : esperado == 1 ? "jogador 1 venceu" : "jogador 2 venceu");
    printf("     Tentativas reais do RF04: J1=%d J2=%d Total=%d\n",
           ObterTentativas(1), ObterTentativas(2), ObterTotalTentativas());
}

int main(void)
{
    assert(ConsultarJogo() == NULL);
    assert(PartidaEncerrada() == 0);
    assert(ObterVencedor() == RESULTADO_INVALIDO);
    assert(EscolherCarta(0) == JOGADA_INVALIDA);
    puts("[OK] Jogada antes de iniciar: recusada");
    for (int i = 0; i <= 8; i++) partida(i);
    Embaralhar();
    assert(ObterPontos(1) == 0 && ObterPontos(2) == 0);
    assert(ObterTotalTentativas() == 0);
    assert(PartidaEncerrada() == 0 && ObterJogadorAtual() == 1);
    Placar invalido = *ConsultarPlacar();
    invalido.paresEncontrados = 1;
    assert(rf05_apurar_placar(ConsultarJogo(), &invalido) == RESULTADO_INVALIDO);
    assert(apurarVencedor(-1, 0) == RESULTADO_INVALIDO);
    assert(apurarVencedor(5, 4) == RESULTADO_INVALIDO);
    puts("[OK] Inicializacao, pares, turnos, pontos e tentativas reais");
    puts("[OK] Carta repetida e par encontrado nao duplicam pontos");
    puts("[OK] Bloqueio apos encerramento e reinicio com dados zerados");
    puts("RF01 + RF02 + RF03 + RF04 + RF05: todos os testes passaram.");
    return 0;
}
