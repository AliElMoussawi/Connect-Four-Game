
#include <stdio.h>
#include<stdlib.h>
//function prototypes
void  startGame();
//ENUM for signaling what player turn it is
enum player {
	P_ONE,
	P_TWO
};

void getInfo();
void displayBoard();
//global variables
char board[7][6];
char name[2][30]; //double dimensional array to store names of the player
int player; //to store the chance, to track which player is to enter the move
char gameOptions[2][40]={"Multi-player","alone"};// here we want to specify the option that play can game offer
int currentPlayer = 1;
int game_playing =1;
int value=0;

//begin main function
int main() {
int input = 0;
do{
    int i;
    printf("\t\t\t\t\t\tConnect Four Game\n");
    printf("\t\t\t\t\t\t");

    for(i=0;i<17;i++)printf("%c",223);
    displayBoard();
    getInfo();
    printf("\n\t%s, you have been given R",name[0]);
    printf("\t\t\t\t\t%s, you have been given Y\n",name[1]);
    printf("start the game with %s \n",name[0]);
    do {
			printf("[1] Play game\n");
			printf("[0] Exit\n");
			printf("-> ");
			scanf("%d", &input);

			if(input < 0 || input > 1) {
				printf("INVALID INPUT PLEASE TRY AGAIN!\n");
			}
		} while(input < 0 || input > 1);

		if(input == 1) {
			printf("+----------+\n");
			gameController();
		}

	} while(input != 0);

	printf("\nTHANK YOU FOR PLAYING TIK TAK TOE!\n");
    return 0 ;}
void resetBoard(char **board) {
	for(int i = 0; i < 6; i++) {
		for(int j = 0; j < 7; j++) {
			board[i][j] = '0';
		}
	}
}
int checkTaken(char **board, int x) {
   int y=0;
    do{
        if(board[y][x]!='0'){y++;}
        else{return y; }
    }while(y<6);//if y is 6 the function will return -1 and the programmer will recall it from another x
    return -1;}
void placePiece(char **board, char character, int x, int y) {
	board[(y - 1)][(x - 1)] = character;
}
// display the game for players
void displayBoard() {

    printf("\n\n\n\t\t\t\t\t\t  -------------\n");
       int i,j;
    for(i=0;i<6;i++){
            printf("\t\t\t\t\t\t ");
      for(j=0;j<7;j++)
      {
	      printf("|%d",board[i][j]);
	      }
	      printf("|\n");     }
    printf("\t\t\t\t\t\t  -------------\n");
return 0;
}
enum player switchPlayer(enum player playerTurn) {
	if(playerTurn == 0) {
		enum player temp = P_TWO;
		return temp;
	}
	enum player temp = P_ONE;
	return temp;
}
void getInfo(){//get players info
    printf("Welcome To Connect Four Game\n");
    printf("To win you have to be the first player to connect 4  of the same type discs in \na row (either vertically, horizontally, or diagonally)");
    printf("\nOnly Multi-player option is allowed in  this version\n");
    printf("Enter Player 1 name: ");
    scanf("%s", &name[0]);
    printf("Enter Player 2 name: ");
    scanf("%s", &name[1]);
    printf("Player 1: %s\nPlayer 2: %s",&name[0],&name[1]);
    return 0;
}

//This is the function that will be called to start the game
void gameController(void) {
	enum player playerTurn = P_ONE;
	int winner = -1;
	int counter = 0;
	resetBoard(board);

	do {
		displayBoard();
		makeTurn(board, playerTurn);
		winner = checkWonGame(board, playerTurn);

		if(winner == -1) {
			playerTurn = switchPlayer(playerTurn);
		}

		printf("\n+----------+\n");
		counter++;
	} while (winner == -1 && counter < 42);

	displayBoard();

	if(winner == -1) {
		printf("+-----------+\n");
		printf("| NO WINNER |\n");
		printf("+-----------+\n");
	} else {
		printf("+-----------------+\n");
		printf("| WINNER PLAYER %d |\n", (playerTurn + 1));
	       	printf("+-----------------+\n");
	}

}

void checkForFour(){
     return;
}

//Function for getting input from keyboard to make a player place a piece
void makeTurn(char **board, enum player playerTurn) {
	printf("| Player %d |\n", (playerTurn + 1));
	int validPos = 0;
	int xCord = -1;
	//Getting the character to be placed;
	char characters[3] = {'R', 'Y', '\0'};

	do {
		//input validation for X cord
		do {
			printf("X cord: ");
			scanf("%d", &xCord);

			if(xCord < 1 || xCord > 7) {
				printf("INVALID INPUT PLEASE TRY AGAIN!\n");
		}
		} while(xCord < 1 || xCord > 7);

		validPos = checkTaken(board, xCord);

		if(validPos != 1) {
			printf("SORRY THIS POSITION IS TAKEN TRY AGAIN!\n");
		}
	} while(validPos != 1);

	printf("Placing \"%c\" at position (%d)\n", characters[playerTurn], xCord);
    placePiece(board, characters[playerTurn], xCord, validPos);
}
