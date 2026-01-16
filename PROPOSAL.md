# Final Project Proposal

## Group Members:

Steven Wu
Jun Jie Li

# Intentions:

Basic number guessing game. 1 player waits for a challenger and another player accepts, starting a game between the two.


# Intended usage:

Play a lot of guessing games

# Technical Details:

P2P, where a challenging player is the server and waits for a client (player) to connect. Then they connect to eachother and play the game.
### Extra Features:
Instead of P2P, Clients (players) connect to a constant server and wait to be matched for a game. Server will keep track of board state via a files for each game
  - See Game history, player winrates
  - Players pick and choose who to play against
  - Chat feature lol
### Topics:
Allocating Memory, Sockets, Processes, Signals
### Breakdown
  - Set up basic sockets and handshake between 2 players
  - Wait for a player to initiate
  - Play the game and end the game

<!-- (CHANGE THIS!!!!!) -->

<!-- A description of your technical design. This should include: -->

<!-- How you will be using the topics covered in class in the project. -->

<!-- How you are breaking down the project and who is responsible for which parts. -->


# Intended pacing:
1/8: Basic Client-Server connection and handshake working
1/9: Code a basic game
1/12: MVP
<!-- A timeline with expected completion dates of parts of the project. (CHANGE THIS!!!!!) -->
