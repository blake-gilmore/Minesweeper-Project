#define UNICODE
#include <windows.h>
#include <winuser.h>
#include <iostream>
#include <wingdi.h>

int main()
{
    LPCWSTR windowName = L"Visual Studio Code";
    HWND hWND = FindWindow(NULL, windowName);
    while (hWND == NULL)
    {
        std::cout << "Start game!\n";
        Sleep(500);
        hWND = FindWindow(NULL, windowName);
    }
    Sleep(50);
    //start infinite loop
    while (true)
    {
        if (GetKeyState(VK_NUMPAD1) & 0x8000)
        {
            //Get mouse position
            POINT p;
            GetCursorPos(&p);
            ScreenToClient(hWND, &p);
            std::cout << "Numpad 1 is pressed: x|" << p.x << " y|" << p.y << std::endl;
            Sleep(2000);
            //COLORREF myPixel = GetPixel(hDc, p.x, p.y);
            //std::cout << "Red: " << (int)GetRValue(myPixel) << std::endl;
            //std::cout << "Blue: " << (int)GetBValue(myPixel) << std::endl;
            //std::cout << "Green: " << (int)GetGValue(myPixel) << std::endl;

        }
        if (GetAsyncKeyState(VK_NUMPAD2) & 0x8000)
        {
            HDC hDC= GetDC(hWND);
            POINT p;
            GetCursorPos(&p);
            ScreenToClient(hWND, &p);
            COLORREF myPixel = GetPixel(hDC, p.x, p.y);
            ReleaseDC(hWND, hDC);
            std::cout << "Red: " << (int)GetRValue(myPixel) << std::endl;
            std::cout << "Blue: " << (int)GetBValue(myPixel) << std::endl;
            std::cout << "Green: " << (int)GetGValue(myPixel) << std::endl;
        }
        if (GetKeyState(VK_NUMPAD0))
        {
            return 0;
        }

    }
}