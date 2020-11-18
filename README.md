# Image Renderer

The project contains two programs:

- Renderer - it receives the commands and reacts on them by both responding and rendering the image,
- Commander - the command line proxy between the user and Renderer.

The main goal is to become acquainted with modern C++ language features (including `std::filesystem`, smart pointers, rvalue references, enum classes, exception classes, move semantics, range-based for loops, etc.).

Read the [Developer Notes](#developer-notes) for more thoughts.

## Features

- set width and height of the image
- draw rectangle and triangle
- render to a specified file
- validate input arguments
- save invalid commands to a log file
- parse input data prompted by user of from a file

## Requirements

Author's environment in parenthesis.

- Linux x64 (Ubuntu 20.04)
- GCC (9.2)
- CMake (3.16)
- Make (4.2.1)
- Ninja (1.10.0)

Optional:
- VSCode (1.51.1)
- valgrind (3.16.1)

## Getting started

### Configure

The following dependencies are considered typical.

```
sudo apt-get install gcc g++ cmake ninja-build
```

### Build

Select a mode then build. It will produce two files: `commander` and `renderer` in `_build` folder whereas CMake build files will be in `_build/cmake` (by default).

The suggested generator is `Ninja`. There are two build modes: `release` and `debug`. You can also print verbose build information if needed.

#### Consequences

- `release` - you have very limited information printed in console (only confirmations of valid commands sent to the `renderer` in [interactive mode](#interactive-mode)) and you have `-Os -g0 -DNDEBUG` options,
- `debug`- you can have the module-oriented logging of programs execution to a console (`log_settings.hpp`) and you have `-O1 -ggdb3 -DDEBUG` options,
- `VERBOSE` - it shows a verbose build log only and does not affect the target.

#### Compilation

###### with Make helper

```shell
make release # -Os -g0 -DNDEBUG
# or
make debug # -O1 -ggdb3 -DDEBUG
# or verbosely
make [debug|release] VERBOSE=1
```

###### CMake only

1. Configure

Assuming you provide `BUILD_TYPE` (either `Debug` or `Release`), run the configuration command below. To allow to compile verbosely, append `-DCMAKE_VERBOSE_MAKEFILE=TRUE`.

```shell
cmake -GNinja -S . -B _build/cmake -DCMAKE_BUILD_TYPE=<BUILD_TYPE>
```

2. Compile

```shell
cmake --build _build/cmake --target all
```

The `CMAKE_OUTPUT_DIRECTORY` is set to `_build` by default so please find compiled targets there.

### Run

There are two modes of operation. In both you are launching commander which further runs the renderer. Beware of [build consequences](#consequences). You need to run Commander which will then launch Renderer in a separate process automatically.

**Warning**: Renderer and Commander depend on each other. You cannot run either of programs standalone! Modify source code a bit if needed.

###### Interactive mode

```shell
# in _build directory run:
./commander # you need to type commands manually
```

###### Lazy mode

```shell
# in _build directory run:
./commander ../samples/squared.txt # provide the file with commands
```

The `squared.bmp` will be saved in `_build/renders/squared`.

### Clean

```shell
make clean
# or
rm -rf _build
```

### Test

In order to verify the memory state during the program execution run

```
make memcheck
```

Unfortunately Unit Tests have not been implemented yet.

### Developer Notes

#### Project structure

(simplified)

```shell
├── CMakeLists.txt                # build script
├── commander                     # master application
├── log_settings.hpp              # log settings
├── Makefile                      # helper build script
├── renderer                      # slave application
├── samples                       # sample commands
└── sdk                           # custom development kit
    ├── dice
    │   └── Dicer.hpp             # random color
    ├── graphics
    │   ├── include
    │   │   ├── Image.hpp         # image processing library wrapper
    │   │   └── Paint.hpp         # R,G,B color structure
    ├── logging                   # local logging mechanism
    ├── shell
    │   ├── include
    │   │   ├── Channel.hpp       # communication channel
    │   │   └── CommandParser.hpp # command parser
    └── validation                # custom exceptions and validators
```

#### Inter-process communication

We have the `commander` (master) and `renderer` (slave) programs. They communicate with bidirectional communication channel implemented with [POSIX message queues][2] - one queue per direction.

The commander sends the raw message queued from the user to the renderer on one channel and wait for positive message acknowledgement on another. The message is acknowledged by an empty slave response. If error occurs, slave responds with the whole message content and the `UnderstandingException` is thrown.

#### Input validation

  1. Make sure with regex match if command name and arguments are
  provided, separated by a whitespace.
  2. Decode message into name token and args token.
  3. Make sure command with given name is supported. Ignore case.
  4. Split arguments string into argument tokens with arg sep (colon).
  5. Validate the number of arguments (should match the expectance).
  6. Validate if arguments are not empty.
  7. Decode command.

#### Error handling

A child of `std::runtime_error` has been proposed. `VerificationException` is a base exception in the project. There are:
- `LimitException` - thrown when given image coordinates/sizes are invalid
- `ParsingException` - thrown when command has been improperly parsed
- `UnderstandingException` - thrown when the slave did not understood the message from the master.

For the simplicity, some exceptions are handled in the top level modules.

#### Graphics

Decided on:
- 8192x8192 maximal size
- static background
- randomized color of drawn object (algorithm: classic Mersenne Twister)
- single image layer
- 1-byte depth per color

The [C++ Bitmap Library][1] (Arash Partow, MIT License) was used for the image processing. It is downloaded automatically during project build to `_build/external`.

#### Environment

The project contains the initial setup for VS Code:
- Local debug configurations
- Debug and Release variants
- CMake integration
- Editor Config integration
- Language spell check

Extensions:
- C/C++ (Microsoft)
- CMake Tools
- CSpell Check

[1]: https://github.com/ArashPartow/bitmap.git
[2]: https://www.man7.org/linux/man-pages/man7/mq_overview.7.html
