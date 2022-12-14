# TalkingSimulator

![Screenshot 1](https://i.imgur.com/vj8sKV6.png)


A talking simulator game written in C++ with SFML Lib. 

Main game mechanic is player going around, talking with npc and do question (Discrete Math, Data Structure and Algorithm, Politics, History, ...)
Answering question will give you point in stats, and your stats with affect the game ending.


Currently the game have up to 9 Ending!


# Project Structure

- main.cpp : Running the game
- Game.cpp : Main game loop
- GameStateBase.cpp, GameStateMachine.cpp: Handle the game state <INTRO (Splash screen) -> STORY -> MENU -> PLAY -> QUIZ -> END>
- GSQuiz.cpp, Quiz.cpp: Handle the question system
- MapConnector.cpp: Store player data like stats, last map, current map, map ...
- GSPlay.cpp: Play game state, Gameplay, handle the conversation with npc, render object, interact object
- DialogSystem.cpp: Handle the dialog chat


# Installation

## Prerequisites

In order to compile this project you will need to:
 - have [SFML](https://www.sfml-dev.org/index.php) installed on your system. If you don't know how to do it see [this link](https://www.sfml-dev.org/tutorials/2.5/#getting-started).
 - have [CMake](https://cmake.org/) installed

## Compilation

Detailed explanation [here](https://preshing.com/20170511/how-to-build-a-cmake-based-project/)

### On Linux with `install.sh`
- Go in the repo folder

`cd the/repo/location`

- Execute `install.sh` script

`./install.sh`


### On Windows with CMake GUI and Visual Studio
 - Install the right SFML version or compile it (see [this](https://www.sfml-dev.org/tutorials/2.5/start-vc.php))
 - Run CMake
 - Select the repo location
 - Click on `Configure`, if you have installed the `x64` version of SFML, in the pop up window select `x64` in the `Optionnal platform for generator` drop down
 - Click on `Finish`
 - Click on `Generate`

# Screenshots
------------------------

![Screenshot 2](https://i.imgur.com/tiCHg2v.png)
![Screenshot 3](https://i.imgur.com/jsYBOYF.png)
![Screenshot 4](https://i.imgur.com/jwhpUHl.png)![Screenshot 5](https://i.imgur.com/4DQE5wL.png)
![Screenshot 6](https://i.imgur.com/Z74iD4G.png)
![Screenshot 7](https://i.imgur.com/R94tQ3R.png)
