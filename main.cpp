#include "header.h"

/* Global Variables */
char matrix[3][3];
int userTurns = 0;
int computerTurns = 0;
vector<int> computerMap;
vector<int> userMap;

/* These are the winning combinations */
int winCombo[8][3] = {{1,2,3}, {4,5,6}, {7,8,9}, {1,4,7}, {2,5,8}, {3,6,9}, {1,5,9}, {3,5,7}};

/*   M A I N   */
int main()
{
    bool gameOver = false;
    int playerTurn = 0;
    int retval = 0;

    /* Randomize who will get the 1st chance */
    playerTurn = generateRandom(1,100);

    /* Initialize the TicTacToe matrix */
    initMatrix();

    if (!isPlayerTurn(playerTurn))
    {
        cout<<"Computer plays first"<<endl;
        sleep(2);
    }

    displayMatrix();

    while (!gameOver)
    {
        if (isPlayerTurn(playerTurn))
        {
            /* Ask for input */
            retval = FAILURE;
            cout<<"+-------------------------+"<<endl;
            cout<<"|        YOUR TURN        |"<<endl;
            cout<<"+-------------------------+"<<endl;
            cout<<"Put a 'x' at your choice. "<<endl;;
            while (retval != SUCCESS)
            {
                retval = fetchPlayerInput();
            }

            userTurns++;

            /* Check if there is a win */
            retval = checkWin(USER);
            if ((retval == DRAW) || (retval == WIN_USER))
            {
                gameOver = true;
            }
        }
        else
        {
            /* Handle AI */
            cout<<"+-------------------------+"<<endl;
            cout<<"|     COMPUTER'S TURN     |"<<endl;
            cout<<"+-------------------------+"<<endl;
            retval = simulateComputer();
            computerTurns++;

            /* Check if there is a win */
            retval = checkWin(COMPUTER);
            if ((retval == DRAW) || (retval == WIN_COMPUTER))
            {
                gameOver = true;
            }

        }
    
        system("clear");
        displayMatrix();


        /* To keep track of user/computer turn */
        playerTurn++;
    }

    /* Display appropriate message at the end */
    if (gameOver && retval == DRAW)
    {
        cout<<"> Game ended in a draw"<<endl<<endl;
    }
    else if (gameOver && retval == WIN_COMPUTER)
    {
        cout<<"> You've lost the game!"<<endl<<endl;
    }
    if (gameOver && retval == WIN_USER)
    {
        cout<<"> CONGRATULATIONS! You won!!"<<endl<<endl;
    }

    return 0;
}
