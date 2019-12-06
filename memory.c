// PROJ 9 FINAL PROJECT
// MEMORY GAME
// A program that ______
// V0.1
// DEVS: RYAN ALMAZAN, ULYSSES RIVERA, DEL MYER

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define MAX_STR 100
#define MAX_NAME 15
#define TOTAL_NAME 10

void game(int difficulty);
void outputnames (FILE*fp, char array[][MAX_NAME], int score[]);
int menu();
int difficultySelect();
void coordinate( int *x, int *y, int *a ,  int *b);
void getcoord(int *x,int *y);
_Bool duplicate( int x, int y, int a, int b);
void prefill_board(int board_size, char game_board[board_size][board_size]);
void fill_board_with_pairs(int difficulty, int board_size, char game_board[board_size][board_size]);
void shuffle_game_board(int difficulty, int board_size, char game_board[board_size][board_size]);
int random_number_generator(int board_size);
char random_symbol_generator(void);

int main()
{
	FILE *fp;
	int choice, difficulty, scoreboard[10] = 'NULL', score = 0;
	int finalscore;
	char array[TOTAL_NAME][MAX_STR];
	
	int x=0, y=0, a=0, b=0;
	coordinate( &x,  &y, &a, &b);
	
	//seed the "random" number generator with NULL
    	srand(time(NULL));

	//declare local variables
	int board_size = 0;
	difficulty = 5;
	
	do
	{
		choice = menu();

		switch(choice)
		{
				// first case deals with games.
			case 1:	difficulty = difficultySelect();
				game(difficulty);
				outputnames(fp, array,&score);
				break;
				
				// second case deals with scoreboard display.
			case 2:	
			//	scores();


				break;
				
				// case 0 does nothing.
			case 0:	break;
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

void game(int difficulty)
{
	//define board size as a variable of difficulty
	board_size = (2 * difficulty);

	//declare VLA: now that we have the difficulty, which determines the size of the game board
	//(or 2D array), after adding 1 to properly shift the indices
	char game_board[board_size][board_size];
	
	//prefill the game board with X's before the random characters, so we know which spots are taken
	prefill_board (board_size, game_board);

	//fill the game board with pairs, in tandem
	fill_board_with_pairs(difficulty, board_size, game_board);
	
	//shuffle the board
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
}

void outputnames(FILE*fp, char array[][MAX_NAME], int score[])
{
	FILE*output;
	char temp;
	int i = 0, j = 0, counter = 0;

		for (i; i< 15; i++)
		{
			for (j; (j< 15) || (temp != '\n') ; j++)
			{
				scanf("%c", &temp);
				fprintf(output,"%c", temp);
			}

			do
			{
				fprintf(output, " %d", *score);
				counter ++;
			}
			while (counter != 10);
		}

}

void coordinate( int *x, int *y, int *a, int *b)
{
	_Bool dup = 0;

	getcoord(x,y);
	getcoord(a,b);
	dup = duplicate(*x,*y,*a,*b);
	while(dup)
	{
		printf("Duplicate\n");
		getcoord(a,b);
		dup = duplicate(*x,*y,*a,*b);
	}
	
}

void getcoord(int *x, int *y)
{
	printf("Enter your coordinates\n");
	scanf("%d\t%d",x,y);
}


_Bool duplicate(int x, int y, int a, int b)
{
	if(x ==a && y==b)
	{
		return 1;
	}
	return 0;
}

//declare global variables

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
}

void fill_board_with_pairs(int difficulty, int board_size, char game_board[board_size][board_size])
{
	// declare local variables
	int row = 0, column = 0, number_pairs = 0, counter = 0;
	char pair_symbol = 'A';
	_Bool pair = 1;
    
	// controlling expression for previous looping attempt below (commented out)
	// number_pairs = (difficulty * board_size);

	// new idea for assigning pairs of "randomly" generated symbols, in tandem order (must be shuffled)
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
	}while(counter <= number_pairs);
    */
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

