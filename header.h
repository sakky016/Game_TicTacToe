#include <stdio.h>
#include <iostream>
#include <string.h>
#include <sys/time.h>
#include <stdlib.h>
#include <vector>
#include <list>
#include <stdlib.h>

using namespace std;

#define SUCCESS 0
#define FAILURE 1
#define MAX_TURNS 9
#define USER 100
#define COMPUTER 101

#define NONE 20
#define DRAW 21
#define WIN_USER 22
#define WIN_COMPUTER 23

#define CROSS 'x'
#define CIRCLE '#'

/* Global Variables */
extern char matrix[3][3];
extern int userTurns;
extern int computerTurns;
extern int winCombo[8][3];
extern vector<int> computerMap;
extern vector<int> userMap;

/* Functions */
int initMatrix();
void displayMatrix();
int checkWin(int player);
int fetchPlayerInput();
bool isPlayerTurn(int playerTurn);
int simulateComputer();
unsigned int generateRandom(int min, int max);
bool findInMap(vector<int> tmpMap, int val);
