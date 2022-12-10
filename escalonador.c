#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "escalonador.h"
#include "logtree.h"

void e_inicializar(Escalonador *e, int caixas, int delta_t, int n_1, int n_2, int n_3, int n_4, int n_5) {
    int i;

    e->delta_t = delta_t;
    e->quant_caixas = caixas;
    for (i = 0; i < 10; i++)
        e->timers_caixas[i] = 0;
    e->relogio = 0;

    e->disciplinas_fila[0] = n_1;
    e->disciplinas_fila[1] = n_2;
    e->disciplinas_fila[2] = n_3;
    e->disciplinas_fila[3] = n_4;
    e->disciplinas_fila[4] = n_5;
    e->fila_atual = 1;
    for (i = 0; i < 5; i++)
        f_inicializar(&e->filas[i]);
    e->cont_atendimento = 0;

    log_inicializar(&e->registrador);
}

int e_inserir_por_fila(Escalonador *e, int classe, int num_conta, int qtde_operacoes) {
    return f_inserir(&e->filas[classe - 1], num_conta, qtde_operacoes);
}

int e_obter_prox_num_conta(Escalonador *e) {
    if (e_consultar_prox_fila(e) == -1)
        return -1;

    e->cont_atendimento++;
    return f_obter_proxima_chave(&e->filas[e->fila_atual - 1]);
}

int e_consultar_prox_num_conta(Escalonador *e) {
    int num_conta;

    if (e_consultar_prox_fila(e) == -1)
        return -1;

    num_conta = f_consultar_proxima_chave(&e->filas[e->fila_atual - 1]);
    return num_conta;
}

int e_consultar_prox_qtde_oper(Escalonador *e) {
    int num_operacoes;

    if (e_consultar_prox_fila(e) == -1)
        return -1;

    num_operacoes = f_consultar_proximo_valor(&e->filas[e->fila_atual - 1]);
    return num_operacoes;
}

int e_consultar_prox_fila(Escalonador *e) {
    if (!f_num_elementos(&e->filas[0]) && !f_num_elementos(&e->filas[1]) && !f_num_elementos(&e->filas[2]) && !f_num_elementos(&e->filas[3]) && !f_num_elementos(&e->filas[4]))
        return -1;

    if (e->fila_atual > 5)
        e->fila_atual = 1;

    if ((f_num_elementos(&e->filas[e->fila_atual - 1]) == 0) || (e->cont_atendimento >= e->disciplinas_fila[e->fila_atual - 1])) {
        e->fila_atual++;
        e->cont_atendimento = 0;
        return e_consultar_prox_fila(e);
    }

    return e->fila_atual;
}

int e_consultar_qtde_clientes(Escalonador *e) {
    int i, soma;
    soma = 0;

    for (i = 0; i < 5; i++)
        soma = soma + f_num_elementos(&e->filas[i]);

    return soma;
}

int e_consultar_tempo_prox_cliente(Escalonador *e) {
    int quant_oper;
    quant_oper = e_consultar_prox_qtde_oper(e);

    if (quant_oper != -1)
        return quant_oper * e->delta_t;
    else
        return -1;
}

