import {useState, useEffect, useRef} from "react";
import {loadPyodide, type PyodideInterface} from "pyodide";

import boardCode from "@external/board.py?raw";
import solverCode from "@external/solver.py?raw";

export function useMancalaSolver() {
  const [isReady, setIsReady] = useState<boolean>(false);
  const pyodideRef = useRef<PyodideInterface | null>(null);

  useEffect(() => {
    async function initPyodide() {
      const pyodide = await loadPyodide({
        indexURL: "https://cdn.jsdelivr.net/pyodide/v314.0.5/full/"
      });

      pyodide.FS.writeFile("board.py", boardCode);
      pyodide.FS.writeFile("solver.py", solverCode);

      await pyodide.runPythonAsync("from board import MancalaBoard");
      await pyodide.runPythonAsync("from solver import MancalaSolver");

      pyodideRef.current = pyodide;
      setIsReady(true);
    }

    initPyodide();
  }, []);

  const getBestMove = async (board: number[], depth: number = 10) => {
    if (!isReady || !pyodideRef.current) {
      return null;
    }

    const pythonExecutionScript = `
      board = MancalaBoard([${board.toString()}])
      solver = MancalaSolver(1)
      solver.findBestMove(board, ${depth})
    `;

    const result = await pyodideRef.current.runPythonAsync(pythonExecutionScript);
    const bestMove = result.toJs({dict_converter: Object.fromEntries});
    result.destroy();

    return bestMove;
  };

  return {isReady, getBestMove};
}
