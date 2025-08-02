# simple-ncurses-typing-test
A simple terminal-based typing test game written in C using the ncurses library.


Features

- Runs inside the terminal using `ncurses`
- Real-time character accuracy (green for correct, red for wrong)
- 3 Difficulty levels: Easy, Medium, Hard
- Dynamic word display and timer
- Calculates:
  - Words Per Minute (WPM)
  - Characters Per Second (CPS)
  - Accuracy
  - Keystroke statistics
- Clean restart/exit prompts


Requirements:

- `ncurses` library installed

Linux/macOS:

gcc -o typingtest typingtest -lncurses

./typingtest < wordlist.txt

Windows:

gcc -o typingtest.exe typingtest.c -lncurses

typingtest.exe < wordlist.txt
