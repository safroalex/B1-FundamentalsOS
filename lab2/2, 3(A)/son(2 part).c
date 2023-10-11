#include <stdio.h>
#include <unistd.h>

int main()
{
    int pid, ppid;
    pid = getpid();
    ppid = getppid();
    
    printf("SON: PID = %d, PPID = %d\n", pid, ppid);
    
    sleep(15);
    
    ppid = getppid();
    printf("SON: New PPID = %d\n", ppid);
    
    return 0;
}
