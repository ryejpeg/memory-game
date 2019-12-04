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


