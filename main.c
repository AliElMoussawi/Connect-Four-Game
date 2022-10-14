#include <stdbool.h>
#include <stdio.h>
#include<stdlib.h>
#include <time.h>


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
char* winnerName[];
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


void reset() {
    *winnerName="";
    value=0;
    winner = -1;
    timer[0]= 0.0;
    timer[1]= 0.0;
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

int checkForFour(int x,int y,char* character){
      checkHorizontally(x,y, character);
      checkVertically(x,y, character);
      checkOblique(x,y, character);
    }



//Function for getting input from keyboard to make a player place a piece
void makeTurn(enum player playerTurn) {
    clock_t start=clock();
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
    clock_t finish = clock();
    timer[playerTurn]= ((double)(finish-start));
   checkForFour(xCord,validPos,characters[playerTurn]);
}

void checkVertically(int x,int y,char* character){
    int counter=0;
    if(5-y>=3){
            int j;
        for(j=y;j<=5;j++){
            if(character==board[j][x-1]){
                counter++;
    }
            else{counter=0;}
            if(counter==4){
            winner = 1;
           }}
   }
    return 0;}

void checkHorizontally(int x,int y,char* character){
    int counter=0;
    int i,j=0;
    if(x<=4){
    while(j<x){
    for(i=0;i<4;i++){
        if(board[y][j+i]==character){
                counter++;
                if(counter==4){
            winner = 1;
           }}
        else{counter=0;}
       }
       j++;
       counter=0;
    }

   }else if(x==4){
        if(board[y][j+i]==character){
                counter++;}
        else{counter=0;}
    }
    else{
 while(j<x-6){
    for(i=0;i<4;i++){
        if(board[y][x-j-i-1]==character){
                counter++;
        if(counter==4){
                winner = 1;
           }
                }
        else{counter=0;}
        }
    j++;
    }
    }

    return 0;

    }
void checkOblique(int x,int y,char* character){
    int line,i,j ;
    int counter=0;
    if(x-1+2==y){
        line =2;
    }
    else if(x==y){
        line =1;
    }
    else if(x-1==y){
        line =0;
    }
     else if(x-2==y){
        line =-1;
    } else if(x-3==y){
        line =-2;
    }
     else if(x-4==y){
        line =-3;
    }
    for(i=0;i<6;i++){
            if(counter==4){
        winner=1;
        break;
    }
        if(character==board[i+line][i]){
            counter++;

        }else{
        counter=0;
        }
    }
      if(-(x-1)+3==y){
        line =3;
        printf("checking x  y" );
    }
    else if(-(x-1)+4==y){
        line =4;
    }
    else if(-(x-1)+5==y){
        line =5;
    }
     else if(-(x-1)+6==y){
        line =6;
    } else if(-(x-1)+7==y){
        line =7;
    }
     else if(-(x-1)+8==y){
        line =8;
        printf("checking x  y %d",line );
    }
    for(i=0;i<=8;i++){
            if(counter==4){
        winner=1;
        break;
    }
        if(character==board[-i+line][i]){
            counter++;
            printf("value : %c",board[-i+line][i]);

        }else{
        counter=0;
        }
    }

    }

