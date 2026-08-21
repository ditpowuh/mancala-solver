import styles from "./App.module.css";
import {useState} from "react";

import "./global.css";

import MancalaBoard from "@/components/MancalaBoard";

import {useMancalaSolver} from "@/hooks/useMancalaSolver";

import {getDefaultBoard} from "@/lib/utility";

export default function App() {
  const [board, setBoard] = useState<number[]>(getDefaultBoard());
  const [outlinesEnabled, setOutlinesEnabled] = useState<boolean>(true);
  const [resultText, setResultText] = useState<string>("Ready to solve.");

  const solver = useMancalaSolver();

  const toggleOutlines = () => {
    setOutlinesEnabled((previousOutlinesEnabled) => !previousOutlinesEnabled);
  }

  const findBestMove = async () => {
    if (!solver.isReady) {
      return;
    }
    setResultText("Processing...");
    const result = await solver.getBestMove(board, 10);
    if (result?.move) {
      setResultText(`Your best move is pit ${result.move + 1} (top to bottom).`);
    }
  }

  return (
    <main className={styles.content}>
      <h1>Mancala Solver</h1>
      <div className={styles.board}>
        <div className={styles.playerindicator}>You</div>
        <MancalaBoard board={board} setBoard={setBoard} enableOutline={outlinesEnabled}/>
        <div className={styles.opponentindicator}>Opponent</div>
      </div>
      <div className={styles.controls}>
        <button className={styles.button} onClick={toggleOutlines}>Toggle outlines</button>
        <button className={styles.button} onClick={findBestMove}>Solve</button>
      </div>
      <div>{solver.isReady ? resultText : "Loading solver..."}</div>
    </main>
  );
}
