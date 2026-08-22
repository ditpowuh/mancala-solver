#include <emscripten/bind.h>

#include "board.hpp"
#include "solver.hpp"

using namespace emscripten;

EMSCRIPTEN_BINDINGS(mancala_module) {

  auto Array14 = value_array<std::array<int, 14>>("BoardArray");
  Array14.element(emscripten::index<0>());
  Array14.element(emscripten::index<1>());
  Array14.element(emscripten::index<2>());
  Array14.element(emscripten::index<3>());
  Array14.element(emscripten::index<4>());
  Array14.element(emscripten::index<5>());
  Array14.element(emscripten::index<6>());
  Array14.element(emscripten::index<7>());
  Array14.element(emscripten::index<8>());
  Array14.element(emscripten::index<9>());
  Array14.element(emscripten::index<10>());
  Array14.element(emscripten::index<11>());
  Array14.element(emscripten::index<12>());
  Array14.element(emscripten::index<13>());

  register_vector<int>("VectorInt");

  auto PlayerEnum = enum_<Player>("Player");

  PlayerEnum.value("FIRST_PLAYER", Player::First);
  PlayerEnum.value("SECOND_PLAYER", Player::Second);

  auto TurnResultEnum = enum_<TurnResult>("TurnResult");

  TurnResultEnum.value("NO_EXTRA_MOVE", TurnResult::NoExtraMove);
  TurnResultEnum.value("EXTRA_MOVE", TurnResult::ExtraMove);

  auto MancalaBoardClass = class_<MancalaBoard>("MancalaBoard");

  MancalaBoardClass.constructor<>();
  MancalaBoardClass.constructor<std::array<int, 14>>();
  // MancalaBoardClass.constructor<const MancalaBoard&>();

  MancalaBoardClass.class_property("FIRST_PLAYER_STORE_INDEX", &MancalaBoard::FIRST_PLAYER_STORE_INDEX);
  MancalaBoardClass.class_property("SECOND_PLAYER_STORE_INDEX", &MancalaBoard::SECOND_PLAYER_STORE_INDEX);

  MancalaBoardClass.property("board", &MancalaBoard::board);

  MancalaBoardClass.function("getPlayerFromPit", &MancalaBoard::get_player_from_pit);
  MancalaBoardClass.function("checkGameOver", &MancalaBoard::check_game_over);
  MancalaBoardClass.function("collectFinalPits", &MancalaBoard::collect_final_pits);
  MancalaBoardClass.function("getStoreOfPlayer", &MancalaBoard::get_store_of_player);
  MancalaBoardClass.function("makeMove", &MancalaBoard::make_move);
  MancalaBoardClass.function("getPossibleMoves", &MancalaBoard::get_possible_moves);

  auto EvaluationStruct = value_object<Evaluation>("Evaluation");
  EvaluationStruct.field("move", &Evaluation::move);
  EvaluationStruct.field("value", &Evaluation::value);

  auto MancalaSolverClass = class_<MancalaSolver>("MancalaSolver");
  MancalaSolverClass.constructor<Player>();
  MancalaSolverClass.property("solvingPlayer", &MancalaSolver::solving_player);
  MancalaSolverClass.function("evaluate", &MancalaSolver::evaluate);
  MancalaSolverClass.function("minimax", &MancalaSolver::minimax);
  MancalaSolverClass.function("findBestMove", &MancalaSolver::find_best_move);

}
