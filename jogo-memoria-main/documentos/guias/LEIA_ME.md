# Parte de Eduardo Shioga

Eduardo Shioga, RA 2565579, integrante 3.

## O que está pronto

- Planejamento e cronograma da seção C, com divisão das tarefas e situações confirmadas ou previstas.
- RF03 em C, integrado ao RF02 de Arthur e ao tabuleiro do projeto.
- Versão web compilada para demonstrar RF01, RF02 e RF03.
- Slide 4 do cronograma em PowerPoint editável, PNG e PDF.
- Guia de funcionamento, integração, execução e fala para a apresentação.

O planejamento já foi colocado na seção C do relatório coletivo:
https://docs.google.com/document/d/1OG4QsGdN56zUUXdb3ZEBB1Rv-IkP9FNglgoW3n0h56c/edit

O slide deve ser inserido na página 4 da apresentação do Canva. A conexão permitiu a leitura do design, mas recusou sua edição. O arquivo PowerPoint contém uma tabela editável e as notas de apresentação. O PNG pode ser usado se a importação do PowerPoint não preservar a formatação.

## Arquivos

| Arquivo ou pasta | Uso |
| --- | --- |
| Planejamento_Eduardo.docx | Versão editável da sua parte escrita |
| Planejamento_Eduardo.pdf | Versão em PDF da sua parte escrita |
| Guia_RF03_Eduardo.pdf | Estudo do código, execução e roteiro de fala |
| Slide_4_Cronograma_Eduardo_v2.pptx | Slide editável para inserir no Canva |
| Slide_4_Cronograma_Eduardo_v2.png | Imagem do slide para inserção direta |
| Slide_4_Cronograma_Eduardo_v2.pdf | Cópia do slide em PDF |
| codigo | Cópia do projeto com RF01, RF02 e RF03 integrados |
| Entrega_Eduardo_RF03.patch | Alterações em relação ao commit 177550696bd75cc88afa7634390f48cd1c2cbd1c do repositório |

## Como executar

Extraia o ZIP, abra o terminal dentro da pasta codigo e execute:

```sh
python -m http.server 8000 --directory docs
```

Abra http://localhost:8000 no navegador. A pasta docs já está compilada. Para gerar novos arquivos web, use Emscripten 6.0.11, ative seu ambiente e execute build.bat no Windows ou sh build.sh no Linux e macOS.

## Como integrar no repositório

Menezes pode copiar os arquivos da pasta codigo para uma cópia atualizada do repositório, comparando alterações dos colegas antes de substituir os arquivos compartilhados. Os detalhes do contrato de pontuação estão em codigo/documentos/RF03_Eduardo.md.

Se estiver exatamente no commit base indicado acima, também pode verificar e aplicar o patch:

```sh
git apply --check /caminho/Entrega_Eduardo_RF03.patch
git apply /caminho/Entrega_Eduardo_RF03.patch
```

O código foi preparado localmente. Nenhum commit foi enviado ao GitHub nesta entrega.

## O que ainda falta no trabalho coletivo

João Vitor Taques deve fornecer o módulo final RF04, que calcula pontos e tentativas. Menezes deve fornecer RF05, ligar o encerramento ao fluxo da partida, consolidar os módulos e publicar a versão final. O evento de tentativa informa separadamente o jogador que realizou a jogada e quem joga em seguida.

O grupo precisa testar uma partida completa, incluindo vitória e empate, e substituir os trechos restantes do modelo de vendas nas demais seções do relatório. A sua seção C já foi adaptada. A versão de codigo deste pacote demonstra RF01, RF02 e RF03 e depende de RF04 e RF05 para completar os cinco requisitos.

Prazo indicado no Moodle: 16/10/2026, às 18h40, com PDF e apresentação presencial.

## Verificação

Passaram os testes nativos de RF02, da ponte C, de RF03 e da integração entre cartas e turnos com AddressSanitizer e UndefinedBehaviorSanitizer. A compilação para WebAssembly passou. O teste JavaScript executa esse WebAssembly real com DOM simulado e verifica vez na tela, autor da tentativa, atraso do erro, reinício e os oito pares. Não houve verificação em um navegador gráfico nesta execução.
