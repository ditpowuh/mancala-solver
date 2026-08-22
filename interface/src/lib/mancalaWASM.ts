import createModule from "@/assets/WASM/mancala.mjs";

let modulePromise: ReturnType<typeof createModule> | null = null;

export function getMancalaModule() {
  if (!modulePromise) {
    modulePromise = createModule({
      locateFile(path: string) {
        return new URL(`../assets/WASM/${path}`, import.meta.url).href;
      },
    });
  }
  return modulePromise;
}
