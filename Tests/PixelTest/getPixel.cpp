#define UNICODE
#include <windows.h>
#include <winuser.h>
#include <iostream>

int main()
{
    LPCWSTR windowName = L"Microsoft Minesweeper";
    HWND hWnd = FindWindow(NULL, windowName);
    while (hWnd == NULL)
    {
        std::cout << "Start game!\n";
        Sleep(500);
        hWnd = FindWindow(NULL, windowName);
    }
    HDC hDc = GetDC(hWnd);
    Sleep(50);
    //start infinite loop
    while (true)
    {
        if (GetKeyState(VK_NUMPAD1))
        {
            //Get mouse position
            POINT p;
            GetCursorPos(&p);
            ScreenToClient(hWnd, &p);
            ReleaseDC(hWnd, hDc);
            std::cout << "Numpad 1 is pressed: x|" << p.x << " y|" << p.y << std::endl;
            Sleep(2000);
        }
        if (GetKeyState(VK_NUMPAD2))
        {
            //Get pixel color
            COLORREF myPixel;

        }
        if (GetKeyState(VK_NUMPAD0))
        {
            ReleaseDC(hWnd, hDc);
            return 0;
        }

    }
}