@echo off
setlocal
cd /d "%~dp0"

call emcc src/projetocertificador.c src/rf02.c src/turnos.c src/pontuacao.c src/resultado.c tests/teste_integracao.c -Wall -Wextra -o tests/teste_integracao.html

if errorlevel 1 exit /b 1

echo Teste compilado.
echo Execute: python -m http.server 8000
echo Abra: http://localhost:8000/tests/teste_integracao.html
