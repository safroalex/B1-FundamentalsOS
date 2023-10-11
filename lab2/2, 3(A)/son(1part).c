#include <stdio.h>
#include <unistd.h>

int main()
{
    int pid, ppid;
    pid = getpid();
    ppid = getppid();
    
    printf("SON: PID = %d, PPID = %d\n", pid, ppid);
    
    sleep(5);  // Допустим, что дочерний процесс "сын" делает некую работу на протяжении 5 секунд
    
    printf("SON: Done.\n");
    
    return 0;
}
