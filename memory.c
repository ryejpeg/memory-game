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

void game(int difficulty, int *score1, char name[MAX_STR]);
void outputnames(FILE* fp, char array[][MAX_STR], int score[]);
int menu();
int difficultySelect();
void coordinate(int *x, int *y, int *a ,  int *b);
void getcoord(int *x,int *y);
_Bool duplicate(int x, int y, int a, int b);
void displayScore(FILE *fp);

void get_coordinates(int board_size, int *row1, int *column1, int *row2, int *column2);
void prefill_board(int board_size, char game_board[][board_size + 1]);
void fill_board_with_pairs(int difficulty, int board_size, char game_board[][board_size + 1]);
void shuffle_game_board(int difficulty, int board_size, char game_board[][board_size + 1]);
void blank_board(int board_size, char game_board[][board_size + 1]);
void playing_game_board(int difficulty, int *row1, int *column1, int *row2, int *column2, int board_size, char game_board[][board_size + 1]);
void prefill_bool_board(int board_size, _Bool match_board[][board_size + 1]);
_Bool matches_made_board(int difficulty, int *row1, int *column1, int *row2, int *column2, int board_size, char game_board[][board_size + 1], _Bool match_board[][board_size + 1], int win_matches, int *matches);
int scoreGet(int *score1, int *row1, int *column1, int *row2, int *column2, int board_size, char game_board[][board_size + 1]);
_Bool check_matches(int row1, int column1, int row2, int column2, int board_size, char game_board[][board_size + 1]);
int random_number_generator(int board_size);
char random_symbol_generator();

void scoreToFile(FILE *fp, int score, char nameWinner[MAX_STR], char open_status);
void scoreSort(FILE *fp, char name[MAX_STR], int scoreNew, int scoreboard[TOTAL_NAMES], char arrayNames[TOTAL_NAMES][MAX_STR]);

int main()
{
	//seed the "random" number generator with NULL
    	srand(time(NULL));
	
	FILE *fp;
	int choice, scoreboard[TOTAL_NAME], score = 0;
	char open_status;
	char nameWinner[MAX_STR];
	
	//declare local variables
	int board_size = 0, difficulty = -1;
	
	// NOTE: the previous only allows reading. we need to close the file after each operation that handles the file to read from top
	
	int row1 = 1, column1 = 1, row2 = 2, column2 = 2;

	// initialize scoreboard array
	// -1 intiialization indicates it's not a true score 
	for(int index = 0; index < TOTAL_NAME; index++)
	{
		scoreboard[index] = -1;
	}
	
	
	do
	{
		choice = menu();

		switch(choice)
		{
			case 1:	// first case deals with games.

				if((fopen("scores.txt", "r")) == NULL)
				{
					fp = fopen("scores.txt", "w");
					open_status = 'w';
				}
				else
				{
					fp = fopen("scores.txt", "r");
					open_status = 'r';
				}
				difficulty = difficultySelect();
				game(difficulty, &score, nameWinner);
//				scoreToFile(fp, score, nameWinner, open_status);
				fclose(fp);
//				outputnames(fp, array, &score);
				break;
				
			case 2:	// second case deals with scoreboard display.

				fp = fopen("scores.txt", "r");
				displayScore(fp);
				fclose(fp);
				break;
				
			case 0:	// case 0 does nothing.

				break;
		}
	}
	while(choice != 0);
	
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

	return choice;
}

int difficultySelect()
{
	int difficulty;
	
	printf("Enter difficulty (1, 2, or 3): ");
	scanf("%d", &difficulty);
	
	return difficulty;
}

void game(int difficulty, int *score, char name[MAX_STR])
{
	int row1 = 1, column1 = 1, row2 = 2, column2 = 2;
	//define board size as a variable of difficulty
	int board_size = (2 * difficulty);
	*score = (board_size * 2);

	//declare VLA, now that we have the difficulty, which determines the size of the game board
	//(or 2D array), after adding 1 to properly shift the indices
	char game_board[board_size][board_size + 1];
	_Bool match_board[board_size][board_size + 1];
	
	//prefill the game board with X's before the random characters, so we know which spots are taken
	prefill_board (board_size, game_board);

	//fill the game board with pairs, in tandem
	fill_board_with_pairs(difficulty, board_size, game_board);

	//shuffle the board
	shuffle_game_board(difficulty, board_size, game_board);
                    
	//prefill matches board
	prefill_bool_board(board_size, match_board);
                    
	//display blank playing board once, each time option 1 is chosen
	blank_board(board_size, game_board);
			   
	//declare local variables;
	_Bool won = 0;
	int win_matches = board_size, matches = 0, scoreSaveUser;

	do
	{
		//acquire user input
		get_coordinates(board_size, &row1, &column1, &row2, &column2);

		//display board with cards of selected coordinates
		playing_game_board(difficulty, &row1, &column1, &row2, &column2, board_size, game_board);

		//update score
		scoreGet(score, &row1, &column1, &row2, &column2, board_size, game_board);

		won = matches_made_board(difficulty, &row1, &column1, &row2, &column2, board_size, game_board, match_board, win_matches, &matches);
	}while(!won);

	if(won)
	{
		printf("YOU WON!!!\n");
		printf("%d points!\n", *score);
		printf("Save score? 1 - yes: ");
		scanf("%d", &scoreSaveUser);

		if(scoreSaveUser == 1)
		{
			printf("Enter your name: ");
			scanf("%s", name);
		}
	}
}

