#include <stdio.h>
#include <iostream>
#include "GameVariables.h"

void PrintBoard(char board[ROWS][COLUMNS]){
    int i, j;

    printf("  ");
    for (i = 0; i < COLUMNS; i++)
        printf("%d   ", i + 1);
    printf("\n");

    printf("  ");
    for (i = 0; i < COLUMNS; i++)
        printf("v   ");
    printf("\n");

    for (i = 0; i < ROWS; i++) {
        printf(" ");
        for (j = 0; j < COLUMNS; j++)
            printf("--- ");
        printf("\n");

        printf("|");
        for (j = 0; j < COLUMNS; j++)
            printf(" %c |", board[i][j]);
        printf("\n");
    }

    printf(" ");
    for (i = 0; i < COLUMNS; i++)
        printf("--- ");
    printf("\n");
}
int Odds(char board[ROWS][COLUMNS]){
    int cont = 0;
    for(int j = 0;j<COLUMNS;j++){
        if(board[0][j] == ' '){
            cont++;
        }
    }
    return cont;
}
int CPUVictory(char board[ROWS][COLUMNS]){
    int i;int j;
    char token = Token_CPU;
    // Chequeo horizontal
    for(i=0;i<ROWS;i++){
        for(j=0;j<(COLUMNS-3);j++){
            if(board[i][j] == token && board[i][j+1] == token && board[i][j+2] == token && board[i][j+3] == token){
                return 1;
            }
        }
    }

    // Chequeo vertical
    for(j=0;j<COLUMNS;j++){
        for(i=0;i<(ROWS-3);i++){
            if(board[i][j] == token && board[i+1][j] == token && board[i+2][j] == token && board[i+3][j] == token){
                return 1;
            }
        }
    }

    // Chequeo diagonal principal
    for(i=0;i<(ROWS-3);i++){
        for(j=0;j<(COLUMNS-3);j++){
            if(board[i][j] == token && board[i+1][j+1] == token && board[i+2][j+2] == token && board[i+3][j+3] == token){
                return 1;
            }
        }
    }

    // Chequeo diagonal contraria
    for(i=0;i<5;i++){
        for(j=COLUMNS-1;j>2;j--){
            if(board[i][j] == token && board[i+1][j-1] == token && board[i+2][j-2] == token && board[i+3][j-3] == token){
                return 1;
            }
        }
    }

    return 0;

}
int PlayerVictory(char board[ROWS][COLUMNS]){
    int i;int j;
    char token = Token_Player;
    // Chequeo horizontal
    for(i=0;i<ROWS;i++){
        for(j=0;j<(COLUMNS-3);j++){
            if(board[i][j] == token && board[i][j+1] == token && board[i][j+2] == token && board[i][j+3] == token){
                return 1;
            }
        }
    }

    // Chequeo vertical
    for(j=0;j<COLUMNS;j++){
        for(i=0;i<(ROWS-3);i++){
            if(board[i][j] == token && board[i+1][j] == token && board[i+2][j] == token && board[i+3][j] == token){
                return 1;
            }
        }
    }

    // Chequeo diagonal principal
    for(i=0;i<(ROWS-3);i++){
        for(j=0;j<(COLUMNS-3);j++){
            if(board[i][j] == token && board[i+1][j+1] == token && board[i+2][j+2] == token && board[i+3][j+3] == token){
                return 1;
            }
        }
    }

    // Chequeo diagonal contraria
    for(i=0;i<5;i++){
        for(j=COLUMNS-1;j>2;j--){
            if(board[i][j] == token && board[i+1][j-1] == token && board[i+2][j-2] == token && board[i+3][j-3] == token){
                return 1;
            }
        }
    }

    return 0;

}
void ApplyRoll(char board[ROWS][COLUMNS],int column, char token){
    for(int i = 0;i<ROWS;i++){
        if(board[ROWS-1-i][column]== ' '){
            board[ROWS-1-i][column] = token;
            break;
        }
    }

}
double Heuristic(char board[ROWS][COLUMNS]){
    if(CPUVictory(board))return VICTORY_VALUE;
    if(PlayerVictory(board))return VICTORY_VALUE;
    double humanConnectionValue = evaluateHumanConnection(board);
    return VICTORY_VALUE + humanConnectionValue;


}
double evaluateHumanConnection(char board[ROWS][COLUMNS]) {
    double value = 0.0;

    // Evaluar horizontalmente
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLUMNS - 2; ++j) {
            if (board[i][j] == Token_Player &&
                board[i][j + 1] == Token_Player &&
                board[i][j + 2] == Token_Player) {
                value += 1.0;  // Puedes ajustar este valor según su importancia
            }
        }
    }

    // Evaluar verticalmente
    for (int i = 0; i < ROWS - 2; ++i) {
        for (int j = 0; j < COLUMNS; ++j) {
            if (board[i][j] == Token_Player &&
                board[i + 1][j] == Token_Player &&
                board[i + 2][j] == Token_Player) {
                value += 1.0;  // Puedes ajustar este valor según su importancia
            }
        }
    }

    // Evaluar diagonalmente hacia abajo y hacia arriba
    for (int i = 0; i < ROWS - 2; ++i) {
        for (int j = 0; j < COLUMNS - 2; ++j) {
            // Diagonal hacia abajo
            if (board[i][j] == Token_Player &&
                board[i + 1][j + 1] == Token_Player &&
                board[i + 2][j + 2] == Token_Player) {
                value += 1.0;  // Puedes ajustar este valor según su importancia
            }

            // Diagonal hacia arriba
            if (board[i + 2][j] == Token_Player &&
                board[i + 1][j + 1] == Token_Player &&
                board[i][j + 2] == Token_Player) {
                value += 1.0;  // Puedes ajustar este valor según su importancia
            }
        }
    }

    return value;
}
