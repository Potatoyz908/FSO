// timed-mini-shell.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <errno.h>
#include <string.h>

static long long diff_tenths(const struct timeval *a, const struct timeval *b) {
    // diferença b-a em décimos de segundo, com arredondamento para 1 casa
    long long du = (long long)(b->tv_sec - a->tv_sec) * 1000000LL
                 + (long long)(b->tv_usec - a->tv_usec);
    if (du < 0) du = 0;
    // 0.1s = 100000 us; +50000 para arredondar para o mais próximo
    return (du + 50000LL) / 100000LL;
}

int main(void) {
    char path[256+1], arg[256+1];
    long long total_tenths = 0;

    while (scanf("%255s %255s", path, arg) == 2) {
        struct timeval t0, t1;
        gettimeofday(&t0, NULL);

        pid_t pid = fork();
        if (pid < 0) {
            // falha no fork (raro): considere como erro imediato
            fprintf(stdout, "> Erro: %s\n", strerror(errno));
            gettimeofday(&t1, NULL);
            long long tenths = diff_tenths(&t0, &t1);
            total_tenths += tenths;
            // Sem child para esperar, retorne não-zero simbólico (2)
            fprintf(stdout, "> Demorou %lld.%lld segundos, retornou %d\n",
                    tenths/10, tenths%10, 2);
            fflush(stdout);
            continue;
        }

        if (pid == 0) {
            // filho: tenta executar; em caso de erro, imprime e sai com 2
            // arg0 convencionalmente é o próprio caminho/programa
            execl(path, path, arg, (char*)NULL);

            // só chega aqui se execl falhou
            fprintf(stdout, "> Erro: %s\n", strerror(errno));
            fflush(stdout);
            _exit(2); // exemplo mostra retorno 2 para erro de exec
        }

        // pai: espera término e mede tempo
        int status = 0, rc = 0;
        if (waitpid(pid, &status, 0) < 0) {
            // erro ao esperar; trate como retorno 2
            rc = 2;
        } else {
            if (WIFEXITED(status)) {
                rc = WEXITSTATUS(status);
            } else if (WIFSIGNALED(status)) {
                // convensão comum: 128+signal
                rc = 128 + WTERMSIG(status);
            } else {
                rc = 0;
            }
        }

        gettimeofday(&t1, NULL);
        long long tenths = diff_tenths(&t0, &t1);
        total_tenths += tenths;

        fprintf(stdout, "> Demorou %lld.%lld segundos, retornou %d\n",
                tenths/10, tenths%10, rc);
        fflush(stdout);
    }

    // resumo final
    fprintf(stdout, ">> O tempo total foi de %lld.%lld segundos\n",
            total_tenths/10, total_tenths%10);
    fflush(stdout);
    return 0;
}
