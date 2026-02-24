#include<iostream>
#include<string>
using namespace std;

// global variables
char board[3][3] = {
    {'-', '-', '-'},
    {'-', '-', '-'},
    {'-', '-', '-'}
};

char currentPlayer = 'X';
bool gameRunning = true;

void displayBoard()
{
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            cout << board[i][j];
            if (j < 2) cout << " | ";
        }
        cout << endl;
        if (i < 2) cout << "---------\n";
    }
}


bool checkWinner()
{
    // horizontal
    for (int i = 0; i < 3; i++)
    {
        if (board[i][0] == board[i][1] && board[i][2] == board[i][1] && board[i][0] != '-')
        {
            return true;
        }
    }
    
    // vertical
    for (int i = 0; i < 3; i++)
    {
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != '-')
        {
            return true;
        }
    }
    
    //diagnol
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != '-')
    {
        return true;
    }

    if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != '-')
    {
        return true;
    }

    return false;

}

// Check tie
bool checkDraw() {
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            if(board[i][j] == '-')
                return false;
    return true;
}


//get input
void getInput()
{
    int row, col;
    while (true) 
    { 
        cout << "\nPlayer " << currentPlayer << " make a move (eg. 0 2): ";
        cin >> row >> col;
        if(row >= 0 && row <= 2 && col >= 0 && col <= 2 && board[row][col] == '-')
        {
            board[row][col] = currentPlayer;
            break;
        }else
        {
            cout << "\nInvalid move! Try again.\n";
        }
    }
}


void resetBoard()
{
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            board[i][j] = '-';

    currentPlayer = 'X';
}


void playAga()
{
    char playAgain;

    while (true) 
    {
        cout << "\nPlay Again? (y/n): ";
        cin >> playAgain;
        if (playAgain == 'n' || playAgain == 'N')
            {
            cout << "\nThanks for playing !!";
            gameRunning = false;
            break;

            } else if (playAgain == 'y' || playAgain == 'Y'){
                cout << "\n";
                resetBoard();
                break;

            }else {
                cout << "Invalid Input!";
            }
    }
}


int main()
{
   cout << "\n------TicTacToe------\n" <<endl;
    displayBoard();
    cout <<endl;

    while (gameRunning)
    {

        getInput();
        cout <<endl;

        if (checkWinner()){
            displayBoard();
            cout << endl;
            cout << currentPlayer << " Wins!!\n";
            playAga();
        }

        if (checkDraw()){
            displayBoard();
            cout << endl;
            cout << "Its a tie !!\n";
            playAga();
        }

        displayBoard();
        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X'; //ternary operation

    }
}
