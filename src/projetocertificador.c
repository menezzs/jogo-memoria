#include <emscripten.h>
#include <stdio.h> 
#include <stdlib.h>
#include <time.h>

char *cartas[16] = {
    "Ana", "Carlos", "Beatriz", "Jair",
    "Marcio", "Odete", "Claudia", "Mauricio",
    "Ana", "Carlos", "Beatriz", "Jair",
    "Marcio", "Odete", "Claudia", "Mauricio"
};

EMSCRIPTEN_KEEPALIVE
void Embaralhar (){
    srand(time(NULL));
    int j = 0;
    char* guard;

    for(int i = 15; i>0; i--){
        j = rand() % (i+1);
        guard = cartas[i];
        cartas[i] = cartas[j];
        cartas[j] = guard;        
    }
}


EMSCRIPTEN_KEEPALIVE
char* ReturnCart (int posicao) {
    return cartas[posicao];
}

int main(){
}