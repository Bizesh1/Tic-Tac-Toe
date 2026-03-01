# Version 1.0
* Basic Model
* Basic Input Validation; on;y checks if the entered integers are between 0 or 2
* playable if input isnt invalid
## v1.0 bugs
- if there's an invalid move, the game passes the turn again to the next player
- Board displayed multiple times per turn

# Version 1.1
* Added a solid Input Validation
## v1.1 bugs
- too many boards
- if user enters 'y' at play again query, game starts with an Invalid 

# Version 1.2
* Added a function to clear screen after every move
* Added a highlight to outro message: "Press Enter to continue...".
## v1.2 bugs
- if user enters 'y' at play again query, game starts with an Invalid i.e. Replay caused invalid input due 
to leftover buffer in cin 

# Version 1.3
- Added cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n') to clear input buffer before replay

---

---


### Verdict for Version 1.x
- Clean Logic
- Foundation for fine tuning
- Overall Playable

### Limitations of v1.x
- Use of system() introducing security concerns
- No use of enums or structures
- Board isnt Centered
- Use of two integers for input

### Vision for Version 2.x
- Replace global variables with struct
- Introduce enum for Player
- Convert input system to 1–9 mapping
- Center the board


---

---

# Version 2.0
- Changed the name of function; playAga() to playAgain()
- Changed the clearScreen() logic from using system() to using ANSI code
- Added enableANSI() function to enable ANSI code for clearing screen on Windows
- Fixed a bug in win and draw condition using of else-if and else. Bug: When a player won on the last move
it triggered both win and draw condition
- Shows the currentPlayer in the input prompt

# Version 2.1
- Removed Global Variable and encapsulated board, current player and game status in a structure
- Added a function to initialize members of the game structure
- Modified the arguments of the checkDraw(), checkWinner(), inputValidation2 to be constant using "const"
- Added "limits" header file to clear input buffer

# Version 2.2
- Added enum for players
- Added a function to convert enum to character
- Added a function for the game UI to reduce code redundancy

# Version 2.3
- Positing Mapping: Use 1–9 input system 
- Input Validation 2 now only has one goal; to check if the slot is free
- Position Validity is checked in the getInput block