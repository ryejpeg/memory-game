// PROJ 9 FINAL PROJECT
// MEMORY GAME
// A program that ______
// V0.1
// DEVS: RYAN ALMAZAN, ULYSSES RIVERA, DEL MYER

#include <stdio.h>
#include <string.h>
#define MAX_STR 100
#define MAX_NAME 15

void game(int difficulty);
void outputnames (FILE*fp, char array[]);
int menu();
int difficultySelect();
void coordinate( int *x, int *y, int *a ,  int *b);
void getcoord(int *x,int *y);
_Bool duplicate( int x, int y, int a, int b);


int main()
{
	FILE *fp;
	int choice, difficulty, scoreboard[10] = NULL;
  
	do
	{
		choice = menu();


		switch(choice)
		{
			case 1:	difficulty = difficultySelect();
				game(difficulty);
				break;
			case 2:	scores();
				
				
				
				outputnames(fp, array);
				break;
			case 0:	break;
//				does nothing.
		}
	}
	while(choice != 0);
		
	
  
	 
	fclose(fp);
	
	return 0;
}

int menu()
{
	int choice;
	
	printf("***MEMORY!***\n");
	printf("1 - Play Game\n");
	printf("2 - Check Scores\n");
	printf("0 - EXIT\n");
	
	scanf("%d", &choice);
}

int diffiultySelect()
{
	int difficulty;
	
	printf("Enter difficulty (1, 2, or 3): ");
	scanf("%d", &difficulty);
	
	return difficulty;
}

void outputnames(FILE*fp, char array[][10], int score[])
{
	char temp;
	int score, i = 0, j = 0, counter = 0;

		for (i; i< 15; i++)
		{
			for (j; (j< 15) || (temp[i][j] != '\n') ; j++)
			{
				scanf("%c", temp[i][j]);
				fprintf(output,"%c", temp[i][j]);
			}

			do
			{
				fprintf(output, " %d", score);
				counter ++;
			}
			while (counter != 10);
		}

	return char; 
}

#include <stdio.h>
void coordinate( int *x, int *y, int *a ,  int *b);
_Bool duplicate( int x, int y, int a, int b);
void getcoord(int *x,int *y);
int main()
{
int x=0, y=0, a=0, b=0;
	coordinate( &x,  &y, &a, &b);
	

return 0;
}

void coordinate( int *x, int *y, int *a, int *b)
{
int dup= 0;

	getcoord(x,y);
	getcoord(a,b);
	dup = duplicate(*x,*y,*a,*b);
	while (dup )
	{
		printf("duplicate\n");
		getcoord(a,b);
		dup = duplicate(*x,*y,*a,*b);
	}

	


	
}
void getcoord(int *x, int*y)
{

	printf("Enter your coordinates\n");
	scanf("%d\t%d",x,y);




}


_Bool duplicate( int x, int y, int a, int b)
{
	if(x ==a && y==b)
	{
		return 1;
	}
return 0;
		
}






//Del Myer, Project 9 (FINAL), TA Sara, group members: Ulysses & Ryan.
//Create a basic, rudimentary game of memory. This will encompass evrything we have learned in class,
//over the entire semester.
//This verison of the game will incldue the extra credit option of making the matrix (game board) appear
//each time an individual coordinate is entered by the user.

//preprocessor directives and header files 
#include <stdio.h>
#include <string.h> //should try not to use
#include <time.h>
#include <stdlib.h>

//define macro constants 

//declare function prototypes
void prefill_board(int board_size, char game_board[board_size][board_size]);

void fill_board_with_pairs(int difficulty, int board_size, char game_board[board_size][board_size]);

void shuffle_game_board(int difficulty, int board_size, char game_board[board_size][board_size]);

int random_number_generator(int board_size);

char random_symbol_generator(void);

//declare global variables

