#include "header.h"

/********************************************************************************************
* @name         : initMatrix
* @Description  :  
********************************************************************************************/

int initMatrix()
{
    int i = 0;
    int j = 0;
    char tmp[5]; 
    int index = 1;

    /* Fill in blanks */
    while (i < 3)
    {
        j = 0;
        while (j < 3)
        {
            sprintf(tmp, "%d", index);
            matrix[i][j] = tmp[0];
            j++;
            index++;
        }
        i++;
    }

}
/********************************************************************************************
* @name         : displayMatrix
* @Description  : 
********************************************************************************************/

void displayMatrix()
{
    cout<<endl;
     cout<<"+-----+-----+-----+"<<endl;
    printf("|  %c  |  %c  |  %c  |\n", matrix[0][0], matrix[0][1], matrix[0][2]);
     cout<<"+-----+-----+-----+"<<endl;
    printf("|  %c  |  %c  |  %c  |\n", matrix[1][0], matrix[1][1], matrix[1][2]);
     cout<<"+-----+-----+-----+"<<endl;
    printf("|  %c  |  %c  |  %c  |\n", matrix[2][0], matrix[2][1], matrix[2][2]);
     cout<<"+-----+-----+-----+"<<endl;
    cout<<endl;

}
/********************************************************************************************
* @name         : checkWin
* @Description  : 
********************************************************************************************/
int checkWin(int player)
{
    int i = 0;
    int j = 0;
    int k = 0;
    vector<int> tmpMap;
    int val = 0;
    bool found = false;
    int foundCount = 0;


    if (player == USER)
    {
        tmpMap = userMap;
    }
    else if (player == COMPUTER)
    {
        tmpMap = computerMap;
    }

    /* Atleast 3 rounds should have been played */
    if (tmpMap.size() < 3)
    {
        return NONE;
    }

    /* Check all win combos */    
    while (i < 8)
    {
        //cout<<"Checking Combo #"<<i+1<<endl;
        j = 0;
        foundCount = 0;
        while (j < 3)
        {
            found = false;
            val = winCombo[i][j];
            //cout<<" Find ["<<val<<"]"<<endl;
            found = findInMap(tmpMap, val);
            if (found)
            {
                //cout<<"  -->found"<<endl;
                foundCount++;
            }
            else
            {
                /* Check in another combo */
                //cout<<"  -->NOT found. Check in another combo"<<endl;
                break;
            }
            j++;
        }

        /* 3 winning positions found */
        if (foundCount == 3)
        {
            found = true;
            break;
        }
        i++;
    }/* End of check for a combination */

    if (found && player == USER)
    {
        return WIN_USER;
    }
    else if (found && player == COMPUTER)
    {
        return WIN_COMPUTER;
    }
    else if (userTurns + computerTurns == MAX_TURNS)
    {
        return DRAW;
    }
    else
    {
        return NONE;
    }
}

/* Check if val is present in tmpMap */
bool findInMap(vector<int> tmpMap, int val)
{
    int i = 0;
    int len = tmpMap.size();
    while (i < len)
    {
        if (val == tmpMap[i])
        {
            return true;
        }
        i++;
    }

    return false;
}
/********************************************************************************************
* @name         : isPlayerTurn
* @Description  : Check if this turn is user's or computer's 
********************************************************************************************/
bool isPlayerTurn(int playerTurn)
{
    if (playerTurn % 2 == 0)
    {
        return false;
    }

    return true;
}

/********************************************************************************************
* @name         : mapNumToIndex
* @Description  : Map the choice entered to matrix indices
********************************************************************************************/
int mapNumToIndex(int numChoice, int *i, int *j)
{
    switch(numChoice)
    {
        case 1:
            *i = 0;
            *j = 0;
            break;
        case 2:
            *i = 0;
            *j = 1;
            break;
        case 3:
            *i = 0;
            *j = 2;
            break;
        case 4:
            *i = 1;
            *j = 0;
            break;
        case 5:
            *i = 1;
            *j = 1;
            break;
        case 6:
            *i = 1;
            *j = 2;
            break;
        case 7:
            *i = 2;
            *j = 0;
            break;
        case 8:
            *i = 2;
            *j = 1;
            break;
        case 9:
            *i = 2;
            *j = 2;
            break;
        default:
            cout<<"Invalid response!\n"<<endl;
            return FAILURE;
    }/* End of Switch */

    return SUCCESS;
}

/********************************************************************************************
* @name         : fetchPlayerInput
* @Description  :  
********************************************************************************************/
int fetchPlayerInput()
{
    char choice[10];
    int i = 0;
    int j = 0;
    int numChoice = 0;
    int retval = 0;

    memset(choice, 0, sizeof(choice));

    cout<<"Choice (1-9): ";
    cin>>choice;
    numChoice = atoi(choice);
    if (numChoice < 1 || numChoice > 9)
    {
        cout<<"Invalid choice"<<endl; 
        return FAILURE;
    }

    retval = mapNumToIndex(numChoice, &i, &j);
    if (retval != SUCCESS)
    {
        return FAILURE;
    }

    if ((matrix[i][j] == CROSS) || (matrix[i][j] == CIRCLE))
    {
        cout<<"Already filled"<<endl;
        return FAILURE;
    }

    /* Update the matrix and user's mapping */
    userMap.push_back(numChoice);
    matrix[i][j] = CROSS;

    return SUCCESS;
}

/********************************************************************************************
* @name         : simulateComputer
* @Description  : Current implementation just selects any position randomly. No
                  intelligence is involved.
********************************************************************************************/
int simulateComputer()
{
    int min = 1;
    int max = 9;
    int i = 0;
    int j = 0;
    unsigned int val = 0;
    int retval = 0;
    bool found = false;

    sleep(1);
    while (!found)
    {
        val = generateRandom(min, max);
        // TODO in future: Generate 'val' from some intelligent algorithm.
        retval = mapNumToIndex(val, &i, &j);
        if (retval != SUCCESS)
        {
            return FAILURE;
        }

        /* Check to see if it is not filled already */
        if ((matrix[i][j] != CROSS) && (matrix[i][j] != CIRCLE))
        {
            found = true;
        }
    }

    /* Update the matrix and computer's mapping */
    computerMap.push_back(val);
    matrix[i][j] = CIRCLE;

    return SUCCESS;
}

/********************************************************************************************
* @name         : generateRandom
* @Description  : Generate a random number in the range [min, max]
********************************************************************************************/
unsigned int generateRandom(int min, int max)
{
    unsigned int num = 0;
    unsigned int tmp = 0;
    struct timeval tp;

    gettimeofday(&tp, NULL);
    srand(tp.tv_usec);
    num = rand();

    /* restirict within min and max */
    tmp = (num % max) + min;

    /* Wrap around */
    if (tmp > max)
    {
        num = min + (tmp - max);
    }
    else
    {
        num = tmp;
    }

    return num; 
}

