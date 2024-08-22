#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <shlwapi.h>

#pragma comment(lib, "Shlwapi.lib")

int wmain(int argc, wchar_t *argv[])
{
    STARTUPINFOW si;
    PROCESS_INFORMATION process;
    DWORD ret;

    // Initialize memory for the structures
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&process, sizeof(process));

    // Construct the command line string
    wchar_t commandLine[] = L"\"C:\\Program Files\\nodejs\\node.exe\" \"C:\\Users\\rory\\AppData\\Roaming\\npm\\node_modules\\yarn\\bin\\yarn.js\"";

    // Create the process
    if (!CreateProcessW(NULL, commandLine, NULL, NULL, TRUE, 0, NULL, NULL, &si, &process))
    {
        return 1;
    }

    // Wait for the process to complete
    WaitForSingleObject(process.hProcess, INFINITE);

    // Get the exit code
    GetExitCodeProcess(process.hProcess, &ret);

    // Close process and thread handles
    CloseHandle(process.hProcess);
    CloseHandle(process.hThread);

    return ret;
}
