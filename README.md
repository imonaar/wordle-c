# Wordle Game

Welcome to the Wordle game! This is a simple command-line implementation of the popular word-guessing game.

## Table of Contents
- [Features](#features)
- [Requirements](#requirements)
- [Compilation Instructions](#compilation-instructions)
- [How to Play](#how-to-play)
- [License](#license)

## Features
- Guess the correct 5-letter word within 5 attempts.
- Color-coded feedback for each guess:
  - Green for correct letters in the correct position.
  - Yellow for correct letters in the wrong position.
  - Red for incorrect letters.

## Requirements
- A C compiler (e.g., GCC)
- Standard C library

## Compilation Instructions
To compile the game, follow these steps:

1. Open a terminal.
2. Navigate to the directory where the `wordle.c` file is located.
3. Run the following command to compile the code:

   ```bash
   gcc -o wordle wordle.c
   ```

   This will create an executable file named `wordle`.

## How to Play
1. Run the game by executing the following command in the terminal:

   ```bash
   ./wordle
   ```

2. Follow the on-screen instructions to guess the 5-letter word.
3. Enter your guesses when prompted. You have a total of 5 attempts to guess the correct word.
4. After each guess, you will receive feedback on your guess:
   - Letters in the correct position will be highlighted in green.
   - Letters that are in the word but in the wrong position will be highlighted in yellow.
   - Letters that are not in the word will be highlighted in red.
5. Good luck!

## License
This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.