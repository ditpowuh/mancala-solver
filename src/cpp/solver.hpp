#ifndef SOLVER_H
#define SOLVER_H

#include "board.hpp"

struct Evaluation {
  int move;
  int value;
};

class MancalaSolver {
  public:

    Player solving_player;

    MancalaSolver(Player solving_player);

    int evaluate(const MancalaBoard& board, Player player);
    int minimax(const MancalaBoard& board, int depth, Player player, int alpha, int beta);
    Evaluation find_best_move(const MancalaBoard& board, int depth);

};

#endif
