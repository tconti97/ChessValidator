#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <cstdlib>

using namespace std;

// Piece Class used to indicate if a piece is black or white and what type of piece, if any, is on the board.
class Piece
{
private:
    bool isWhite;
    string pieceType;

public:
    Piece();
    Piece(bool, string);
    bool validateMove(int, int, int, int, Piece[][8]);
    bool getIsWhite();
    string getPieceType();
};

Piece::Piece()
{
    isWhite = true;
    pieceType = "NULL";
}

Piece::Piece(bool inWhite, string inType)
{
    isWhite = inWhite;
    pieceType = inType;
}

bool Piece::validateMove(int posX, int posY, int locX, int locY, Piece board[][8])
{
    if (board[locY][locX].getIsWhite() == isWhite && board[locY][locX].getPieceType() != "NULL")
        return false;

    if(pieceType == "Pawn")
    {
        if(isWhite)
        {
            if(board[locY][locX].getPieceType() == "NULL" && (locX == posX && locY == posY - 1)) // white pawn moves forward one space to an empty square
            {
                return true;
            }
            else if(posY == 6 && board[locY][locX].getPieceType() == "NULL" && board[locY - 1][locX].getPieceType() == "NULL" && (locX == posX && locY == posY - 2)) // first white pawn move, two squares
            {
                return true;
            }
            else if(((locX == posX + 1 && locY == posY - 1) || (locX == posX - 1 && locY == posY - 1)) && board[locY][locX].getIsWhite() == !isWhite && board[locY][locX].getPieceType() != "NULL") // white pawn to take black piece at either forward diagonal
            {
                return true;
            }
        }
        else // isWhite false -> piece is black
        {
            if(board[locY][locX].getPieceType() == "NULL" && (locX == posX && locY == posY + 1)) // black pawn moves forward one space to an empty square
            {
                return true;
            }
            else if(posY == 1 && board[locY][locX].getPieceType() == "NULL" && board[locY + 1][locX].getPieceType() == "NULL" && (locX == posX && locY == posY + 2)) // first black pawn move, two squares
            {
                return true;
            }
            else if(((locX == posX - 1 && locY == posY + 1) || (locX == posX + 1 && locY == posY + 1)) && board[locY][locX].getIsWhite() == !isWhite && board[locY][locX].getPieceType() != "NULL") // black pawn to take white piece at either forward diagonal
            {
                return true;
            }
        }
    }
    else if(pieceType == "Knight")
    {
        if(abs(posX - locX) == 1 && abs(posY - locY) == 2 || abs(posX - locX) == 2 && abs(posY - locY) == 1) // checks to see the location to be moved in is a distance of 1 in one direction and 2 in another.
        {
            return true;
        }
    }
    else if(pieceType == "Bishop")
    {
        if(posX == locX || posY == locY) // if pos and loc are in the same rank or file, Bishop can't move that way
        {
            return false;
        }
        else if(abs(posX - locX) == abs(posY - locY)) // check to see if loc shares a diagonal with pos.
        {
            if(posX < locX)
            {
                if(posY < locY)
                {
                    for(int i = 1; i < abs(posX - locX); i++)
                    {
                        if(board[posY + i][posX + i].getPieceType() == "NULL") // checks spaces between pos and loc to make sure nothing is blocking
                        {
                            continue;
                        }
                        else
                        {
                            return false;
                        }
                    }
                    if(board[locY][locX].getPieceType() == "NULL" || board[locY][locX].getIsWhite() == !isWhite) // if piece @ loc is of opposite color of bishop or if space is empty, it can move there.
                    {
                        return true;
                    }
                }
                else if(posY > locY)
                {
                    for(int i = 1; i < abs(posX - locX); i++)
                    {
                        if(board[posY - i][posX + i].getPieceType() == "NULL")
                        {
                            continue;
                        }
                        else
                        {
                            return false;
                        }
                    }
                    if(board[locY][locX].getPieceType() == "NULL" || board[locY][locX].getIsWhite() == !isWhite)
                    {
                        return true;
                    }
                }
            }
            else if(posX > locX)
            {
                if(posY < locY)
                {
                    for(int i = 1; i < abs(posX - locX); i++)
                    {
                        if(board[posY + i][posX - i].getPieceType() == "NULL")
                        {
                            continue;
                        }
                        else
                        {
                            return false;
                        }
                    }
                    if(board[locY][locX].getPieceType() == "NULL" || board[locY][locX].getIsWhite() == !isWhite)
                    {
                        return true;
                    }
                }
                else if(posY > locY)
                {
                    for(int i = 1; i < abs(posX - locX); i++)
                    {
                        if(board[posY - i][posX - i].getPieceType() == "NULL")
                        {
                            continue;
                        }
                        else
                        {
                            return false;
                        }
                    }
                    if(board[locY][locX].getPieceType() == "NULL" || board[locY][locX].getIsWhite() == !isWhite)
                    {
                        return true;
                    }
                }
            }
        }
    }
    else if(pieceType == "Rook")
    {       
        if(posX == locX && posY != locY) // Rook and loc are on same horizontal
        {
            if(posY > locY) // Determine direction of loc from pos
            {
                for(int i = 1; i < abs(posY - locY); i++)
                {
                    if(board[posY - i][locX].getPieceType() == "NULL") // Pieces between pos and loc should be empty
                    {
                        continue;
                    }
                    else
                    {
                        return false;
                    }
                }
                if(board[locY][locX].getPieceType() == "NULL" || board[locY][locX].getIsWhite() == !isWhite)
                {
                    return true;
                }
            }
            else if(posY < locY)
            {
                for(int i = 1; i < abs(posY - locY); i++)
                {
                    if(board[posY + i][locX].getPieceType() == "NULL")
                    {
                        continue;
                    }
                    else
                    {
                        return false;
                    }
                }
                if(board[locY][locX].getPieceType() == "NULL" || board[locY][locX].getIsWhite() == !isWhite)
                {
                    return true;
                }
            }
        }
        else if(posX != locX && posY == locY) // Rook and loc are on same vertical
        {
            if(posX > locX)
            {
                for(int i = 1; i < abs(posY - locY); i++)
                {
                    if(board[locY][posX - i].getPieceType() == "NULL")
                    {
                        continue;
                    }
                    else
                    {
                        return false;
                    }
                }
                if(board[locY][locX].getPieceType() == "NULL" || board[locY][locX].getIsWhite() == !isWhite)
                {
                    return true;
                }
            }
            else if(posX < locX)
            {
                for(int i = 1; i < abs(posY - locY); i++)
                {
                    if(board[locY][posX + i].getPieceType() == "NULL")
                    {
                        continue;
                    }
                    else
                    {
                        return false;
                    }
                }
                if(board[locY][locX].getPieceType() == "NULL" || board[locY][locX].getIsWhite() == !isWhite)
                {
                    return true;
                }
            }
        }
    }
    else if(pieceType == "Queen") // Queen is a mashup of the Bishop and Rook validations. 
    {
        if(posX == locX && posY != locY)
        {
            if(posY > locY)
            {
                for(int i = posY - 1; i > locY; i--)
                {
                    if(board[i][locX].getPieceType() == "NULL")
                    {
                        continue;
                    }
                    else
                    {
                        return false;
                    }
                }
                if(board[locY][locX].getPieceType() == "NULL" || board[locY][locX].getIsWhite() == !isWhite)
                {
                    return true;
                }
            }
            else if(posY < locY)
            {
                for(int i = posY + 1; i < locY; i++)
                {
                    if(board[i][locX].getPieceType() == "NULL")
                    {
                        continue;
                    }
                    else
                    {
                        return false;
                    }
                }
                if(board[locY][locX].getPieceType() == "NULL" || board[locY][locX].getIsWhite() == !isWhite)
                {
                    return true;
                }
            }
        }
        else if(posX != locX && posY == locY)
        {
            if(posX > locX)
            {
                for(int i = posX - 1; i > locX; i--)
                {
                    if(board[locY][i].getPieceType() == "NULL")
                    {
                        continue;
                    }
                    else
                    {
                        return false;
                    }
                }
                if(board[locY][locX].getPieceType() == "NULL" || board[locY][locX].getIsWhite() == !isWhite)
                {
                    return true;
                }
            }
            else if(posX < locX)
            {
                for(int i = posX + 1; i < locX; i++)
                {
                    if(board[locY][i].getPieceType() == "NULL")
                    {
                        continue;
                    }
                    else
                    {
                        return false;
                    }
                }
                if(board[locY][locX].getPieceType() == "NULL" || board[locY][locX].getIsWhite() == !isWhite)
                {
                    return true;
                }
            }
        }
        else if((abs(posX - locX) == abs(posY - locY)) && !(posX == locX || posY == locY))
        {
            if(posX < locX)
            {
                if(posY < locY)
                {
                    for(int i = 1; i < abs(posX - locX); i++)
                    {
                        if(board[posY + i][posX + i].getPieceType() == "NULL")
                        {
                            continue;
                        }
                        else
                        {
                            return false;
                        }
                    }
                    if(board[locY][locX].getPieceType() == "NULL" || board[locY][locX].getIsWhite() == !isWhite)
                    {
                        return true;
                    }
                }
                else if(posY > locY)
                {
                    for(int i = 1; i < abs(posX - locX); i++)
                    {
                        if(board[posY - i][posX + i].getPieceType() == "NULL")
                        {
                            continue;
                        }
                        else
                        {
                            return false;
                        }
                    }
                    if(board[locY][locX].getPieceType() == "NULL" || board[locY][locX].getIsWhite() == !isWhite)
                    {
                        return true;
                    }
                }
            }
            else if(posX > locX)
            {
                if(posY < locY)
                {
                    for(int i = 1; i < abs(posX - locX); i++)
                    {
                        if(board[posY + i][posX - i].getPieceType() == "NULL")
                        {
                            continue;
                        }
                        else
                        {
                            return false;
                        }
                    }
                    if(board[locY][locX].getPieceType() == "NULL" || board[locY][locX].getIsWhite() == !isWhite)
                    {
                        return true;
                    }
                }
                else if(posY > locY)
                {
                    for(int i = 1; i < abs(posX - locX); i++)
                    {
                        if(board[posY - i][posX - i].getPieceType() == "NULL")
                        {
                            continue;
                        }
                        else
                        {
                            return false;
                        }
                    }
                    if(board[locY][locX].getPieceType() == "NULL" || board[locY][locX].getIsWhite() == !isWhite)
                    {
                        return true;
                    }
                }
            }
        }
    }
    else if(pieceType == "King")
    {
        // White castles king side
        if(isWhite && posX == 4 && posY == 7 && locX == 6 && posY == 7 && board[7][5].getPieceType() == "NULL" && board[7][6].getPieceType() == "NULL" && (board[7][7].getPieceType() == "Rook" && board[7][7].getIsWhite() == isWhite))
            {
                return true;
            }
        // White castles queen side
        else if(isWhite && posX == 4 && posY == 7 && locX == 2 && posY == 7 && (board[7][3].getPieceType() == "NULL" && board[7][2].getPieceType() == "NULL" && board[7][1].getPieceType() == "NULL" && (board[7][0].getPieceType() == "Rook" && board[7][0].getIsWhite() == isWhite)))
            {
                return true;
            }
        // Black castles king side
        else if(!isWhite && posX == 4 && posY == 0 && locX == 6 && posY == 0 && (board[0][5].getPieceType() == "NULL" && board[0][6].getPieceType() == "NULL" && (board[0][7].getPieceType() == "Rook" && board[0][7].getIsWhite() == isWhite)))
            {
                return true;
            }
        // Black castles queen side
        else if(!isWhite && posX == 4 && posY == 0 && locX == 2 && posY == 0 && (board[0][3].getPieceType() == "NULL" && board[0][2].getPieceType() == "NULL" && board[0][1].getPieceType() == "NULL" && (board[0][0].getPieceType() == "Rook" && board[0][0].getIsWhite() == isWhite)))
            {
                return true;
            }
        // King moves 1 space in any direction
        else if(abs(posX - locX) <= 1 && abs(posY - locY) <= 1)
        {
            return true;
        }
    }
    return false;
}

