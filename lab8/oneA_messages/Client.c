// Client.c
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include "mesg.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    Message message;
    key_t key;
    int msgid, length;

    /* Тип посылаемого сообщения */
    message.mtype = 1L;

    /* Получим ключ */
    if ((key = ftok("server", 'A')) < 0) {
        printf("Невозможно получить ключ\n");
        exit(1);
    }

    /* Получим доступ к очереди сообщений */
    /* очередь уже должна быть создана сервером */
    if ((msgid = msgget(key, 0)) < 0) {
        printf("Невозможно получить доступ к очереди\n");
        exit(1);
    }

    /* Подготовим сообщение */
    if ((length = sprintf(message.buff, "IPC Messages!\n")) < 0) {
        printf("Ошибка копирования в буфер\n");
        exit(1);
    }

    /* Передадим сообщение */
    if (msgsnd(msgid, (void*)&message, length, 0) != 0) {
        printf("Ошибка записи сообщения в очередь\n");
        exit(1);
    }

    /* Удалим очередь сообщений */
    if (msgctl(msgid, IPC_RMID, 0) < 0) {
        printf("Ошибка удаления очереди\n");
        exit(1);
    }

    exit(0);
}

