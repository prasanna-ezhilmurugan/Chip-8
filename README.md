# CHIP-8 Emulator

Welcome to the CHIP-8 Emulator project! This emulator is developed using C++ and SDL2. It aims to replicate the behavior of the CHIP-8, a simple, interpreted programming language used on some vintage computers and gaming systems.

## Table of Contents
0. [references]
1. [Introduction](#introduction)
2. [Features](#features)
3. [Installation](#installation)
4. [Usage](#usage)
5. [Controls](#controls)
6. [Contributing](#contributing)
7. [License](#license)
8. [Acknowledgments](#acknowledgments)

## Introduction
The CHIP-8 Emulator project aims to provide a functional and educational emulator for the CHIP-8 programming language. The emulator is written in C++ and utilizes the SDL2 library for rendering graphics and handling input.

## Features
- Accurate emulation of the CHIP-8 instruction set
- Support for loading and running CHIP-8 ROMs
- Graphical display using SDL2
- Keyboard input handling

## Installation

### Prerequisites
- C++ compiler (e.g., g++, clang++)
- SDL2 library

### Building from Source
1. Clone the repository:
    ```sh
    git clone https://github.com/prasanna-ezhilmurugan/Chip-8.git
    cd chip-8
    ```
2. Install SDL2 if not already installed. Refer to the SDL2 [installation guide](https://wiki.libsdl.org/Installation) for instructions.
3. Build the project using a Makefile or CMake:
    ```sh
    mkdir build
    cd build
    cmake ..
    ninja
    ```

## Usage
After building the project, you can run the emulator with a CHIP-8 ROM file as an argument:
```sh
./chip-8 path/to/rom.ch8
```

## Controls
The CHIP-8 uses a 16-key hexadecimal keypad. The controls are mapped to the following keys on your keyboard:

| CHIP-8 Key | Keyboard Key |
|------------|--------------|
| 1          | 1            |
| 2          | 2            |
| 3          | 3            |
| C          | 4            |
| 4          | Q            |
| 5          | W            |
| 6          | E            |
| D          | R            |
| 7          | A            |
| 8          | S            |
| 9          | D            |
| E          | F            |
| A          | Z            |
| 0          | X            |
| B          | C            |
| F          | V            |

## Contributing
Contributions are welcome! Feel free to open an issue or submit a pull request with your changes. Please ensure that your code adheres to the project's coding standards and includes appropriate tests.

## License
This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

## Acknowledgments
- The SDL2 library for providing the necessary tools to handle graphics and input.
- Various online resources and tutorials on CHIP-8 emulation and SDL2.

Thank you for checking out this project! If you have any questions or feedback, feel free to reach out.