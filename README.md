# Animating Shape Rocket
My CTIS-164 (Technical Mathematic) homework written in C/C++ using openGL and GLUT libraries.

Aim was to just coding meaningful shapes and make them move.

I coded this project on Xcode. So, to implement the libraries both openGL and GLUT, do the following -> Build Phases -> Link Binary with Libraries. then type the name of the libraries and add both.


# Running on different IDEs
However, if you want to run this program in another IDE maybe Visual Studio, you should change "vsprintf" to "vsprintf_s" at 129 and 146th lines. And the main function should be void instead of returning int. 

And try this one " #include <GL/glut.h> " instead of " #include <GLUT/GLUT.h> " 36th line.

![164-1hw](https://user-images.githubusercontent.com/32802165/63017498-2ae15a00-be9f-11e9-96c6-4f1f45388a12.gif)
