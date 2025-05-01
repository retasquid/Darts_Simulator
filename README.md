# Darts Game Project

Our project consists of developing a program capable of simulating dart throws and determining the landing position of darts on a target, based on various conditions such as initial velocity, vertical and horizontal angles, as well as the respective positions of the player and the target. The objective is to perform all necessary calculations to simulate the dart's path and, eventually, to use interfaces such as Dart Simulator to visualize the dart trajectories.

## Tools

For this purpose, we have chosen to use the C++ programming language and the SFML 3.0 library. Additionally, for collaborative project management, we have used GitHub, which allows multiple developers to work simultaneously on the code, modify it, and share updates with other team members.

## How to Use

### Modes

You can choose between 5 modes:
* 2D without wind
* 2D with wind
* 3D without wind
* 3D with wind
* 3D with strong wind

### Information Required for Each Throw

For modes without wind, each player must provide 3 inputs:
* Dart speed in meters/second
* Alpha angle in degrees
* Initial launch height in meters

For modes with wind, each player must provide 5 inputs:
* Dart speed in meters/second
* Alpha angle in degrees
* Phi angle in degrees
* Distance from the launch line in meters
* Initial launch height in meters

### Wind Information

Wind can be generated in any direction with a speed between:
* 0 and 24 for normal wind modes
* 0 and 40 for strong wind mode

### Graphics Explanation

Left target: represents a side view of the shot

Right target: represents the front view of the shot

The color bar represents the strength of the wind:
- Green: 0 < wind strength < 8
- Orange: 8 < wind strength < 16
- Red: 16 < wind strength

## Installation

You need to install SFML 3.0: https://www.sfml-dev.org/download/sfml/3.0.0/

This game was only tested on Visual Studio Code with the GCC compiler and SFML 3.0 configured.

For compiling, you need to open all files in tabs on your code software and then compile the main.cpp file.
You also need to replace the library path in your "args" section of task.json file on VScode :

            "args": [
                "-fdiagnostics-color=always",
                "-g",
                "${file}",
                "-o",
                "${fileDirname}\\${fileBasenameNoExtension}.exe",
                "-I",
                "C:\\your_path\\SFML-3.0.0\\include",
                "-L",
                "C:\\your_path\\SFML-3.0.0\\lib",
                "-lsfml-graphics",
                "-lsfml-window",
                "-lsfml-system"
            ],
            
## Roadmap

- Q3 2025: Support for more than 2 players and customizable player names
- Q4 2025: Direct input through the graphic window and hiding of command terminal
- Q1 2026: Add air resistance effects on dart trajectory

## User License

Anyone can use, modify, and share this code.
Contributors' names should be credited.

## Credits

### Contributors
- retasquid / Noé Dargaud: code and readme
- Alan2005-code / Alan Bayt: project documentation and readme introduction

### Acknowledgements
- Claude AI: code correction and function usage examples
- YouTube @MesosAurum: SFML 3.0 tutorials