//Keeps track of which cards have been mathced, with bools. Returns won bool as true when the game is over.
_Bool matches_made_board(int difficulty, int *row1, int *column1, int *row2, int *column2, int board_size, char game_board[][board_size + 1], _Bool match_board[][board_size + 1], int win_matches, int *matches)
{
	_Bool match = 0;

    //Call check match to check of their is a match between the two coordiante pairs.
    match = check_matches(*row1, *column1, *row2, *column2, board_size, game_board);

    //If there is match, assign those locations on the bool board 1's and increment the number of matches made
    if(match)
    {
        match_board[*row1 - 1][*column1 - 1] = 1;
        match_board[*row2 - 1][*column2 - 1] = 1;
        *matches += 1;
    }

    //display matches made board
    printf("\n");
    for(int row_index = 0; row_index < board_size; row_index++)
    {
        for(int col_index = 0; col_index < board_size; col_index++)
        {
            if(match_board[row_index][col_index] == 1)
            {
                printf("[%c]", game_board[row_index][col_index]);
            }
            else
            {
                printf("[ ]");
            }
            
        }   
        printf("\n");
    }

    //game is won, end function
    if(*matches == win_matches)
    {
        return 1;
    }

    //game is not won, end function
    return 0;
}

void outputnames(FILE *fp, char array[][MAX_STR], int score[])
{
	FILE *output;
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

_Bool duplicate(int x, int y, int a, int b)
{
	if(x ==a && y==b)
	{
		return 1;
	}
	return 0;
}

void get_coordinates(int board_size, int *row1, int *column1, int *row2, int *column2)
{
	_Bool valid = 0;
	//get 1st pair of coordinates
	printf("Enter your coordinates from 1 to %d\n", board_size);
	scanf("%d %d", row1, column1);

	//check that they are valid
	while(!valid)
	{
		if((((*row1 < 1) || (*row1 > board_size)) || ((*column1 < 1) || (*column1 > board_size)) ) )
		{
			printf("Please enter valid coordinates between 1 and %d\n", board_size);
			scanf("%d %d", row1, column1);
		}
		else
		{
			valid = 1;
		}
	}

	printf("\n");

	//get 2nd pair of coordinates
	printf("Enter your coordinates from 1 to %d\n", board_size);
	scanf("%d %d", row2, column2);

	//check that they are valid
	while(!valid)
	{
		if((((*row2 < 1) || (*row2 > board_size)) || ((*column2 < 1) || (*column2 > board_size)) ) )
		{
			printf("Please enter valid coordinates between 1 and %d\n", board_size);
			scanf("%d %d", row2, column2);
		}
		else
		{
			valid = 1;
		}
	}

	//return line for proper formating
	printf("\n");
}

//This function prefills the game board with X's, so that when it is filled with random characters, we know which
//spots have already been taken.
void prefill_board (int board_size, char game_board[][board_size + 1])
{
    int row_index = 0, col_index = 0;
    for(row_index = 0; row_index < board_size; row_index++)
    {
        for(col_index = 0; col_index < board_size; col_index++)
        {
            game_board[row_index][col_index] = 'X';
        } 
        game_board[row_index][col_index] = '\0'; 
    }
    //end function
    return;
}

//This function fills the game board with pairs of symbols, that do not repeat, in a linear fashion.
void fill_board_with_pairs(int difficulty, int board_size, char game_board[][board_size + 1])
{
    //declare local variables
    char pair_symbol = 'A';
    _Bool duplicate_symbol = 0;
    int number_of_symbols = (difficulty * board_size);
    
    //This is a 1d array that holds the symbols of the generated pairs and is used to check that each new pair
    // is unique.
    char symbol_check[number_of_symbols + 1];

    //prefill symbol check with X's
    int index = 0;
    for(index = 0; index < (number_of_symbols); index++)
    {
        symbol_check[index] = 'X';
    }
    //last element assigned the NULL character
    symbol_check[index] = '\0';

    //new idea for assigning pairs of "randomly" generated symbols, in tandem order (must be shuffled)
    //{BEGIN}
    //check that each randomly generated symbol is not duplicated.
    //generate a symbol until it is unique, and fill symbol array with them.
    int symbol_index = 0;
    pair_symbol = random_symbol_generator();
    for(int index = 0; index < number_of_symbols; index++)
    {
        for(int index = 0; symbol_check[index] != '\0'; index++)
        {
            //printf("%c ", symbol_check[index]);
            if(symbol_check[index] == pair_symbol)
            {
                pair_symbol = random_symbol_generator();
                index = -1;
            }
        }
            symbol_check[symbol_index] = pair_symbol;
            symbol_index++;
    }
    
    index = 0;
    for(int row_index = 0; row_index < board_size; row_index++)
    {
        for(int col_index = 0; col_index < board_size; col_index++)
        {
            //assigne the unique symbol, in pairs to the game board array
            game_board[row_index][col_index] = symbol_check[index];
            //is safe to increment the column index, since the pairs are even and it stays within the bounds of the array
            col_index++;
            game_board[row_index][col_index] = symbol_check[index];
            index++;
        }   
    }
}

//This function shuffles the random characters, that were placed in the borad in linear pairs.
void shuffle_game_board(int difficulty, int board_size, char game_board[][board_size + 1])
{
	int row = 0, column = 0;
	char pair_symbol1  = 'A', pair_symbol2 = 'A';

	//The outer loop performs repeated shuffles, for adequate randomness
	for(int index = 0; index < 6; index++)
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

void blank_board( int board_size, char game_board[][board_size + 1])
{
	for(int row_index = 0; row_index < board_size; row_index++)
	{
		for(int col_index = 0; col_index < board_size; col_index++)
		{
			printf("[ ]");
		}   
		printf("\n");
	}
}

//Is passed user coordinates and displays cards as they are flipped and checks for matches. Passes mathces to mathces made board
void playing_game_board(int difficulty, int *row1, int *column1, int *row2, int *column2, int board_size, char game_board[][board_size + 1])
{
    //declare local variables
    _Bool displayed1 = 0, displayed2 = 0;

/* 
Display board, based on difficulty. Will initially be blank. This will display cards, as they are flipped and
call the check matches funciton to check for matches.
*/

    for(int row_index = 0; row_index < board_size; row_index++)
    {
        for(int col_index = 0; col_index < board_size; col_index++)
        {
            if(!displayed1 && ((*row1 - 1) == row_index) && ((*column1 - 1) == col_index))
            {
            
                printf("[%c]", game_board[row_index][col_index]);
                displayed1 = 1;
            }
            else if(!displayed2 && ((*row2 - 1) == row_index) && ((*column2 - 1) == col_index))
            {
                printf("[%c]", game_board[row_index][col_index]);
                displayed2 = 1;
            }
            else
            {
                printf("[ ]");
            }
        }
        printf("\n");   
    }
    //reset flags back to zero 
    displayed1 = 0;
    displayed2 = 0;

    if(check_matches(*row1, *column1, *row2, *column2, board_size, game_board))
    {
        printf("MATCHED!");
        printf("\n");
    }

    return;
}

void prefill_bool_board(int board_size, _Bool match_board[][board_size + 1])
{
    int row_index = 0, col_index = 0;
    for(row_index = 0; row_index < board_size; row_index++)
    {
        for(col_index = 0; col_index < board_size; col_index++)
        {
            match_board[row_index][col_index] = 0;
        } 
        match_board[row_index][col_index] = '\0'; 
    }

    return;
}


/*
//Keeps track of which cards have been mathced, with bools. Returns won bool as true when the game is over.
_Bool matches_made_board(int difficulty, int *row1, int *column1, int *row2, int *column2, int board_size, char game_board[][board_size + 1], _Bool match_board[][board_size + 1])

{
    int win_matches = 0, matches = 0;
    _Bool match = 0;
    win_matches = (board_size);
    
    //Call check match to check of their is a match between the two coordiante pairs.
    match = check_matches(*row1, *column1, *row2, *column2, board_size, game_board);


    //If there is match, assign those locations on the bool board 1's and increment the number of matches made
    if(match)
    {
        match_board[*row1 - 1][*column1 - 1] = 1;
        match_board[*row2 - 1][*column2 - 1] = 1;
        matches++;
    }

    //display matches made board
    printf("\n");
    for(int row_index = 0; row_index < board_size; row_index++)
    {
        for(int col_index = 0; col_index < board_size; col_index++)
        {
            if(match_board[row_index][col_index] == 1)
            {
                printf("[%c]", game_board[row_index][col_index]);
            }
            else
            {
                printf("[ ]");
            }
            
        }   
        printf("\n");
    }

    //game is won, end function
    if(matches == win_matches)
    {
        return 1;
    }

    //game is not won, end function
    return 0;
}
*/

int scoreGet(int *score, int *row1, int *column1, int *row2, int *column2, int board_size, char game_board[][board_size + 1])
{
    if(check_matches(*row1, *column1, *row2, *column2, board_size, game_board))
    {
        return *score;
    }
    else
    {
        return (*score -= 1);
    }
}

_Bool check_matches(int row1, int column1, int row2, int column2, int board_size, char game_board[][board_size + 1])
{
    //declare local variables
    _Bool match = 0;

    //Check for matches. Subtract 1 from each of the coordinates to align them with the proper indices in the array.
    if(game_board[row1 - 1][column1 - 1] == game_board[row2 - 1][column2 - 1])
    {
        //match made
        match = 1;
        return match;
    }

    //no match
    return match;
}

//generates a random number between 1 and 3 (the difficulty levels)
int random_number_generator(int board_size)
{
    //declare local variables
    int number = 4;
    
    //use rand to make the number "random" within the range of the game board size
    //(size of the indices of the 2D array) which is based on the difficulty level
    number = ((rand() % ((board_size - 1) - 0 + 1)) + 0);
    return number;
}

//generates a random symbol between @ and !
char random_symbol_generator(void)
{
    //declare local variables
    char symbol = 'A';
    
    //use rand to make the symbol "random" within the range of ! to @
    symbol = ((rand() % ('@' - '!' + 1)) + '!');
    return symbol;
}

// ******
// DO NOT MODIFY WITHOUT TELLING RYAN
// SCOREKEEPING or SCORE.TXT FILE HANDLING BEGIN
// ******

void displayScore(FILE *fp)
{
	int counter = 0, indexName = 0, indexScore = 0;
	int scoreboard[TOTAL_NAME];
	char array[10][100];

	while(fscanf(fp, "%s %d\n", array[indexScore], &scoreboard[indexScore]) == 2)
	{
		counter++;
		indexScore++;
	}

	printf("**HIGH SCORES**\n");
	for(int index = 0; index < counter; index++)
	{
		printf("%s: ", array[index]);
		printf("%d\n", scoreboard[index]);
	}

	printf("\n");
}

/*
void scoreToFile(FILE *fp, int score, char name[MAX_STR], char open_status)
{
	char arrayNames[TOTAL_NAMES][MAX_STR]
	int scoreboard[TOTAL_NAMES];

	if(open_status == 'r')
	{
		scoreSort(fp, name, score, scoreboard, arrayNames);
	}

	fclose(fp);
	fp = fopen("scores.txt", "a");
	while(fprintf(fp, "%s %d\n", arrayNames[tempIndex], &scoreboard[tempIndex] == 2));
	{
		tempIndex++;
	}
}

void scoreSort(FILE *fp, char name[MAX_STR], int scoreNew, int scoreboard[TOTAL_NAMES], char arrayNames[TOTAL_NAMES][MAX_STR])
{
	int scoreTotal, scoreStore, tempIndex; counter;
	char nameStore[TOTAL_NAME][MAX_STR];

	// Check how many scores there are ('counter' variable):
	tempIndex = 0;
	counter = 0;
	while(fscanf(fp, "%s %d\n", array[tempIndex], &scoreboard[tempIndex]) == 2)
	{
		counter++;
		tempIndex++;
	}

	// SORTING
	if(scoreboard[0] < 0)
	{
		scoreboard[0] = scoreNew;
	}
	else if((counter < 10) && (scoreNew < scoreboard[counter - 1])
	{
		scoreboard[counter] = scoreNew;
	}
	else if((counter == 10) && (scoreNew > scoreboard[counter - 1]
	{
	 	for(int index = 0; index < 10; index++) 
		{
			if
		}
	}

}
*/

// ******
// DO NOT MODIFY WITHOUT TELLING RYAN
// SCOREKEEPING or SCORE.TXT FILE HANDLING END
// ******
