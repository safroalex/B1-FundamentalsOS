#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <stdio.h>
#include "shmem.h"  

int main() {
    Message *msgptr;
    key_t key;
    int shmid, semid;

    if((key = ftok("server", 'A')) < 0) {
        printf("Невозможно получить ключ\n");
        exit(1);
    }

    if((shmid = shmget(key, sizeof(Message), PERM | IPC_CREAT)) < 0) {
        printf("Невозможно создать область\n");
        exit(1);
    }

    if((msgptr = (Message*)shmat(shmid, 0, 0)) < 0) {
        printf("Ошибка присоединения\n");
        exit(1);
    }

    if((semid = semget(key, 2, PERM | IPC_CREAT)) < 0) {
        printf("Невозможно создать семафор\n");
        exit(1);
    }

    if(semop(semid, &proc_wait[0], 1) < 0) {
        printf("Невозможно выполнить операцию\n");
        exit(1);
    }

    if(semop(semid, &mem_lock[0], 2) < 0) {
        printf("Невозможно выполнить операцию\n");
        exit(1);
    }

    printf("%s", msgptr->buff);

    if(shmdt(msgptr) < 0) {
        printf("Ошибка отключения\n");
        exit(1);
    }

    exit(0);
}