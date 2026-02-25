#include<iostream>
#include<string>
#include<sstream>
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


bool inputValidation(const string &line, int &row, int &col) // function to see if there is only two integers as input or not
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

//get input
void getInput()
{
    string line;
    int row, col;

    while (true)
    {
        cout << "\nEnter a move (eg. 1 2): ";
        getline(cin, line);

        if (inputValidation(line, row, col)) //calling the validation function
        {
            if (row < 1 || row > 3 || col < 1 || col > 3)      // simple input validation
            {
                cout << "Invalid Input! Enter numbers ranging from 1 to 3.\n";
            }
            else if (board[row-1][col-1] != '-') 
            {
                cout << "Space Occupied!\n";
            }
            else
            {
                board[row-1][col-1] = currentPlayer; // updating board
                break;
            }
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
