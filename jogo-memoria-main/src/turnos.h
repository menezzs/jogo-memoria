#ifndef TURNOS_H
#define TURNOS_H

typedef struct {
    int jogadorAtual;
    int ultimoJogador;
} ControleTurnos;

void rf03_inicializar(ControleTurnos *turnos);
int rf03_obter_jogador(const ControleTurnos *turnos);
int rf03_obter_ultimo_jogador(const ControleTurnos *turnos);
int rf03_processar_resultado(ControleTurnos *turnos, int resultado);

void IniciarTurnos(void);
int ObterJogadorAtual(void);
int ObterJogadorDaUltimaJogada(void);
int ProcessarResultadoJogada(int resultado);

#endif
