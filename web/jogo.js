(() => {
  "use strict";

  const TOTAL_CARTAS = 16;
  const TEMPO_ERRO = 1200;
  let aguardandoErro = false;
  let temporizadorErro = null;
  let jogoPronto = false;

  const $ = (id) => document.getElementById(id);
  const chamar = (nome, tipo = "number", tipos = [], valores = []) =>
    Module.ccall(nome, tipo, tipos, valores);

  function texto(id, valor) {
    const elemento = $(id);
    if (elemento) elemento.textContent = valor;
  }

  function atualizarPlacar() {
    const jogadorAtual = chamar("ObterJogadorAtual");
    const pares = chamar("ObterParesEncontrados");
    const total = chamar("ObterTotalTentativas");

    texto("vez-jogador", `Vez do Jogador ${jogadorAtual}`);
    texto("pontos-j1", chamar("ObterPontos", "number", ["number"], [1]));
    texto("pontos-j2", chamar("ObterPontos", "number", ["number"], [2]));
    texto("tentativas-j1", chamar("ObterTentativas", "number", ["number"], [1]));
    texto("tentativas-j2", chamar("ObterTentativas", "number", ["number"], [2]));
    texto("pares-encontrados", `${pares} de 8`);
    texto("tentativas-total", total);

    $("jogador-1").classList.toggle("ativo", jogadorAtual === 1 && !chamar("PartidaEncerrada"));
    $("jogador-2").classList.toggle("ativo", jogadorAtual === 2 && !chamar("PartidaEncerrada"));
  }

  function criarCarta(posicao) {
    const carta = document.createElement("button");
    carta.type = "button";
    carta.className = "carta";
    carta.dataset.posicao = posicao;
    carta.setAttribute("aria-label", `Carta ${posicao + 1}, fechada`);
    carta.innerHTML = '<span class="verso" aria-hidden="true">?</span>';
    carta.addEventListener("click", () => selecionarCarta(posicao));
    return carta;
  }

  function desenharTabuleiro() {
    const tabuleiro = $("tabuleiro");
    tabuleiro.replaceChildren();
    for (let i = 0; i < TOTAL_CARTAS; i++) tabuleiro.appendChild(criarCarta(i));
  }

  function sincronizarCartas() {
    for (let i = 0; i < TOTAL_CARTAS; i++) {
      const estado = chamar("EstadoDaCarta", "number", ["number"], [i]);
      const nome = chamar("ReturnCart", "string", ["number"], [i]);
      const carta = $("tabuleiro").querySelector(`[data-posicao="${i}"]`);
      if (!carta) continue;

      carta.classList.remove("virada", "encontrada");
      carta.disabled = false;
      if (estado === 0) {
        carta.innerHTML = '<span class="verso" aria-hidden="true">?</span>';
        carta.setAttribute("aria-label", `Carta ${i + 1}, fechada`);
      } else {
        carta.textContent = nome;
        carta.classList.add("virada");
        carta.setAttribute("aria-label", `Carta ${i + 1}: ${nome}`);
        if (estado === 2) {
          carta.classList.add("encontrada");
          carta.disabled = true;
        }
      }
    }
  }

  function mostrarMensagem(mensagem, tipo = "") {
    const area = $("mensagem");
    area.textContent = mensagem;
    area.className = `mensagem ${tipo}`.trim();
  }

  function finalizarPartida() {
    const resultado = chamar("ObterVencedor");
    let mensagem;
    if (resultado === 0) {
      mensagem = "Empate! Os dois jogadores terminaram com a mesma pontuação.";
    } else if (resultado === 1 || resultado === 2) {
      mensagem = `Jogador ${resultado} venceu a partida!`;
    } else {
      mensagem = "A partida foi encerrada.";
    }
    texto("resultado-titulo", resultado === 0 ? "Deu empate!" : `Jogador ${resultado} venceu!`);
    texto("resultado-detalhe",
      `Placar final: ${chamar("ObterPontos", "number", ["number"], [1])} a ${chamar("ObterPontos", "number", ["number"], [2])}.`);
    $("modal-resultado").hidden = false;
    $("btn-novo-jogo-modal").focus();
    mostrarMensagem(mensagem, "sucesso");
    atualizarPlacar();
    bloquearTabuleiro(true);
  }

  function bloquearTabuleiro(bloquear) {
    $("tabuleiro").querySelectorAll(".carta").forEach((carta) => {
      if (bloquear || carta.classList.contains("encontrada")) carta.disabled = true;
    });
  }

  function selecionarCarta(posicao) {
    if (!jogoPronto || aguardandoErro || chamar("PartidaEncerrada")) return;

    const carta = $("tabuleiro").querySelector(`[data-posicao="${posicao}"]`);
    if (!carta || carta.disabled || carta.classList.contains("virada")) return;

    const resultado = chamar("EscolherCarta", "number", ["number"], [posicao]);

    if (resultado === -1 || resultado === 3) return;

    sincronizarCartas();
    atualizarPlacar();

    if (resultado === 0) {
      mostrarMensagem("Agora escolha a segunda carta.");
    } else if (resultado === 1) {
      mostrarMensagem("Par encontrado! Você marcou um ponto.", "sucesso");
      atualizarPlacar();
      if (chamar("PartidaEncerrada")) finalizarPartida();
    } else if (resultado === 2) {
      aguardandoErro = true;
      mostrarMensagem("Não formou um par. As cartas serão viradas novamente.", "aviso");
      bloquearTabuleiro(true);
      temporizadorErro = window.setTimeout(() => {
        chamar("OcultarErro");
        aguardandoErro = false;
        temporizadorErro = null;
        sincronizarCartas();
        atualizarPlacar();
        mostrarMensagem(`Vez do Jogador ${chamar("ObterJogadorAtual")}. Tente encontrar um par.`);
        bloquearTabuleiro(false);
      }, TEMPO_ERRO);
    }
  }

  function novoJogo() {
    if (!jogoPronto) return;
    if (temporizadorErro !== null) {
      window.clearTimeout(temporizadorErro);
      temporizadorErro = null;
    }
    aguardandoErro = false;
    chamar("Embaralhar", "void");
    $("modal-resultado").hidden = true;
    desenharTabuleiro();
    atualizarPlacar();
    mostrarMensagem("Jogo iniciado! Jogador 1 começa. Escolha uma carta.");
    bloquearTabuleiro(false);
  }

  function iniciarInterface() {
    jogoPronto = true;
    $("btn-novo-jogo").addEventListener("click", novoJogo);
    $("btn-novo-jogo-modal").addEventListener("click", novoJogo);
    $("btn-fechar-modal").addEventListener("click", () => {
      $("modal-resultado").hidden = true;
      $("btn-novo-jogo").focus();
    });
    novoJogo();
    $("status-carregamento").hidden = true;
    $("area-jogo").hidden = false;
  }

  window.addEventListener("load", () => {
    $("btn-novo-jogo").disabled = true;
  });

  var Module = {
    onRuntimeInitialized: iniciarInterface,
    onAbort: (motivo) => {
      mostrarMensagem(`Não foi possível carregar o jogo: ${motivo}`, "erro");
    }
  };
  window.Module = Module;
})();