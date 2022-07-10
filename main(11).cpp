#include <iostream>
#include <vector>
#include <thread>         // std::this_thread::sleep_for
#include <chrono>
#include <conio.h>
#include <windows.h>
#include <random>
#include <math.h>

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

using namespace std;

//places the food randomly on the board
void placeFood(int &foodX, int &foodY, vector <int> xCoord, vector <int> yCoord)
{
    ///generate a random number between 17 and 3 for x coord
    int randNumX = rand()%(17-3 + 1) + 3;
    int randNumY = rand()%(57-3 + 1) + 3;

    //if previous random numbers are where snake already is, then generate new numbers
    while(randNumX == xCoord[0] && randNumY == yCoord[0])
        randNumX = rand()%(17-3 + 1) + 3;
        randNumY = rand()%(57-3 + 1) + 3;
        foodX = randNumX;
        foodY = randNumY;



}


//lengthens the snake by 1 (should be called 3 times every time food is eaten)
void foodEaten(vector<int> &xCoord, vector<int> &yCoord)
{
    ///resize xcoord vector by one, inserting the val of 3

    if(xCoord[xCoord.size() - 2] < xCoord.back())
    {
        xCoord.push_back(xCoord.back() + 1);
        yCoord.push_back(yCoord.back());
    }

    else if (xCoord[xCoord.size() - 2] > xCoord.back())
    {
        xCoord.push_back(xCoord.back() - 1);
        yCoord.push_back(yCoord.back());
    }

    else if(yCoord[yCoord.size() - 2] < yCoord.back())
    {
        yCoord.push_back(yCoord.back() + 1);
        xCoord.push_back(xCoord.back());
    }

    else if (yCoord[yCoord.size() - 2] > yCoord.back())
    {
        yCoord.push_back(yCoord.back() + 1);
        xCoord.push_back(xCoord.back());
    }

}

void constructBoard(const int xLength, const int yLength, int foodX, int foodY, int (&board)[20][60], vector<int> xCoord, vector<int> yCoord)
{

    for(int i = 0; i < xLength; i++)
        for(int j = 0; j < yLength; j++)
        {
            if(i == 0 || i == 19)
                board[i][j] = 1;
            else if(j == 0 || j == 59)
                board[i][j] = 2;
            else if(i == foodX && j == foodY)
                board[i][j] = 4;
            else
                board[i][j] = 0;

            for(int k = 0; k < xCoord.size(); k++)
                if(xCoord[k] == i && yCoord[k] == j)
                {
                    board[i][j] = 3;
                }
        }
}

//checks if there is a collision
void checkCollision(const int xLength, const int yLength, int (&board)[20][60], vector<int> &xCoord, vector<int> &yCoord, int &foodX, int &foodY, bool &gameOver)
{


        for(int i = 1; i < xCoord.size(); i++)
            if(xCoord[i] == xCoord[0] && yCoord[i] == yCoord[0])
                gameOver = true;


        if (xCoord[0] == 20)
        {
            cout << "Game Over" << endl;
            gameOver = true;
        }
        else if (xCoord[0] == 1)
        {
            cout << "Game Over" << endl;
            gameOver = true;
        }
        else if (yCoord[0] == 1)
        {
            cout << "Game Over" << endl;
            gameOver = true;
        }
        else if (yCoord[0] == 60)
        {
            cout << "Game Over" << endl;
            gameOver = true;
        }

        else if(xCoord[0] == foodX && yCoord[0] == foodY)
        {
            foodEaten(xCoord, yCoord);
            foodEaten(xCoord, yCoord);
            foodEaten(xCoord, yCoord);
            placeFood(foodX, foodY, xCoord, yCoord);
        }


    }






//prints to screen based on board array. 1 and 2 are used for edges of board. 3 is used for snake. 4 is used for food.
void printBoard(int board[][60])
{
    for(int i = 0; i < 20; i++)
        for(int j = 0; j < 60; j++)
        {
            if(board[i][j] == 0)
                cout << " ";
            else if(board[i][j] == 1)
                cout << "_";
            else if(board[i][j] == 2)
                cout << "|";
            else if(board[i][j] == 3)
                cout << "X";
            else if(board[i][j] == 4)
                cout << "O";
            if(j == 59)
                cout << endl << flush;
        }
}

