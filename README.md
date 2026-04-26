## Overview
This project appears to be a command-line Lua-like interpreter written in C/C++. The interpreter supports custom language features such as the "karol" type and various system functions like sleeping.

## Features
- Command-line execution of scripts written in a Lua-like syntax.
- Support for a custom "karol" type with methods for manipulation (e.g., `new`, `get`, `setp`, `turnl`).
- System functions for controlling the execution environment (`msleep`, `usleep`, `nsleep`).

## Project Structure
```
<Project>/
├── build/              # .exe files produced by Main.c
├── bin/                # .so / .dll produced by *.c in libs
├── libs/               # *.c for bin
├── lib/                # librarys for my own languages
├── code/               # scripts from my custom languages for example .rex, .ll, .omml
├── data/               # Datafile for example .txt or dumped files
├── assets/             # images and sound files
├── src/                # src code
│   ├── Main.c          # Entry point
│   └── *.h             # stand alone Header-based C-files, without *.c files that implement it
├── Makefile.linux      # Linux Build configuration
├── Makefile.windows    # Windows Build configuration
└── README.md           # This file
```

### Prerequisites
- C/C++ Compiler and Debugger (GCC, Clang)
- Make utility
- Standard development tools

## Build & Run
### Build Process
To build the project for Linux:
```sh
cd <Project>
make -f Makefile.linux all
```

For Windows:
```sh
cd <Project>
make -f Makefile.windows all
```

To clean and rebuild:
```sh
make -f Makefile.(os) clean
make -f Makefile.(os) all
```

### Execution
To execute the built binary:
```sh
make -f Makefile.(os) exe
```