#define UNICODE
#include <windows.h>
#include <Gdiplus.h>

int main()
{
    BYTE* bitPointer;
    RECT rect;
    LPCWSTR windowName = L"Microsoft Minesweeper";
    HWND hWND = FindWindow(NULL, windowName);
    //Get the window. Got it.
    HDC windowDC = GetDC(hWND);
    HDC virtualDC = CreateCompatibleDC(windowDC);
    int width = GetDeviceCaps(windowDC, HORZRES);
    int height = GetDeviceCaps(windowDC, VERTRES);

    HBITMAP mainBitmap = CreateCompatibleBitmap(windowDC, width, height);
    HGDIOBJ newDC = SelectObject(virtualDC, mainBitmap);
    

    return 0;
}