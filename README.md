<h1 align="center">cub3D</h1>

<p align="center">
  <em>My first RayCaster with miniLibX.</em><br>
  A Wolfenstein 3D-style 3D engine written in C as part of the 42 curriculum.
</p>

<p align="center">
  <img alt="Language" src="https://img.shields.io/badge/language-C-blue">
  <img alt="Norm" src="https://img.shields.io/badge/norminette-passing-brightgreen">
  <img alt="42" src="https://img.shields.io/badge/school-42-black">
  <img alt="Bonus" src="https://img.shields.io/badge/bonus-done-success">
</p>

---

## Table of Contents

- [About](#about)
- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [Controls](#controls)
- [Map Format](#map-format)
- [Project Structure](#project-structure)
- [How It Works](#how-it-works)
- [Error Handling](#error-handling)
- [Authors](#authors)
- [Acknowledgments](#acknowledgments)

---

## About

**cub3D** is a small 3D game engine inspired by the legendary *Wolfenstein 3D*. It uses **raycasting** to render a first-person view of a maze from a 2D map, using the **MiniLibX** graphics library.

The project is a deep dive into graphics programming, trigonometry, parsing and clean memory management.

## Features

### Mandatory

- Real-time **raycasting** rendering with the **DDA algorithm**
- Different **wall textures** depending on orientation (North, South, East, West)
- Configurable **floor and ceiling colors**
- Smooth **player movement** and **camera rotation**
- Strict **map parsing and validation** (closed map, valid characters, single player spawn)
- Clean window management (`ESC` and the window close button)

### Bonus

- **Doors** that can be opened and closed
- **Menu screen** before the game starts
- **Animated sprites** (`p0` to `p3` textures)
- Custom **garbage collector** (`gc.c`) for safe memory management

## Installation

### Requirements

- A UNIX-like system (Linux)
- `gcc` or `cc`
- `make`
- MiniLibX dependencies (X11 and Xext)

On Debian/Ubuntu:

```bash
sudo apt-get install build-essential xorg libxext-dev libx11-dev libbsd-dev
```

### Build

```bash
git clone https://github.com/mohamedzeouaoui/cub3d.git
cd cub3d
make
```

### Makefile rules

| Rule          | Description                              |
|---------------|------------------------------------------|
| `make`        | Compile the project                      |
| `make clean`  | Remove object files                      |
| `make fclean` | Remove object files and the executable   |
| `make re`     | Recompile from scratch                   |

## Usage

```bash
./cub3D maps/<map_name>.cub
```

Example:

```bash
./cub3D maps/map.cub
```

## Controls

| Key            | Action                  |
|----------------|-------------------------|
| `W` / `S`      | Move forward / backward |
| `A` / `D`      | Strafe left / right     |
| `←` / `→`      | Rotate the camera       |
| `ESC`          | Quit the game           |

## Map Format

The map is described in a `.cub` file made of two parts: the **configuration** and the **map grid**.

```text
NO ./wall_north.xpm
SO ./wall_south.xpm
WE ./wall_west.xpm
EA ./wall_east.xpm

F 220,100,0
C 225,30,0

        1111111111111111111111111
        1000000000110000000000001
        1011000001110000000000001
        1001000000000000000000001
111111111011000001110000000000001
100000000011000001110111111111111
11110111111111011100000010001
11110111111111011101010010001
11000000110101011100000010001
10000000000000001100000010001
10000000000000001101010010001
11000001110101011111011110N0111
11110111 1110101 101111010001
11111111 1111111 111111111111
```

| Identifier | Meaning                          |
|------------|----------------------------------|
| `NO`       | Path to the north wall texture   |
| `SO`       | Path to the south wall texture   |
| `WE`       | Path to the west wall texture    |
| `EA`       | Path to the east wall texture    |
| `F`        | Floor color in `R,G,B`           |
| `C`        | Ceiling color in `R,G,B`         |

### Map characters

| Char        | Meaning                                         |
|-------------|-------------------------------------------------|
| `0`         | Empty space (walkable)                          |
| `1`         | Wall                                            |
| `N S E W`   | Player start position and facing direction      |
| `D`         | Door (bonus)                                    |
| ` ` (space) | Void outside the map                            |

The map must be **closed** (surrounded by walls) and contain **exactly one** player spawn.

## Project Structure

```text
cub3d/
├── Makefile
├── cub3d.h               # Structures, prototypes and macros
├── main.c                # Entry point and game loop
├── error.c               # Error messages and exit handling
├── gc.c                  # Garbage collector
├── gc_strdup.c           # Garbage-collected strdup
├── parsing/              # .cub file parsing and map validation
├── raycasting/           # Raycasting, rendering and player movement
├── maps/                 # Example maps
├── libft/                # Custom C library
├── get_next_line/        # Line-by-line file reading
├── wall_north.xpm        # Wall textures
├── wall_south.xpm
├── wall_east.xpm
├── wall_west.xpm
├── door.xpm              # Door texture (bonus)
├── menu.xpm              # Menu screen (bonus)
└── p0.xpm ... p3.xpm     # Animated sprite frames (bonus)
```

## How It Works

1. **Parse**: the `.cub` file is read with `get_next_line`, textures and colors are loaded, and the map grid is validated (closed borders, valid characters, one spawn point).
2. **Init**: the MiniLibX window is created and the XPM textures are loaded into images.
3. **Cast rays**: for each vertical column of the screen, a ray is sent from the player's position using the **DDA algorithm** until it hits a wall.
4. **Compute the wall slice**: the distance to the wall gives the height of the vertical line to draw. The perpendicular distance is used to avoid the fisheye effect.
5. **Texture mapping**: the exact hit position on the wall selects the texture column, and the wall side selects which texture to use.
6. **Draw**: the ceiling, the textured wall slice and the floor are written into an image buffer, then pushed to the window in one go.
7. **Handle events**: key presses update the player's position and angle, with collision checks against walls (and closed doors).

## Error Handling

On an invalid file or map, the program prints `Error` followed by a message and exits cleanly:

```text
Error
Map is not closed
```

Cases handled include: wrong arguments, wrong file extension, missing or invalid textures, bad color values, duplicate or missing identifiers, invalid characters, unclosed map, and missing or multiple player spawns.

All allocated memory is released on exit through the garbage collector.

## Authors

- **Mohamed Zeouaoui**: [@mohamedzeouaoui](https://github.com/mohamedzeouaoui)
- **N1ghtm4r3e**: [@N1ghtm4reee](https://github.com/N1ghtm4reee)

## Acknowledgments

- The 42 network for the subject and the peer-learning environment
- [Lode's Computer Graphics Tutorial: Raycasting](https://lodev.org/cgtutor/raycasting.html)
- The MiniLibX documentation
