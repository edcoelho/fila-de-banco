#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "escalonador.h"
int main(int narg, char *argv[]) {
    Escalonador *escalonador;
    char arq_saida[16] = "saida-", arq_entrada[18], *buf;

    escalonador = (Escalonador *) malloc(sizeof(Escalonador));

    if (argv[1] != NULL) {
        strcpy(arq_entrada, argv[1]);
        buf = strtok(arq_entrada, "-");
        buf = strtok(NULL, "-");
        strcat(arq_saida, buf);
        e_rodar(escalonador, argv[1], arq_saida);
    } else {
        printf("Nenhum arquivo entrado!\nSintaxe: ./main [ARQUIVO]\n");
        EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}