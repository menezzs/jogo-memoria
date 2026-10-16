#ifndef JOGO_API_H
#define JOGO_API_H
#include "rf02.h"
void Embaralhar(void);
const char *ReturnCart(int posicao);
int EstadoDaCarta(int posicao);
int EscolherCarta(int posicao);
int RealizarJogada(int linha1, int coluna1, int linha2, int coluna2);
int OcultarErro(void);
const JogoMemoria *ConsultarJogo(void);
#endif
