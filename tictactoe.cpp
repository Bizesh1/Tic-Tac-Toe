/*
 Tic-Tac-Toe 2.3
*/

#include<iostream>
#include<string>
#include<limits>
#include<sstream>
#ifdef _WIN32
#include <windows.h> // Required for the fix
#endif
using namespace std;

const int pad = 10;
enum Player {X, O};
struct Game
{
    char board[3][3];
    Player currentPlayer;
    bool gameRunning = true;
};

void initGame(Game &game)
{
    for(int i = 0; i < 3; i++)
    for(int j = 0; j < 3; j++)
        game.board[i][j] = '-';
    game.currentPlayer = X;
    game.gameRunning = true;
}

char playerToChar(Player p)
{
    return (p == X) ? 'X' : 'O';
}


void displayBoard(const Game &game)
{
    for (int i = 0; i < 3; i++)
    {
        cout << string(pad, ' ');
        for (int j = 0; j < 3; j++)
        {
            cout << game.board[i][j];
            if (j < 2) cout << " | ";
        }
        cout << endl;
        if (i < 2) 
        {
            cout << string(pad, ' ');
            cout << "---------\n";
        }
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
        if (game.board[i][0] == game.board[i][1] && 
            game.board[i][2] == game.board[i][1] && 
            game.board[i][0] != '-')
        {
            return true;
        }
    }
    
    // vertical
    for (int i = 0; i < 3; i++)
    {
        if (game.board[0][i] == game.board[1][i] && 
            game.board[1][i] == game.board[2][i] && 
            game.board[0][i] != '-')
        {
            return true;
        }
    }
    
    //diagonol
    if (game.board[0][0] == game.board[1][1] && 
        game.board[1][1] == game.board[2][2] && 
        game.board[0][0] != '-')
    {
        return true;
    }

    if (game.board[0][2] == game.board[1][1] && 
        game.board[1][1] == game.board[2][0] && 
        game.board[0][2] != '-')
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


bool inputValidation1(const string &line, int &pos) // function to see if there's only one input
{
    stringstream ss(line);
    
    if (ss >> pos)      // extracting the positon integer
    {
        
        string extra;   // string to check for extra invalid input
        if (ss >> extra)
        {
            cout << "Invalid Input! Enter exactly one position.\n";
            return false;

        }else
            {return true;}
    }else
    {
        cout << "Invalid Input! Enter exactly one position.\n";
        return false;
    }

}

bool inputValidation2(const Game &game, int row, int col)
{
    if (game.board[row][col] != '-')  // checking if the slot is occupied
    {
        cout << "Space Occupied!\n";
        return false;
    }
    else
    {
        return true;
    }
}


void posMap(int pos, int &row, int &col)
{
    row = (pos - 1) / 3;
    col = (pos - 1) % 3;
}


void getInput(Game &game)          //get input
{
    string line;
    int row, col, pos;
    char player = playerToChar(game.currentPlayer);

    while (true)
    {
        cout << "\n Player " <<  player << " enter a move (1-9): ";
        getline(cin, line);

        if (inputValidation1(line, pos)) //calling the first validation function
        {
            if (pos < 1 || pos > 9)
            {
                cout << "Invalid Input! Enter numbers ranging from 1 to 9.\n";
                continue;
            }

            posMap(pos, row, col);
            if (inputValidation2(game, row, col))  // calling the second validation function
            {
                game.board[row][col] = player; // updating board
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

    game.currentPlayer = X;
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

void gameUI(const Game &game)
{
    clearScreen();
    cout << string(pad - 7, ' ') << "------ TicTacToe ------\n\n";
    displayBoard(game);
    cout <<endl;
}

int main()
{
    Game game;
    initGame(game);

    enableANSI(); 


    while (game.gameRunning)
    {

        gameUI(game);
        getInput(game);

        if (checkWinner(game))
        {
            gameUI(game);
            cout << playerToChar(game.currentPlayer) << " Wins!!\n";
            playAgain(game);
        }

        else if (checkDraw(game))
        {
            gameUI(game);
            cout << "Its a tie!!\n";
            playAgain(game);
        }

        else
        {
        game.currentPlayer = (game.currentPlayer == X) ? O : X; //ternary operation to alternate turns for X and O
        }
    }
    return 0;
}
