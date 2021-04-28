## RenderEngine



An attempt at a simple engine for loading and rendering meshes and basic animation in the spirit of learning OpenGL 4.0. 



#### Prerequisites

The program uses SDL2 for all the OS specific stuff and GLEW for loading OpenGL function, along with glm as a math library. You can install them using the following command in ubuntu-20.4

```
sudo apt install build-essentials cmake libsdl2-dev libglew-dev 
```



#### Build

We are using `cmake` for building this application. To build the project execute the following command in the parent directory of source - 

```
mkdir -p ./build
cd build
cmake ../
make
```

 

