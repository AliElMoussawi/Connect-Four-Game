#include <stdbool.h>
#include <stdio.h>
#include<stdlib.h>
#include <time.h>



#include <ctype.h>
#include <sys/types.h>

#define row 6
#define column 7
//function prototypes
void  startGame();
//ENUM for signaling what player turn it is
enum player {
	P_ONE,//player one
	P_TWO//player two
};
void gameControllerMultiplayer(void);

int value=0;
void getInfo(int in);
void displayBoard();
//global variables
char board[6][7];// initialize board
char name[2][30]; //double dimensional array to store names of the player
char gameOptions[2][40]={"Multi-player","alone"};// here we want to specify the option that play can game offer
int winner = -1;//if winner = -1 then there is no winner until then - if winner = 1 then there is a winner
char* winnerName[];//displays the winner name
double timer[2] = {0.0,0.0};
//begin main function
int main() {
int input = 0;
int inputG=0;
int botLevel=0;

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
			printf("+----------+\n");
		if(input == 1) {
       do{ printf("[1] Multiplayer\n");
        printf("[0] alone \n");
        printf("-> ");
        scanf("%d", &inputG);
         printf("+----------+\n");
         getInfo(inputG);
        if(inputG==1){
            printf("\n\t%s, you have been given R\n",name[0]);
            printf("\t\t\t\t\t%s, you have been given Y\n",name[1]);
            printf("start the game with %s \n",name[0]);
            gameControllerMultiplayer();}
	 else{
             printf("\n\t%s, sadly you area playing alone\n",name[0]);
             printf("\n\t Level :");
             scanf("%d", &botLevel);
               if(botLevel==0){
               easyBot();
             }

	 }
        }while(inputG<0 || inputG>1);

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
			board[i][j] = 0;
		}
	}
}
//requires: positive integer represeting the 1<= column <= 7
//effcts: checks if the position of the token that will be fallen into is tacken or not
int checkTaken( int x) {
   int y=5;
    do{
        if(board[y][x]!=0){y--;}
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
	      printf("|%d",board[i][j]);
	      }
	      printf("|\n");
	      }
    printf("\t\t\t\t\t\t  -------------\n");
