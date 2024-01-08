#include <stdio.h>
#include <stdbool.h>

bool isEmpty(char gameField[6][7], int col) {
    /// True si la colonne est vide ( dernière case vide )
    return gameField[0][col] == ' ';
}

int placecoin(char gameField[6][7], int col, char token){
    /// Boucle pour trouver la première case vide de la colonne et lui insérer le Token
    for(int i=6;i>=0;i--){
        if(gameField[i][col] == ' '){
            return gameField[i][col] = token;
        }
    }
}

int askPlayerAMove() {
    /// Intervention du Joueur pour le choix du placement de son Token dans une colonne
    int input = -1;
    do{
        printf("Choisissez votre colonne de 1-7 :");
        scanf("%d", &input);

    }while(input < 1 || input > 7);
    return input-1;
}

char getPlayerturn(int turnCpt, char tokenPlayer1, char tokenPlayer2){
    /// Méthode pour obtenir le token du joueur qui est entrain de jouer
    if(turnCpt%2 == 0){
        return tokenPlayer1;
    }else{
        return tokenPlayer2;
    }
}

bool isFull(char gameField[6][7]){
    /// True si le jeu est complet de token confondus
    for(int y = 0; y < 6; y++){
        for(int x = 0; x < 7; x++) {
            if(gameField[y][x] == ' '){
                return false;
            }
        }
    }
    return true;
}

char checkWinner(char gameField[6][7]){
    /// Return le gagnant si ses 4 tokens sont alignés
    char state = ' ';

    // Lignes
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 4; j++) {
            if (gameField[i][j] == gameField[i][j + 1] && gameField[i][j] == gameField[i][j + 2] && gameField[i][j] == gameField[i][j + 3] && gameField[i][j] != ' ') {
                return gameField[i][j];
            }
        }
    }

    // Colonnes
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 6; j++) {
            if (gameField[i][j] == gameField[i + 1][j] && gameField[i][j] == gameField[i + 2][j] && gameField[i][j] == gameField[ i + 3 ][j] && gameField[i][j] != ' ') {
                return gameField[i][j];
            }
        }
    }

    // Diagonales gauche/droite
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 4; j++) {
            if (gameField[i][j] == gameField[i + 1][j + 1] && gameField[i][j] == gameField[i + 2][j + 2] && gameField[i][j] == gameField[i + 3][j + 3] && gameField[i][j] != ' ') {
                return gameField[i][j];
            }
        }
    }

    // Diagonales droite/gauche
    for (int i = 0; i < 3; i++) {
        for (int j = 6; j > 2; j--) {
            if (gameField[i][j] == gameField[i + 1][j - 1] && gameField[i][j] == gameField[i + 2][j - 2] && gameField[i][j] == gameField[i + 3][j - 3] && gameField[i][j] != ' ') {
                return gameField[i][j];
            }
        }
    }

    if(isFull(gameField)){
        return 'n';
    }
    return state;
}

void displayWinner(char token){
    /// Affiche le vainqueur ou si le match est nul
    if( token == 'n'){
        printf("Match Nul");
    }else{
        printf("Le Joueur %c gagne!", token);
    }
}

void DisplayBoard(char gameField[6][7]){
    /// Affiche le plateau du puissance4

    // Première ligne pour les numéros de colonnes
    for(int i=1;i<8;i++){
        printf(" %d  ",i);
    }
    printf("\n");

    // Colonnes séparées par des "|"
    for(int y = 0; y < 6; y++){
        for( int x = 0; x < 7; x++){
            printf(" %c ", gameField[y][x]);
            if(x < 6){
                printf("|");
            }
        }
        printf("\n");
    }
}

void main(){
    /// Main avec un void puisqu'il qu'il ne fait qu'éxecuter les autres méthodes

    // Initialisation de la zone de jeu ( dimensions reprise du jeu original )
    char gameField[6][7] = {{' ', ' ', ' ', ' ', ' ', ' ', ' '},
                            {' ', ' ', ' ', ' ', ' ', ' ', ' '},
                            {' ', ' ', ' ', ' ', ' ', ' ', ' '},
                            {' ', ' ', ' ', ' ', ' ', ' ', ' '},
                            {' ', ' ', ' ', ' ', ' ', ' ', ' '},
                            {' ', ' ', ' ', ' ', ' ', ' ', ' '}};

    // Initialisation dy symbole des token au Joueurs 1 et 2
    char tokenP1 = '0';
    char tokenP2 = 'O';

    int turnCpt = 0;
    bool gameIsOver = false;

    while(!gameIsOver){
        int col = -1;
        do{
            DisplayBoard(gameField);
            col = askPlayerAMove();
        }while(!isEmpty(gameField, col));
        placecoin(gameField, col, getPlayerturn(turnCpt, tokenP1, tokenP2));
        turnCpt++;

        if(checkWinner(gameField) != ' '){
            gameIsOver = true;
        }
    }
    DisplayBoard(gameField);
    displayWinner(checkWinner(gameField));
}
