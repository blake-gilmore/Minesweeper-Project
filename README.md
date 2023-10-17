# Automated Minesweeper Project
Documenting my progress learning how to make a computer play minesweeper through c++. This program uses C++ and the Win32 API to guide the mouse on screen to auto left click or right click on a Microsoft Minesweeper board to try and win the game. In its current state, it can win virtually all Easy boards, some Medium boards, but no Expert boards yet.

This program uses Bitblt to build a capture of the screen's RGB values, and build a guess of what the Minesweeper board looks like. It's able to do this from evaluating the RGB values of each square to determine if each square hasn't been touched, has been opened, or has a specific number. In addition to color, patterns of number shapes have been hard-coded in, so the program will check the main RGB value of the square as well as the general shape of the number of each square in order to categorize it correctly into the right number value. Based on those values, it builds a list of squares it needs to left click or right click on the board at the time of the screen capture, and sets out clicking away based on predefined rules.



## Main Program File
Works only with Microsoft Minesweeper at full screen. Use g++ *.cpp -l gdi32 -o main to compile and ./main.exe to run.
Once running, enter the number of mines you have and open a Microsoft Minesweeper window with a game ready at full screen. Press 3 on the numpad to start the bot. Return to the program and press control + C to close. 

### Easy Board Demo
https://github.com/blake-gilmore/Minesweeper-Project/assets/80655017/050fd994-b91c-4943-a0f5-7bcffef6315c

### Medium Board Demo

https://github.com/blake-gilmore/Minesweeper-Project/assets/80655017/bdbbae1d-abb9-44f1-a5ee-cc998ef9b491




## Test Files

### GetPixel
Test file used to get the current coordinates and RGB value of where your mouse is pointing.

### Move
Test file used to simulate a mouse movement and click when any numpad number is pressed.

### Click
Test file used to simulate a mouse click when any numpad number is pressed.
