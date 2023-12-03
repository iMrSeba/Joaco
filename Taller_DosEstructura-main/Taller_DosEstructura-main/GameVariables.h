#define ROWS 6
#define COLUMNS 7
#define VICTORY_VALUE 1024
#define Token_CPU 'X'
#define Token_Player 'O'

void PrintBoard(char [ROWS][COLUMNS]);
int Odds(char[ROWS][COLUMNS]);
int CPUVictory(char board[ROWS][COLUMNS]);
int PlayerVictory(char board[ROWS][COLUMNS]);
void ApplyRoll(char [ROWS][COLUMNS],int, char);
double Heuristic(char [ROWS][COLUMNS]);
double evaluateHumanConnection(char [ROWS][COLUMNS]);
