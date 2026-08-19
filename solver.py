import math

from board import MancalaBoard

class MancalaSolver:
    def __init__(self, solvingPlayerNumber: int):
        if solvingPlayerNumber != 1 and solvingPlayerNumber != 2:
            raise ValueError("Cannot set player solving - player number must be 1 or 2")
        self.solvingPlayerNumber = solvingPlayerNumber

    def evaluate(self, board: MancalaBoard, playerNumber: int) -> int:
        if playerNumber != 1 and playerNumber != 2:
            raise ValueError("Cannot evaluate - player number must be 1 or 2")
        if playerNumber == MancalaBoard.FIRST_PLAYER:
            playerStore = board.board[MancalaBoard.FIRST_PLAYER_STORE_INDEX]
            opponentStore = board.board[MancalaBoard.SECOND_PLAYER_STORE_INDEX]

        if playerNumber == MancalaBoard.SECOND_PLAYER:
            playerStore = board.board[MancalaBoard.SECOND_PLAYER_STORE_INDEX]
            opponentStore = board.board[MancalaBoard.FIRST_PLAYER_STORE_INDEX]

        return playerStore - opponentStore

    def minimax(self, board: MancalaBoard, depth: int, playerNumber: int, alpha: int, beta: int):
        if board.checkGameOver():
            finalBoard = board.copy()
            finalBoard.collectFinalPits()
            return self.evaluate(finalBoard, self.solvingPlayerNumber)

        if depth == 0:
            return self.evaluate(board, self.solvingPlayerNumber)

        moves = board.getPossibleMoves(playerNumber)

        if len(moves) == 0:
            return self.evaluate(board, self.solvingPlayerNumber)

        if playerNumber == self.solvingPlayerNumber:
            bestValue = -math.inf
            for move in moves:
                nextMoveBoard = board.copy()
                extraMove = nextMoveBoard.makeMove(move)

                nextPlayerNumber = playerNumber if extraMove == MancalaBoard.EXTRA_MOVE else (playerNumber % 2) + 1

                value = self.minimax(nextMoveBoard, depth - 1, nextPlayerNumber, alpha, beta)
                bestValue = max(bestValue, value)

                alpha = max(alpha, bestValue)
                if beta <= alpha:
                    break

            return bestValue
        else:
            bestValue = math.inf
            for move in moves:
                nextMoveBoard = board.copy()
                extraMove = nextMoveBoard.makeMove(move)

                nextPlayerNumber = playerNumber if extraMove == MancalaBoard.EXTRA_MOVE else (playerNumber % 2) + 1

                value = self.minimax(nextMoveBoard, depth - 1, nextPlayerNumber, alpha, beta)
                bestValue = min(bestValue, value)

                beta = min(beta, bestValue)
                if beta <= alpha:
                    break

            return bestValue

    def findBestMove(self, board: MancalaBoard, depth: int) -> dict[str, int] | None:
        moves = board.getPossibleMoves(self.solvingPlayerNumber)
        if not moves:
            return None

        bestValue = -math.inf
        bestMove = moves[0]

        for move in moves:
            nextBoard = board.copy()
            extraMove = nextBoard.makeMove(move)

            nextPlayerNumber = self.solvingPlayerNumber if extraMove == MancalaBoard.EXTRA_MOVE else (self.solvingPlayerNumber % 2) + 1

            value = self.minimax(nextBoard, depth - 1, nextPlayerNumber, -math.inf, math.inf)

            if value > bestValue:
                bestValue = value
                bestMove = move

        return {"move": bestMove, "value": bestValue}
