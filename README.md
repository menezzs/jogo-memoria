# Jogo da Memória — TEDI

Projeto desenvolvido na disciplina Certificadora de Competência I
do curso de Engenharia de Computação da UTFPR — Cornélio Procópio.

## Contexto

O TEDI — Tecnologia e Educação Digital para a Terceira Idade —
promove a inclusão e a alfabetização digital da comunidade idosa
por meio de oficinas e atividades práticas.

## Objetivo do sistema

Desenvolver um jogo da memória para apoiar a Oficina de Jogos
Digitais do TEDI.

A proposta é oferecer uma atividade simples e acessível para
que os participantes pratiquem a interação com interfaces
digitais e ganhem confiança no uso da tecnologia.

## Funcionamento previsto

- Partida com 2 jogadores, alternando as jogadas no mesmo tabuleiro.
- Tabuleiro com 16 cartas formando 8 pares.
- Seleção de cartas e identificação de pares.
- Registro de pontuação e tentativas de cada jogador.
- Encerramento quando todos os pares forem encontrados.
- Vence quem encontrar mais pares. Se os dois encontrarem a mesma quantidade, a partida termina empatada.
- Execução diretamente no navegador.

## Desenvolvimento em grupo

Além da implementação técnica, o projeto envolve planejamento,
divisão de tarefas, comunicação e resolução de problemas
entre os integrantes.

## Regras da partida

- Participam dois jogadores.
- O tabuleiro contém 16 cartas, formando oito pares.
- Cada par encontrado vale um ponto.
- Ao acertar, o jogador mantém a vez.
- Ao errar, a vez passa para o outro jogador.
- A partida termina quando os oito pares são encontrados.
- Vence quem tiver mais pontos. O resultado 4 a 4 representa empate.

## Estado atual

Os cinco requisitos funcionais estão implementados em C e
passaram nos testes de integração executados no navegador
com WebAssembly.

A interface visual é um protótipo. Sua integração completa
com jogadas, turnos, pontuação e resultado ainda está pendente.

## Ferramentas necessárias

- Emscripten: compilação do código C para WebAssembly.
- Python 3: disponibilização dos arquivos por HTTP local.
- Navegador atualizado.

O servidor HTTP local serve os arquivos para o navegador.
A lógica do jogo é executada no próprio navegador.

## Compilar o projeto

Com o ambiente do Emscripten ativado, execute na raiz do projeto:

    build.bat

Os arquivos da versão web são gerados na pasta docs.

Para abrir o protótipo localmente, execute:

    python -m http.server 8000

Acesse:

http://localhost:8000/docs/

## Executar os testes

Com o ambiente do Emscripten ativado, execute:

    testar.bat

Com o servidor HTTP local em execução, acesse:

http://localhost:8000/tests/teste_integracao.html

O resultado esperado é:

“RF01 + RF02 + RF03 + RF04 + RF05: todos os testes passaram.”

## Documentação

- [Relatório, slides, diagramas e planejamento](documentos/README.md)
- [Testes de integração](tests/README.md)
