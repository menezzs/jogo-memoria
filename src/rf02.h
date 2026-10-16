#ifndef RF02_H
#define RF02_H

#define RF02_TOTAL_CARTAS 16
#define RF02_LADO_TABULEIRO 4

typedef enum {
    CARTA_OCULTA = 0,
    CARTA_VISIVEL = 1,
    CARTA_ENCONTRADA = 2
} EstadoCarta;

typedef enum {
    JOGADA_INVALIDA = -1,
    PRIMEIRA_CARTA = 0,
    PAR_ENCONTRADO = 1,
    PAR_DIFERENTE = 2,
    AGUARDANDO_LIBERACAO = 3
} ResultadoJogada;

typedef struct {
    const char *simbolo;
    EstadoCarta estado;
} Carta;

typedef struct {
    Carta cartas[RF02_TOTAL_CARTAS];
} Tabuleiro;

typedef struct {
    int primeira;
    int segunda;
    int aguardando;
} Jogada;

typedef struct {
    Tabuleiro tabuleiro;
    Jogada jogada;
} JogoMemoria;

int rf02_inicializar(JogoMemoria *jogo, const char *const simbolos[]);
ResultadoJogada rf02_escolher_carta(JogoMemoria *jogo, int posicao);
ResultadoJogada rf02_jogar_par(JogoMemoria *jogo, int linha1, int coluna1,
                             int linha2, int coluna2);
int rf02_ocultar_erro(JogoMemoria *jogo);

#endif
