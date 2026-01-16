[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/QfAIDTGi)
# Number Guesser

### Brist

Steven Wu  
Jun Jie Li
##
[Demo Video](https://drive.google.com/file/d/1eRHBLgRjfc3UTTg5Ng0TTo66BBarZIbE/view?usp=drive_link)
### Project Description:

Turn-based guessing game where 2 players connect over TCP and compete to guess a random number (0-10). The server player starts the game, and both players take turns guessing until someone wins. You can still send messages along the way, but that consumes your turn!

### Install/Compile/Run Instructions:

Prerequisites:
makefile


Clone the Repo:  
(SSH):  
```
git clone git@github.com:Stuycs-K/p03-final-09f-wus-lij.git
```
Go into the repo:  
```
cd p03-final-09f-wus-lij
```




Player 1 (Server): Compile and run:

Optional: SSH onto marge
```
ssh 149.89.40.100
```

```
make server
```
Run the file:
```
./server
```
Enter your name when prompted.

Player 2 (Client): compile:
```
make client
```
Run the file, with Player 1's IP Address as an argument.
Running with no argument will default to marge.
```
./client IPADRESSHERE
```
Enter your name when prompted.

Both players should be connected to each other!

### Game Instructions:

1. Server player types "start" to begin the game
2. A random number between 0-10 is generated
3. Players take turns guessing numbers
4. First player to guess correctly wins
5. Server can type "start" again after a game ends to play another round

### Resources/References:

- Networking lab
- Server with Select demo from class notes
