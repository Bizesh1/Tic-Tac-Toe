/*
 Tic-Tac-Toe 2.1
*/

#include<iostream>
#include<string>
#include<limits>
#include<sstream>
#ifdef _WIN32
#include <windows.h> // Required for the fix
#endif
using namespace std;

struct Game
{
    char board[3][3];
    char currentPlayer = 'X';
    bool gameRunning = true;
};

void initGame(Game &game)
{
    for(int i = 0; i < 3; i++)
    for(int j = 0; j < 3; j++)
        game.board[i][j] = '-';
    game.currentPlayer = 'X';
    game.gameRunning = true;
}


void displayBoard(const Game &game)
{
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            cout << game.board[i][j];
            if (j < 2) cout << " | ";
        }
        cout << endl;
        if (i < 2) cout << "---------\n";
    }
}

void enableANSI() // function to enable ANSI on windows
{
    #ifdef _WIN32
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
    #endif
}

void clearScreen()           // function to clear screen after every move
{   
    std::cout << "\033[2J\033[1;1H"; // ANSI code to clear the screen
}


bool checkWinner(const Game &game)
{
    // horizontal
    for (int i = 0; i < 3; i++)
    {
        if (game.board[i][0] == game.board[i][1] && game.board[i][2] == game.board[i][1] && game.board[i][0] != '-')
        {
            return true;
        }
    }
    
    // vertical
    for (int i = 0; i < 3; i++)
    {
        if (game.board[0][i] == game.board[1][i] && game.board[1][i] == game.board[2][i] && game.board[0][i] != '-')
        {
            return true;
        }
    }
    
    //diagnol
    if (game.board[0][0] == game.board[1][1] && game.board[1][1] == game.board[2][2] && game.board[0][0] != '-')
    {
        return true;
    }

    if (game.board[0][2] == game.board[1][1] && game.board[1][1] == game.board[2][0] && game.board[0][2] != '-')
    {
        return true;
    }

    return false;

}

// Check tie
bool checkDraw(const Game &game) 
{
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            if(game.board[i][j] == '-')
                return false;
    return true;
}


bool inputValidation1(const string &line, int &row, int &col) // function to see if there is only two integers as input or not
{
    stringstream ss(line);
    // try to extract two integers
    if (ss >> row >> col)
    {
        // check for extra invalid input
        string extra;
        if (ss >> extra)
        {
            cout << "Invalid input! Enter exactly two numbers.\n";
            return false;

        }else
            {return true;}
    }else
    {
        cout << "Invalid Input! Enter exactly two interger characters!\n";
        return false;
    }

}

bool inputValidation2(const Game &game, int row, int col)
{
    if (row < 1 || row > 3 || col < 1 || col > 3)      // simple input validation
    {
        cout << "Invalid Input! Enter numbers ranging from 1 to 3.\n";
        return false;
    }
    else if (game.board[row-1][col-1] != '-')  // checking if the slot is occupied
    {
        cout << "Space Occupied!\n";
        return false;
    }
    else
    {
        return true;
    }
}



//get input
void getInput(Game &game)
{
    string line;
    int row, col;

    while (true)
    {
        cout << "\n Player " <<  game.currentPlayer << " enter a move (eg. 1 2): ";
        getline(cin, line);

        if (inputValidation1(line, row, col)) //calling the first validation function
        {
            if (inputValidation2(game, row, col))  // calling the second validation function
            {
                game.board[row-1][col-1] = game.currentPlayer; // updating board
                break;
            }
        }
    }
}


void resetBoard(Game &game)
{
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            game.board[i][j] = '-';

    game.currentPlayer = 'X';
}


void playAgain(Game &game)
{
    char playAgain;
    while (true) 
    {
        cout << "\nPlay Again? (y/n): ";
        cin >> playAgain;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clears the input buffer up to the next newline to prevent leftover input issues

        if (playAgain == 'n' || playAgain == 'N')
            {
            cout << "\nThanks for playing !!\n";
            game.gameRunning = false;
            cout << "Press Enter to continue...\n";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
            break;

            } else if (playAgain == 'y' || playAgain == 'Y'){
                cout << "\n";
                resetBoard(game);
                clearScreen();
                break;

            }else {
                cout << "Invalid Input! Enter either y or n.\n";
            }
    }
}


int main()
{
    Game game;
    initGame(game);

    enableANSI(); 
    cout << "\n------TicTacToe------\n" <<endl;
    displayBoard(game);
    cout <<endl;

    while (game.gameRunning)
    {

        clearScreen();
        cout << "\n------TicTacToe------\n" <<endl;
        displayBoard(game);

        getInput(game);
        cout <<endl;

        if (checkWinner(game))
        {
            clearScreen();
            displayBoard(game);
            cout << endl;
            cout << game.currentPlayer << " Wins!!\n";
            playAgain(game);
        }

        else if (checkDraw(game))
        {
            clearScreen();
            displayBoard(game);
            cout << endl;
            cout << "Its a tie !!\n";
            playAgain(game);
        }

        else
        {
        game.currentPlayer = (game.currentPlayer == 'X') ? 'O' : 'X'; //ternary operation to alternate turns for X and O
        }
    }
    return 0;
}
