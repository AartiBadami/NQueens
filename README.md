# NQueens
This project attempts to solve the n-queens problem

This repository contains the following:

queens.c : src file and executes the core functionality of this project

Makefile : compiles queens.c (to use, type the following command in the command line: "make queens")

board.txt : sample txt file


BACKGROUND: A chessboard is an 8 × 8 grid of squares, each of which may contain up to one chess piece.  The queen is the most powerful piece in chess, capable of moving any number of squares vertically, horizontally, or diagonally, provided that it does not change direction during the move.  The N-queens problem asks how many ways N queens can be arranged on a board such that no queen can take another. That is, no queen can be moved to a square occupied by another queen in a single move.


INPUT FORMAT: This program takes in a populated chessboard and first determines whether any queen can take any other queen. If so, it will print Invalid. If not, it will determine, for each empty square, whether a queen placed there could be taken by any other queen. It will print a new chessboard with these available squares marked with q.

When +2 is given, the program will further determine if there is any way to place two additional queens on the board such that no queen can take any other queen. 

If this is possible, queens will print Two or more. 
If only one queen may be placed, queens will print One. 
If no queens may be placed, queens will print Zero.

Finally, when -w is given, queens will consider boards that may contain warrior queens (a queen that fights on horseback, and thus may move like a queen or like a knight) and distinguish between squares where a warrior queen may be placed (marked w) and squares where only a regular queen may be placed (marked q). Additionally, queens will accept chessboards containing warrior queens.

Example inputs:
./queens board.txt
./queens +2 -w board.txt


OUTPUT FORMAT:  If any queens on the board may take another, queens will print Invalid and terminate. Otherwise, queens will print a chessboard similar to the input, but with additional symbols q and w to indicate squares where a queen or warrior queen may be placed. The mark w will only be used if the -w option is given.

Next, if the +2 option is given, queens will print Zero, One, or Two or more, depending on how many additional queens may be safely placed on the board.
