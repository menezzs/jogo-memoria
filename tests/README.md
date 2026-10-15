# Testes do jogo

## Teste inicial realizado

A versão compilada foi executada localmente no navegador.

Foi verificado:
- Exibição das 16 cartas.
- Revelação do nome ao clicar.
- Funcionamento do botão Embaralhar.

## Testes de integração planejados

- Confirmar que um par correto é registrado.
- Confirmar a atualização de pontos e tentativas.
- Verificar o encerramento após encontrar os 8 pares.
- Conferir o resultado final.
- Impedir novas jogadas após o encerramento.
- Verificar se reiniciar limpa os dados da partida.

Esses testes serão implementados após a integração
dos módulos do grupo.

## Testes do módulo de resultado — 15/10/2026

Os testes isolados de resultado.c foram executados com
Emscripten no navegador e passaram.

Cenários verificados:
- Partida em andamento.
- Vitória do jogador 1.
- Vitória do jogador 2.
- Empate.
- Nenhum par encontrado.
- Todos os pares encontrados pelo mesmo jogador.
- Dados inválidos.

Resultado: todas as verificações executadas passaram.

Os testes de integração com os demais módulos permanecem pendentes.

## Integração RF02, RF03 e RF05 — 15/10/2026

Teste compilado com Emscripten e executado no navegador.

Resultado: todas as verificações executadas passaram.

Foram verificados:
- Validação de cartas e pares.
- Manutenção da vez no acerto e troca no erro.
- Encerramento após os 8 pares.
- Vitória dos dois jogadores e empate.
- Bloqueio de seleções após o encerramento.
- Reinicialização da partida.

O RF04 ainda não participou do teste.
Os totais de pares foram atualizados pelo código de teste.
A interface do jogo ainda precisa ser conectada aos módulos.
