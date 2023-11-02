// Server.c
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "mesg.h"

int main() {
    Message message;
    key_t key;
    int msgid, length, n;

    /* Получим ключ */
    if ((key = ftok("server", 'A')) < 0) {
        printf("Невозможно получить ключ\n");
        exit(1);
    }

    /* Тип принимаемых сообщений */
    message.mtype = 1L;

    /* Создадим очередь сообщений */
    if ((msgid = msgget(key, PERM | IPC_CREAT)) < 0) {
        printf("Невозможно создать очередь\n");
        exit(1);
    }

    /* Примем сообщение */
    n = msgrcv(msgid, &message, sizeof(message), message.mtype, 0);

    /* Если сообщение поступило, выведем его содержимое на терминал */
    if (n > 0) {
        if (write(1, message.buff, n) != n) {
            printf("Ошибка вывода\n");
            exit(1);
        }
    } else {
        printf("Ошибка чтения сообщения\n");
        exit(1);
    }

    /* Удалить очередь должен клиент */
    exit(0);
}