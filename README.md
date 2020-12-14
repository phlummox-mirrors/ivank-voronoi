
# ivank's Voronoi diagram implementation in C++

Slight tweaks to Ivan Kutskir's implementation of Fortune's Voronoi-diagram-building
algorithm (from <http://blog.ivank.net/fortunes-algorithm-and-implementation.html>)
to allow it to be compiled easily on Linux. (Plus translation of an error message
from Czech to English, using Google Translate.)

Source code taken from the .zip file at
<http://www.ivank.net/blogspot/vor/voronoi.zip>.

## requirements

Usual C++ build tools - g++, GNU make, etc.

Headers and libraries for the OpenGL GLUT and GLEW libraries.
On ubuntu, these can be installed with:

```
sudo apt-get install freeglut3-dev libglew-dev
```

## to build

```
make
```
