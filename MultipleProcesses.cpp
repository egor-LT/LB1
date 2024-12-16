
#include <windows.h>
#include <iostream>
#include <vector>

int main() {
    const int processCount = 3;
    LPCSTR applications[] = {
        "C:\\Windows\\System32\\notepad.exe",
        "C:\\Windows\\System32\\mspaint.exe",
        "C:\\Windows\\System32\\calc.exe"
    };

    std::vector<PROCESS_INFORMATION> processes(processCount);
    STARTUPINFO si = { sizeof(STARTUPINFO) };

    for (int i = 0; i < processCount; ++i) {
        if (CreateProcess(applications[i], NULL, NULL, NULL, FALSE, 0, NULL, NULL, &si, &processes[i])) {
            std::cout << "Процес " << i + 1 << " створено успішно.\n";
        } else {
            std::cerr << "Не вдалося створити процес " << i + 1 << ". Код помилки: " << GetLastError() << "\n";
        }
    }

    // Очікування завершення всіх процесів
    for (int i = 0; i < processCount; ++i) {
        WaitForSingleObject(processes[i].hProcess, INFINITE);
        DWORD exitCode;
        if (GetExitCodeProcess(processes[i].hProcess, &exitCode)) {
            std::cout << "Процес " << i + 1 << " завершився з кодом: " << exitCode << "\n";
        }
        CloseHandle(processes[i].hProcess);
        CloseHandle(processes[i].hThread);
    }

    return 0;
}
