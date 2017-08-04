# FuGen
This is my procedural plant generator library.

# Dependencies

## OpenMesh 6.3
The TreeGen library uses OpenMesh to generate convex hulls. It was tested against OpenMesh 6.3. You need to copy the OpenMesh library into the Dependencies folder. The top level CMakeLists.txt must be in the Dependencies/OpenMesh folder.

The library can be downloaded here:
https://www.openmesh.org/download/

## Qt 5
The editor uses Qt 5 to implement its graphical user interface. The CMakeLists.txt depends on find_package to find the Qt5 headers and libraries.

The library can be downloaded here:
https://www.qt.io/download/

## SDL2
The TreeGen demo programs are using SDL2 for windowing and event handling. The CMakeLists.txt depends on find_package to fing the SDL2 headers and libraries.

The library can be downloaded here:
https://www.libsdl.org/download-2.0.php

## SOIL
The TreeGen demo programs are using SOIL for loading bark textures. You need to copy the SOIL source code (the contents of the src folder) into the Dependencies/SOIL subdirectory.

The library can be downloaded here:
https://github.com/kbranigan/Simple-OpenGL-Image-Library