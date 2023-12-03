#include "GameVariables.h"
#include "minimax.h"

void newGame(char [ROWS][COLUMNS]);
int PlayCPU(char [ROWS][COLUMNS],int,char);
int PlayPlayer(char [ROWS][COLUMNS],int, char);
void mainMenu();
void SelectDifficulty(int *);
void ScreenScore();
void PlayWithCPU();
void PlayerVsPlayer();
void CopyName(char *, char *);
void SeeScores(char [30][10],int [30]);
void NewScore(int ,int );