bool Piece::getIsWhite()
{
    return isWhite;
}

string Piece::getPieceType()
{
    return pieceType;
}

int setPositionX(char pos) 
{
    switch(pos){
        case 'A': return 0;
        case 'B': return 1;
        case 'C': return 2;
        case 'D': return 3;
        case 'E': return 4;
        case 'F': return 5;
        case 'G': return 6;
        case 'H': return 7;
    }
    return 99;
}

int setPositionY(char pos)
{
    switch(pos){
        case '8': return 0;
        case '7': return 1;
        case '6': return 2;
        case '5': return 3;
        case '4': return 4;
        case '3': return 5;
        case '2': return 6;
        case '1': return 7;
    }
    return 99;
}

int main(int argc, char **argv)
{
    if(argc != 3)
    {
        cout << "Invalid number of arguments!";
        return 0;
    }
    string filename = argv[1];
    ifstream states(filename);
    
    filename = argv[2];
    ifstream moves(filename);

    Piece board[8][8]; // 8x8 2d Array of pieces that are used to mimic a chess board. see chessBoardReference.png
    int file = 0;
    string line = "";
    string move = "";

    while(getline(states, line)) // reads lines of the board states file
    {
        if(line == "END")
        {
            break;
        }
        else if(line == "\n" || line == "") // skips blank lines
        {
            continue;
        }

        for(int i = 0; i < 8; i++) // initializes pieces on the board based on the char from the string obtained via getline
        {
            //black pieces
            if(line[i] == 'i') board[file][i] = Piece(false, "Rook");
            else if(line[i] == 'j') board[file][i] = Piece(false, "Knight");
            else if(line[i] == 'k') board[file][i] = Piece(false, "Bishop");
            else if(line[i] == 'l') board[file][i] = Piece(false, "Queen");
            else if(line[i] == 'm') board[file][i] = Piece(false, "King");
            else if(line[i] == 'o') board[file][i] = Piece(false, "Pawn");

            //black pieces
            else if(line[i] == 'p') board[file][i] = Piece(true, "Rook");
            else if(line[i] == 'q') board[file][i] = Piece(true, "Knight");
            else if(line[i] == 'r') board[file][i] = Piece(true, "Bishop");
            else if(line[i] == 's') board[file][i] = Piece(true, "Queen");
            else if(line[i] == 't') board[file][i] = Piece(true, "King");
            else if(line[i] == 'u') board[file][i] = Piece(true, "Pawn");
            else board[file][i] = Piece(false, "NULL"); //represents an empty square
        }
        file++;
        if(file < 8)
        {
            continue;
        }

        int x1 = 99, y1 = 99, x2 = 99, y2 = 99, begin = 0, pos = 0;
        string moveToTest = "";

        getline(moves, move); // reads line from move sets
        while((pos = move.find(",", begin)) != string::npos) // looks at part of string between start point and next ',' which is the length of 1 move
        {
            moveToTest = move.substr(begin, pos-begin);
            begin = pos + 1;
            for(int j = 0; j < moveToTest.length(); j++) // pos is set first, when x1 and y1 are 99, then the loc.
            {
                if(moveToTest[j] == '-' || moveToTest[j] == '>') 
                {
                    continue;
                }
                if(x1 == 99)
                {
                    x1 = setPositionX(moveToTest[j]);
                }
                else if(y1 == 99)
                {
                    y1 = setPositionY(moveToTest[j]);
                }
                else if(x2 == 99)
                {
                    x2 = setPositionX(moveToTest[j]);
                }
                else if(y2 == 99)
                {
                    y2 = setPositionY(moveToTest[j]);
                }
            }

            if(board[y1][x1].validateMove(x1, y1, x2, y2, board))
            {
                cout << "OK" << endl;
            }
            else
            {
                cout << "NO GOOD" << endl;
            }
            // set values back to 99 so they can be set again in order
            y1 = 99;
            x1 = 99;
            y2 = 99;
            x2 = 99;
        }
        cout << endl;
        file = 0;
    }

    return 0;
}
