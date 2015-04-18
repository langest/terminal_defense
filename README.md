Terminal Defense
===============

:snail:
Work in progress, pre-alpha~ish
:snail:

## Overview of this project ##
Tower Defense game written in a modern C++ style and is run in the terminal using ASCII art. Currently this project only supports ncurses and is only tested on the Linux platform. This project keeps a MVC architecture with the Model is most of this project, the View and Controller is the GUI class handling various drawing, keeping track of the cursor and getting input from keyboard. 

The content is loaded from file and can be found in the **info** folder. 
The key for building a tower is loaded in the Game constructor, so you will need to restart the game when adding a new tower; however, when modifying a tower, you only need to start a new gameboard (map). 

Virus and projectiles can be added, modified etc. and only need a new gameboard for the change to apply.

## About the game ##
You are a hacker minding your own business when suddenly viruses are invading your terminal!
Viruses (as you all know) begins on the right side and travels to the left.
You lose 1 Terminal Control Point (aka lives) if you let a virus get to the left, making you lose some control of your terminal.
You lose when you lose control over your terminal (reach 0 terminal control points).
You win by defeating ALL the viruses!

You defend your terminal by building towers.
Towers costs RAM to build (you need to place them in memory somewhere!), you gain more RAM by destroying viruses (viruses take RAM, but you free it when they are destroyed). 

### More Details! ###
You cannot block the path entirely. When building the would-blocking tower, it will not built.
The Virus will find a path through your maze. You cannot build during the virus invasion phase. 

# This is awesome! #
Yes, we know! Tower Defence in the terminal! Hearing that a project is appreciated is fun, so if you like it, please inform us :)
