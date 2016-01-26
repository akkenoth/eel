# EEL
Modern OpenGL (3+) sample program.

## Main features
* Working in OpenGL 3.3 Core profile
* Most computations happen in shaders (almost zero CPU usage)
* Improved Blinn-Phong attenuated shading model
* Normal mapping
* N light sources per scene, M materials per object (with alpha-blending - it's possible to apply a non-specular material on a very glossy one)

## Controls
* WSAD for camera movement
* Mouse for camera rotation (when enabled - see below)
* F to toggle fullscreen
* M to toggle mouse capture (disabled on startup)

## Requirements
* OpenGL 3.3 capable graphic card, e.g. Intel HD Graphics 3000 (Intel Core 2nd gen CPUs), NVidia GeForce 8 series, ATI/AMD Radeon HD 2000 series and newer
* C++11 compatible compiler (tested on modern GCC and VC++)
* For non-Windows OS: installed OpenGL, GLUT, GLEW, zlib and libpng libraries (Windows headers and pre-compiled .lib files are included)

## Compilation & running the program
* Windows: use eel.snl Visual Studio solution file or eel/eel.vcxproj project file (open with VS or import to your IDE of choice). Build and run.
* Linux/*nix: use provided Makefile (`make` or `make run` should be enough).

## Known issues:
* Execution caveat: hardcoded relative paths to textures (in main.cpp). Run from 'eel' directory (with Resources directory in it - see Makefile) or modify the paths (or change the way they're passed).
* Mouse capture may not be working in MacOS (GLUT limitations; should work with up-to-date GLUT though)

## Special thanks
* [Vlad Badoiu](http://in2gpu.com/author/vlad-badoiu/) for his great [tutorial on modern OpenGL](http://in2gpu.com/opengl-3/).
* [Christian Schüler](http://www.thetenthplanet.de/about) for his [note on normal mapping without precomputed tangents](http://www.thetenthplanet.de/archives/1180)

## Copyright notice
This software is licensed under MIT License:

Copyright 2016 Akkenoth

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.