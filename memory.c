// PROJ 9 FINAL PROJECT
// MEMORY GAME
// A program that ______
// V0.1
// DEVS: RYAN ALMAZAN, ULYSSES RIVERA, DEL MYER

#include <stdio.h>
#include <string.h>
#define MAX_STR 100
#define MAX_NAME 15

int main()
{
  FILE *fp;
  
  menu();
	
  output = fopen(argv[1], "w");
	 
   fclose(output);
  return 0;
}

void menu()
{
	int choice;

	do
	{
		printf("MEMORY GAME\n");
		printf("1. Play\n");
		printf("2. Scoreboard\n");
		printf("0. EXIT\n");

		scanf("%d", &choice);

		switch(choice)
		{
			case 1:	game();
				break;
			case 2:	scores();
				break;
			case 0:	break;
//				does nothing.
		}

	}
	while(choice != 0);
}

void diffiultySelect()
