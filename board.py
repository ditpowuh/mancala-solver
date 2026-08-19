class MancalaBoard:
    FIRST_PLAYER: int = 1
    SECOND_PLAYER: int = 2

    FIRST_PLAYER_STORE_INDEX: int = 6
    SECOND_PLAYER_STORE_INDEX: int = 13

    EXTRA_MOVE: bool = True
    NO_EXTRA_MOVE: bool = False

    def __init__(self, board: list[int] | None = None):
        if board is not None:
            self.board = list(board)
            if len(self.board) != 14:
                raise ValueError("Cannot set board - board must contain exactly 14 values")
            if not all(item >= 0 for item in self.board):
                raise ValueError("Cannot set board - negative value inside board")
        else:
            self.board = [4] * 14
            self.board[MancalaBoard.FIRST_PLAYER_STORE_INDEX] = 0
            self.board[MancalaBoard.SECOND_PLAYER_STORE_INDEX] = 0

    def __iter__(self):
        return iter(self.board)

    def __str__(self):
        labels = ["P1"] * 6 + ["S1"] + ["P2"] * 6 + ["S2"]

        columns = [(str(i), labels[i], str(self.board[i])) for i in range(len(self.board))]

        width = max(max(len(row) for row in column) for column in columns)

        rowNames = ["INDEX", "TYPE", "SEEDS"]
        rowNameWidth = max(len(name) for name in rowNames)

        rows = [f"{rowName:<{rowNameWidth}} | " + " ".join(f"{column[row]:<{width}}" for column in columns) for row, rowName in enumerate(rowNames)]
        return "\n".join(rows)

    def copy(self):
        return MancalaBoard(self.board)

    def getPlayerFromPit(self, pitIndex: int, includeStore: bool = False) -> int:
        if pitIndex < 0 or pitIndex > 13:
            raise IndexError("Cannot get player from pit - pit index is out of range")

        if pitIndex == MancalaBoard.FIRST_PLAYER_STORE_INDEX:
            if not includeStore:
                raise ValueError("Cannot get player from pit - pit index is store")
            return MancalaBoard.FIRST_PLAYER
        if pitIndex == MancalaBoard.SECOND_PLAYER_STORE_INDEX:
            if not includeStore:
                raise ValueError("Cannot get player from pit - pit index is store")
            return MancalaBoard.SECOND_PLAYER

        if pitIndex < MancalaBoard.FIRST_PLAYER_STORE_INDEX:
            return MancalaBoard.FIRST_PLAYER
        if pitIndex > MancalaBoard.FIRST_PLAYER_STORE_INDEX and pitIndex < MancalaBoard.SECOND_PLAYER_STORE_INDEX:
            return MancalaBoard.SECOND_PLAYER

        return 0

    def checkGameOver(self) -> bool:
        firstPlayerEmpty = all(self.board[i] == 0 for i in range(0, 6))
        secondPlayerEmpty = all(self.board[i] == 0 for i in range(7, 13))

        return firstPlayerEmpty or secondPlayerEmpty

    def collectFinalPits(self) -> None:
        if not self.checkGameOver():
            return

        firstPlayerRemaining = sum(self.board[0:6])
        secondPlayerRemaining = sum(self.board[7:13])

        self.board[MancalaBoard.FIRST_PLAYER_STORE_INDEX] = self.board[MancalaBoard.FIRST_PLAYER_STORE_INDEX] + firstPlayerRemaining
        self.board[MancalaBoard.SECOND_PLAYER_STORE_INDEX] = self.board[MancalaBoard.SECOND_PLAYER_STORE_INDEX] + secondPlayerRemaining

        for i in range(0, 6):
            self.board[i] = 0
        for i in range(7, 13):
            self.board[i] = 0

    def getStoreOfPlayer(self, playerNumber: int) -> int | None:
        if playerNumber != 1 and playerNumber != 2:
            raise ValueError("Cannot get store of player - player number must be 1 or 2")

        if playerNumber == MancalaBoard.FIRST_PLAYER:
            return MancalaBoard.FIRST_PLAYER_STORE_INDEX
        if playerNumber == MancalaBoard.SECOND_PLAYER:
            return MancalaBoard.SECOND_PLAYER_STORE_INDEX
        return None

    def getPitsOfPlayer(self, playerNumber: int) -> list[int]:
        if playerNumber != 1 and playerNumber != 2:
            raise ValueError("Cannot get store of player - player number must be 1 or 2")

        if playerNumber == MancalaBoard.FIRST_PLAYER:
            return list(range(0, 6))
        if playerNumber == MancalaBoard.SECOND_PLAYER:
            return list(range(7, 13))
        return []

    def makeMove(self, pitIndex: int) -> bool:
        if self.board[pitIndex] == 0:
            raise ValueError("Cannot make move - pit must be not empty")

        seeds = self.board[pitIndex]
        self.board[pitIndex] = 0

        playerNumber = self.getPlayerFromPit(pitIndex)

        playerStore = self.getStoreOfPlayer(playerNumber)
        opponentStore = self.getStoreOfPlayer((playerNumber % 2) + 1)

        currentIndex = pitIndex
        while seeds > 0:
            currentIndex = (currentIndex + 1) % 14

            if currentIndex == opponentStore:
                continue

            self.board[currentIndex] = self.board[currentIndex] + 1
            seeds = seeds - 1

        if currentIndex == playerStore:
            return MancalaBoard.EXTRA_MOVE

        playerPits = self.getPitsOfPlayer(playerNumber)
        if currentIndex in playerPits and self.board[currentIndex] == 1:
            oppositeIndex = 12 - currentIndex
            if self.board[oppositeIndex] > 0:
                self.board[playerStore] = self.board[playerStore] + (self.board[currentIndex] + self.board[oppositeIndex])

                self.board[currentIndex] = 0
                self.board[oppositeIndex] = 0

        return MancalaBoard.NO_EXTRA_MOVE

    def getPossibleMoves(self, playerNumber: int) -> list[int]:
        if playerNumber != 1 and playerNumber != 2:
            raise ValueError("Cannot get possible moves - player number must be 1 or 2")

        if playerNumber == MancalaBoard.FIRST_PLAYER:
            return [i for i in range(0, 6) if self.board[i] > 0]
        if playerNumber == MancalaBoard.SECOND_PLAYER:
            return [i for i in range(7, 13) if self.board[i] > 0]
        return []
