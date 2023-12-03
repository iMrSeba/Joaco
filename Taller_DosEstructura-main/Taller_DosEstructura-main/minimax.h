typedef struct nodo{
    struct nodo **childrens;
    int *moves;
    int num_children;
    char board[ROWS][COLUMNS];
    double worth;
    int level;
} Nodo;


void copyBoard(char [ROWS][COLUMNS],char [ROWS][COLUMNS]);
Nodo createNodo(char [ROWS][COLUMNS], int , int);
void createLevel(Nodo *,char,int);
void createDoubleLevel(Nodo *,int);
void createTree(Nodo *,int,int);
void deleteTree(Nodo *);
void PrintTree(Nodo *);
void EvaluateLeaves(Nodo *);
void MiniMax(Nodo *);
void MiniMaxPoda(Nodo *,double,double);
int chooseRoll(char [ROWS][COLUMNS],int);