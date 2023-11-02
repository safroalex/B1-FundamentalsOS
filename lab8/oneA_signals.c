#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>

void handler(int signo) {
    printf("Son3: Caught SIGUSR1\n");
}

int main() {
    pid_t son1, son2, son3;

    son1 = fork();
    if (son1 == 0) {
        // son1: Default behavior for SIGUSR1
        pause(); // wait for signal
        exit(0);
    }

    son2 = fork();
    if (son2 == 0) {
        // son2: Ignore SIGUSR1
        signal(SIGUSR1, SIG_IGN);
        pause(); // wait for signal
        exit(0);
    }

    son3 = fork();
    if (son3 == 0) {
        // son3: Catch and handle SIGUSR1
        signal(SIGUSR1, handler);
        pause(); // wait for signal
        exit(0);
    }

    sleep(1); // give sons time to set up handlers

    // Father: send SIGUSR1 to all sons
    kill(son1, SIGUSR1);
    kill(son2, SIGUSR1);
    kill(son3, SIGUSR1);

    // Father: Check process status before and after sending signals
    system("ps -s >> file");

    // Wait for sons to exit
    wait(NULL);
    wait(NULL);
    wait(NULL);

    return 0;
}