//main function
int main( int argc, char *argv[])
{
    //seed the "random" number generator with NULL
    srand(time(NULL));

    //declare local variables
    int difficulty = 5, board_size = 0;

    //testing out game board with pseudo board_size
    difficulty = ((rand() % (3 - 1 + 1)) + 1);

    //define board size as a variable of difficulty
    board_size = (2 * difficulty);

    //declare VLA, now that we have the difficulty, which determines the size of the game board
    //(or 2D array), after adding 1 to properly shift the indices
    char game_board[board_size][board_size];

    //prefill the game board with X's before the random characters, so we know which spots are taken
    prefill_board (board_size, game_board);

    //fill the game board with pairs, in tandem
    fill_board_with_pairs(difficulty, board_size, game_board);

    //shufflew the board
    shuffle_game_board(difficulty, board_size, game_board);

    //testing to display the shuffled board, so that you can see it. it willl be a different size each time you run the game
    for(int row_index = 0; row_index < board_size; row_index++)
    {
        for(int col_index = 0; col_index < board_size; col_index++)
        {
            printf("%c", game_board[row_index][col_index]);
        }   
        printf("\n");
    }


    


    //end program
    return 0;
}

//define functions
void prefill_board (int board_size, char game_board[board_size][board_size])
{
    for(int row_index = 0; row_index < board_size; row_index++)
    {
        for(int col_index = 0; col_index < board_size; col_index++)
        {
            game_board[row_index][col_index] = 'X';
        }   
    }

    //end function
    return;
}

void fill_board_with_pairs(int difficulty, int board_size, char game_board[board_size][board_size])
{
    //declare local variables
    int row = 0, column = 0, number_pairs = 0, counter = 0;
    char pair_symbol = 'A';
    _Bool pair = 1;
    
    //controlling expression for previous looping attempt below (commented out)
    number_pairs = (difficulty * board_size);

    //new idea for assigning pairs of "randomly" generated symbols, in tandem order (must be shuffled)
    for(int row_index = 0; row_index < board_size; row_index++)
    {
        for(int col_index = 0; col_index < board_size; col_index++)
        {
            game_board[row_index][col_index] = random_symbol_generator();
            pair_symbol = game_board[row_index][col_index];
            col_index++;
            game_board[row_index][col_index] = pair_symbol;
        }   
    }

    //This should work, and almost does; upon testing. Find out why is does not.
    /*
    do
    {
        row = random_number_generator(board_size - 1);
        column = random_number_generator(board_size - 1);
        printf("1\n");
        if(game_board[row][column] == 'X')
        {
            printf("2\n");
            game_board[row][column] = random_symbol_generator();
            pair_symbol = game_board[row][column];
            pair = 1;
            while(pair)
            {
                printf("3\n");
                row = random_number_generator(board_size - 1);
                column = random_number_generator(board_size - 1);
                if(game_board[row][column] == 'X')
                {
                    printf("4\n");
                    game_board[row][column] = pair_symbol;
                    pair = 0;
                    counter++;
                }
            }
        }
        
    } while(counter <= number_pairs);
    */

    return;
}

void shuffle_game_board(int difficulty, int board_size, char game_board[board_size][board_size])
{
    int row = 0, column = 0;
    char pair_symbol1  = 'A', pair_symbol2 = 'A';

    for(int index = 0; index < 3; index++)
    {
    for(int row_index = 0; row_index < board_size; row_index++)
    {
        for(int col_index = 0; col_index < board_size; col_index++)
        {
            pair_symbol1 = game_board[row_index][col_index];
            row = random_number_generator(board_size);
            column = random_number_generator(board_size);
            game_board[row_index][col_index] = game_board[row][column];
            game_board[row][column] = pair_symbol1;
            
        }   
    }
    }
    return;
}

int random_number_generator(int board_size)
{
    //declare local variables
    int number = 3;
    
    //use rand to make the number "random" within the range of the game board size
    //(size of the indices of the 2D array) which is based on the difficulty level
    number = ((rand() % ((board_size - 1) - 0 + 1)) + 0);
    return number;
}

char random_symbol_generator(void)
{
    //declare local variables
    char symbol = 'A';
    
    //use rand to make the symbol "random" within the range of ! to @
    symbol = ((rand() % ('@' - '!' + 1)) + '!');
    return symbol;
}



