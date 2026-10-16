#ifndef PONTUACAO_H
#define PONTUACAO_H

typedef struct {
    int pontos;
    int tentativas;
} Jogador;

typedef struct {
    Jogador jogadores[2];
    int totalTentativas;
    int paresEncontrados;
} Placar;

void rf04_inicializar(Placar *placar);
int rf04_registrar(Placar *placar, int jogador, int resultado);
void IniciarPontuacao(void);
int RegistrarTentativa(int jogador, int resultado);
int ObterPontos(int jogador);
int ObterTentativas(int jogador);
int ObterTotalTentativas(void);
int ObterParesEncontrados(void);
const Placar *ConsultarPlacar(void);

#endif
