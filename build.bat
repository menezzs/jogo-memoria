@echo off
setlocal
cd /d "%~dp0"

if not exist docs mkdir docs

call emcc src/projetocertificador.c -O2 -sEXPORTED_RUNTIME_METHODS=ccall --shell-file web/shell.html -o docs/projetoweb.html

if errorlevel 1 (
    echo Erro na compilacao.
    exit /b 1
)

move /Y docs\projetoweb.html docs\index.html >nul
copy /Y web\jogo.js docs\jogo.js >nul
type nul > docs\.nojekyll

echo Compilacao concluida!