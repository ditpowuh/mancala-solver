#include "solver.hpp"

#include <stdexcept>
#include <limits>

MancalaSolver::MancalaSolver(Player solving_player) {
  this->solving_player = solving_player;
}

int MancalaSolver::evaluate(const MancalaBoard& board, Player player) {
  int player_store;
  int opponent_store;

  if (player == Player::First) {
    player_store = board.board[MancalaBoard::FIRST_PLAYER_STORE_INDEX];
    opponent_store = board.board[MancalaBoard::SECOND_PLAYER_STORE_INDEX];
  }
  if (player == Player::Second) {
    player_store = board.board[MancalaBoard::SECOND_PLAYER_STORE_INDEX];
    opponent_store = board.board[MancalaBoard::FIRST_PLAYER_STORE_INDEX];
  }

  return player_store - opponent_store;
}

int MancalaSolver::minimax(const MancalaBoard& board, int depth, Player player, int alpha, int beta) {
  if (board.check_game_over()) {
    MancalaBoard final_board = MancalaBoard(board);
    final_board.collect_final_pits();
    return this->evaluate(final_board, this->solving_player);
  }

  if (depth == 0) {
    return this->evaluate(board, this->solving_player);
  }

  std::vector<int> moves = board.get_possible_moves(player);

  if (moves.size() == 0) {
    return this->evaluate(board, this->solving_player);
  }

  if (player == solving_player) {
    int best_value = std::numeric_limits<int>::min();
    for (const int& move : moves) {
      MancalaBoard next_move_board = MancalaBoard(board);

      TurnResult extra_move = next_move_board.make_move(move);
      Player next_player = extra_move == TurnResult::ExtraMove ? player : static_cast<Player>(3 - static_cast<int>(player));

      int value = this->minimax(next_move_board, depth - 1, next_player, alpha, beta);
      best_value = std::max(best_value, value);

      alpha = std::max(alpha, best_value);
      if (beta <= alpha) {
        break;
      }
    }
    return best_value;
  }
  else {
    int best_value = std::numeric_limits<int>::max();
    for (const int& move : moves) {
      MancalaBoard next_move_board = MancalaBoard(board);

      TurnResult extra_move = next_move_board.make_move(move);
      Player next_player = extra_move == TurnResult::ExtraMove ? player : static_cast<Player>(3 - static_cast<int>(player));

      int value = this->minimax(next_move_board, depth - 1, next_player, alpha, beta);
      best_value = std::min(best_value, value);

      beta = std::min(beta, best_value);
      if (beta <= alpha) {
        break;
      }
    }
    return best_value;
  }
}

Evaluation MancalaSolver::find_best_move(const MancalaBoard& board, int depth) {
  std::vector<int> moves = board.get_possible_moves(this->solving_player);
  if (moves.size() == 0) {
    throw std::invalid_argument("Cannot find best move - no possible moves available");
  }

  int best_value = std::numeric_limits<int>::min();
  int best_move = -1;

  for (const int& move : moves) {
    MancalaBoard next_board = MancalaBoard(board);

    TurnResult extra_move = next_board.make_move(move);
    Player next_player = extra_move == TurnResult::ExtraMove ? this->solving_player : static_cast<Player>(3 - static_cast<int>(this->solving_player));

    int value = this->minimax(next_board, depth - 1, next_player, std::numeric_limits<int>::min(), std::numeric_limits<int>::max());

    if (value > best_value) {
      best_value = value;
      best_move = move;
    }
  }

  return {best_move, best_value};
}
