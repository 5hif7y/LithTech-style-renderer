# LithTech-style Renderer Demo

A LithTech-style modular renderer technical demo.


## Design Goals

This project explores a LithTech-style inspired renderer architecture, where the game
code depends on a renderer-agnostic interface (`IRenderer.h`) and concrete rendering
backends are implemented as interchangeable modules.

This modular system requires **normalized drawing operations**, which refer to a small,
renderer-agnostic set of high-level drawing commands (e.g. sprites, quads, batches)
implemented by each backend.

This is not intended to be a full engine, but a technical exploration of modular
renderer design and backend interchangeability.

## Architecture diagram

<p align="center">
  <img src="./assets/architecture-graph.png" alt="Renderer Architecture Diagram" >
</p>


## Project files structure

```sh
.
├── README.md       # This file
├── CMakeLists.txt  # root CMake file
├── engine
│   ├── CMakeLists.txt
│   ├── include
│   │   └── IRenderer.h
│   └── src
│       └── Engine.cpp
├── game
│   ├── CMakeLists.txt
│   ├── include
│   │   └── DemoScene.h
│   └── src
│       ├── DemoScene.cpp
│       └── main.cpp
└── renderers
    └── OGL4REN
        ├── CMakeLists.txt
        ├── gl.c
        ├── include
        │   ├── glad
        │   │   └── gl.h
        │   └── KHR
        │       └── khrplatform.h
        ├── RendererOGL4.cpp
        ├── RendererOGL4.h
        └── shaders
            ├── sprite.frag
            └── sprite.vert

12 directories, 17 files
```


## Build and run (Linux, Makefile generator)

```sh
mkdir build && cd build && cmake ..
make && cd game
./game
```


## TODO

 1.  Code cleanup and general refactoring.
 2.  Add more "**normalized drawing operations**".
 3.  Reimplement LearnOpenGL tutorials using these "**normalized drawing operations**" as a **testing framework**.
 4.  Implement simple 2D games to **demonstrate functionality**.
 5.  Refactor these 2D games to use **Lua scripting** instead of hardcoded game logic.


## OPTIONAL

 1.  Add `Legacy OpenGL`, `Vulkan` and `DirectX 11` support through `IRenderer.h` interface.
 2.  Decouple SDL2 dependency through an `IPlatform.h` interface as a modular platform layer.
 3.  If implemented, add `GLFW` support through `IPlatform.h` interface.
 4.  If implemented, decouple the embedded Lua scripting system through an `IScriptingVM.h` interface.


