#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <cstdlib>

using namespace std;

// Base Class Piece
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
            if(board[locY][locX].getPieceType() == "NULL" && (locX == posX && locY == posY - 1))
            {
                return true;
            }
            else if(posY == 6 && board[locY][locX].getPieceType() == "NULL" && board[locY - 1][locX].getPieceType() == "NULL" && (locX == posX && locY == posY - 2))
            {
                return true;
            }
            else if(((locX == posX + 1 && locY == posY - 1) || (locX == posX - 1 && locY == posY - 1)) && board[locY][locX].getIsWhite() == !isWhite && board[locY][locX].getPieceType() != "NULL")
            {
                return true;
            }
        }
        else // isWhite false -> piece is black
        {
            if(board[locY][locX].getPieceType() == "NULL" && (locX == posX && locY == posY + 1))
            {
                return true;
            }
            else if(posY == 1 && board[locY][locX].getPieceType() == "NULL" && board[locY + 1][locX].getPieceType() == "NULL" && (locX == posX && locY == posY + 2))
            {
                return true;
            }
            else if(((locX == posX - 1 && locY == posY + 1) || (locX == posX + 1 && locY == posY + 1)) && board[locY][locX].getIsWhite() == !isWhite && board[locY][locX].getPieceType() != "NULL")
            {
                return true;
            }
        }
    }
    else if(pieceType == "Knight")
    {
        if(abs(posX - locX) == 1 && abs(posY - locY) == 2 || abs(posX - locX) == 2 && abs(posY - locY) == 1)
        {
            return true;
        }
    }
    else if(pieceType == "Bishop")
    {
        if(posX == locX || posY == locY)
        {
            return false;
        }
        else if(abs(posX - locX) == abs(posY - locY))
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
    else if(pieceType == "Rook")
    {       
        if(posX == locX && posY != locY)
        {
            if(posY > locY)
            {
                for(int i = 1; i < abs(posY - locY); i++)
                {
                    if(board[posY - i][locX].getPieceType() == "NULL")
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
        else if(posX != locX && posY == locY)
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
    else if(pieceType == "Queen")
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
/*
// Pawn Class, Child of Piece
class Pawn: public Piece
{
public:
    Pawn();
    Pawn(bool);
    bool validateMove(int, int, int, int, Piece[][8]) override;
};

Pawn::Pawn() : Piece(true){pieceType = "Pawn";}

Pawn::Pawn(bool inWhite)
{
    isWhite = inWhite;
    pieceType = "Pawn";
}

bool Pawn::validateMove(int posX, int posY, int locX, int locY, Piece board[][8])
{
    //if pawn is white
    if(isWhite)
    {
        if(board[locX][locY].getPieceType() == "NULL" && (locX == posX + 1 && locY == posY))
        {
            return true;
        }
        else if(posX == 6 && board[locX][locY].getPieceType() == "NULL" && board[locX - 1][locY].getPieceType() == "NULL" && (locX == posX + 2 && locY == posY))
        {
            return true;
        }
        else if(((locX == posX + 1 && locY == posY - 1) || (locX == posX + 1 && locY == posY + 1)) && board[locX][locY].getIsWhite() == !isWhite && board[locX][locY].getPieceType() != "NULL")
        {
            return true;
        }
    }
    else // isWhite false -> piece is black
    {
        if(board[locX][locY].getPieceType() == "NULL" && (locX == posX - 1 && locY == posY))
        {
            return true;
        }
        else if(posX == 1 && board[locX][locY].getPieceType() == "NULL" && board[locX + 1][locY].getPieceType() == "NULL" && (locX == posX - 2 && locY == posY))
        {
            return true;
        }
        else if(((locX == posX - 1 && locY == posY - 1) || (locX == posX - 1 && locY == posY + 1)) && board[locX][locY].getIsWhite() == !isWhite && board[locX][locY].getPieceType() != "NULL")
        {
            return true;
        }
    }

    //if space in front is NULL || if diagonal, must be !isWhite
    return false;
}

// Knight Class, Child of Piece
class Knight: public Piece
{
public:
    Knight();
    Knight(bool);
    bool validateMove(int, int, int, int, Piece[][8]) override;
};

Knight::Knight() : Piece(true){pieceType = "Knight";}

Knight::Knight(bool inWhite)
{
    isWhite = inWhite;
    pieceType = "Knight";
}

bool Knight::validateMove(int posX, int posY, int locX, int locY, Piece board[][8])
{
    //if knight is @ location

    //determine available spaces based on if NULL || has piece with !isWhite
    return true;
}

// Bishop Class, Child of Piece
class Bishop: public Piece
{
public:
    Bishop();
    Bishop(bool);
    bool validateMove(int, int, int, int, Piece[][8]) override;
};

Bishop::Bishop() : Piece(true){pieceType = "Bishop";}

Bishop::Bishop(bool inWhite)
{
    isWhite = inWhite;
    pieceType = "Bishop";
}

bool Bishop::validateMove(int posX, int posY, int locX, int locY, Piece board[][8])
{
    //if bishop is @ location

    //determine available spaces based on if NULL and being blocked by other pieces || has piece with !isWhite
    return true;
}

// Rook Class, Child of Piece
class Rook: public Piece
{
public:
    Rook();
    Rook(bool);
    bool validateMove(int, int, int, int, Piece[][8]) override;
};

Rook::Rook() : Piece(true){pieceType = "Rook";}

Rook::Rook(bool inWhite)
{
    isWhite = inWhite;
    pieceType = "Rook";
}

bool Rook::validateMove(int posX, int posY, int locX, int locY, Piece board[][8])
{
    //if rook is @ location

    //determine available spaces based on if NULL and being blocked by other pieces || has piece with !isWhite
    return true;
}

// Queen Class, Child of Piece
class Queen: public Piece
{
public:
    Queen();
    Queen(bool);
    bool validateMove(int, int, int, int, Piece[][8]) override;
};

Queen::Queen() : Piece(true){pieceType = "Queen";}

Queen::Queen(bool inWhite)
{
    isWhite = inWhite;
    pieceType = "Queen";
}

bool Queen::validateMove(int posX, int posY, int locX, int locY, Piece board[][8])
{
    //if queen is @ location

    //determine available spaces based on if NULL and being blocked by other pieces || has piece with !isWhite
    return true;
}

// King Class, Child of Piece
class King: public Piece
{
public:
    King();
    King(bool);
    bool validateMove(int, int, int, int, Piece[][8]) override;
};

King::King() : Piece(true){pieceType = "King";}

King::King(bool inWhite)
{
    isWhite = inWhite;
    pieceType = "King";
}

bool King::validateMove(int posX, int posY, int locX, int locY, Piece board[][8])
{
    //if king is @ location

    //determine available spaces based on if NULL and being blocked by other pieces || has piece with !isWhite
    return true;
}
*/
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


    //states = 
    Piece board[8][8];
    int file = 0;
    string line = "";
    string move = "";

    while(getline(states, line))
    {
        if(line == "END")
        {
            break;
        }
        else if(line == "\n" || line == "")
        {
            continue;
        }

        for(int i = 0; i < 8; i++)
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
            else board[file][i] = Piece(false, "NULL");
        }
        file++;
        if(file < 8)
        {
            continue;
        }

        int x1 = 99, y1 = 99, x2 = 99, y2 = 99, begin = 0, pos = 0;
        string moveToTest = "";

        getline(moves, move);
        while((pos = move.find(",", begin)) != string::npos)
        {
            moveToTest = move.substr(begin, pos-begin);
            begin = pos + 1;
            for(int j = 0; j < moveToTest.length(); j++)
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
