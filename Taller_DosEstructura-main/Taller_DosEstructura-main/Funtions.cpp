#include <iostream>
#include "Funtions.h"
#include "GameVariables.h"

void newGame(char board[ROWS][COLUMNS]){
    for(int i = 0;i<ROWS;i++){
        for(int j = 0;j<COLUMNS;j++){
            board[i][j ]= ' ';
        }
    }
}
int PlayPlayer(char board[ROWS][COLUMNS],int num_player, char token){
    char answer;
    int column;

    PrintBoard(board);

    std::cout << "Ingrese el numero de columna (1-7): ";
    std::cin >> answer;


    column = answer - '0' - 1;
    if (column < 0 || column >=7) {
        PrintBoard(board);
        std::cout << "Columna seleccionada fuera del tablero. Seleccione otra." << std::endl;
        return PlayPlayer(board, num_player, token);
    }

    if (board[0][column] != ' ') {
        PrintBoard(board);
        std::cout << "La columna %d esta llena! Selecciona otra." << column+1 << std::endl;
        return PlayPlayer(board, num_player, token);
    }

    ApplyRoll(board, column, token);
    return 0;

}
int PlayCPU(char board[ROWS][COLUMNS],int difficulty,char token){
    PrintBoard(board);
    //printf("Valor heuristico del tablero actual: %lf\n",Heuristic(board));
    std::cout<<"Esperando al rival...\n ";

    int column = chooseRoll(board,difficulty);
    ApplyRoll(board,column,token);


    return 0;
}
void mainMenu(){
    int opcion;

    do {
        std::cout << "----CONECTA 4----" << std::endl;
        std::cout << "1) Jugar contra la CPU" << std::endl;
        std::cout << "2) Jugar contra un amigo" << std::endl;
        std::cout << "3) Ver Puntajes" << std::endl;
        std::cout << "4) Salir" << std::endl;

        // Solicitar la entrada del usuario
        std::cout << "Ingrese su opcion (1-4): ";
        std::cin >> opcion;

        // Realizar acciones basadas en la opción ingresada
        switch (opcion) {
            case 1:
                // Código para la opción "Jugar contra la CPU"
                std::cout << "Has seleccionado 'Jugar contra la CPU'." << std::endl;
                PlayWithCPU();
                break;
            case 2:
                // Código para la opción "Jugar contra un amigo"
                std::cout << "Has seleccionado 'Jugar contra un amigo'." << std::endl;
                PlayerVsPlayer();
                break;
            case 3:
                // Código para la opción "Ver Puntajes"
                std::cout << "Has seleccionado 'Ver Puntajes'." << std::endl;
                ScreenScore();
                break;
            case 4:
                // Código para la opción "Salir"
                std::cout << "Saliendo del programa." << std::endl;
                break;
            default:
                // Mensaje para opciones no válidas
                std::cout << "Opción no válida. Por favor, elija una opción del 1 al 4." << std::endl;
        }
    } while (opcion != 4);  // Repetir el bucle hasta que el usuario elija salir (opción 4)

}


void SelectDifficulty(int *difficulty) {

    std::cout << "Seleccione la dificultad" << std::endl;
    std::cout << "    3 - Facil" << std::endl;
    std::cout << "    2 - Normal" << std::endl;
    std::cout << "    1 - Dificil" << std::endl;
    std::cout << "Ingrese su opcion (1-3): ";

    char answer;
    std::cin >> answer;

    *difficulty = answer - '0'-1 ;
    std::cout<<*difficulty<< std::endl;
    if (*difficulty < 0 || *difficulty > 2) {
        std::cout << "1, 2 o 3. Opcion no encontrada" << std::endl;
        SelectDifficulty(difficulty);
    }
}

