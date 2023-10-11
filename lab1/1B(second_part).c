#include <windows.h>
#include <stdio.h>
#include <string.h>

DWORD WINAPI ThreadProc(LPVOID lpParameter)
{
    int param;
    param = *(int*)lpParameter;

    while (TRUE)
    {
        printf("Ya potok %d i ya vipoln9us!\n", param + 1);
        Sleep(100);
    }
}

int main(int argc, char* argv[])
{
    HANDLE mHandle[2];
    DWORD mArg[2], mId[2];
    int i;

    for (i = 0; i < 2; i++)
    {
        mArg[i] = i;
        mHandle[i] = CreateThread(NULL, 0, ThreadProc, mArg + i, 0, mId + i);
    }

    // Здесь нет бесконечного цикла, базовый поток завершит работу
    return 0;
}