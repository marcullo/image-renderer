# image-renderer

The project contains two programs:

- Commander - the command line proxy between the user and renderer,
- Renderer - it receives the commands and reacts on them.

## Features

The goal is to render images in one program based on the commands passed by the user to the second program.

TODO: Describe the features

## Requirements

The following dependencies are considered typical. Testing environment in parenthesis.

- Linux x64 (Ubuntu 20.04)
- GCC (9.2)
- CMake (3.16)
- Ninja (1.10.0)

## Getting started

### Configure

```
sudo apt-get install gcc g++ cmake ninja-build
```

### Build

Select a mode then build. It will produce two files: `commander` and `renderer` in `_build` folder.

```shell
make release # -Os -g0 -DNDEBUG
# or
make debug # -O1 -ggdb3 -DDEBUG
```

### Run

TODO: Describe how to run the project

### Test

TODO: Describe how to test the project
