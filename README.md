# Breakout
 Arcade game

![Breakout_game](https://user-images.githubusercontent.com/17955370/115384232-16f30d00-a1d7-11eb-8cec-e1c0f2b8f3be.PNG)

Hi, my name is Zerin and here I present to you my version of simple Breakout game.

# About game
Game is played as standard Breakout. In order to win you have to remove all bricks from levels. 
On second level, bricks are moving down on every 5th board hit (watch out !)
You have 3 lives that are being passed through levels.

# How to play
To start game, press any mouse button. Move board with your mouse inside game window (moving mouse slower will reduce board's lag).
To enable music in game press number 9, or to disable it number 0.
To Exit game click on X at top right of window.

# Setup
In order to run this game or code, you will be in need to setup and include SDL2 library.

To do so, after cloning or downloading this code, copy folders within SDL_Library and 
paste them in newly created folder "VisualStudio_libraries\" in C: (or any other directory).

After that is done, open your Environment Variable, then under System variables, enter %Path% and create new paths:
`C:\VisualStudio_libraries\SDL2-2.0.14\lib\x64`
`C:\VisualStudio_libraries\SDL2_image-2.0.5\lib\x64`
`C:\VisualStudio_libraries\SDL2_mixer-2.0.4\lib\x64`
`C:\VisualStudio_libraries\SDL2_ttf-2.0.15\lib\x64`
Save and exit. (Reset IDE if opened)

# Future plans
This game is far from being completed. In future, I am looking into making sharpe angles for ball when it hits end of board.
Adding new levels, new difficulties (board getting smaller, time trials, etc),
new features (getting extra life from brick, extra board size, etc). 

I hope you will like this simple humble game :D