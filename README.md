# FSO — Fundamentos de Sistemas Operacionais

Repositório com exercícios e pequenos programas para estudar conceitos de sistemas operacionais.

Conteúdo principal (pasta `MOJ`):

- `escalonadorRoundRobin.c` — Simulador de escalonamento Round Robin (entrada por stdin).
- `TimedShell.c` — Mini-shell que executa comandos, mede tempo de execução e imprime retorno.
- `ProcessoZumbi.c` — Programa que demonstra criação e eliminação controlada de um processo zumbi usando sinais.

Como compilar
--------------

Abra um terminal no diretório raiz do repositório e execute:

```bash
gcc -O2 -o escalonadorRoundRobin MOJ/escalonadorRoundRobin.c
gcc -O2 -o TimedShell MOJ/TimedShell.c
gcc -O2 -o ProcessoZumbi MOJ/ProcessoZumbi.c
```

Como executar
--------------

- `escalonadorRoundRobin` — lê a entrada conforme especificação do problema (stdin). Exemplo:

```bash
./escalonadorRoundRobin < input.txt
```

- `TimedShell` — execute de forma interativa ou com redirecionamento. Cada linha de entrada deve conter dois tokens: o caminho completo do binário e um argumento. Exemplos:

```bash
./TimedShell < comandos.txt
```

ou interativo:

```bash
./TimedShell
/bin/sleep 1
/bin/sleep 1.1
/bin/eunaoexisto 123
<Ctrl+D>
```

- `ProcessoZumbi` — execute em background e envie 3 sinais `SIGUSR1`/`SIGUSR2` para controlar criação/remoção do zumbi:

```bash
./ProcessoZumbi &
kill -USR1 <PID>   # 1º sinal: cria zumbi
kill -USR1 <PID>   # 2º sinal: recolhe o filho (elimina zumbi)
kill -USR1 <PID>   # 3º sinal: termina o programa
```

Testes e exemplos
------------------

Exemplos de entrada/saída esperada para cada programa estão comentados nos enunciados originais dos exercícios (os exemplos usados durante o desenvolvimento estão no histórico do repositório).

Notas e dicas
------------

- Para medições de tempo, os programas usam `gettimeofday()` e imprimem tempos com uma casa decimal.
- Mensagens de erro (quando `execl` falha) são impressas no `stderr` com a mensagem retornada por `strerror(errno)`.
- Os programas foram desenvolvidos para uso educacional e podem assumir um ambiente GNU/Linux com os binários padrões em `/bin`.

Contribuições
-------------

Sinta-se livre para abrir issues ou pull-requests com melhorias, ajustes de estilo, testes adicionais ou correções.

Licença
-------

Use conforme a licença do seu curso/universidade. Este repositório não contém materiais proprietários.
# FSO
Este repositório  é destinado ao estudo sobre Fundamentos de Sistemas Operacionais (FS0) 