//moves the snake one to the right
void moveRight(vector<int> &xCoord, vector<int> &yCoord)
{

    for(int k = xCoord.size()-1; k > 0; k--)
        xCoord[k] = xCoord[k - 1];

    for(int k = yCoord.size()-1; k > 0; k--)
        yCoord[k] = yCoord[k - 1];

    yCoord[0]++;

}

//moves the snake one to the left
void moveLeft(vector<int> &xCoord, vector<int> &yCoord)
{

    for(int k = xCoord.size()-1; k > 0; k--)
        xCoord[k] = xCoord[k - 1];

    for(int k = yCoord.size() - 1; k > 0; k--)
        yCoord[k] = yCoord[k - 1];

    yCoord[0]--;

}

//moves the snake one upwards
void moveUp(vector<int> &xCoord, vector<int> &yCoord)
{

    for(int k = yCoord.size() - 1; k > 0; k--)
        yCoord[k] = yCoord[k - 1];

    for(int k = xCoord.size() - 1; k > 0; k--)
        xCoord[k] = xCoord[k - 1];

    xCoord[0]--;

}

//moves the snake one downwards
void moveDown(vector<int> &xCoord, vector<int> &yCoord)
{

    for(int k = yCoord.size() - 1; k > 0; k--)
        yCoord[k] = yCoord[k - 1];

    for(int k = xCoord.size() - 1; k > 0; k--)
        xCoord[k] = xCoord[k - 1];

    xCoord[0]++;
}

//based on the key pressed, call "move" functions
void getKeyPressed(vector<int> &xCoord, vector<int> &yCoord, bool &first, int &last)
{
    //Only get key from keyboard if one is being pressed
    char c = ' ';
    if(first == false)
    {
        if(_kbhit() == 1)
        {
            c=getch();
            c=getch();
        }
    }
    first = false;

    //move in the direction of the key being pressed, or continue in same direction
    switch((c)) {
        case KEY_UP:
            if(last != 2)
            {
                moveUp(xCoord, yCoord);
                last = 3;
            }
            else
                moveDown(xCoord, yCoord);
            break;
        case KEY_DOWN:
            if(last != 3)
            {
                moveDown(xCoord, yCoord);
                last = 2;
            }
            else
                moveUp(xCoord, yCoord);
            break;
        case KEY_LEFT:
            if(last != 0)
            {
                moveLeft(xCoord, yCoord);
                last = 1;
            }
            else
                moveRight(xCoord, yCoord);
            break;
        case KEY_RIGHT:
            if(last != 1)
            {
                moveRight(xCoord, yCoord);
                last = 0;
            }
            else
                moveLeft(xCoord, yCoord);
            break;
        default:
            switch(last)
            {
            case 0:
                moveRight(xCoord, yCoord);
                break;
            case 1:
                moveLeft(xCoord, yCoord);
                break;
            case 2:
                moveDown(xCoord, yCoord);
                break;
            case 3:
                moveUp(xCoord, yCoord);
                break;
            }
            break;
    }
}



int main()
{

    const int xLength = 20;
    const int yLength = 60;

    bool gameOver = false;

    int foodX, foodY = 0;

    vector <int> xCoord;
    vector <int> yCoord;
    xCoord.assign(5, 10);
    yCoord.assign(5, 30);



    int board[xLength][yLength];
    int last = 0;
    bool first = true;

    placeFood(foodX, foodY, xCoord, yCoord);

    while(!gameOver)
    {

        constructBoard(xLength, yLength, foodX, foodY, board, xCoord, yCoord);
        printBoard(board);
        getKeyPressed(xCoord, yCoord, first, last);
        checkCollision(xLength, yLength, board, xCoord, yCoord, foodX, foodY, gameOver);

        //pauses for 50 miliseconds between steps
        Sleep(500);
        //clears console
        system("cls");

    }


    return 0;
}