void ScreenScore(){
    char player[30][10];
    int points[30];
    SeeScores(player,points);
    printf("--------------------- HIGHSCORES -----------------\n");
    printf("\n    FACIL     |     NORMAL     |     DIFICIL      \n");
    printf("--------------------------------------------------\n");
    for(int i = 0;i<10;i++){
        printf(" %-10s %3d | %-10s %3d | %-10s %3d\n",player[i],points[i],player[10+i],points[10+i],player[20+i],points[20+i]);
    }

}
void PlayWithCPU(){
    char board[ROWS][COLUMNS];int difficulty;
    newGame(board);
    SelectDifficulty(&difficulty);
    char player[30][10];int points[30];
    SeeScores(player, points);

    int MIN_RECORD = points[(3 - difficulty) * 10 - 1];
    int cont_plays = 1;

    while (1) {
        // Turno del jugador
        int EXIT = PlayPlayer(board, 0, 'O');
        if (EXIT == 1) {
            break;
        }

        if (PlayerVictory(board)) {
            PrintBoard(board);
            std::cout << "Gana el jugador 1 en " << cont_plays << " jugadas" << std::endl;
            if (cont_plays < MIN_RECORD) {
                NewScore(cont_plays, difficulty);
                ScreenScore();
            }
            break;
        }

        //Turno CPU

        PlayCPU(board, difficulty, 'X');
        if (CPUVictory(board)) {
            PrintBoard(board);
            std::cout << "Gana la CPU " <<std::endl;
            break;
        }

        if (Odds(board) == 0) {
            PrintBoard(board);
            std::cout << "Se acabo el juego." << std::endl;
            break;
        }

        cont_plays++;
    }
}
void PlayerVsPlayer(){
    char board[ROWS][COLUMNS];
    int EXIT;
    newGame(board);
    int cont_plays = 1;
    while(1){
        EXIT = PlayPlayer(board,1,'O');
        if(EXIT == 1){
            break;
        }
        if(PlayerVictory(board)){
            PrintBoard(board);
            std::cout<<"Gana el jugador 1!"<<std::endl;
            break;
        }
        EXIT = PlayPlayer(board,2,'X');
        if(EXIT == 1){
            break;
        }
        if(CPUVictory(board)){
            PrintBoard(board);
            std::cout<<"Gana el jugador 2!"<<std::endl;
            break;
        }
        if(Odds(board) == 0){
            PrintBoard(board);
            std::cout<<"Se acabo el juego. Empate."<<std::endl;
            break;
        }
        cont_plays++;
    }
}
void CopyName(char *dest, char *source){
    int i = 0;
    while (source[i]!='\0'){
        dest[i] = source[i];
        i++;
    }
    dest[i] = '\0';
}

void SeeScores(char player[30][10],int points[30]){
    FILE *HIGHSCORES = fopen("highscores.txt","r+");
    for (int i=0;i<30;i++) fscanf(HIGHSCORES,"%s %d",player[i],points+i);
    fclose(HIGHSCORES);
}
void NewScore(int playerPoints ,int difficulty){
    printf("\n\n********************* NUEVO RECORD!!! *********************\n");
    char player[30][10];
    int points[30];
    SeeScores(player,points);

    int pos = (3-difficulty)*10-1;
    while (playerPoints<points[pos]){
        pos--;
    }
    char playerName[10];
    printf("Introduce tu nombre (maximo 10 caracteres): "); scanf("%s",&playerName);

    for(int i=(3-difficulty)*10-1;i>(3-difficulty-1)*10;i--){
        if(playerPoints < points[i-1]){
            CopyName(player[i],player[i-1]);
            points[i] = points[i-1];
            CopyName(player[i-1],playerName);
            points[i-1] = playerPoints;
        }
        else break;
    }

    FILE *NEWHIGHSCORES = fopen("highscores.txt","w+");
    for (int i=0;i<30;i++){
        fprintf(NEWHIGHSCORES,"%s %d\n",player[i],points[i]);
    }
    fclose(NEWHIGHSCORES);
}
