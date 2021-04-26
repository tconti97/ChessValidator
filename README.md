# ChessValidator

Program that takes in a list board states and moves and determines if the moves are valid. 

## File Breakdown

chess_validator_problem.txt is an explanation of the prompt and gives example format for input files

board_states.txt is the input containing board states

move_sets.txt is the input containing sets of moves to test

main.cpp is the file containing the C++ code

main.exe is the executable compiled using main.cpp

chessBoardReference.png is an image I created to help visualize the layout of the board with the 2d array coordinate system of C++

## Notes about running file

When running with arguments in a compiler or via commandline, make sure that there are only 3 arguments, program will return "Invalid number of arguments!" and the program will end without testing the files.

Using powershell, I tested the states using > .\main board_states.txt move_sets.txt
main is the first arg, board_states is the second, and move_sets is the third.

For the given board_states.txt and move_sets.txt, this is the output I generated:
"NO GOOD
NO GOOD
OK     
NO GOOD
       
NO GOOD
NO GOOD
OK     
OK     
OK
OK
OK
NO GOOD

OK
NO GOOD
NO GOOD
NO GOOD
NO GOOD
NO GOOD
OK

NO GOOD
OK
OK
OK
NO GOOD
NO GOOD
OK
NO GOOD
NO GOOD
OK

"