import styles from "./App.module.css";
import {useState, useEffect} from "react";

import "./global.css";

import MancalaBoard from "@/components/MancalaBoard";

import {getMancalaModule} from "@/lib/mancalaWASM";
import {getDefaultBoard} from "@/lib/utility";

import type {Board} from "@/types/board";

export default function App() {
  const [board, setBoard] = useState<Board>(getDefaultBoard());
  const [outlinesEnabled, setOutlinesEnabled] = useState<boolean>(true);

  const [wasmReady, setWasmReady] = useState<boolean>(false);
  const [isCalculating, setIsCalculating] = useState<boolean>(false);
  const [resultText, setResultText] = useState<string>("Ready to solve.");

  const toggleOutlines = () => {
    setOutlinesEnabled((previousOutlinesEnabled) => !previousOutlinesEnabled);
  }

  const findBestMove = async () => {
    if (isCalculating || !wasmReady) {
      return;
    }

    setIsCalculating(true);

    try {
      const Module = await getMancalaModule();

      const mancalaBoard = new Module.MancalaBoard(board);
      const solver = new Module.MancalaSolver(Module.Player.FIRST_PLAYER);

      try {
        const result = solver.findBestMove(mancalaBoard, 10);
        setResultText(`Your best move is pit ${result.move + 1} (top to bottom).`);
      }
      finally {
        mancalaBoard.delete();
        solver.delete();
      }
    }
    catch (error) {
      console.error("Solver failed:", error);
      setResultText("Something went wrong while solving.");
    }
    finally {
      setIsCalculating(false);
    }
  }

  useEffect(() => {
    const loadWasm = async () => {
      try {
        await getMancalaModule();
        setWasmReady(true);
      }
      catch (error) {
        console.error("Failed to load WASM:", error);
        setResultText("Failed to load solver.");
      }
    };

    loadWasm();
  }, []);

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
      <div>{!isCalculating ? resultText : "Loading solver..."}</div>
    </main>
  );
}
