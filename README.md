# mancala-solver

This project is a Kalah engine featuring two implementations in different languages.
It was originally intended to be used to solve for GamePigeon's Mancala game (which is Kalah), despite the repository being titled `mancala-solver`.

> Note that this is intended for Capture mode. Avalanche mode has yet to be accounted for and implemented.

The engine uses the Minimax algorithm with alpha-beta pruning, and was originally written in Python, before a C++ implementation was written.

A user interface for finding the best move was made using React and TypeScript, with the engine for that being in WASM, which was compiled from the C++ implementation with Emscripten.

All bindings for the Emscripten WASM have been implemented to be make everything accessible except for the copy constructor of `MancalaBoard`.

### Example code for usage
The following are example entry points, with a depth of 10 for the solver.
#### Python
```python
from board import MancalaBoard
from solver import MancalaSolver

if __name__ == "__main__":
    mancalaBoard = MancalaBoard()
    solver = MancalaSolver(1)

    result = solver.findBestMove(mancalaBoard, 10)
    print(result)
```
#### C++
```cpp
#include <iostream>

#include "board.hpp"
#include "solver.hpp"

int main() {
  MancalaBoard mancala_board = MancalaBoard();
  MancalaSolver solver = MancalaSolver(Player::First);

  Evaluation result = solver.find_best_move(mancala_board, 10);

  std::cout << "Best move index: " << result.move << std::endl;
  std::cout << "Value: " << result.value << std::endl;

  return 0;
}
```

### How to locally use the user interface
1. Ensure that you have Node.JS and Emscripten installed and setup.
2. Build the C++ code using the following command:
```
em++ board.cpp solver.cpp bindings.cpp --bind -O3 -sMODULARIZE -sEXPORT_ES6 -o mancala.mjs --emit-tsd mancala.d.ts
```
3. Move the outputs (`mancala.d.ts`, `mancala.mjs` & `mancala.wasm`) to `/interface/src/assets/WASM/`.
4. Run `npm run dev` in the `inferface` folder.