return 0;
}
//requires: none
//effects:displays on the screen the instructions and asks for the names of the players
void getInfo(int in){
    printf("Welcome To Connect Four Game!\n\n");
    printf("In order to win:\nYou have to be the first player to connect 4 discs of the same type in a row (either vertically, horizontally, or diagonally).\n");
    printf("\nIf the game ends in a tie, the player with the faster moves wins!\n");
    printf("Enter Player 1 name: ");
    scanf("%s", &name[0]);
    if(in==1){
    printf("Enter Player 2 name: ");
    scanf("%s", &name[1]);
    printf("Player 1: %s\nPlayer 2: %s",&name[0],&name[1]);
    }
    else{printf("Player 1: %s\n",&name[0]);
    }return 0;
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
void gameControllerMultiplayer(void) {
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
	int characters[3] = {1, 2, '\0'};
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

int  gameControllerBot(int n){
    return 0;
}
#ifndef CONNECT4_FUNCTIONS
#define CONNECT4_FUNCTIONS


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>


#endif

#include <ctype.h>
#include <sys/types.h>


#define BOARD_SIZE_HORIZ 7
#define BOARD_SIZE_VERT 6

int print_welcome(void);


void display_board(int board[][BOARD_SIZE_VERT]);


int random_move(int board[][BOARD_SIZE_VERT], int computer_num);



int player_move(int board[][BOARD_SIZE_VERT], int player_num);


bool check_win_or_tie(int board[][BOARD_SIZE_VERT], int last_move);


bool is_column_full(int board[][BOARD_SIZE_VERT], int m);

void update_board(int board[][BOARD_SIZE_VERT], int m, int player_num);

int check_winner(int board[][BOARD_SIZE_VERT], int last_move);

int best_move(int board[][BOARD_SIZE_VERT], int computer_num);


/* Forward function declarations  */

bool check_diagRD     (int board[][BOARD_SIZE_VERT], int m);
bool check_diagRU     (int board[][BOARD_SIZE_VERT], int m);
bool check_vertical   (int board[][BOARD_SIZE_VERT], int m);
bool check_horizontal (int board[][BOARD_SIZE_VERT], int m);
int  build2           (int board[][BOARD_SIZE_VERT], int computer_num);
int  build2_diagDN    (int board[][BOARD_SIZE_VERT], int computer_num);
int  build2_diagUP    (int board[][BOARD_SIZE_VERT], int computer_num);
int  build2horiz      (int board[][BOARD_SIZE_VERT], int computer_num);
int  build2vert       (int board[][BOARD_SIZE_VERT], int computer_num);
int  check3win        (int board[][BOARD_SIZE_VERT], int computer_num);
int  check3_diagRDwin (int board[][BOARD_SIZE_VERT], int computer_num);
int  check3_diagRUwin (int board[][BOARD_SIZE_VERT], int computer_num);
int  check3_horizwin  (int board[][BOARD_SIZE_VERT], int computer_num);
int  check3_vertwin   (int board[][BOARD_SIZE_VERT], int computer_num);




/*   Function print_welcome()  */
int print_welcome(void)
{

    char c;

    srand(time(NULL));


    printf("\n*** Welcome to the Connect-Four game!!! ***\n");
    printf("Would you like to make the first move [y/n]: \n");

    c = getchar();

    while (getchar() != '\n') { } //clears stdin

    if (c ==    'n' || c == 'N') return 2;
    else return 1;

}
void display_board(int board[] [BOARD_SIZE_VERT])
{

    int r = 0;
    int c = 0;

       printf("\n\n\n\t\t\t\t\t\t  -------------\n");


    for (r = 0; r < BOARD_SIZE_VERT; ++r)
    {
                  printf("\t\t\t\t\t\t ");



        for (c = 0; c < BOARD_SIZE_HORIZ; ++c)
        {
            switch (board[c][r])
            {
                case 0:
                    printf("|0");
                    break;

                case 1:
                    printf("|1");
                    break;

                case 2:
                    printf("|2");
                    break;
                default:
                    printf("Error: board entry %d,%d invaid.\n",r,c);
                    break;
            }
        }
        printf("|\n");
    }    printf("\t\t\t\t\t\t  -------------\n");



    printf ("\t\t\t\t\t\t  1 2 3 4 5 6 7\n\n");
    return;
}


/*  Function random_move()  */

int random_move(int board[][BOARD_SIZE_VERT], int computer_num)
{
    bool valid = false;
    int m = 0;

    while (!valid)
    {
        m = (rand() % BOARD_SIZE_HORIZ) + 1;

        valid = !is_column_full(board,m);
    }
    update_board(board, m, computer_num);
    return m;
}
/*  Function player_move()  */
int player_move(int board[][BOARD_SIZE_VERT], int player_num)
{
    char c = 'c';  //Initializes c to a non-digit so isdigit(c) returns false
    int x = 0;

    /* the loop will repeat until the player enters a digit */
    while (!isdigit(c))
    {
        printf("Please enter your move: ");

        c = getchar();

        while (getchar() != '\n') { } //clears stdin

        /* x is the ASCII value of c; if c represents a digit, subtracting '0' *
         * will convert the character to the integer it represents.            */
        x = c - '0';

        //Checks whether x is valid, i.e. between 1 and 8
        if (x < 1 || x > 8)
        {
            printf("Not a valid move. Enter a column number!\n");
            c = 'c';       //reset c to a non-digit to continue looping
                           //in case the user entered a digit that was invalid
        }

        else
        {
            if (is_column_full(board,x))
            {
                printf("This column is full. Try again!.\n");
                c = 'c';
            }
            update_board(board, x, player_num);
        }
    }
    return x;
}

/*  Function check_win_or_tie()  */
bool check_win_or_tie(int board[][BOARD_SIZE_VERT], int last_move)
{
    int w;
    int c;
    int r = 0;

    w = check_winner(board, last_move);
    if (check_winner(board, last_move))
    {
        printf("*****************************\n");
        printf("* Player %c won!!! Game over *\n", (w == 1 ? 'X' : 'O'));
        printf("*****************************\n");
        return true;
    }
    else
    {
        for (c = 0; c < BOARD_SIZE_VERT; c++)
        {
            if (board[c][r] == 0) return false;
        }
        printf("*****************************\n");
        printf("* Game is a tie!! No winner *\n");
        printf("*****************************\n");
        return true;
    }
}

/*  Function is_column_full()  */
bool is_column_full(int board[][BOARD_SIZE_VERT], int m)
{
    if (board[m-1][0] == 0)
        return false;

    else
        return true;
}

/*  Function update_board()  */
void update_board(int board[][BOARD_SIZE_VERT], int m, int player_num)
{

    int c, i;

    // convert the column number to the array index for that column
    c = m - 1;

    for (i = BOARD_SIZE_VERT-1; i >= 0; --i)
    {
        if (board[c][i] != 0) continue;
        else
        {
            board[c][i] = player_num;
            return;
        }
    }
}


/*  Function check_winner  */
int check_winner(int board[][BOARD_SIZE_VERT], int last_move)
{
    int c;
    int i;

    //again, converts column of last_move to that column's array index
    c = last_move - 1;

    if (check_diagRU    (board, last_move) == true ||
        check_diagRD    (board, last_move) == true ||
        check_horizontal(board, last_move) == true ||
        check_vertical  (board, last_move) == true )
    {
        for (i = 0; i < BOARD_SIZE_VERT; i++)
        {
            switch (board[c][i])
            {
                case 0:
                    continue;
                case 1:
                    return 1;
                case 2:
                    return 2;
                default:
                    printf("Error! Value in board[%d][%d] invalid.\n",c,i);
                    return 0;
            }
        }
    }
    return 0;
}

/*  Function check_diagRD()  */
bool check_diagRD(int board[][BOARD_SIZE_VERT], int last_move)
{
    int r;  //row index
    int c;  //column index

    for (r = 0; r < 3; r++)
    {
        for (c = 0; c < 4; c++)
        {
            if (board[c][r] != 0               &&
                board[c][r] == board[c+1][r+1] &&
                board[c][r] == board[c+2][r+2] &&
                board[c][r] == board[c+3][r+3])
            {
                return true;
            }
            else continue;
        }
    }
    return false;
}

/*  Function check_diagRU()  */
bool check_diagRU(int board[][BOARD_SIZE_VERT], int last_move)
{
    int r;  //row index
    int c;  //column index

    for (r = 3; r < BOARD_SIZE_VERT; r++)
    {
        for (c = 0; c < 4; c++)
        {
            if (board[c][r] != 0               &&
                board[c][r] == board[c+1][r-1] &&
                board[c][r] == board[c+2][r-2] &&
                board[c][r] == board[c+3][r-3])
            {
                return true;
            }
            else continue;
        }
    }
    return false;
}

/*  Function check_ vertical()  */

bool check_vertical(int board[][BOARD_SIZE_VERT], int m)
{
    int r;  //row index
    int c;  //column index

    for (r = 0; r < 3; r++)
    {
        for (c = 0; c < BOARD_SIZE_HORIZ; c++)
        {
            if (board[c][r] != 0             &&
                board[c][r] == board[c][r+1] &&
                board[c][r] == board[c][r+2] &&
                board[c][r] == board[c][r+3])
            {
                return true;
            }
            else continue;
        }
    }
    return false;
}

/*  Function check_horizontal() checks for 4 in a row  */

bool check_horizontal(int board[][BOARD_SIZE_VERT], int m)
{
    int r;  //row index
    int c;  //column index

    for (r = 0; r < BOARD_SIZE_VERT; r++)
    {
        for (c = 0; c < 4; c++)
        {
            if (board[c][r] != 0             &&
                board[c][r] == board[c+1][r] &&
                board[c][r] == board[c+2][r] &&
                board[c][r] == board[c+3][r])
            {
                return true;
            }
            else continue;
        }
    }
    return false;
}

/*  Function best_move() - To be used in extra credit competition  */
int  best_move(int board[][BOARD_SIZE_VERT], int computer_num)
{
    int playerNum;
    int bestMove;

    playerNum = (computer_num == 1 ? 2 : 1);

    if (check3win(board, computer_num) != 8)
    {
        bestMove = check3win(board, computer_num);
        update_board(board, bestMove, computer_num);
        return bestMove;
    }
    else if (build2(board,computer_num) != 8)
    {
        bestMove = build2(board, computer_num);
        update_board(board, bestMove, computer_num);
        return bestMove;
    }

    else
    {
        bestMove = rand() % 7 + 1;
        update_board(board, bestMove, computer_num);
        return bestMove;
    }

}

/*  Function build2()  */
int build2(int board[][BOARD_SIZE_VERT], int computer_num)
{
    int build2;

    if (build2_diagDN(board,computer_num) != 8)
    {
        build2 = build2_diagDN(board,computer_num);
        return build2;
    }

    if (build2_diagUP(board,computer_num) != 8)
    {
        build2 = build2_diagUP(board,computer_num);
        return build2;
    }
    if (build2vert(board,computer_num) != 8)
    {
        build2 = build2vert(board,computer_num);
        return build2;
    }
    if (build2horiz(board,computer_num) != 8)
    {
        build2 = build2horiz(board,computer_num);
        return build2;
    }
    return 8;
}

/*  Function build2_diagDN()  */
int build2_diagDN(int board[][BOARD_SIZE_VERT], int computer_num)
{
    int c;
    int r;

    for (r = 0; r < 4; r++)
    {
        for (c = 0; c < 4; c++)
        {
            //check X X [] []
            if (board[c][r]     == computer_num  &&
                board[c+1][r+1] == computer_num  &&
                board[c+3][r+3] == 0             &&
                board[c+2][r+2] == 0)
            {
                if (is_column_full(board,c+3)) continue;

                if (r == 3 || board[c+2][r+1] != 0) return c+3;
            }

            //check [] [] X X
            if (board[c+2][r+2]  == computer_num  &&
                board[c+3][r+3]  == computer_num  &&
                board[c][r]      == 0             &&
                board[c+1][r+1]  == 0             &&
                board[c+1][r+2]  != 0)
            {
                if (is_column_full(board,c+2)) continue;

                return c+2;
            }

            //check [] X X []
            if (board[c+2][r+2]  == computer_num  &&
                board[c+1][r+1]  == computer_num  &&
                board[c][r]      == 0             &&
                board[c+3][r+3]  == 0)
            {
                if (is_column_full(board,c+4)) continue;

                if (r == 3 || board[c+3][r+3]  != 0) return c+4;
            }

            //check [] X [] X
            if (board[c+1][r+1]  == computer_num  &&
                board[c+3][r+3]  == computer_num  &&
                board[c][r]      == 0             &&
                board[c+2][r+2]  == 0             &&
                board[c][r+1]    != 0)
            {
                if (is_column_full(board,c+1)) continue;

                return c+1;
            }

            //check X [] X []
            if (board[c+2][r+2]  == computer_num  &&
                board[c][r]      == computer_num  &&
                board[c+1][r+1]  == 0             &&
                board[c+3][r+3]  == 0)
            {
                if (is_column_full(board,c+4)) continue;

                if (r == 3 || board[c+3][r+3]  != 0) return c+4;
            }

            //check X [] [] X
            if (board[c][r+1]    == computer_num  &&
                board[c+3][r+3]  == computer_num  &&
                board[c+1][r+1]  == 0             &&
                board[c+2][r+2]  == 0             &&
                board[c+2][r+3]  != 0)
            {
                if (is_column_full(board,c+3)) continue;

                return c+3;
            }
        }
    }
    return 8;
}


/*  Function build2_diagUP()  */
int build2_diagUP(int board[][BOARD_SIZE_VERT], int computer_num)
{
    int c;
    int r;

    for (r = 3; r < BOARD_SIZE_VERT; r++)
    {
        for (c = 0; c < 4; c++)
        {
            //check X X [] []
            if (board[c][r]      == computer_num  &&
                board[c+1][r-1]  == computer_num  &&
                board[c+3][r-3]  == 0             &&
                board[c+2][r-2]  == 0             &&
                board[c+3][r-2]  != 0)

                return c+4;

            //check [] [] X X
            if (board[c+2][r-2]  == computer_num  &&
                board[c+3][r-3]  == computer_num  &&
                board[c][r]      == 0             &&
                board[c+1][r-1]  == 0)
            {
                if (r == BOARD_SIZE_VERT || board[c][r+1] != 0) return c+1;
            }

            //check [] X X []
            if (board[c+2][r-2]  == computer_num  &&
                board[c+1][r-1]  == computer_num  &&
                board[c][r]      == 0             &&
                board[c+3][r-3]  == 0             &&
                board[c+3][r-2]  != 0)

                return c+4;

            //check [] X [] X
            if (board[c+1][r-1]  == computer_num  &&
                board[c+3][r-3]  == computer_num  &&
                board[c][r]      == 0             &&
                board[c+2][r-2]  == 0)
            {
                if (r == BOARD_SIZE_VERT || board[c][r+1] != 0)  return c+1;
            }

            //check X [] X []
            if (board[c+2][r-2]  == computer_num  &&
                board[c][r]      == computer_num  &&
                board[c+1][r-1]  == 0             &&
                board[c+3][r-3]  == 0             &&
                board[c+3][r-2]  != 0)

                return c+4;

            //check X [] [] X
            if (board[c][r+1]    == computer_num  &&
                board[c+3][r-3]  == computer_num  &&
                board[c+1][r-1]  == 0             &&
                board[c+2][r-2]  == 0             &&
                board[c+1][r-2]  != 0)

                return c+2;
        }
    }
    return 8;
}


/*  Function build2vert()  */
int build2vert(int board[][BOARD_SIZE_VERT], int computer_num)
{
    int c;
    int r;

    for (r = 2; r < BOARD_SIZE_VERT; r++)
    {
        for (c = 0; c < BOARD_SIZE_HORIZ; c++)
        {
            if (is_column_full(board,c))
            {
                //printf("column %d full. Skipping\n", c);
                continue;
            }
            if (board[c][r-1]  == 0            &&
                board[c][r]    == computer_num &&
                board[c][r+1]  == computer_num)
            {
                return c+1;
            }
        }
    }
    return 8;
}


/*  Function build2horiz()  */
int build2horiz(int board[][BOARD_SIZE_VERT], int computer_num)
{
    int c;
    int r;

    for (r = 5; r >= 0; r--)
    {
        for (c = 0; c < 4; c++)
        {
            //check X X [] []
            if (board[c+3][r]  == 0             &&
                board[c+2][r]  == 0             &&
                board[c+1][r]  == computer_num  &&
                board[c][r]    == computer_num)
            {
                if (r == 5 || board[c+3][r+1] != 0) return c+4;
            }
            //check [] [] X X
            if (board[c][r]    == 0             &&
                board[c+1][r]  == 0             &&
                board[c+2][r]  == computer_num  &&
                board[c+3][r]  == computer_num)
            {
                if (r == 5 || board[c][r+1] != 0) return c+1;
            }
            //check [] X X []
            if (board[c][r]    == 0             &&
                board[c+3][r]  == 0             &&
                board[c+2][r]  == computer_num  &&
                board[c+1][r]  == computer_num)
            {
                if (r == 5 || board[c+1][r+1] != 0) return c+1;
            }

            //check X [] X []
            if (board[c+3][r]  == 0             &&
                board[c+1][r]  == 0             &&
                board[c+2][r]  == computer_num  &&
                board[c][r]    == computer_num)
            {
                if (r == 5 || board[c+3][r+1] != 0) return c+4;
            }
            //check [] X [] X
            if (board[c][r]    == 0             &&
                board[c+2][r]  == 0             &&
                board[c+1][r]  == computer_num  &&
                board[c+3][r]  == computer_num)
            {
                if (r == 5 || board[c][r+1] != 0) return c+1;
            }
            //check X [] [] X
            if (board[c+1][r]  == 0             &&
                board[c+2][r]  == 0             &&
                board[c][r]    == computer_num  &&
                board[c+3][r]  == computer_num)
            {
                if (r == 5 || board[c+1][r+1] != 0) return c+2;
            }
        }
    }
    return 8;
}


/*  Function check3win()  */
int check3win(int board[][BOARD_SIZE_VERT], int computer_num)
{
    int winMove;
    int blockMove;
    int playerNum;

    playerNum = (computer_num == 1 ? 2 : 1);

    if (check3_vertwin(board, computer_num) != 8) {
        winMove = check3_vertwin(board, computer_num);
        return winMove;
    }
    if (check3_horizwin(board, computer_num) != 8) {
        winMove = check3_horizwin(board, computer_num);
        return winMove;
    }
    if (check3_diagRUwin(board, computer_num) != 8) {
        winMove = check3_diagRUwin(board, computer_num);
        return winMove;
    }
    if (check3_diagRDwin(board, computer_num) != 8) {
        winMove = check3_diagRDwin(board, computer_num);
        return winMove;
    }
    if (check3_vertwin(board, playerNum) != 8) {
        blockMove = check3_vertwin(board, playerNum);
        return blockMove;
    }
    if (check3_horizwin(board, playerNum) != 8) {
        blockMove = check3_horizwin(board, playerNum);
        return blockMove;
    }
    if (check3_diagRUwin(board, playerNum) != 8) {
        blockMove = check3_diagRUwin(board, playerNum);
        return blockMove;
    }
    if (check3_diagRDwin(board, playerNum) != 8) {
        blockMove = check3_diagRDwin(board, playerNum);
        return blockMove;
    }
    return 8;
}
/*  Function check3_vertwin()  */
int check3_vertwin(int board[][BOARD_SIZE_VERT], int computer_num)
{
    int c; //column index
    int r; //row index

    //start checking from 5th row; can't make a move if top row full
    for (r = 1; r < 4; r++)
    {
        for (c = 0; c < BOARD_SIZE_HORIZ; c++)
        {
            if (is_column_full(board,c))
            {
              //  printf("Column %d full. Skipping\n", c);
                continue;
            }

            if (board[c][r-1]   == 0                 &&
                board[c][r]     == computer_num      &&
                board[c][r+1]   == computer_num      &&
                board[c][r+2]   == computer_num)
            {
                return c+1; //changed from c
            }
        }
    }
    return 8;
}
/*  Function check3_horizwin()  */
int check3_horizwin(int board[][BOARD_SIZE_VERT], int computer_num)
{
    int c; //column index
    int r; //row index

    for (r = 5; r >= 0; r--)
    {
        for (c = 0; c < 5; c++)
        {
            //check X X X []
            if (board[c+3][r]  == 0                 &&
                board[c][r]    == computer_num      &&
                board[c+1][r]  == computer_num      &&
                board[c+2][r]  == computer_num)
            {
                if (r == 5 || board[c+3][r+1] != 0) return c+4; //changed from 3
            }
            //check X [] X X
            if (board[c+1][r] == 0                 &&
                board[c][r]   == computer_num      &&
                board[c+2][r] == computer_num      &&
                board[c+3][r] == computer_num)
            {
                if (r == 5 || board[c+1][r+1] != 0) return c+2;  //changed from 1
            }
            //check X X [] X
            if (board[c+2][r]   == 0                 &&
                board[c][r]     == computer_num      &&
                board[c+1][r]   == computer_num      &&
                board[c+3][r]   == computer_num)
            {
                if (r == 5 || board[c+2][r+1] != 0) return c+3; //changed from 2
            }
            //check [] X X X
            if (board[c][r]   == 0                 &&
                board[c+1][r] == computer_num      &&
                board[c+2][r] == computer_num      &&
                board[c+3][r] == computer_num)
            {
                if (r == 5 || board[c][r+1] != 0) return c+1; //changed from 3
            }
        }
    }
    return 8;
}

/*  Function check3_diagRDwin()  */
int check3_diagRDwin(int board[][BOARD_SIZE_VERT], int computer_num)
{
    int c; //column index
    int r; //row index

    for (r = 0; r < 4; r++)
    {
        for (c = 0; c < 4; c++)
        {
            //check X X X []
            if (board[c+3][r+3] == 0            &&
                board[c][r]     == computer_num &&
                board[c+1][r+1] == computer_num &&
                board[c+2][r+2] == computer_num)
            {
                if (r == 3 || board[c+3][r+4] == 1 || board[c+3][r+4] == 2) return c+4;
            }

            //check X X [] X
            if (board[c+2][r+2] == 0            &&
                board[c][r]     == computer_num &&
                board[c+1][r+1] == computer_num &&
                board[c+3][r+3] == computer_num &&
                board[c+2][r+3] != 0 )
            {
                return c+3;
            }
            //check X [] X X
            if (board[c+1][r+1] == 0            &&
                board[c][r]     == computer_num &&
                board[c+2][r+2] == computer_num &&
                board[c+3][r+3] == computer_num &&
                board[c+1][r+2] != 0)
            {
                return c+2;
            }
            //check [] X X X
            if (board[c][r]     == 0                 &&
                board[c+1][r+1] == computer_num      &&
                board[c+2][r+2] == computer_num      &&
                board[c+3][r+3] == computer_num)
            {
                if (r == 5 || board[c][r+1] != 0) return c+1; //changed from 3
            }
        }
    }
    return 8;
}
/*  Function check3_diagRUwin()  */
int check3_diagRUwin(int board[][BOARD_SIZE_VERT], int computer_num)
{
    int c; //column index
    int r; //row index

    for (r = 3; r < BOARD_SIZE_VERT; r++)
    {
        for (c = 0; c < 4; c++)
        {
            //check X X X []
            if (board[c+3][r-3] == 0            &&
                board[c][r]     == computer_num &&
                board[c+1][r-1] == computer_num &&
                board[c+2][r-2] == computer_num &&
                board[c+3][r-2] != 0)
            {
                return c+4; //changed from 3?
            }

            //check X X [] X
            if (board[c+2][r-2] == 0            &&
                board[c][r]     == computer_num &&
                board[c+1][r-1] == computer_num &&
                board[c+3][r-3] == computer_num &&
                board[c+2][r-1] != 0)
            {
                return c+3;  //changed from 2?
            }
            //check X [] X X
            if (board[c+1][r-1] == 0            &&
                board[c][r]     == computer_num &&
                board[c+2][r-2] == computer_num &&
                board[c+3][r-3] == computer_num &&
                board[c+1][r] != 0)
            {
                return c+2;  //changed from 1?
            }
            //check [] X X X
            if (board[c][r]     == 0                 &&
                board[c+1][r+1] == computer_num      &&
                board[c+2][r+2] == computer_num      &&
                board[c+3][r+3] == computer_num)
            {
                if (r == 5 || board[c][r+1] != 0) return c+1; //changed from 3
            }
        }
    }
    return 8;
}


/*  End of file  */





int easyBot()
{
   int board[BOARD_SIZE_HORIZ][BOARD_SIZE_VERT] = { {0} };
   int player_num, computer_num;
   int last_move;


   /* Ask Alice if she wants to go first */
   player_num = print_welcome();
   if (player_num == 1) computer_num = 2;
   else computer_num = 1;

   /* If Alice wants to go first, let her make a move */
   if (player_num == 1)
   {
      display_board(board);
      last_move = player_move(board,player_num);
      display_board(board);
   }


   /* The main loop */

   while (1)
   {
      /* Make a computer move, then display the board */
      last_move = best_move(board,computer_num);
      printf("Computer moved in column: %d\n", last_move);
      display_board(board);

      /* Check whether the computer has won */
      if (check_win_or_tie(board,last_move)) return 0;


      /* Let Alice make a move, then display the board */
      last_move = player_move(board,player_num);
      display_board(board);

      /* Check whether Alice has won */
      if (check_win_or_tie(board,last_move)) return 0;


   } /* end of while (1) */

} /* end of main() */



