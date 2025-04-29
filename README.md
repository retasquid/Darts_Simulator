# Darts Game Project
Our project consists of developing a program capable of simulating dart throws and determining the landing position of these darts on a target, based on various conditions such as initial velocity, vertical and horizontal angles, as well as the respective positions of the player and the target. The objective is to perform all necessary calculations to simulate the arrow's path and, eventually, to use interfaces such as Dart Simulator to visualize the dart trajectories.

# Tools
For this purpose, we have chosen to use the C++ programming language and the SFML 3.0 library, Dart Simulator, for which installation instructions will be provided below. Additionally, for collaborative project management, we have used GitHub, which allows multiple developers to work simultaneously on the code, modify it, and share updates with other team members.

# How to use
You can choose between 5 modes :

* 2D without wind
*  2D with wind
*  3D without wind
*  3D with wind
*  3D with strong wind

Each round, the actual player provide 3 information for modes without wind : 
* the bullet speed
* the alpha angle
* the initial height of the launch

And he provide 5 information for modes with wind : 
* the bullet speed
* the alpha angle
* the phi angle
* his distance from the launch line
* the initial height of the launch

The wind can be generated in every direction with a speed between 0 and 24 for normal wind modes and between 0 and 40 for strong wind mode.

# Installation
You need to install SFML 3.0 : https://www.sfml-dev.org/fr/download/sfml/3.0.0/
This game was only tested on Visual Studio Code with gcc compiler and SFML 3.0 configured.
For compiling, you need to open all files in tabs on your code software and then compile the main.cpp file.
