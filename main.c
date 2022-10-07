#include <stdbool.h>
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
char board[6][7];
char name[2][30]; //double dimensional array to store names of the player
char gameOptions[2][40]={"Multi-player","alone"};// here we want to specify the option that play can game offer
int value=0;
int winner = -1;
//begin main function
int main() {
int input = 0;
do{
    int i;
    printf("\t\t\t\t\t\tConnect Four Game\n");
    printf("\t\t\t\t\t\t");

    for(i=0;i<17;i++)printf("%c",223);
    resetBoard();
    displayBoard();

  do {
        printf("[1] Play game\n");
        printf("[0] Exit\n");
        printf("-> ");
        scanf("%d", &input);

			if(input < 0 || input > 1) {
				printf("INVALID INPUT PLEASE TRY AGAIN!\n");
			}
		}while(input < 0 || input > 1);

		if(input == 1) {
			printf("+----------+\n");
			 getInfo();
    printf("\n\t%s, you have been given R",name[0]);
    printf("\t\t\t\t\t%s, you have been given Y\n",name[1]);
    printf("start the game with %s \n",name[0]);
	 gameController();
	}
		}while(input != 0);

	printf("\nTHANK YOU FOR PLAYING Connect Four !\n");

    return 0 ;}


void resetBoard() {
	for(int i = 0; i < 6; i++) {
		for(int j = 0; j < 7; j++) {
			board[i][j] = '0';
		}
	}
}
int checkTaken( int x) {
   int y=5;
    do{
        if(board[y][x]!='0'){y--;}
        else{return y; }
    }while(y>=0);//if y is 6 the function will return -1 and the programmer will recall it from another x
    return -1;
}

void placePiece(char character, int x, int y) {

	board[(y )][(x-1)] = character;
}
// display the game for players
void displayBoard() {

    printf("\n\n\n\t\t\t\t\t\t  -------------\n");
       int i,j;
    for(i=0;i<6;i++){
            printf("\t\t\t\t\t\t ");
      for(j=0;j<7;j++)
      {
	      printf("|%c",board[i][j]);
	      }
	      printf("|\n");
	      }
    printf("\t\t\t\t\t\t  -------------\n");
return 0;
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

enum player switchPlayer(enum player playerTurn) {
	if(playerTurn == 0) {
		enum player temp = P_TWO;

		return temp;
	}
	enum player temp = P_ONE;
	return temp;
}



//This is the function that will be called to start the game
void gameController(void) {
	enum player playerTurn = P_ONE;

	int counter = 0;
	resetBoard();

	do {
		displayBoard();
		makeTurn(playerTurn);
		//winner = checkWonGame(board, playerTurn);

		if(winner == -1) {
			playerTurn = switchPlayer(playerTurn);
		}

		printf("\n----------+\n");
		counter++;


	} while (winner == -1 && counter < 42);

	displayBoard();

	if(winner == -1) {

		printf("+-----------+\n");
		printf("| NO WINNER |\n");
		printf("+-----------+\n");
	} else {
		printf("+-----------------+\n");
		printf("| WINNER PLAYER %s |\n", name[playerTurn]);
	       	printf("+-----------------+\n");
	}

}

int checkForFour(int x,int y,char* character){
    checkVertically(x,y, character);

    }



//Function for getting input from keyboard to make a player place a piece
void makeTurn(enum player playerTurn) {
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

		validPos = checkTaken(xCord-1);
		if(validPos ==-1) {
			printf("SORRY THIS ROW IS FULL TRY ANOTHER ONE!\n");
		}
	} while(validPos ==-1);

	printf("Placing \"%c\" at position (%d)(%d)\n", characters[playerTurn], xCord,validPos);
    placePiece(characters[playerTurn], xCord, validPos);
   checkVertically(xCord,validPos,characters[playerTurn]);
   // printf(winner);
}

void checkVertically(int x,int y,char* character){
    int counter=0;
    if(5-y>=3){
            int j;
        for(j=y;j<=5;j++){
                printf("j:%d\n",j);

            if(character==board[j][x-1]){
                counter++;
                printf("c:%d",counter);
    }
            else{counter=0;}
            if(counter==4){
            winner = 1;
            int winner1=winner;
         printf("winner :%d",winner1);
           }}
   }
    else{
            printf("less than 4 ");
    }

    return 0;}
    /*
int checkHorizontally(int x,int y,char* character){
    int counter=0;
    int moveX=0;
    if(x<=4){
    int i,j=0;
    while(j!=y){
            j++;
    for(i=0;i<4;i++){
        if(board[y][j+moveX]==character){
                counter++;}
        else{counter=0;}
        }
    }
    }
    return 0;}

*/
