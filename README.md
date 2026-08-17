*This project has been created as part of the 42 curriculum by moabed, melshata.*

# Cub3D — 3D Raycasting Engine

A dynamic 3D raycasting engine written in C using **MiniLibX**, inspired by the seminal 1992 game *Wolfenstein 3D*. This project explores graphical rendering, linear algebra, DDA (Digital Differential Analysis), event-driven programming, and rigorous map parsing.

---

## Table of Contents
1. [Description](#description)
2. [Instructions](#instructions)
   - [Prerequisites](#prerequisites)
   - [Compilation](#compilation)
   - [Execution](#execution)
   - [Controls](#controls)
3. [Execution Flow in Every Scenario](#execution-flow-in-every-scenario)
   - [1. CLI Arguments & File Verification](#1-cli-arguments--file-verification)
   - [2. Scene Configuration & Header Parsing](#2-scene-configuration--header-parsing)
   - [3. Map Validation & Enclosure Checking](#3-map-validation--enclosure-checking)
   - [4. Vector & Camera Plane Initialization](#4-vector--camera-plane-initialization)
   - [5. Graphic Engine & Texture Loading](#5-graphic-engine--texture-loading)
   - [6. Raycasting & DDA Rendering Cycle](#6-raycasting--dda-rendering-cycle)
   - [7. Movement, Wall Collision & Sliding](#7-movement-wall-collision--sliding)
   - [8. Teardown & Clean Exit](#8-teardown--clean-exit)
4. [Testing Suite](#testing-suite)
5. [Resources & AI Usage](#resources--ai-usage)

---

## Description

**Cub3D** renders a 3D first-person perspective inside a maze-like grid defined by a `.cub` configuration file. The engine casts rays across a 2D grid representation to calculate the distances to surfaces, determining the height and texture alignment of walls projected onto a 2D pixel buffer.

### Key Capabilities:
- **Fast DDA Raycasting**: Ray marching algorithm with wall boundary calculation.
- **Directional Texture Mapping**: Distinct textures for North, South, East, and West wall faces.
- **Half-Plane Background Rendering**: Smooth ceiling and floor coloring with customizable RGB values.
- **Axis-Independent Wall Collision**: Player slides along walls rather than stopping abruptly upon collision.
- **Strict Error Handling**: Validates closed borders, space leakage, unique player position, and texture paths.

---

## Instructions

### Prerequisites
On Linux (Ubuntu/Debian), ensure X11 development headers and MinilibX dependencies are installed:
```bash
sudo apt-get update
sudo apt-get install -y gcc make xorg libx11-dev libxext-dev libbsd-dev
```

### Compilation
The project includes a `Makefile` that compiles all sources into an `obj/` directory using strict compiler flags (`-Wall -Wextra -Werror`):

```bash
# Compile cub3D executable
make

# Clean object files
make clean

# Full clean (removes objects and executable)
make fclean

# Recompile from scratch
make re
```

### Execution
Pass a valid `.cub` scene file as the sole argument:
```bash
./cub3D tests/maps/valid/standard_box.cub
```

### Controls

| Key / Action | Function |
| :--- | :--- |
| <kbd>W</kbd> / <kbd>▲</kbd> | Move forward in direction of view |
| <kbd>S</kbd> / <kbd>▼</kbd> | Move backward |
| <kbd>A</kbd> | Strafe left (orthogonal to view direction) |
| <kbd>D</kbd> | Strafe right (orthogonal to view direction) |
| <kbd>◀</kbd> | Rotate camera left |
| <kbd>▶</kbd> | Rotate camera right |
| <kbd>ESC</kbd> | Exit program cleanly |
| **Window Close (`X`)** | Destroy display and exit cleanly |

---

## Execution Flow in Every Scenario

The program execution is divided into distinct lifecycle phases:

```
                  ┌────────────────────────┐
                  │         main()         │
                  └───────────┬────────────┘
                              │
             ┌────────────────┴────────────────┐
             ▼                                 ▼
   [Invalid Input / Map]             [Valid Map File]
   • Print "Error\n<msg>"            • Extract Textures & RGB
   • Free allocated memory           • Validate 4-Way Wall Enclosure
   • exit(1)                         • Initialize MLX Display & Textures
                                     • Enter mlx_loop() Raycasting Engine
                                               │
                                               ▼
                                     [Player Inputs (WASD / Rotate)]
                                     • Update position with wall sliding
                                     • Re-project rays (DDA) & draw frame
                                               │
                                               ▼
                                     [ESC or Window Close Button]
                                     • Destroy images, window & display
                                     • Free all structures
                                     • exit(0)
```

---

### 1. CLI Arguments & File Verification
* **Scenario A (Valid invocation)**: `ac == 2` and `av[1]` ends with `.cub`. The file descriptor is opened via `open(av[1], O_RDONLY)`.
* **Scenario B (Invalid invocation)**:
  - If `ac != 2`, triggers `handle_exit(cub, ERR_ARG_COUNT, 1)` -> Prints `Error\nUsage: ./cub3D map.cub`.
  - If extension != `.cub`, triggers `ERR_FILE_EXT` -> Prints `Error\nInvalid file extension (.cub required)`.
  - If file does not exist or has no read permissions, `read_file` triggers `ERR_FILE_OPEN` -> Prints `Error\nError opening map file`.

---

### 2. Scene Configuration & Header Parsing
The configuration file is read line-by-line via `get_next_line`:
* **Texture Identifiers (`NO`, `SO`, `WE`, `EA`)**:
  - The path following each identifier is stored.
  - If duplicate identifiers are encountered, `ERR_DUPLICATE_ELEMENT` is raised.
  - In `mini_parse()`, each texture path is opened via `open()` to ensure existence before launching graphics.
* **Colors (`F`, `C`)**:
  - Comma-separated strings are split into R, G, and B components.
  - Each component is verified to be numeric and within range `[0, 255]`.
  - Out-of-range or malformed values raise `ERR_COLOR_RANGE`.

---

### 3. Map Validation & Enclosure Checking
Once all 6 scene elements are acquired (`data_count == 6`), lines are treated as the map grid:
1. **Character Validation**: Ensures only `'0'`, `'1'`, `' '`, and player characters (`'N'`, `'S'`, `'E'`, `'W'`) are present.
2. **Player Count**: Exactly **one** player must exist. 0 or >1 players raises `ERR_PLAYER_COUNT` (`"wanna party or play?"`). Player coordinate `(x, y)` and direction orientation are stored.
3. **Boundary Enclosure (4-Way Perimeter Check)**:
   - For every `'0'` or player cell, adjacent cells (North, South, East, West) must not be empty or out of bounds.
   - Spaces (`' '`) must never be adjacent to walkable floor cells (`'0'`) or the player.
   - Any gap raises `ERR_MAP_OPEN` (`"Error, map is open"`).

---

### 4. Vector & Camera Plane Initialization
When map validation succeeds, `init_player_vectors()` sets up 2D Cartesian vectors:
* **Position Vector**: `pos = (int_position.x + 0.5, int_position.y + 0.5)` (centered in starting tile).
* **Direction (`dir`) & Camera Plane (`plane`) Vectors**:
  - **North (`N`)**: `dir = (0.0, -1.0)`, `plane = (0.66, 0.0)`
  - **South (`S`)**: `dir = (0.0, 1.0)`, `plane = (-0.66, 0.0)`
  - **West (`W`)**: `dir = (-1.0, 0.0)`, `plane = (0.0, -0.66)`
  - **East (`E`)**: `dir = (1.0, 0.0)`, `plane = (0.0, 0.66)`

---

### 5. Graphic Engine & Texture Loading
1. `mlx_init()` initializes the connection to the X-Window server.
2. `mlx_new_window()` opens a `1920x1080` window.
3. `mlx_new_image()` creates the primary frame buffer.
4. `load_images()` loads all four wall textures using `mlx_xpm_file_to_image()`, storing dimensions and data addresses:
   - `walls[0]` = North (`NO`)
   - `walls[1]` = South (`SO`)
   - `walls[2]` = West (`WE`)
   - `walls[3]` = East (`EA`)
5. Event hooks (`DestroyNotify`, `KeyPress`, `mlx_loop_hook`) are registered, and `mlx_loop()` is entered.

---

### 6. Raycasting & DDA Rendering Cycle
On every frame tick (`game_loop`):
1. **Background**: `render_background()` fills top half of the buffer with Ceiling color (`C`) and bottom half with Floor color (`F`).
2. **Ray Generation**: For each screen column $x \in [0, \text{WIDTH})$:
   - Camera X: $\text{camera\_x} = 2x / \text{WIDTH} - 1$.
   - Ray Direction: $\vec{ray\_dir} = \vec{dir} + \vec{plane} \times \text{camera\_x}$.
   - Delta Distance: $\Delta_x = |1 / \text{ray\_dir}_x|$, $\Delta_y = |1 / \text{ray\_dir}_y|$.
3. **DDA Stepping**: Advances through the map grid tile-by-tile until hitting a wall cell (`'1'`), tracking whether a vertical (`side = 0`) or horizontal (`side = 1`) face was struck.
4. **Perpendicular Wall Distance**:
   $$\text{perp\_wall\_dist} = \begin{cases} \text{side\_dist}_x - \Delta_x & \text{if } side = 0 \\ \text{side\_dist}_y - \Delta_y & \text{if } side = 1 \end{cases}$$
5. **Wall Projection & Texture Mapping**:
   - Projected line height: $\text{line\_height} = \text{HEIGHT} / \text{perp\_wall\_dist}$.
   - Exact wall hit coordinate: $\text{wall\_x}$ determines column in the texture ($\text{tex\_x}$).
   - The selected texture column is scaled and painted to the screen buffer via `draw_wall_stripe()`.
6. `mlx_put_image_to_window()` pushes the complete rendered frame to the display.

---

### 7. Movement, Wall Collision & Sliding
When a movement key is pressed (`handle_keypress`):
* **Forward/Backward**: Moves along $\pm \vec{dir} \times \text{MOVE\_SPEED}$.
* **Strafe Left/Right**: Moves along $\pm (\text{dir}_y, -\text{dir}_x) \times \text{MOVE\_SPEED}$.
* **Wall Sliding**: Collision is evaluated separately on the X and Y axes using a collision margin ($0.15$). If moving diagonally into a corner or wall, the player slides along the unblocked axis.
* **Rotation**: Applies 2D rotation matrix to $\vec{dir}$ and $\vec{plane}$:
  $$\begin{bmatrix} x' \\ y' \end{bmatrix} = \begin{bmatrix} \cos(\theta) & -\sin(\theta) \\ \sin(\theta) & \cos(\theta) \end{bmatrix} \begin{bmatrix} x \\ y \end{bmatrix}$$

---

### 8. Teardown & Clean Exit
When exiting via <kbd>ESC</kbd> or the window close button:
1. `clean_mlx()` destroys all 4 texture images, the frame buffer image, the window, and closes the X11 display connection via `mlx_destroy_display()`.
2. `free_cub()` deallocates texture paths, floor/ceiling strings, and 2D arrays (`splitted_lines`).
3. `exit(0)` terminates the process cleanly with zero memory leaks.

---

## Testing Suite

An automated test suite is located in `tests/` and can be run with:

```bash
./tests/run_tests.sh
```

### Coverage (46 Test Cases):
* **CLI & Arguments (8 tests)**: Missing arguments, extra arguments, non-existent files, directories, empty files, malformed file extensions.
* **Textures (6 tests)**: Missing textures, duplicate textures, invalid identifiers, unreadable file paths.
* **Colors (7 tests)**: Out of range (>255, negative), non-numeric characters, missing/extra RGB components, duplicate colors.
* **Player (4 tests)**: 0 players, multiple players, player placed out-of-bounds, player adjacent to void.
* **Borders (6 tests)**: Open North, South, East, and West walls, holes in perimeter, floor touching space.
* **Characters (3 tests)**: Invalid characters in map matrix.
* **Valid Maps (12 tests)**: Minimal 3x3, standard rooms, all 4 orientations (N/S/E/W), irregular shapes, boundary RGB values, mazes.

---

## Resources & AI Usage

### References & Documentation
- **Lode's Computer Graphics Tutorial**: [Raycasting Tutorial](https://lodev.org/cgtutor/raycasting.html) — Foundation for 2D DDA raycasting, camera plane mathematics, and vertical texture scaling.
- **42 School Subject**: `cub3D.pdf` specifications.
- **MiniLibX Documentation**: [Harm-Smits MiniLibX Guide](https://harm-smits.github.io/42docs/libs/minilibx) — Event hooks, image buffers, and X11 color encoding.

### AI Usage Disclosure
Artificial Intelligence (Antigravity Assistant) was used during this project for the following specific tasks:
1. **Architectural Review & Refactoring**: Audited execution flow to eliminate redundant render cycles, isolate dead legacy code, and modularize functions to adhere strictly to the 42 Norminette limit (maximum 5 functions per `.c` file and $\le 25$ lines per function).
2. **Automated Test Suite Creation**: Designed and generated 42+ automated test maps (`tests/maps/`) and an ANSI color-coded test runner (`tests/run_tests.sh`) to validate all edge cases.
3. **Build Configuration**: Configured `Makefile` to isolate object files into an `obj/` directory and generated language server configurations (`compile_flags.txt` and `.vscode/c_cpp_properties.json`).
4. **Documentation**: Assisted in structuring this comprehensive `README.md` and flow breakdown.