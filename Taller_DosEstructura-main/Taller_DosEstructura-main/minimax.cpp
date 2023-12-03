#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <limits>
#include <ctime>
#include <iostream>
#include "../Taller2V2/GameVariables.h"
#include "minimax.h"

void copyBoard(char board1 [ROWS][COLUMNS],char board2[ROWS][COLUMNS]){
    for(int i = 0;i<ROWS;i++){
        for(int j = 0;j<COLUMNS;j++){
            board2[i][j] = board1[i][j];
        }
    }
}
Nodo createNodo(char board [ROWS][COLUMNS], int level, int difficulty){
    Nodo p;
    p.level = level;
    copyBoard(board,p.board);
    p.num_children = Odds(board);
    p.worth = 0;
    if(CPUVictory(p.board)|| PlayerVictory(p.board)|| p.level == 2*difficulty+2){
        p.num_children = 0;
    }
    if(p.num_children != 0){
        p.childrens = (Nodo **) malloc(p.num_children*sizeof (Nodo *));
        p.moves = (int *) malloc(p.num_children*sizeof (int));
        int j = 0;
        int i = 0;
        for(i = 0;i<COLUMNS;i++){
            if(board[0][i] == ' '){
                p.moves[j] = i;
                j+= 1;
            }

        }
    }
    else{
        p.childrens = NULL;
        p.moves = NULL;
    }
    return p;

}
void createLevel(Nodo * Father,char token,int difficulty){
    int i;
    Nodo * children;
    for(i = 0;i< Father->num_children;i++){
        children = (Nodo *) malloc(sizeof (Nodo));
        copyBoard(Father->board,children->board);
        ApplyRoll(children->board,Father->moves[i],token);
        *children = createNodo(children->board,Father->level+1,difficulty);
        Father->childrens[i] = children;
    }
}

void createDoubleLevel(Nodo * root,int difficulty){
    createLevel(root,Token_CPU,difficulty);
    for(int i = 0; i<root->num_children;i++){
        createLevel(root->childrens[i],Token_Player,difficulty);
    }
}
void createTree(Nodo *root,int depth,int difficulty){
    createDoubleLevel(root,difficulty);
    if(depth == 0)return;
    else{
        for(int i = 0;i<root->num_children;i++){
            for(int j = 0;j<root->childrens[i]->num_children;j++){
                createTree(root->childrens[i]->childrens[j],depth-1,difficulty);
            }
        }
    }
    return;
}
void deleteTree(Nodo *root){
    if(root->num_children == 0){
        free(root);
    }else{
        for(int i= 0;i<root->num_children;i++){
            deleteTree(root->childrens[i]);
        }
        free(root->childrens);
        free(root->moves);
    }
    return;
}
void PrintTree(Nodo *root){
    char * tab = "";
    if(root -> level != 0){
        tab = (char *) malloc((2*root->level+1)*sizeof(char));
        for(int j = 0;j<2*root->level;j++)tab[j] = ' ';
        tab[2*root->level] = '\0';
    }
    if (root->num_children == 0) printf("%sNodo (valor %lf)\n",tab,root->worth);
    else{
        int i;
        printf("%sNodo (valor %lf)\n",tab,root->worth);
        for (i=0;i<root->num_children;i++) PrintTree(root->childrens[i]);
    }
    free(tab);
}
void EvaluateLeaves(Nodo *root){
    if(root->num_children == 0){
        root->worth = Heuristic(root->board);
    }else{
        for(int i = 0;i<root->num_children;i++){
            EvaluateLeaves(root->childrens[i]);
        }
    }
}
void MiniMax(Nodo *root){
    int i;
    if(root->num_children != 0){
        for(i = 0;i<root->num_children;i++){
            if(root->childrens[i]->num_children != 0){
                MiniMax(root->childrens[i]);
            }
        }
        if(root->level % 2 == 0){ //Max
            root->worth = root->childrens[0]->worth;
            for(i = 1;i<root->num_children;i++){
                if(root->childrens[i]->worth > root->worth){
                    root->worth = root->childrens[i]->worth;
                }
            }
        }
        if(root->level % 2 == 1){ //Min
            root->worth = root->childrens[0]->worth;
            for(i = 1;i<root->num_children;i++){
                if(root->childrens[i]->worth < root->worth){
                    root->worth = root->childrens[i]->worth;
                }
            }
        }
        root->worth /= 2;
    }
}
void MiniMaxPoda(Nodo *root, double alpha, double beta) {
    int i;

    if (root->num_children != 0) {
        for (i = 0; i < root->num_children; i++) {
            if (root->childrens[i]->num_children != 0) {
                MiniMaxPoda(root->childrens[i], alpha, beta);
            }

            if (root->level % 2 == 0) { // Max
                alpha = std::max(alpha, root->childrens[i]->worth);
                if (beta <= alpha) {
                    break; // Poda alfa-beta
                }
            } else { // Min
                beta = std::min(beta, root->childrens[i]->worth);
                if (beta <= alpha) {
                    break; // Poda alfa-beta
                }
            }
        }

        if (root->level % 2 == 0) { // Max
            root->worth = alpha;
        } else { // Min
            root->worth = beta;
        }
        root->worth /= 2;
    }
}


int chooseRoll(char board [ROWS][COLUMNS],int difficulty) {
    Nodo root = createNodo(board, 0, difficulty);
    int move;
    createTree(&root, difficulty, difficulty);
    EvaluateLeaves(&root);
    //MiniMax(&root);
    MiniMaxPoda(&root, std::numeric_limits<double>::lowest(), std::numeric_limits<double>::max());
    //PrintTree(&root);

    // Se elige random entre todas las posibilidades igual de buenas
    int num_trys_goods = 0;
    int trys_goods[6];
    int j = 0;
    for (int i = 0; i < root.num_children; i++) {
        if (root.childrens[i]->worth == 2.0 * root.worth) {
            num_trys_goods++;
            trys_goods[j] = root.moves[i];
            j++;
        }
    }
    srand(time(NULL));
    int index = rand() % num_trys_goods;
    move = trys_goods[index];
    deleteTree(&root);
    return move;

}