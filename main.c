
#include <stdio.h>

//function prototypes

void  startGame();
void getInfo();
void displayBoard();
int verifySelection(int,int);
void checkForFour();

//global variables
char board[6][7];
char name[2][30]; //double dimensional array to store names of the player
int player; //to store the chance, to track which player is to enter the move
char gameOptions[2][40]={"Multi-player","alone"};// here we want to specify the option that play can game offer
int currentPlayer = 0;

//begin main function
int main() {
    getInfo();

    printf("\n%s, you take Y",name[0]);
    printf("\n%s, you take X\n",name[1]);
    displayBoard();

    return;}

void displayBoard() {

    printf("\t\t\t\t\t-------------\n");
       int i,j;
    for(i=0;i<7;i++){
            printf("\t\t\t\t\t");
      for(j=0;j<6;j++)
      {
	      //printf("element - [%d],[%d] : ",i,j);

	      printf("|%d",board[i][j]);
	      }
	      printf("|\n");     }
    printf("\t\t\t\t\t-------------\n");
return 0;

}
void startGame(){

return 0;}
int verifySelection(int square, int player) {
    return 0;
}
void getInfo(){//get players info
    printf("Only Multi-player game is allowed in  this version\n");
    printf("Enter Player 1 name: ");
    scanf("%s", &name[0]);
    printf("Enter Player 2 name: ");
    scanf("%s", &name[1]);
    printf("Player 1: %s\nPlayer 2: %s",&name[0],&name[1]);
    return 0;
}
void checkForFour() {

     int i,
         counter = 0;


     for(i = 0; i < 41; i++)
         if(board[i] != ' ')
               counter++;

     if(counter == 42) {

        printf("\nCAT GAME\n");
        return;
     }

}
