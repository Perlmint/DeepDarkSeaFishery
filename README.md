# DeepDarkSeaFishery
DeepDarkSeaFishery

## Requirement for building

* CMake (>= 3.0)
* C++ Compiler (Support almost cpp14 feature)
* SDL2 (place into ext directory or system directory)
* SDL2_image (place into ext directory or system directory)

## How to build

1. Download SDL2 Development Library from https://www.libsdl.org/download-2.0.php
2. Download SDL2_image Development Library from https://www.libsdl.org/projects/SDL_image/
3. Extract both into *ext* folder
4. make build directory(usually *build*)
5. run cmake at build directory - use proper generator
  * You can check available generator via running `cmake --help`
  * Example for xcode : `cmake -GXcode ..`

## How to add new source files

All sources are placed under the *src* folder. Each folder that containing source files also contains *CMakeLists.txt*. Source file list is managed by *CMakeLists.txt*. So, you should update proper *CMakeLists.txt* to add new source file. Below is an example adding new *src/new_feature.cpp* and *src/new_feature.h*.

### Original a part of  *CMakeLists.txt* in src
```
add_sources(
  Sources
  ${R}/main.cpp
  ${R}/platform.h)
```

### After add files
```
add_sources(
  Sources
  ${R}/main.cpp
  ${R}/platform.h
  ${R}/new_feature.h
  ${R}/new_feature.cpp)
```

## How to add new resource file?

All resources are placed under *res* folder. Update *res/CMakeLists.txt*.

## Too annoying. Why should use cmake?

Because C++ is sucks for building on many platforms. CMake can handle it, can works with many compilers - VC, clang, gcc.
