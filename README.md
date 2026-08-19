# Core Wars

A C++ implementation of the **Core Wars** game, in which autonomous programs compete against each other in a shared memory arena.

Players write their programs in **RedCode**, an assembly-like programming language. At the beginning of a match, each program is loaded into a random location on the arena and then executed autonomously.

<img width="1429" height="876" alt="image" src="https://github.com/user-attachments/assets/ecc0040f-4839-4717-9708-02be4042b05f" />

## Overview

The arena is represented as a set of memory cells. Each cell contains a RedCode instruction, and programs occupy consecutive memory cells when loaded.

For example, a program consisting of five instructions will occupy five consecutive cells on the arena.

The main objective of each player is to **overwrite the opponent's program with a `DAT` instruction**. Executing a `DAT` instruction terminates the execution of the program, effectively eliminating the player from the match.

The RedCode language supports instructions for:

* Memory copying
* Arithmetic operations
* Comparing memory cells
* Conditional jumps
* Unconditional jumps

The game continues until only one program remains active.

## Architecture

The application is divided into several independent components. The main goal of this structure is to separate the application logic from the graphical interface and the program entry point.

```text
Project

├── Logic
│   └── Core application and game logic
│
├── GUI
│   └── Graphical user interface
│       └── Qt6
│
├── TestSuite
│   └── Set of tests for validating application correctness
│
├── logger
│   └── Logging utility reused across modules
│
└── main
    └── Application entry point
```

### Logic

The `Logic` module contains the core functionality of the application.

It is responsible for implementing the game mechanics, including:

* Arena and memory management
* RedCode instruction execution
* Program loading
* Program execution
* Memory manipulation
* Arithmetic and comparison operations
* Conditional and unconditional jumps
* Detecting terminated programs

The logic layer is independent from the graphical user interface.

### GUI

The `GUI` module is responsible for displaying the game and providing interaction with the user.

It uses **Qt6** for the graphical interface and communicates with the logic layer to display the current state of the arena and the running programs.


### main

The `main` component serves as the application entry point.

It is responsible for initializing the application and connecting the GUI and logic components.

Keeping the entry point separate from the rest of the application makes the project easier to maintain and allows the individual components to be built independently.

## Build System

The project uses **CMake** as its build system.

Each major component of the application has its own CMake configuration. This allows the GUI, logic, and main application to remain separated while still being combined into a single executable.

The `Logic` component is built as a static library:

```cmake
add_library(Logic STATIC
    ${SRC_FILES}
    ${HDR_FILES}
)
```

The `GUI` component is also built as a static library.

## Requirements

Before building the project, make sure the following dependencies are installed:

* **C++ compiler** supporting atleast C++ 20 standard
* **CMake**
* **Qt6**
* **Make** or another supported build tool

## Building

To build the application, create a separate build directory and invoke CMake from within it. Specify the path to the Qt gcc_64 installation using the CMAKE_PREFIX_PATH option:

```bash
mkdir build
cd build
cmake ../ -DCMAKE_PREFIX_PATH=/<Qt install location>/Qt/6.<qt6 version>/gcc_64
make
```

After a successful build, the resulting `main` executable should be available in the `build` directory.

The complete process can therefore be summarized as:

```bash
git clone <repository-url>
cd <project-directory>

mkdir build
cd build

cmake ../ -DCMAKE_PREFIX_PATH=/<Qt install location>/Qt/6.<qt6 version>/gcc_64
make
```

Then run the application with:

```bash
./main
```

## Project Goals

The main goals of the project are:

* Implement the core mechanics of the **Core Wars** game.
* Provide an execution environment for RedCode programs.
* Simulate a shared memory arena.
* Allow autonomous programs to compete against each other.
* Separate game logic from the graphical interface.
* Use Qt6 to provide a graphical representation of the game.
* Maintain a modular architecture using CMake.

## Technologies

* **C++**
* **CMake**
* **Qt6**
* **RedCode**
* **Model-View architecture**

