#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    int pid, ppid;
    pid = getpid();
    ppid = getppid();
    
    printf("FATHER: PID = %d, PPID = %d\n", pid, ppid);
    
    pid_t child_pid = fork();
    
    if(child_pid == 0) 
    {
        execl("./son", "son", NULL);
    }
    else if(child_pid > 0)
    {
        printf("FATHER: Created child process. Exiting now.\n");
        _exit(0);
    }
    else 
    {
        perror("Fork failed");
        return 1;
    }

    return 0;
}
