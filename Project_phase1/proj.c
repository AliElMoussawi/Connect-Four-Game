#include <stdbool.h>
#include <stdio.h>
#include<stdlib.h>
#include <time.h>
#define row 6
#define column 7
//function prototypes
void  startGame();
//ENUM for signaling what player turn it is
enum player {
	P_ONE,//player one
	P_TWO//player two
};

void getInfo();
void displayBoard();
//global variables
char board[6][7];// initialize board
char name[2][30]; //double dimensional array to store names of the player
char gameOptions[2][40]={"Multi-player","alone"};// here we want to specify the option that play can game offer
int value=0;
int winner = -1;//if winner = -1 then there is no winner until then - if winner = 1 then there is a winner
char* winnerName[];//displays the winner name
double timer[2] = {0.0,0.0};
//begin main function
int main() {
int input = 0;
do{
    int i;
    printf("\t\t\t\t\t\tConnect Four Game\n");
    printf("\t\t\t\t\t\t");

    for(i=0;i<17;i++)printf("%c",223);
    reset();
    displayBoard();

  do {
        printf("[1] Play game\n");
        printf("[0] Exit\n");
        printf("-> ");
        scanf("%d", &input);//the system assume the input is integer

			if(input < 0 || input > 1) {
				printf("INVALID INPUT PLEASE TRY AGAIN!\n");
			}
		}while(input < 0 || input > 1);

		if(input == 1) {
			printf("+----------+\n");
			 getInfo();
    printf("\n\t%s, you have been given 1",name[0]);
    printf("\t\t\t\t\t%s, you have been given 2\n",name[1]);
    printf("start the game with %s \n",name[0]);
	 gameController();
	}
		}while(input != 0);

	printf("\nTHANK YOU FOR PLAYING Connect Four !\n");

    return 0 ;}

//requires: none
//effects: fill the board with zeros
void reset() {
    *winnerName="";
    value=0;
    winner = -1;
    timer[0]= 0.0;
    timer[1]= 0.0;
	for(int i = 0; i < row; i++) {
		for(int j = 0; j < column; j++) {
			board[i][j] = '0';
		}
	}
}
//requires: positive integer represeting the 1<= column <= 7
//effcts: checks if the position of the token that will be fallen into is tacken or not
int checkTaken( int x) {
   int y=5;
    do{
        if(board[y][x]!='0'){y--;}
        else{return y; }
    }while(y>=0);//if y is 6 the function will return -1 and the programmer will recall it from another x
    return -1;
}

//requires: two positive integers representing the coordinates of the disc and a character that is either 1 or 2 depending on the player
//effects: replace the zero with 1 or 2 on those coordinates
void placePiece(char character, int x, int y) {
	board[(y )][(x-1)] = character;
}
//requires: none
//effects: display the game for players
void displayBoard() {

    printf("\n\n\n\t\t\t\t\t\t  -------------\n");
       int i,j;
    for(i=0;i< row;i++){
            printf("\t\t\t\t\t\t ");
      for(j=0;j< column;j++)
      {
	      printf("|%c",board[i][j]);
	      }
	      printf("|\n");
	      }
    printf("\t\t\t\t\t\t  -------------\n");
return 0;
}
//requires: none
//effects:displays on the screen the instructions and asks for the names of the players
void getInfo(){
    printf("Welcome To Connect Four Game!\n\n");
    printf("In order to win:\nYou have to be the first player to connect 4 discs of the same type in a row (either vertically, horizontally, or diagonally).\n");
    printf("\nIf the game ends in a tie, the player with the faster moves wins!\n");
    printf("\nNote that: only Multi-player option is allowed in this version\n\n");
    printf("Enter Player 1 name: ");
    scanf("%s", &name[0]);
    printf("Enter Player 2 name: ");
    scanf("%s", &name[1]);
    printf("Player 1: %s\nPlayer 2: %s",&name[0],&name[1]);
    return 0;
}
//effects: switch turns 
enum player switchPlayer(enum player playerTurn) {
	if(playerTurn == 0) {
		enum player temp = P_TWO;

		return temp;
	}
	enum player temp = P_ONE;
	return temp;
}



//effects: This is the function that will be called to start the game
void gameController(void) {
	enum player playerTurn = P_ONE;

	int counter = 0;
	reset();

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

	if(winner == -1 && timer[0]==timer[1]) {
		printf("+-----------+\n");
		printf("| NO WINNER |\n");
		printf("+-----------+\n");

	} else {
	    if(winner == -1 && counter==42 ){
        if (timer[0]<timer[1]){
            *winnerName=&name[1];}
        else if(timer[0]>timer[1]){
             *winnerName=&name[0];}
        }
        else {
              *winnerName=&name[playerTurn];
        }
		printf("+-----------------+\n");
		printf("| WINNER PLAYER %s |\n",*winnerName);
        printf("+-----------------+\n");
	}}

void checkForFour(char* character){
      winner = check(character);
    }



//Function for getting input from keyboard to make a player place a piece
void makeTurn(enum player playerTurn) {
    clock_t start=clock();
	printf("| Player %d |\n", (playerTurn + 1));
	int validPos = 0;
	int xCord = -1;
	//Getting the character to be placed;
	char characters[3] = {'1', '2', '\0'};
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
    clock_t finish = clock();
    timer[playerTurn]= ((double)(finish-start));
   checkForFour(characters[playerTurn]);
}
//requires: character 1 or 2
//effects: determines whether there is a horizontal, vertical, or oblique straight 4 1's or 2's around it 
int check(char* character){
    int i, j; 
        //checks oblique to the left ^ <-
    for (i=3; i<column; i++){
        for (j=0; j <= row-3; j++){
            if (board[i][j] == character && board[i-1][j+1] == character && board[i-2][j+2] == character && board[i-3][j+3] == character)
                return 1;
        }
    }
    //checks oblique to the right -> ^
    for (i=3; i < column; i++){
        for (j=3; j <= row; j++){
            if (board[i][j] == character && board[i-1][j-1] == character && board[i-2][j-2] == character && board[i-3][j-3] == character)
                return 1;
        }
    }
    //checks vertically
    for (j = 0; j<=row -3 ; j++ ){
        for (i = 0; i<column; i++){
            if (board[i][j] == character && board[i][j+1] == character && board[i][j+2] == character && board[i][j+3] == character){
                return 1;
            }          
        }
    }
    //checks horizontally
    for (i = 0; i<column-3 ; i++ ){
        for (j = 0; j <= row; j++){
            if (board[i][j] == character && board[i+1][j] == character && board[i+2][j] == character && board[i+3][j] == character){
                return 1;
            }          
        }
    }
    return -1;//if none are winner moves then winner remains -1 

}


