#include <stdio.h>
#include <limits.h>
#define MAX 100

typedef struct {
    int pid;
    long long tempo_restante;
    long long turnaround;
} Processo;

int main() {
    int N;
    long long T;
    Processo processos[MAX];
    int fila[MAX];
    Processo ordem[MAX];
    int ini = 0, fim = 0, tam = 0, concluidos = 0;
    long long tempo_global = 0;

    if (scanf("%d", &N) != 1) return 0;
    if (scanf("%lld", &T) != 1) return 0;

    for (int i = 0; i < N; i++) {
    int pid, t;
    if (scanf("%d %d", &pid, &t) != 2) return 0;
    processos[i].pid = pid;
    processos[i].tempo_restante = (long long)t * 1000LL;
        processos[i].turnaround = 0;
        fila[fim] = i;
        fim = (fim + 1) % MAX;
        tam++;
    }

    while (concluidos < N) {
        if (tam == 0) break;

        int can_optimize = 1;
        long long min_rodadas = LLONG_MAX;
        for (int j = 0; j < tam; j++) {
            int idxj = fila[(ini + j) % MAX];
            if (processos[idxj].tempo_restante <= T) {
                can_optimize = 0;
                break;
            }
            min_rodadas = (processos[idxj].tempo_restante - 1) / T < min_rodadas ? (processos[idxj].tempo_restante - 1) / T : min_rodadas;
        }

        if (can_optimize && min_rodadas > 0) {
            tempo_global += min_rodadas * T * tam;
            for (int j = 0; j < tam; j++) {
                int idxj = fila[(ini + j) % MAX];
                processos[idxj].tempo_restante -= min_rodadas * T;
            }
        } else {
            int idx = fila[ini];
            ini = (ini + 1) % MAX;
            tam--;

            if (tam == 0) {
                long long exec = processos[idx].tempo_restante;
                tempo_global += exec;
                processos[idx].tempo_restante = 0;
                processos[idx].turnaround = tempo_global;
                ordem[concluidos++] = processos[idx];
            } else {
                long long exec = (processos[idx].tempo_restante < T) ? processos[idx].tempo_restante : T;
                processos[idx].tempo_restante -= exec;
                tempo_global += exec;

                if (processos[idx].tempo_restante == 0) {
                    processos[idx].turnaround = tempo_global;
                    ordem[concluidos++] = processos[idx];
                } else {
                    fila[fim] = idx;
                    fim = (fim + 1) % MAX;
                    tam++;
                }
            }
        }
    }

    for (int i = 0; i < concluidos; i++) {
        printf("%d (%lld)\n", ordem[i].pid, ordem[i].turnaround);
    }
    return 0;
}