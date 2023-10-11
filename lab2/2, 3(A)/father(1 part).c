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
    
    printf("FATHER: PID = %d, PPID = %d\n", pid, ppid);
    
    pid_t child_pid = fork();
    
    if(child_pid == 0) 
    {
        execl("./son", "son", NULL);  // Предполагается, что исполняемый файл son находится в той же директории
    }
    else if(child_pid > 0)
    {
        wait(&status); // Ожидание завершения дочернего процесса
        printf("FATHER: Child has finished execution.\n");
    }
    else 
    {
        perror("Fork failed");
        return 1;
    }

    return 0;
}
