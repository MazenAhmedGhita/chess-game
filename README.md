# CC212SGL Chess Game

A console + graphical chess game implemented in **C** using the **CC212SGL** graphics library (commonly used in introductory programming/graphics courses).

This project implements most standard chess rules including:

- All piece movements (pawn, rook, knight, bishop, queen, king)
- Special moves (pawn double step, captures)
- Check & Checkmate detection (basic implementation)
- Piece capture & dead pieces display
- Turn system (White ↔ Black)
- Simple keyboard navigation & selection
- Sound effects (move & capture)

**Note:** The check/checkmate logic is partially implemented and contains known bugs/limitations (see below).

## Features

- Classic 8×8 chessboard rendered with CC212SGL
- Keyboard controls (WASD / arrow-like movement + Space to select/move)
- Visual highlighting of legal moves
- Captured pieces displayed on the sides
- Basic check detection
- Attempted checkmate & stalemate awareness (incomplete)
- Sound effects (`move-self.wav`, `capture.wav`, background music commented out)

## Current Status (March 2026)

This is a **work-in-progress student project**.

### Working well

- Piece movement rules for all pieces
- Pawn first move (double step)
- Capture logic
- Turn alternation
- Graphical board & piece rendering
- Keyboard square selection

### Known major issues / incomplete parts

- **Check & Checkmate logic is unreliable**  
  → many false positives/negatives  
  → king safety checking (`kingrook`, `kingbishop`, `safty`, `checksaftymove`) has logical errors  
  → `test()`, `piecekill()`, `kingmove()` functions are buggy / incomplete
- Pinning pieces is **not** correctly handled
- Discovered checks after move are **not** prevented
- Castling, en passant and promotion are **not implemented**
- Stalemate / draw by repetition / 50-move rule → **not implemented**
- Some array boundary bugs (especially in safety checking functions)
- Performance issues when checking many positions (heavy computation)

## Controls

| Key       | Action                              |
|-----------|-------------------------------------|
| `W` `A` `S` `D` | Move cursor up/left/down/right   |
| `w` `a` `s` `d` | Small step movement (fine tuning) |
| `Space`         | Select piece / Make move          |
| (no mouse support yet) |                             |

## Requirements

- Windows OS (uses `<windows.h>`, `conio.h`, `PlaySound`)
- CC212SGL graphics library & header (`CC212SGL.h`, `CC212SGL.lib`)
- Microsoft Visual Studio (or compatible compiler that supports `#pragma comment(lib, ...)`)
- Sound files: `move-self.wav`, `capture.wav` (place them in executable folder)

## How to Build & Run

1. Open Visual Studio
2. Create new **Empty Project** (C++)
3. Add all `.c` / `.cpp` files to project
4. Add `CC212SGL.lib` to linker input
5. Make sure `CC212SGL.h` is in include path
6. Put all image files (`board0.png`, `white0.png` … `black5.png`) and sound files in the same folder as `.exe`
7. Build → Run

## Project Structure
