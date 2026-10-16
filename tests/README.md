# Testes de integração

Os testes verificam a integração dos cinco requisitos funcionais:

- RF01: inicialização e embaralhamento do tabuleiro.
- RF02: processamento das jogadas e validação dos pares.
- RF03: controle dos turnos dos dois jogadores.
- RF04: cálculo da pontuação e contagem de tentativas.
- RF05: encerramento da partida e identificação do vencedor ou empate.

Também são verificadas jogadas inválidas, reinicialização da
partida e bloqueio de novas jogadas após o encerramento.

## Como executar

Com o ambiente do Emscripten ativado, execute na pasta do projeto:

    testar.bat

Depois, inicie um servidor HTTP local:

    python -m http.server 8000

Abra no navegador:

http://localhost:8000/tests/teste_integracao.html

## Resultado verificado

A execução no navegador apresentou a mensagem:

“RF01 + RF02 + RF03 + RF04 + RF05: todos os testes passaram.”

Esses testes validam a lógica em C compilada para WebAssembly.
A integração completa da interface visual é uma etapa separada.
