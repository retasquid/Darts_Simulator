# Darts Game Project
Our project consists of developing a program capable of simulating dart throws and determining the landing position of these darts on a target, based on various conditions such as initial velocity, vertical and horizontal angles, as well as the respective positions of the player and the target. The objective is to perform all necessary calculations to simulate the arrow's path and, eventually, to use interfaces such as Dart Simulator to visualize the dart trajectories.

# Tools
For this purpose, we have chosen to use the C++ programming language and the SFML 3.0 library, Dart Simulator, for which installation instructions will be provided below. Additionally, for collaborative project management, we have used GitHub, which allows multiple developers to work simultaneously on the code, modify it, and share updates with other team members.

# How to use

### Modes

You can choose between 5 modes :
* 2D without wind
*  2D with wind
*  3D without wind
*  3D with wind
*  3D with strong wind

### Information at each shoot

Each round, the actual player provide 3 information for modes without wind : 
* the dart speed in meter/sec
* the alpha angle in degre
* the initial height of the launch in meter

And he provide 5 information for modes with wind : 
* the dart speed in meter/sec
* the alpha angle in degre
* the phi angle in degre
* his distance from the launch line in meter
* the initial height of the launch in meter
### Wind informations

The wind can be generated in every direction with a speed between 0 and 24 for normal wind modes and between 0 and 40 for strong wind mode.

### Graphics explainations

The left target represent a side view of the shot. 

The right target represent the front view of the shot.

The color bar represent the streinght of the wind :
- Green :   0 < wind streinght < 8
- Orange :  8 < wind streinght < 16
- Red :    16 < wind streinght 

# Installation
You need to install SFML 3.0 : https://www.sfml-dev.org/fr/download/sfml/3.0.0/

This game was only tested on Visual Studio Code with gcc compiler and SFML 3.0 configured.

For compiling, you need to open all files in tabs on your code software and then compile the main.cpp file.

# Roadmap
- Q3 2025 : use more than 2 players and choose their names
- Q4 2025 : input everything directly on the graphic window and hide the commande terminal
- Q1 2026 : add the looses caused by the air around the dart

# User licence

Every one can use, modify and share my code.

Contributors name should be credited

# Credits

### Contributors
retasquid / Noé Dargaud : code and readme
Alan2005-code / Alan Bayt : project document and readme introduction

### helps
Claude AI : code correction and function utilisation examples
YouTube @MesosAurum : SFML 3.0 tutorials
