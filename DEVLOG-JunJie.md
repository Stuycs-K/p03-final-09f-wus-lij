# Dev Log:

This document must be updated daily every time you finish a work session.

## Jun Jie Li

### 2026-01-06 - Starting Plan
Created the barebone files to be used for this project. Updated README.md for basic instructions for game

### 2026-01-07 - What is Your Name?
Added a parameter to request_name so buffer can be reused, added send and recv names.

### 2026-01-08 - Socket Communication
Started testing sending messages back and forth from server and client. Partially works (sends only once but displays other side message after)

### 2026-01-09 - Merging
Merge. Learned more about git branches, discuss project to be guessing game.

### 2026-01-12 - Turns
Fixed turns messaging. Fixed names not appearing. Except turns get broken if entering messages when it is not your turn...

### 2026-01-13 - Socket: Select
Instead of trying to fix the turns bug, we decided to just let the user "send" messages (it just doesn't send because it is not your turn). Done with help from the select demo from class website notes.

### 2026-01-14 - Wrap the Function, Plan for Ending
Making the code cleaner so it isn't a mess and just a huge chunk of code on both sides of server and client. Thinking right now how the game part will work as our basic workaround is done. Maybe we will check for a game start message, and we can have two games (guessing and/or rock paper scissors).

### 2026-01-15 - Game Implementation
Added server only "start" command that generates random number (0-10) and sends to client. Added guess checking with sscanf() that displays Higher/Lower/Win feedback. Game resets after win. Added is_number() function to distinguish guesses from regular chat messages.
