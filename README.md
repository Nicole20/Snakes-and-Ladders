Snakes-and-Ladders
==================

This project was first a group project, in teams of three. It covered the simple topics learnt in class and was less of a challenge in a team. So I decided to start the project over on my own and add any features I wanted.
This is a 3D Snakes and Ladders board game using OpenGL. The placement of the snakes and the ladders are random. It has a dice rolling animation and the player movement animation.

GLUT setup
==========

Include your GLUT files in your project properties.
C/C++ -> General -> Additional Include Directories: add the folder where the GLUT include file is located.
Linkers -> General -> Additional Lirbary Directories: add the folder where the GLUT library file is located.
Linkers -> Input -> add the following:
opengl32.lib
glu32.lib
freeglut.lib
glut32.lib

Models
======

Add the .mtl and the .obj files in the project's folder.
If you create your own, the scaling might need some tweaking.
