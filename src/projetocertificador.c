#include <stdlib.h>
#include <time.h>
#include "jogo_api.h"
#include "turnos.h"
#include "pontuacao.h"
#include "resultado.h"
#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#else
#define EMSCRIPTEN_KEEPALIVE
#endif

static JogoMemoria jogo;
static int iniciada;
static int sementeDefinida;
static const char *const originais[RF02_TOTAL_CARTAS] = {
    "Ana", "Carlos", "Beatriz", "Jair", "Marcio", "Odete", "Claudia", "Mauricio",
    "Ana", "Carlos", "Beatriz", "Jair", "Marcio", "Odete", "Claudia", "Mauricio"
};

EMSCRIPTEN_KEEPALIVE
void Embaralhar(void)
{
    const char *simbolos[RF02_TOTAL_CARTAS];
    if (!sementeDefinida) {
        srand((unsigned)time(NULL));
        sementeDefinida = 1;
    }
    for (int i = 0; i < RF02_TOTAL_CARTAS; i++) simbolos[i] = originais[i];
    for (int i = RF02_TOTAL_CARTAS - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        const char *aux = simbolos[i];
        simbolos[i] = simbolos[j];
        simbolos[j] = aux;
    }
    iniciada = rf02_inicializar(&jogo, simbolos);
    IniciarTurnos();
    IniciarPontuacao();
}

const JogoMemoria *ConsultarJogo(void)
{
    return iniciada ? &jogo : NULL;
}

EMSCRIPTEN_KEEPALIVE
const char *ReturnCart(int posicao)
{
    return iniciada && posicao >= 0 && posicao < RF02_TOTAL_CARTAS ?
        jogo.tabuleiro.cartas[posicao].simbolo : "";
}

EMSCRIPTEN_KEEPALIVE
int EstadoDaCarta(int posicao)
{
    return iniciada && posicao >= 0 && posicao < RF02_TOTAL_CARTAS ?
        (int)jogo.tabuleiro.cartas[posicao].estado : -1;
}

/* O resultado da segunda carta atualiza RF03 e RF04 exatamente uma vez.
   O ultimo jogador identifica o autor mesmo quando o erro ja passou a vez. */
static int registrar_resultado(ResultadoJogada resultado)
{
    ProcessarResultadoJogada(resultado);
    if (resultado == PAR_ENCONTRADO || resultado == PAR_DIFERENTE) {
        RegistrarTentativa(ObterJogadorDaUltimaJogada(), resultado);
    }
    return resultado;
}

static int pode_jogar(void)
{
    if (!iniciada || rf05_verificar_fim(&jogo) != 0) return 0;
    return rf05_apurar_placar(&jogo, ConsultarPlacar()) == PARTIDA_EM_ANDAMENTO;
}

EMSCRIPTEN_KEEPALIVE
int EscolherCarta(int posicao)
{
    if (!pode_jogar()) return JOGADA_INVALIDA;
    return registrar_resultado(rf02_escolher_carta(&jogo, posicao));
}

EMSCRIPTEN_KEEPALIVE
int RealizarJogada(int linha1, int coluna1, int linha2, int coluna2)
{
    if (!pode_jogar()) return JOGADA_INVALIDA;
    return registrar_resultado(rf02_jogar_par(&jogo, linha1, coluna1, linha2, coluna2));
}

EMSCRIPTEN_KEEPALIVE
int OcultarErro(void)
{
    return iniciada ? rf02_ocultar_erro(&jogo) : 0;
}
/* main fica somente em console.c ou no arquivo de testes.
   Para web, compilar com --no-entry e sem console.c. */
