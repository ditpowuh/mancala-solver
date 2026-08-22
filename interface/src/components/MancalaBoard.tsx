import styles from "./MancalaBoard.module.css";
import clsx from "clsx";

import type {Board} from "@/types/board";

interface MancalaBoardProps {
  board: Board;
  setBoard: React.Dispatch<React.SetStateAction<Board>>;
  enableOutline?: boolean;
}

export default function MancalaBoard({board, setBoard, enableOutline = false}: MancalaBoardProps) {
  const changeValue = (event: React.MouseEvent<HTMLDivElement>, pitIndex: number) => {
    if (event.button === 0) {
      if (board[pitIndex] === 99) {
        return;
      }
      setBoard((previousBoard) => {
        return previousBoard.map((seeds, index) => index === pitIndex ? seeds + 1 : seeds) as Board
      });
    }
    else if (event.button === 2) {
      event.preventDefault();
      if (board[pitIndex] === 0) {
        return;
      }
      setBoard((previousBoard) => {
        return previousBoard.map((seeds, index) => index === pitIndex ? seeds - 1 : seeds) as Board
      });
    }
  }

  return (
    <div className={styles.board}>
      <div className={clsx(styles.opponentstore, enableOutline && styles.opponentoutline, "unselectable")} onClick={(event) => changeValue(event, 13)} onContextMenu={(event) => changeValue(event, 13)}>
        {board[13]}
      </div>
      <div className={styles.pits}>
        <div className={styles.playerpits}>
          {
            board.slice(0, 6).map((seeds, index) => {
              const originalIndex = index;
              return (
                <div key={`pit-${originalIndex}`} className={clsx(styles.pit, enableOutline && styles.playeroutline, "unselectable")} onClick={(event) => changeValue(event, originalIndex)} onContextMenu={(event) => changeValue(event, originalIndex)}>
                  {seeds}
                </div>
              );
            })
          }
        </div>
        <div className={styles.opponentpits}>
          {
            board.slice(7, 13).map((seeds, index) => {
              const originalIndex = index + 7;
              return (
                <div key={`pit-${originalIndex}`} className={clsx(styles.pit, enableOutline && styles.opponentoutline, "unselectable")} onClick={(event) => changeValue(event, originalIndex)} onContextMenu={(event) => changeValue(event, originalIndex)}>
                  {seeds}
                </div>
              );
            })
          }
        </div>
      </div>
      <div className={clsx(styles.playerstore, enableOutline && styles.playeroutline, "unselectable")} onClick={(event) => changeValue(event, 6)} onContextMenu={(event) => changeValue(event, 6)}>
        {board[6]}
      </div>
    </div>
  );
}
