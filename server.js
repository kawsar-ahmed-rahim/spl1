// server.js — serves the browser UI and runs the compiled C game per move
const express = require("express");
const path = require("path");
const { execFile } = require("child_process");

const app = express();
const PORT = process.env.PORT || 3000;
const RPS_BINARY = path.join(__dirname, "rps"); // compiled from rps.c

app.use(express.json());
app.use(express.static(path.join(__dirname, "public")));

// Same encoding as the original C source: 1=rock, 2=paper, 3=scissors
const CHOICE_TO_INT = { rock: "1", paper: "2", scissors: "3" };

app.post("/play", (req, res) => {
  const choice = req.body && req.body.choice;
  const arg = CHOICE_TO_INT[choice];

  if (!arg) {
    return res.status(400).json({ error: "choice must be rock, paper, or scissors" });
  }

  // Run the C program exactly like the terminal version would, just non-interactively
  execFile(RPS_BINARY, [arg], (err, stdout, stderr) => {
    if (err) {
      console.error("rps binary failed:", stderr || err.message);
      return res.status(500).json({ error: "game engine failed to run" });
    }

    // Parse the 3-line output: PLAYER:x / COMPUTER:y / RESULT:z
    const lines = stdout.trim().split("\n");
    const data = {};
    for (const line of lines) {
      const [key, value] = line.split(":");
      if (key && value) data[key.trim().toLowerCase()] = value.trim();
    }

    if (!data.player || !data.computer || !data.result) {
      return res.status(500).json({ error: "unexpected output from game engine" });
    }

    res.json({
      you: data.player,
      computer: data.computer,
      result: data.result, // "win" | "lose" | "draw"
    });
  });
});

app.listen(PORT, () => {
  console.log(`Rock Paper Scissors server running at http://localhost:${PORT}`);
});
