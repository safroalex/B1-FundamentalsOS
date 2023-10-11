#include <stdio.h>
#include <windows.h>
#include <string.h>

HANDLE hNextEvent;
HANDLE hThread1, hThread2;

DWORD WINAPI Thread1(LPVOID lpParameter)
{
    char str[256];
    BOOL bExit = FALSE;
    printf("Thread1 begins\n");

    while (!bExit)
    {
        WaitForSingleObject(hNextEvent, INFINITE);
        fgets(str, sizeof(str), stdin);
        str[strcspn(str, "\n")] = 0;
        printf("Thread1 User input: %s\n", str);

        while (strcmp(str, "next") && strcmp(str, "exit"))
        {
            fgets(str, sizeof(str), stdin);
            str[strcspn(str, "\n")] = 0;
            printf("Thread1 User input: %s\n", str);
        }

        if (!strcmp(str, "exit"))
        {
            bExit = TRUE;
        }

        SetEvent(hNextEvent);
    }

    printf("Thread1 finished\n");
    return 0;
}

DWORD WINAPI Thread2(LPVOID lpParameter)
{
    char str[256];
    BOOL bExit = FALSE;
    printf("Thread2 begins\n");

    while (!bExit)
    {
        WaitForSingleObject(hNextEvent, INFINITE);
        fgets(str, sizeof(str), stdin);
        str[strcspn(str, "\n")] = 0;
        printf("Thread2 User input: %s\n", str);

        while (strcmp(str, "next") && strcmp(str, "exit"))
        {
            fgets(str, sizeof(str), stdin);
            str[strcspn(str, "\n")] = 0;
            printf("Thread2 User input: %s\n", str);
        }

        if (!strcmp(str, "exit"))
        {
            bExit = TRUE;
        }

        SetEvent(hNextEvent);
    }

    printf("Thread2 finished\n");
    return 0;
}

int main(int argc, char* argv[])
{
    printf("I am main! Hello!\n");

    hNextEvent = CreateEvent(NULL, FALSE, TRUE, NULL);

    hThread1 = CreateThread(NULL, 0, Thread1, NULL, 0, NULL);
    hThread2 = CreateThread(NULL, 0, Thread2, NULL, 0, NULL);

    HANDLE handles[] = { hThread1, hThread2 };
    WaitForMultipleObjects(2, handles, TRUE, INFINITE);

    CloseHandle(hNextEvent);
    CloseHandle(hThread1);
    CloseHandle(hThread2);

    printf("Main thread finished\n");

    return 0;
}