#include <windows.h>
#include <stdio.h>

int main(int argc, char* argv[])
{
    STARTUPINFO startInfo;
    PROCESS_INFORMATION processInfo;

    ZeroMemory(&startInfo, sizeof(STARTUPINFO));
    startInfo.cb = sizeof(startInfo);

    WCHAR proc_name[] = L"C:\\WINDOWS\\SYSTEM32\\NOTEPAD.EXE";

    if (!CreateProcess(NULL, proc_name, NULL, NULL, FALSE,
                       NORMAL_PRIORITY_CLASS | CREATE_NEW_CONSOLE, 
                       NULL, NULL, &startInfo, &processInfo))
    {
        fprintf(stderr, "CreateProcess failed on error %d\n", GetLastError());
        ExitProcess(1);
    }

    printf("ProcessHandle=%d\n", (int)processInfo.hProcess);
    printf("ThreadHandle=%d\n", (int)processInfo.hThread);

    CloseHandle(processInfo.hProcess);
    CloseHandle(processInfo.hThread);

    return 0;
}