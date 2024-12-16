
#include <windows.h>
#include <iostream>

int main() {
    STARTUPINFO si = { sizeof(STARTUPINFO) };
    PROCESS_INFORMATION pi = {};

    LPCSTR applicationName = "C:\\Windows\\System32\\notepad.exe";
    
    if (CreateProcess(
            applicationName,  
            NULL,             
            NULL,             
            NULL,             
            FALSE,            
            0,                
            NULL,             
            NULL,             
            &si,              
            &pi)) {           
        std::cout << "Процес створено успішно.\n";

        
        WaitForSingleObject(pi.hProcess, INFINITE);

        DWORD exitCode;
        if (GetExitCodeProcess(pi.hProcess, &exitCode)) {
            std::cout << "Код завершення процесу: " << exitCode << "\n";
        }

        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
    } else {
        std::cerr << "Не вдалося створити процес. Код помилки: " << GetLastError() << "\n";
    }

    return 0;
}
