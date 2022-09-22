
#include <stdio.h>

//function prototypes

void startGame();
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
    return;}

void displayBoard() {
return 0;
};
void startGame(){

return 0;}
int verifySelection(int square, int player) {
    return 0;
}
void getInfo(){
    printf("Only Multi-player is allowed in  this game\n");
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
