// PROJ 9 FINAL PROJECT
// MEMORY GAME
// A program that ______
// V0.1
// DEVS: RYAN ALMAZAN, ULYSSES RIVERA, DEL MYER

#include <stdio.h>
#include <string.h>
#define MAX_STR 100
#define MAX_NAME 15

char outputnames (FILE*fp, char array[]);
void menu();
int difficultySelect();
void game(int difficulty);



int main()
{
  FILE *fp;
	int choice, difficulty;
  
	do
	{
		menu();
		scanf("%d", &choice);

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
	}while(choice != 0);
		
	
  
	 
   fclose(fp);
  return 0;
}

void menu()
{
		printf("***MEMORY!***\n");
		printf("1 - Play Game\n");
		printf("2 - Check Scores\n");
		printf("0 - EXIT\n");
}

int diffiultySelect()
{
	int difficulty;
	
	printf("Enter difficulty (1, 2, or 3): ");
	scanf("%d", &difficulty);
	
	return difficulty;
}

char outputnames(FILE*fp, char array[][10], int score[])
{
char temp
	do {
		scanf("%s", temp);
		fprintf(output,"%s", temp);
	   }
	while (temp != '\n');

return char 
}



