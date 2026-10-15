#include <assert.h>
#include <stdio.h>
#include "../src/resultado.h"

int main(void)
{
    /* Partida incompleta. */
    assert(verificarFimJogo(2, 3) == 0);
    assert(apurarVencedor(2, 3) == PARTIDA_EM_ANDAMENTO);

    /* Jogador 1 vence. */
    assert(verificarFimJogo(5, 3) == 1);
    assert(apurarVencedor(5, 3) == VITORIA_JOGADOR_1);

    /* Jogador 2 vence. */
    assert(apurarVencedor(3, 5) == VITORIA_JOGADOR_2);

    /* Empate. */
    assert(apurarVencedor(4, 4) == RESULTADO_EMPATE);

    /* Nenhum par encontrado. */
    assert(verificarFimJogo(0, 0) == 0);

    /* Todos os pares encontrados pelo mesmo jogador. */
    assert(apurarVencedor(8, 0) == VITORIA_JOGADOR_1);
    assert(apurarVencedor(0, 8) == VITORIA_JOGADOR_2);

    /* Dados invalidos. */
    assert(verificarFimJogo(-1, 2) == -1);
    assert(apurarVencedor(-1, 2) == RESULTADO_INVALIDO);
    assert(apurarVencedor(5, 4) == RESULTADO_INVALIDO);
    assert(apurarVencedor(9, 0) == RESULTADO_INVALIDO);

    puts("Todos os testes de resultado passaram!");
    return 0;
}
