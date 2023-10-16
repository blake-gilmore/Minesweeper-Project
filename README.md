# Automated Minesweeper Project
Documenting my progress learning how to make a computer play minesweeper through c++. This program uses C++ and the Win32 API to guide the mouse on screen to auto left click or right click on a Microsoft Minesweeper board to try and win the game. In its current state, it can win virtually all Easy boards, some Medium boards, but no Expert boards yet.

## Main Program File
Works only with Microsoft Minesweeper at full screen. Use g++ *.cpp -l gdi32 -o main to compile and ./main.exe to run.
Once running, and you have a Microsoft Minesweeper window at full screen, press 3 on the numpad to start the bot. Return to the program and pres control + C to close. 


https://github.com/blake-gilmore/Minesweeper-Project/assets/80655017/050fd994-b91c-4943-a0f5-7bcffef6315c



## Test Files

### GetPixel
Test file used to get the current coordinates and RGB value of where your mouse is pointing.

### Move
Test file used to simulate a mouse movement and click when any numpad number is pressed.

### Click
Test file used to simulate a mouse click when any numpad number is pressed.
