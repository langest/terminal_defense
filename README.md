Terminal Defense
===============

:snail:
Work in progress, soon playable
:snail:

## Overview of this project ##
Tower Defense game written in a modern C++ style and is run in the terminal using ASCII art. Currently this project only supports ncurses and is only tested on the Linux platform. This project utilizes MVC design pattern.
The GUI is handling all rendering of the game and also gets all the keyboard input.

The content is loaded from files located in the info folder.
The key for building a tower is loaded in the Game constructor, so you will need to restart the game when adding a new tower; however, when modifying a tower, you only need to start a new gameboard (map). 

Viruses and projectiles can be added and modified. And only need a new game session(gameboard object) to run to update.

## Story, so far... ##
You are a hacker minding your own business when suddenly viruses are invading your terminal!
Viruses (as is common knowledge) begins on the right side of the terminal and travels to the left side.
You lose 1 Terminal Control point(TC, your lives) if you let a virus get to the left side.
If your TC reaches 0 you will lose all control of your terminal, which is terminal for you.
To be victorious you need to eliminate all of the invading viruses.

You defend your terminal by building towers.
Towers costs RAM to build (you need to place them somewhere in your memory), you gain more RAM by destroying viruses (viruses occupy RAM, but it is freed once they are destroyed).

## Game mechanics ##
You cannot block the path entirely. You cannot build the would-be-blocking tower.
The Virus will find a path through your maze, they are very clever.
You cannot build anything during the waves of virus.
