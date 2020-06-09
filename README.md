# CPPND: Capstone Project

This is the implementation of the final project coursework of the [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213). It implements some extensions to the exemplary snake game introduced in the description of the capstone project. The code for this repo was inspired by [this](https://codereview.stackexchange.com/questions/212296/snake-game-in-c-with-sdl) excellent StackOverflow post and set of responses.

It was extended by the following features:
- prompt to query for user input 
- enable multiple players (for now only two, but this could easily be extended too many more)
  - first players controls by UP/DOWN/LEFT/RIGHT, second players controls by W/S/A/D
- addition of random obstacles for every food object eaten
- collision checking in between snakes and obstacles

<img src="two_players.gif"/>

## Dependencies for Running Locally
* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* SDL2 >= 2.0
  * All installation instructions can be found [here](https://wiki.libsdl.org/Installation)
  * Note that for Linux, an `apt` or `apt-get` installation is preferred to building from source.
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./SnakeGame`.

## File/Class Structure

The file structure of the original repo has been mainly contained. Adaptions to the ```snake.h/snake.cpp```, ```controller.h/controller.cpp```, ```game.h/game.cpp``` and ```renderer.h/renderer.cpp``` have been made in order to support multiple players. In addition free functions in ```prompt.h/prompt.cpp``` have been provided in order to handle user interaction. 


## Expected Behavior/Output
When starting the game, the player(s) are asked to the number of players. This is currently limited to 2 players, but could easily be extended. When cancelling, the game will quit without any errors or exceptions. Once the number of players is chosen, player(s) will be able to play the snake game. First player controls by arrow keys, second player controls by W/A/S/D. Every time a food object is eaten by one of the snakes, the game's speed is increased and an obstacle is placed. Hitting another snake or an obstacle will end the game. Finally, a prompt is shown indicating the winner of the game. The console prints additional input about the general game score for all players.

## Rubic Points Addressed

### Loops, Functions, I/O
**1. The project demonstrates an understanding of C++ functions and control structures.**

The following functions use a variety of control structures (loops, STL algorithms, conditional statements):
- ```game.cpp::AddObstacle::88```
- ```game.cpp::PlaceFood::64```
- ```game.cpp::Update::112```
- ```snake.cpp::GetAllOccupiedCells::82```
- ```snake.cpp::InCollision::94```

**2. The project accepts user input and processes the input.**

The following functions are querying and processing user input>
- ```prompt.cpp::QueryForNumberOfPlayers::10```
- ```prompt.cpp:ShowFinalScore::66```

### Object Oriented Programming

**3. The project uses Object Oriented Programming techniques..**

The following members/functions have been extended with additional attributes and methods:
- ```game.h::snakes::23```
- ```game.h::obstacles::25```
- ```game.h::free_space::26```
- ```snake.h::GetAllOccupiedCells::28```
- ```snake.h::InCollision::29&30```

**4. Classes abstract implementation details from their interfaces.**

The following member functions are abstracting implementations from their interfaces:
- ```game.cpp::AddObstacle::88```
- ```game.cpp::PlaceFood::64```
- ```game.cpp::Update::112```
- ```snake.cpp::GetAllOccupiedCells::82```
- ```snake.cpp::InCollision::94```

**5. Overloaded functions allow the same function to operate on different parameters.**

The following functions are overloading with different signatures:
- ```snake.h::InCollision::29&30```

### Memory Management

**6. The project makes use of references in function declarations.**

The following functions use pass-by-reference:
- ```game.h::Update()::33```
- ```snake.h::InCollision::29&30```
- ```prompt.h::QueryForNumbersOfPlayers()::9```
- ```prompt.h::ShowFinalScore::11```

