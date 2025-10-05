#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>

volatile int contador = 0;

void handler(int sig) {
    contador++;
}

int main() {
    signal(SIGUSR1, handler);
    signal(SIGUSR2, handler);

    pid_t zumbi_pid = -1;

    while (contador < 3) {
        pause();
        if (contador == 1) {
            // Criar zumbi
            zumbi_pid = fork();
            if (zumbi_pid == 0) {
                // Filho
                exit(0);
            }
            // Pai não chama wait, zumbi criado
        } else if (contador == 2) {
            // Eliminar zumbi
            if (zumbi_pid > 0) {
                waitpid(zumbi_pid, NULL, 0);
            }
        }
    }

    return 0;
}
