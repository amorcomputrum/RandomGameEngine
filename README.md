
# Random Game Engine - RGE

A random game engine, with a random code structure, made out of bordom... yeah, thats really it



## Features

- Windowing and rendering
- GLSL shader loader
- tinyxml2
- tmxparser
- Tiled(tmx) support
- Built-in AA physics engine
- Perlin Noise
- Pre-defined GridWorld(AutoTiler Implemented)
- Custom AutoTiler system


## Demo



Wanna call a Window or Render function from anywhere without paramater passthrough.
Well RGE has what your psychopathic butt needs!!
#### GameLogic.h
```
#include "RGE/Window/Window.h"

void render();
void update();
```
#### GameLogic.cpp
```
#include <iostream>
#include "GameLogic.h"

update(){
    std::cout << RGE::Window::DELTA_TIME << std::endl;
}

render(){
    RGE::Window::Render::drawRect(0,0,20,20);
}
```
#### main.cpp
#include "GameLogic.h"
```
int main(){
    //create window and openGL context
    RGE::Window::createWindow(800,600,"test");
    //set the event functions
    RGE::Window::setUpdateFunction(&update);
    RGE::Window::setRenderFunction(&render);
    //run the window
    RGE::Window::run();
}
```
## Notes for Using RGE::TmxWorld

This implementation of the tmx format does not support the use of ObjectLayers.\
Instead RGE::TmxWorld has a virtual function that allows you to call functions when a block is loaded from the map.
#### ANIMATIONS HAVE NOT BEEN ADDED YET AND OBJECTLAYERS MAY STILL COME



## Acknowledgements

 - [glfw3](https://www.glfw.org/)
 - [tinyxml2](https://github.com/leethomason/tinyxml2)
 - [tmxparser](https://github.com/halsafar/libtmx-parser)
