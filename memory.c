// PROJ 9 FINAL PROJECT
// MEMORY GAME
// A program that ______
// V0.1
// DEVS: RYAN ALMAZAN, ULYSSES RIVERA, DEL MYER

#include <stdio.h>
#include <string.h>
#define MAX_STR 100
#define MAX_NAME 15

char (FILE*fp, char array[]);



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
		printf("MEMORY GAME\n");
		printf("1. Play\n");
		printf("2. Scoreboard\n");
		printf("0. EXIT\n");
}

int diffiultySelect()
{
	
	
	return difficulty;
}

char outputnames(FILE*fp, char array[], int score)
{
char temp
	do {
		scanf("%s", temp);
		fprintf(output,"%s", temp);
	   }
	while (temp != '\n');

return char 
}



