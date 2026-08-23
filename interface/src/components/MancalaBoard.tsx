import styles from "./MancalaBoard.module.css";
import clsx from "clsx";

import type {Board} from "@/types/board";

interface MancalaBoardProps {
  board: Board;
  setBoard: React.Dispatch<React.SetStateAction<Board>>;
  enableOutline?: boolean;
}

export default function MancalaBoard({board, setBoard, enableOutline = false}: MancalaBoardProps) {
  const increaseValue = (pitIndex: number) => {
    if (board[pitIndex] === 99) {
      return;
    }
    setBoard((previousBoard) => {
      return previousBoard.map((seeds, index) => index === pitIndex ? seeds + 1 : seeds) as Board
    });
  }

  const decreaseValue = (pitIndex: number) => {
    if (board[pitIndex] === 0) {
      return;
    }
    setBoard((previousBoard) => {
      return previousBoard.map((seeds, index) => index === pitIndex ? seeds - 1 : seeds) as Board
    });
  }

  return (
    <div className={styles.board}>
      <div className={clsx(styles.opponentstore, enableOutline && styles.opponentoutline, "unselectable")}>
        <div>{board[13]}</div>
        <button className={clsx(styles.button, enableOutline && styles.opponentoutline)} onClick={() => decreaseValue(13)}>-</button>
        <button className={clsx(styles.button, enableOutline && styles.opponentoutline)} onClick={() => increaseValue(13)}>+</button>
      </div>
      <div className={styles.pits}>
        <div className={styles.playerpits}>
          {
            board.slice(0, 6).map((seeds, index) => {
              const originalIndex = index;
              return (
                <div key={`pit-${originalIndex}`} className={clsx(styles.pit, enableOutline && styles.playeroutline, "unselectable")}>
                  <div>{seeds}</div>
                  <button className={clsx(styles.button, enableOutline && styles.playeroutline)} onClick={() => decreaseValue(originalIndex)}>-</button>
                  <button className={clsx(styles.button, enableOutline && styles.playeroutline)} onClick={() => increaseValue(originalIndex)}>+</button>
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
                <div key={`pit-${originalIndex}`} className={clsx(styles.pit, enableOutline && styles.opponentoutline, "unselectable")}>
                  <div>{seeds}</div>
                  <button className={clsx(styles.button, enableOutline && styles.opponentoutline)} onClick={() => decreaseValue(originalIndex)}>-</button>
                  <button className={clsx(styles.button, enableOutline && styles.opponentoutline)} onClick={() => increaseValue(originalIndex)}>+</button>
                </div>
              );
            })
          }
        </div>
      </div>
      <div className={clsx(styles.playerstore, enableOutline && styles.playeroutline, "unselectable")}>
        <div>{board[6]}</div>
        <button className={clsx(styles.button, enableOutline && styles.playeroutline)} onClick={() => decreaseValue(6)}>-</button>
        <button className={clsx(styles.button, enableOutline && styles.playeroutline)} onClick={() => increaseValue(6)}>+</button>
      </div>
    </div>
  );
}
