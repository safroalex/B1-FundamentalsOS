#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <seconds>\n", argv[0]);
        return 1;
    }

    int seconds = atoi(argv[1]);
    if (seconds <= 0) {
        fprintf(stderr, "Please specify a positive number of seconds.\n");
        return 1;
    }

    // Create a waitable timer
    HANDLE hTimer = NULL;
    LARGE_INTEGER liDueTime;
    liDueTime.QuadPart = -10000000LL * seconds; // Convert time to 100-nanosecond intervals

    hTimer = CreateWaitableTimer(NULL, TRUE, NULL);
    if (hTimer == NULL) {
        fprintf(stderr, "CreateWaitableTimer failed (%d)\n", GetLastError());
        return 1;
    }

    // Set the timer
    if (!SetWaitableTimer(hTimer, &liDueTime, 0, NULL, NULL, 0)) {
        fprintf(stderr, "SetWaitableTimer failed (%d)\n", GetLastError());
        CloseHandle(hTimer);
        return 1;
    }

    // Wait for the timer to expire
    if (WaitForSingleObject(hTimer, INFINITE) != WAIT_OBJECT_0) {
        fprintf(stderr, "WaitForSingleObject failed (%d)\n", GetLastError());
    } else {
    printf("Waited for %d seconds.\n", seconds); // Эта строка
    }

    CloseHandle(hTimer);

    return 0;
}