int e_conf_por_arquivo(Escalonador *e, char *nome_arq_conf) {
    int caixas, delta_t, n[5], i, classe, num_conta, num_oper;
    char linha[256], *buf;
    FILE *arq;

    arq = fopen(nome_arq_conf, "rt");
    if (arq == NULL)
        return 0;

    // Leitura da quantidade de caixas
    fgets(linha, 255, arq);
    buf = strtok(linha, "=\n");
    buf = strtok(NULL, "=\n");
    caixas = atoi(buf);

    // Leitura do delta t
    fgets(linha, 255, arq);
    buf = strtok(linha, "=\n");
    buf = strtok(NULL, "=\n");
    delta_t = atoi(buf);

    // Leitura das disciplinas de atendimento
    fgets(linha, 255, arq);
    buf = strtok(linha, "=,{\n");
    buf = strtok(NULL, "=,{\n");
    i = 0;
    while(buf && i < 5) {
        buf = strtok(NULL, "=,{\n");
        n[i] = atoi(buf);
        i++;
    }

    e_inicializar(e, caixas, delta_t, n[0], n[1], n[2], n[3], n[4]);

    // Leitura dos clientes
    while (fgets(linha, 255, arq) != NULL) {
        // Token da classe da conta
        buf = strtok(linha, "- \n");
        if (strcmp(buf, "Premium") == 0)
            classe = 1;
        else if(strcmp(buf, "Ouro") == 0)
            classe = 2;
        else if(strcmp(buf, "Prata") == 0)
            classe = 3;
        else if(strcmp(buf, "Bronze") == 0)
            classe = 4;
        else if(strcmp(buf, "Leezu") == 0)
            classe = 5;

        // Pula o 2º token
        buf = strtok(NULL, "- \n");

        // Token do número da conta
        buf = strtok(NULL, "- \n");
        num_conta = atoi(buf);

        // Token do número de operações
        buf = strtok(NULL, "- \n");
        num_oper = atoi(buf);

        e_inserir_por_fila(e, classe, num_conta, num_oper);
    }

    fclose(arq);

    return 1;
}

void e_rodar(Escalonador *e, char *nome_arq_in, char *nome_arq_out) {
    char linha[256], *buf;
    int i, tempo_sobrando, classe, num_conta, num_oper, cont_clientes_caixa[10];
    float media_operacoes;
    FILE *arq;

    if (!e_conf_por_arquivo(e, nome_arq_in))
        printf("Erro ao ler o arquivo de configuração!\n");

// ----- ESCRITA DO ARQUIVO DE SAÍDA -----

    arq = fopen(nome_arq_out, "wt");
    
    while (e_consultar_qtde_clientes(e) > 0) {
        for (i = 0; i < e->quant_caixas; i++) {
            if (e_consultar_prox_num_conta(e) != -1) {
                if (e->timers_caixas[i] == 0) {
                    classe = e_consultar_prox_fila(e);
                    num_oper = e_consultar_prox_qtde_oper(e);
                    num_conta = e_obter_prox_num_conta(e);
                    cont_clientes_caixa[i]++;
                    
                    fprintf(arq, "T = %d min: Caixa %i chama da categoria %s cliente da conta %d para realizar %d operacao(oes).\n", e->relogio, i+1, classe == 1 ? "Premium" : classe == 2 ? "Ouro" : classe == 3 ? "Prata" : classe == 4 ? "Bronze" : "Leezu", num_conta, num_oper);

                    e->timers_caixas[i] = num_oper * e->delta_t;
                    log_registrar(&e->registrador, num_conta, classe, e->timers_caixas[i], i+1);
                }
            }
        }
        
        e->relogio++;
        for (i = 0; i < e->quant_caixas; i++)
            e->timers_caixas[i]--;
    }

    tempo_sobrando = 0;
    for (i = 0; i < e->quant_caixas; i++)
        if (e->timers_caixas[i] > tempo_sobrando)
            tempo_sobrando = e->timers_caixas[i];
    e->relogio += tempo_sobrando;

    fprintf(arq, "Tempo total de atendimento: %d\n", e->relogio);
    for (i = 0; i < 5; i++) {
        fprintf(arq, "Tempo medio de espera dos %d clientes %s: %.2f\n", log_obter_contagem_por_classe(&e->registrador, i+1), i+1 == 1 ? "Premium" : i+1 == 2 ? "Ouro" : i+1 == 3 ? "Prata" : i+1 == 4 ? "Bronze" : "Leezu", log_media_por_classe(&e->registrador, i+1));

        media_operacoes = (log_obter_soma_por_classe(&e->registrador, i+1) / e->delta_t) / log_obter_contagem_por_classe(&e->registrador, i+1);

        fprintf(arq, "Quantidade media de operacoes por cliente %s = %.2f\n", i+1 == 1 ? "Premium" : i+1 == 2 ? "Ouro" : i+1 == 3 ? "Prata" : i+1 == 4 ? "Bronze" : "Leezu", media_operacoes);
    }
    for (i = 0; i < e->quant_caixas; i++)
        fprintf(arq, "O caixa de número %d atendeu %d clientes.\n", i+1, cont_clientes_caixa[i]);

    fclose(arq);
}