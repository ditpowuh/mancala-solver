#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <array>

enum class Player {
  First = 1,
  Second = 2
};

enum class TurnResult {
  NoExtraMove,
  ExtraMove
};

class MancalaBoard {
  public:

    inline static constexpr int FIRST_PLAYER_STORE_INDEX = 6;
    inline static constexpr int SECOND_PLAYER_STORE_INDEX = 13;

    std::array<int, 14> board;

    MancalaBoard();
    MancalaBoard(std::array<int, 14> board);
    MancalaBoard(const MancalaBoard& other);

    Player get_player_from_pit(int pit_index, bool include_store = false) const;
    bool check_game_over() const;
    void collect_final_pits();
    int get_store_of_player(Player player) const;
    TurnResult make_move(int pit_index);
    std::vector<int> get_possible_moves(Player player) const;

};

#endif
