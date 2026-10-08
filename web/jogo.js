function criarTabuleiro() {
    Module.ccall("Embaralhar", null, [], []);
    const tabuleiro = document.getElementById("tabuleiro");
    tabuleiro.innerHTML = "";

    for (let i = 0; i < 16; i++) {
        const carta = document.createElement("div");
        carta.className = "carta";
        const nome = Module.ccall("ReturnCart", "string", ["number"], [i]);
        carta.dataset.nome = nome;
        carta.textContent = "?";
        carta.addEventListener("click", () => {
            carta.textContent = carta.dataset.nome;
        });
        tabuleiro.appendChild(carta);
    }
}

var Module = {
    onRuntimeInitialized: () => {
        criarTabuleiro();        
    }
};

const embaralhar = document.getElementById("btnEmbaralhar");
embaralhar.addEventListener("click", () => {
    criarTabuleiro();
});