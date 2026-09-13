# Rock, Paper, Scissors — Browser Edition

Your original C game logic, still compiled and run as a real C program —
now with a browser front end. A small Node.js server spawns the compiled
C binary once per move and sends the result back to the page.

## How it works

```
Browser (index.html)
   │  fetch POST /play  { choice: "rock" }
   ▼
Node server (server.js)
   │  execFile("./rps", ["rock"])
   ▼
C program (rps.c → compiled binary "rps")
   │  plays one round, prints YOU / COMPUTER / RESULT
   ▼
Node server parses the output → JSON
   ▼
Browser shows the result
```

`rps.c` is your original game logic, adapted only so it plays a single
round per run (taking the player's move as a command-line argument
instead of reading it interactively with `scanf`), since the server
invokes it fresh for every click. The win/lose/tie rules themselves are
unchanged.

## Setup

You'll need `gcc` and `node` (with `npm`) installed.

```bash
cd rps-web

# 1. Compile the C game
npm run build:c
# (equivalent to: gcc -o rps rps.c)

# 2. Install the server dependency
npm install

# 3. Start the server
npm start
```

Then open **http://localhost:3000** in your browser and play.

## Files

- `rps.c` — your game logic, compiled to a binary named `rps`
- `server.js` — Express server; serves the page and runs `rps` per move
- `public/index.html` — the browser UI (HTML/CSS/JS, no build step)
- `package.json` — npm scripts and the one dependency (Express)

## Notes

- If you deploy this somewhere, make sure the `rps` binary gets compiled
  on that machine too (or compile it there directly) — a binary built on
  your computer won't necessarily run on a different OS/architecture.
- To change the game rules, edit `rps.c` and re-run `npm run build:c`.
  No changes needed on the Node or browser side.
