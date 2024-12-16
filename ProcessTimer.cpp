
#include <windows.h>
#include <iostream>

int main() {
    STARTUPINFO si = { sizeof(STARTUPINFO) };
    PROCESS_INFORMATION pi = {};

    LPCSTR applicationName = "C:\\Windows\\System32\\notepad.exe";

    if (CreateProcess(applicationName, NULL, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
        std::cout << "Процес створено успішно.\n";

       
        DWORD result = WaitForSingleObject(pi.hProcess, 10000);  
        if (result == WAIT_TIMEOUT) {
            std::cout << "Процес виконується занадто довго. Завершуємо...\n";
            TerminateProcess(pi.hProcess, 1);  
        } else if (result == WAIT_OBJECT_0) {
            DWORD exitCode;
            if (GetExitCodeProcess(pi.hProcess, &exitCode)) {
                std::cout << "Код завершення процесу: " << exitCode << "\n";
            }
        }

        
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
    } else {
        std::cerr << "Не вдалося створити процес. Код помилки: " << GetLastError() << "\n";
    }

    return 0;
}
