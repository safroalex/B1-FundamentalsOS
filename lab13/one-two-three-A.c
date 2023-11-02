#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

typedef struct Node {
    int data;
    off_t next;
} Node;

void addNode(int fd, int data) {
    Node new_node;
    new_node.data = data;
    new_node.next = 0;

    // Поиск конца списка и добавление нового узла
    off_t current_offset = 0;
    Node current_node;

    while (1) {
        pread(fd, &current_node, sizeof(Node), current_offset);
        if (current_node.next == 0) {
            current_node.next = lseek(fd, 0, SEEK_END);
            pwrite(fd, &current_node, sizeof(Node), current_offset);
            pwrite(fd, &new_node, sizeof(Node), current_node.next);
            break;
        }
        current_offset = current_node.next;
    }
}

int main() {
    // Создание файла
    int fd = open("list.dat", O_RDWR | O_CREAT, 0666);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    // Создание корневого узла
    Node root = { .data = 0, .next = 0 };
    write(fd, &root, sizeof(Node));

    // Создание дочернего процесса
    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        return 1;
    }

    if (pid == 0) {
        // Дочерний процесс
        addNode(fd, 2);
        exit(0);
    } else {
        // Родительский процесс
        addNode(fd, 1);
        wait(NULL);  // Ожидание завершения дочернего процесса
    }

    void printList(int fd) {
    off_t current_offset = 0;
    Node current_node;

    printf("Node Data | Next Offset\n");
    printf("------------------------\n");

    while (pread(fd, &current_node, sizeof(Node), current_offset) > 0) {
        printf("%9d | %11ld\n", current_node.data, current_node.next);
        if (current_node.next == 0) {
            break;
        }
        current_offset = current_node.next;
    }
}


    printList(fd);

    close(fd);
    return 0;
}
