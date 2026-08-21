#include "board.hpp"

#include <numeric>
#include <stdexcept>
#include <algorithm>

MancalaBoard::MancalaBoard() {
  this->board = {4, 4, 4, 4, 4, 4, 0, 4, 4, 4, 4, 4, 4, 0};
}

MancalaBoard::MancalaBoard(std::array<int, 14> board) {
  this->board = board;
}

MancalaBoard::MancalaBoard(const MancalaBoard& other) {
  this->board = other.board;
}

Player MancalaBoard::get_player_from_pit(int pit_index, bool include_store) const {
  if (pit_index < 0 || pit_index > 13) {
    throw std::out_of_range("Cannot get player from pit - pit index is out of range");
  }

  if (pit_index == MancalaBoard::FIRST_PLAYER_STORE_INDEX) {
    if (!include_store) {
      throw std::invalid_argument("Cannot get player from pit - pit index is store");
    }
    return Player::First;
  }
  if (pit_index == MancalaBoard::SECOND_PLAYER_STORE_INDEX) {
    if (!include_store) {
      throw std::invalid_argument("Cannot get player from pit - pit index is store");
    }
    return Player::Second;
  }

  if (pit_index < MancalaBoard::FIRST_PLAYER_STORE_INDEX) {
    return Player::First;
  }
  if (pit_index > MancalaBoard::FIRST_PLAYER_STORE_INDEX && pit_index < MancalaBoard::SECOND_PLAYER_STORE_INDEX) {
    return Player::Second;
  }

  throw std::logic_error("Unreachable state has been reached in get_player_from_pit");
}

bool MancalaBoard::check_game_over() const {
  bool first_player_empty = true;
  for (int i = 0; i < 6; i++) {
    if (this->board[i] != 0) {
      first_player_empty = false;
      break;
    }
  }

  bool second_player_empty = true;
  for (int i = 7; i < 13; i++) {
    if (this->board[i] != 0) {
      second_player_empty = false;
      break;
    }
  }

  return first_player_empty || second_player_empty;
}

void MancalaBoard::collect_final_pits() {
  if (!this->check_game_over()) {
    return;
  }

  int first_player_remaining = std::accumulate(std::next(board.begin(), 0), std::next(board.begin(), 6), 0);
  int second_player_remaining = std::accumulate(std::next(board.begin(), 7), std::next(board.begin(), 13), 0);

  this->board[MancalaBoard::FIRST_PLAYER_STORE_INDEX] = this->board[MancalaBoard::FIRST_PLAYER_STORE_INDEX] + first_player_remaining;
  this->board[MancalaBoard::SECOND_PLAYER_STORE_INDEX] = this->board[MancalaBoard::SECOND_PLAYER_STORE_INDEX] + second_player_remaining;

  std::fill(std::next(board.begin(), 0), std::next(board.begin(), 6), 0);
  std::fill(std::next(board.begin(), 7), std::next(board.begin(), 13), 0);
}

int MancalaBoard::get_store_of_player(Player player) const {
  if (player == Player::First) {
    return MancalaBoard::FIRST_PLAYER_STORE_INDEX;
  }

  if (player == Player::Second) {
    return MancalaBoard::SECOND_PLAYER_STORE_INDEX;
  }

  throw std::logic_error("Unreachable state has been reached in get_store_of_player");
}

TurnResult MancalaBoard::make_move(int pit_index) {
  if (this->board[pit_index] == 0) {
    throw std::invalid_argument("Cannot make move - pit must be not empty");
  }

  int seeds = this->board[pit_index];
  this->board[pit_index] = 0;

  Player player = this->get_player_from_pit(pit_index);

  int player_store = this->get_store_of_player(player);
  int opponent_store = this->get_store_of_player(static_cast<Player>(3 - static_cast<int>(player)));

  int current_index = pit_index;
  while (seeds > 0) {
    current_index = (current_index + 1) % 14;

    if (current_index == opponent_store) {
      continue;
    }

    this->board[current_index] = this->board[current_index] + 1;
    seeds = seeds - 1;
  }

  if (current_index == player_store) {
    return TurnResult::ExtraMove;
  }

  std::array<int, 6> player_pits_indexes;
  if (player == Player::First) {
    player_pits_indexes = {0, 1, 2, 3, 4, 5};
  }
  if (player == Player::Second) {
    player_pits_indexes = {7, 8, 9, 10, 11, 12};
  }

  if (std::binary_search(std::begin(player_pits_indexes), std::end(player_pits_indexes), current_index) && this->board[current_index] == 1) {
    int opposite_index = 12 - current_index;
    if (this->board[opposite_index] > 0) {
      this->board[player_store] = this->board[player_store] + (this->board[current_index] + this->board[opposite_index]);

      this->board[current_index] = 0;
      this->board[opposite_index] = 0;
    }
  }

  return TurnResult::NoExtraMove;
}

std::vector<int> MancalaBoard::get_possible_moves(Player player) const {
  std::vector<int> possible_moves;

  if (player == Player::First) {
    for (int i = 0; i < 6; i++) {
      if (this->board[i] > 0) {
        possible_moves.push_back(i);
      }
    }
    return possible_moves;
  }

  if (player == Player::Second) {
    for (int i = 7; i < 13; i++) {
      if (this->board[i] > 0) {
        possible_moves.push_back(i);
      }
    }
    return possible_moves;
  }

  throw std::logic_error("Unreachable state has been reached in get_possible_moves");
}
