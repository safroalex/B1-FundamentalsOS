#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main()
{
    int pid, ppid, status;
    pid = getpid();
    ppid = getppid();
    
    printf("\n\n FATHER PARAM: pid=%i ppid=%i \n", pid, ppid);
    
    if(fork() == 0) 
    {
        execl("./son", "son", NULL); // Предполагается, что исполняемый файл son находится в той же директории
    }
    
    system("ps xf > file"); // Сохраняем таблицу процессов в файл

    wait(&status); // Ожидаем завершения процесса-ребенка
    
    return 0;
}
