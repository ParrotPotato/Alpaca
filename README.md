## Alpaca


An attempt at a simple engine for loading and rendering meshes and basic animation in the spirit of learning OpenGL 4.0.


#### Prerequisites

The program uses SDL2 for all the OS specific stuff and GLEW for loading OpenGL function, along with glm as a math library. You can install them using the following command in ubuntu-20.4

```
sudo apt install build-essentials cmake libsdl2-dev libglew-dev 
```

Along with above binaries we are using C++17 for building.

#### Build

To build first we need to clone the git repository along with all its sub-modules.

```
git clone --recurse-submodules https://github.com/ParrotPotato/Alpaca.git
```



We are using `cmake` for building this application. To build the project execute the following command in the parent directory of source - 
```
mkdir -p ./build
cd build
cmake ../
make
```
For users using vscode, the source comes with a `launch.json` file which can be used for debugging purposes.

#### Execute

For running the **"code"** use the following command from the parent directory - 
```
pushd res; ../build/renderEngine; popd;
```

#### TODO

Further tasks that I want to do -

- [ ] Loading textures
- [ ] Loading Meshes from obj files
- [ ] Adding basic Phong lighting in the shaders
