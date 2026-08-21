import {defineConfig} from "vite";
import path from "path";

import react, {reactCompilerPreset} from "@vitejs/plugin-react";
import babel from "@rolldown/plugin-babel";
import checker from "vite-plugin-checker";

export default defineConfig({
  plugins: [
    react(),
    babel({
      presets: [reactCompilerPreset()]
    }),
    checker({
      typescript: {
        tsconfigPath: "./tsconfig.app.json",
      },
      overlay: {
        initialIsOpen: false
      }
    })
  ],
  server: {
    fs: {
      allow: [
        path.resolve(import.meta.dirname, "..")
      ]
    }
  },
  resolve: {
    alias: {
      "@": path.resolve(import.meta.dirname, "./src"),
      "@external": path.resolve(import.meta.dirname, "..")
    }
  }
});
