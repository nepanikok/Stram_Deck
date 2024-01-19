#include <iostream>
#include <windows.h>

//#define APPCOMMAND_MEDIA_PLAY_PAUSE 14
//#define WM_APPCOMMAND 0x0319
#define KEYEVENTF_KEYDOWN 0
#define KEYEVENTF_KEYUP 2

void toggleAudio() {
    keybd_event(VK_VOLUME_MUTE, 0, KEYEVENTF_EXTENDEDKEY, 0);
    keybd_event(VK_VOLUME_MUTE, 0, KEYEVENTF_KEYUP, 0);
}
void openURL(const wchar_t* url) {
    ShellExecute(NULL, L"open", url, NULL, NULL, SW_SHOWNORMAL);
}
void openLightroom() {
    const wchar_t* lightroomPath = L"C:\\Program Files\\Adobe\\Adobe Lightroom Classic\\lightroom.exe";
    ShellExecute(NULL, L"open", lightroomPath, NULL, NULL, SW_SHOWNORMAL);
}
void toggleKeyboardLanguage() {
    keybd_event(VK_LWIN, 0, 0, 0);
    keybd_event(VK_SPACE, 0, 0, 0);
    keybd_event(VK_SPACE, 0, KEYEVENTF_KEYUP, 0);
    keybd_event(VK_LWIN, 0, KEYEVENTF_KEYUP, 0);
}
void openIntelliJ() {
    const wchar_t* lightroomPath = L"C:\\Program Files\\JetBrains\\IntelliJ IDEA Community Edition 2023.2.2\\bin\\idea64.exe";
    ShellExecute(NULL, L"open", lightroomPath, NULL, NULL, SW_SHOWNORMAL);
}
void openXampp() {
    const wchar_t* lightroomPath = L"C:\\xampp\\xampp-control.exe";
    ShellExecute(NULL, L"open", lightroomPath, NULL, NULL, SW_SHOWNORMAL);
}
//C:\xampp
void copyText() {
    keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYDOWN, 0);
    keybd_event(0x43, 0, KEYEVENTF_KEYDOWN, 0); // 0x43 - 'C' raidė
    keybd_event(0x43, 0, KEYEVENTF_KEYUP, 0);
    keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
}

void pasteText() {
    keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYDOWN, 0);
    keybd_event(0x56, 0, KEYEVENTF_KEYDOWN, 0); // 0x56 - 'V' raidė
    keybd_event(0x56, 0, KEYEVENTF_KEYUP, 0);
    keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
}

int main() {
    HANDLE hSerial;
    char buffer[256];

    hSerial = CreateFileA("\\\\.\\COM4", GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

    if (hSerial == INVALID_HANDLE_VALUE) {
        std::cerr << "Error opening serial port\n";
        return 1;
    }
    DWORD bytesRead;
    while (1) {
        ReadFile(hSerial, buffer, sizeof(buffer), NULL, 0);
        if (buffer[0] == 'A') {
            toggleAudio();
            std::cout << "Mygtukas 1 paspaustas\n";
        }
        else if (buffer[0] == 'B') {
            const wchar_t* youtubeURL = L"https://www.youtube.com";
            openURL(youtubeURL);
            std::cout << "Mygtukas 2 paspaustas\n";
        }
        else if (buffer[0] == 'C') {
            openLightroom();
            std::cout << "Mygtukas 3 paspaustas\n";
        }
        else if (buffer[0] == 'D') {
            openXampp();
            std::cout << "Mygtukas 4 paspaustas\n";
        }
        else if (buffer[0] == 'E') {
            toggleKeyboardLanguage();
            std::cout << "Mygtukas 5 paspaustas\n";
        }
        else if (buffer[0] == 'F') {
            openIntelliJ();
            std::cout << "Mygtukas 6 paspaustas\n";
        }
        else if (buffer[0] == 'G') {
            copyText();
            std::cout << "Mygtukas 7 paspaustas\n";
        }
        else if (buffer[0] == 'H') {
            pasteText();
            std::cout << "Mygtukas 8 paspaustas\n";
        }
        else {
            std::cerr << "Error reading from serial port\n";
        }
    }

    CloseHandle(hSerial);
    return 0;
}