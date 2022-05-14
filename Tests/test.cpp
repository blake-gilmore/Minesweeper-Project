#include <iostream>
#include <windows.h>
int main()
{
    using std::cout;
    using std::cin;
    int wait;
    cout << "How long would you like to wait?";
    cin >> wait;
    wait *= 1000;
    Sleep(wait);

    cout << "Hello Tiffanie!";
    return 0;
}