@echo off
setlocal
cd /d "%~dp0"

if not exist docs mkdir docs

call emcc src/projetocertificador.c src/rf02.c src/turnos.c src/pontuacao.c src/resultado.c --no-entry -O2 -sEXPORTED_RUNTIME_METHODS=ccall --shell-file web/shell.html -o docs/projetoweb.html

if errorlevel 1 exit /b 1

move /Y docs\projetoweb.html docs\index.html >nul
if errorlevel 1 exit /b 1

copy /Y web\jogo.js docs\jogo.js >nul
if errorlevel 1 exit /b 1

type nul > docs\.nojekyll

echo Compilacao concluida!
