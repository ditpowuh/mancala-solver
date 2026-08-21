import styles from "./App.module.css";
import {useState} from "react";

import "./global.css";

import MancalaBoard from "@/components/MancalaBoard";

export default function App() {
  const [outlinesEnabled, setOutlinesEnabled] = useState<boolean>(true);

  const toggleOutlines = () => {
    setOutlinesEnabled((previousOutlinesEnabled) => !previousOutlinesEnabled);
  }

  return (
    <main className={styles.content}>
      <h1>Mancala Solver</h1>
      <div className={styles.board}>
        <div className={styles.playerindicator}>You</div>
        <MancalaBoard enableOutline={outlinesEnabled}/>
        <div className={styles.opponentindicator}>Opponent</div>
      </div>
      <div className={styles.controls}>
        <button className={styles.button} onClick={toggleOutlines}>Toggle outlines</button>
        <button className={styles.button}>Solve</button>
      </div>
    </main>
  );
}
