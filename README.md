# Arduino UNO R4 LED Matrix Game Engine

A lightweight **game/demo engine** for the **Arduino UNO R4 WiFi** (or Minima) built-in 12×8 LED matrix. The engine
provides a renderer, frame buffer, input system, and a passive-buzzer sound module — all designed so that new games or
visual demos can be dropped in with minimal boilerplate.

**Tetris** is included as the primary demo.

---

> [!NOTE]
> Created at November/December 2025

## Engine Features

- **Frame buffer** (`Frame`) with dirty-tracking — only pushes pixels to the matrix when something actually changed
- **Engine abstraction** (`EngineCore`) — implement `update()` and `handleInput()` to create a new game or effect
- **Game runner / state machine** — manages transitions between engines (e.g. game → game-over screen → restart)
- **Serial input handler** — maps keyboard characters to typed `Key` events via callback
- **Non-blocking passive buzzer sound system** — 32-note ring buffer, never stalls the game loop
- **Object system** (`ObjectCore`, `IRotatable`) — reusable renderable objects with optional rotation
- **Rendering effects** (`MorphEffect`) — pixel-morphing transition effect, ready to wire into any engine

---

## Tetris Demo

The included Tetris implementation showcases what the engine can do:

- All 7 standard tetrominoes (I, J, L, O, S, T, Z)
- Standard Tetris scoring (single / double / triple / Tetris)
- Progressive difficulty — fall speed increases every 10 lines cleared
- Soft drop & hard drop
- Piece rotation with basic wall-kick correction
- Pause / resume
- Animated game-over screen with pixel-wave effect
- Distinct buzzer sounds for every game event

---

## Hardware Requirements

| Component           | Details                                |
|---------------------|----------------------------------------|
| Board               | Arduino UNO R4 WiFi or Minima          |
| Built-in LED Matrix | 12 × 8 (used automatically)            |
| Passive Buzzer      | Connected to **pin 13** (configurable) |
| USB Cable           | For power and Serial input             |

---

## Getting Started

### 1. Clone / Download

```bash
git clone https://github.com/Dew-Demo-Projects/arduino-uno-r4-game-engine.git
```

### 2. Open in Arduino IDE or PlatformIO

The project is structured for **PlatformIO** (recommended) but can also be opened in the Arduino IDE.  
Make sure the following library is installed:

- **Arduino_LED_Matrix** (bundled with the UNO R4 board package)

### 3. Configure the Buzzer Pin

In `main.cpp`, the second argument to `TetrisGameRunner` is the buzzer pin:

```cpp
TetrisGameRunner gameRunner(matrix, 13); // change 13 to your pin
```

### 4. Upload & Play

Upload the sketch, then open the **Serial Monitor** at **9600 baud** to send control input.

> [!WARNING]
> The game will not start until the Serial Monitor is opened!

---

## Tetris Controls

| Key     | Action                   |
|---------|--------------------------|
| `A`     | Move left                |
| `D`     | Move right               |
| `S`     | Soft drop                |
| `Q`     | Rotate counter-clockwise |
| `E`     | Rotate clockwise         |
| `Space` | Hard drop                |
| `P`     | Pause / Resume           |
| Any key | Restart after game over  |

---

## Scoring (Tetris)

| Lines Cleared | Points             |
|---------------|--------------------|
| 1             | 100 × level        |
| 2             | 300 × level        |
| 3             | 500 × level        |
| 4 (Tetris!)   | 800 × level        |
| Soft drop     | +1 per row         |
| Hard drop     | +2 per row dropped |

Level increases every 10 lines. Fall speed is capped at a minimum of 100 ms per step.

---

## Project Structure

```
.
├── main.cpp                         # Entry point – setup() and loop()
└── UnoR4Matrix/
    ├── Core.h                       # Global constants (Width=12, Height=8)
    ├── Components/
    │   ├── Frame.h / .cpp           # 12×8 pixel frame buffer with dirty-tracking
    │   └── Position.h / .cpp        # 2D position (X, Y)
    ├── Engines/
    │   ├── EngineCore.h / .cpp      # Abstract base engine (update / handleInput)
    │   └── TetrisEngine/
    │       ├── TetrisEngine.h / .cpp        # Tetris game logic
    │       ├── TetrisGameOverEngine.h       # Animated game-over screen engine
    │       ├── TetrisGameRunner.h           # State machine (PLAYING ↔ GAME_OVER)
    │       └── GameInfoPrinter.h            # Serial stats/debug output
    ├── Input/
    │   └── InputHandler.h / .cpp    # Serial-based keyboard input with callbacks
    ├── Objects/
    │   ├── ObjectCore.h / .cpp      # Base renderable object with shape & position
    │   ├── Interfaces/
    │   │   └── IRotatable.h         # Rotation interface (Rotate90Left / Right)
    │   └── Tetris/
    │       ├── TetrisBlock.h / .cpp # Tetromino with rotation logic
    │       ├── Bricks.h / .cpp      # Concrete block classes (I/J/L/O/S/T/Z)
    │       └── TetrisBlockFactory.h # Random block spawning
    ├── Renderer/
    │   ├── Renderer.h / .cpp        # Dirty-frame renderer → Arduino_LED_Matrix
    │   └── RenderingEffects/
    │       └── MorphEffect.h / .cpp # Pixel-morphing transition effect
    └── Sound/
        ├── ISound.h                 # Sound interface
        ├── Note.h                   # Note struct (frequency + duration)
        ├── SoundEvent.h             # Enum of named sound events
        ├── PassiveBuzzerSound.h/.cpp# Non-blocking buzzer driver with ring buffer
        └── Patterns/                # Note sequences for each sound event
            ├── Move.h, Rotate.h, SoftDrop.h
            ├── HardDrop.h, LineClear.h
            ├── LevelUp.h, Pause.h, GameOver.h
```

---

## Architecture Overview

```
loop()
  └─► TetrisGameRunner::run()
        ├─► Renderer::update()   ← calls EngineCore::update() → returns Frame
        ├─► Renderer::render()   ← pushes frame to LED matrix (only if dirty)
        └─► state machine        ← switches between TetrisEngine / TetrisGameOverEngine
```

The renderer only transmits a new bitmap to the matrix when the current frame differs from the previous one. The sound
system ticks via a non-blocking `update()` call inside each engine's `update()`, so audio never stalls the game loop.

---

## Adding a New Game or Demo

1. Create a class that extends `EngineCore`
2. Implement `update()` — build and return a `Frame`
3. Implement `handleInput()` — react to `Input::Key` events
4. Instantiate it in a `GameRunner` (or replace `TetrisGameRunner` with your own state machine)

The renderer, input system, and sound module are all reusable without modification.

---

## Known Limitations

- **Serial required to start**: `begin()` blocks on `while (!Serial)`, so the board won't run standalone (e.g.
  battery-powered) without removing that line
- **Serial-only input**: No physical button support, though extending `InputHandler` is straightforward
- **No next-piece preview**: The 12×8 display doesn't leave room for a sidebar
- **MorphEffect not wired in**: The transition effect class exists but is not currently called from any runner

---

