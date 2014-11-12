/*  Black&White Chess
	Chua Soon Seng
	4313453
*/
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

struct player // Structure for player
{

	char name[20];
	int score, win;
	char symbol;
	
};

struct ScoreBoard // Structure for scoreboard
{

	char name[20];
	int score;

};

// Function
char UserMenu();
void ShowScoreBoard(struct ScoreBoard winners[5]);
void UpdateScoreBoard(struct ScoreBoard winners[5], struct player *player1, struct player *player2);
void PlayerName(struct player *player1, struct player *player2);
char boardgame(char sboard[8][17], char gboard[8][17], char hboard[8][17], struct player *player1, struct player *player2, struct ScoreBoard winners[5]);
void ShowHelp(char gboard[8][17], char hboard[8][17], int *a, int *b, struct player *player1, struct player *player2, int help, int *PlayersTurn, int *TopRightA, int *TopA, int *TopLeftA, int *LeftA, int *BottomLeftA, int *BottomA, int *BottomRightA, int *RightA);
char CountToken(char gboard[8][17], struct player *player1, struct player *player2);
char movement(int *PlayersTurn, char sboard[8][17], char gboard[8][17], char hboard[8][17], int *loop, int *a, int *b, struct player *player1, struct player *player2, int *help, int *TopRightA, int *TopA, int *TopLeftA, int *LeftA, int *BottomLeftA, int *BottomA, int *BottomRightA, int *RightA, int *PositionUnavailable, int *loop2);
char checkslotavailability(char gboard[8][17], char hboard[8][17], int *PlayersTurn, int *a, int *b, struct player *player1, struct player *player2, int *TopRightA, int *TopA, int *TopLeftA, int *LeftA, int *BottomLeftA, int *BottomA, int *BottomRightA, int *RightA);
char AnyMoreMovement(char gboard[8][17], char hboard[8][17], int *PlayersTurn, struct player *player1, struct player *player2, int *TopRightA, int *TopA, int *TopLeftA, int *LeftA, int *BottomLeftA, int *BottomA, int *BottomRightA, int *RightA, int *P1U, int *P2U, int *loop3);
char CheckWinner(int *P1U, int *P2U, struct player *player1, struct player *player2, struct ScoreBoard winners[5], int *loop);
void CheckBoard(char gboard[8][17], char hboard[8][17], struct player *player1, struct player *player2, int *PlayersTurn, int *TopRightA, int *TopA, int *TopLeftA, int *LeftA, int *BottomLeftA, int *BottomA, int *BottomRightA, int *RightA);

// Function to check all directions
char checkpositionTopRight(char gboard[8][17], char hboard[8][17], int *a, int *b, char *Ftoken, char *Stoken, int *TopRightA, int *flip);
char checkpositionTop(char gboard[8][17], char hboard[8][17], int *a, int *b, char *Ftoken, char *Stoken, int *TopA, int *flip);
char checkpositionTopLeft(char gboard[8][17], char hboard[8][17], int *a, int *b, char *Ftoken, char *Stoken, int *TopLeftA, int *flip);
char checkpositionLeft(char gboard[8][17], char hboard[8][17], int *a, int *b, char *Ftoken, char *Stoken, int *LeftA, int *flip);
char checkpositionBottomLeft(char gboard[8][17], char hboard[8][17], int *a, int *b, char *Ftoken, char *Stoken, int *BottomLeftA, int *flip);
char checkpositionBottom(char gboard[8][17], char hboard[8][17], int *a, int *b, char *Ftoken, char *Stoken, int *BottomA, int *flip);
char checkpositionBottomRight(char gboard[8][17], char hboard[8][17], int *a, int *b, char *Ftoken, char *Stoken, int *BottomRightA, int *flip);
char checkpositionRight(char gboard[8][17], char hboard[8][17], int *a, int *b, char *Ftoken, char *Stoken, int *RightA, int *flip);

void CountScore(char gboard[8][17]);

int main()
{

	char sboard[8][17];
	char gboard[8][17];
	char hboard[8][17];
	struct player player1, player2;
	struct ScoreBoard winners[5];

	int x, y, loopmain = 0, loopex;
	char input, Minput;
	
	player1.symbol = '@';
	player2.symbol = 'O';
	player1.score = 2;
	player2.score = 2;
	
	while (loopmain == 0) // Loop for main 
	{
	
		loopex = 0;
		
		printf("***** Welcome to the Black & White Chess ***** \n\n");
		
		UserMenu(&Minput); // Show user menu to user/s
		
		if (Minput == '1')
		{
			ShowScoreBoard(winners); // Show Score Board
			loopex = 1;
		}
		else if (Minput == '2') // Start game
		{
			PlayerName(&player1, &player2);
					
			boardgame(sboard, gboard, hboard, &player1, &player2, winners);
			
			printf("\nRestart (Y/N)?: ");
		}
		else if (Minput == 'Q') // When user wanted to quit
		{
			printf("\nDo you want to continue (Y/N)?: ");
		}
		else
		{
			system("cls");
			printf("Wrong action\n\n");
			loopex = 1;
		}
		
		while (loopex == 0)
		{
			fflush(stdin);
			input = getch();
			
			if (input == 'Y')
			{
				loopex = 1;
				
				system("cls");
			}
			else if (input == 'N')
			{
				loopmain = 1;
				loopex = 1;
				
				system("cls");
				
				printf("\nHave a nice day!\n");
				
				getch();
				return 0;
			}
		}
	
	}	 	 
}

char UserMenu(char *Minput)
{

	printf("\n**Please remember this program is case sensitive**\n");
	printf("**Full-screen mode is recommended for this game **\n");
	printf("\n        -------------------------------");
	printf("\n       | Press '1' to show Score Board |");
	printf("\n       | Press '2' to Start Game       |");
	printf("\n       | Press 'Q' to Quit             |");
	printf("\n       |-------------------------------|");
	printf("\n\n       Choose your action: ");
		
	fflush(stdin);
	*Minput = getch();	  

}

void PlayerName(struct player *player1, struct player *player2)
{

	printf("\n\nPlease input the name of the first player : ");
	fflush(stdin);
	scanf("%s", &(*player1).name);
	printf("Please input the name of the second player: ");
	fflush(stdin);
	scanf("%s", &(*player2).name);

}

char boardgame(char sboard[8][17], char gboard[8][17], char hboard[8][17], struct player *player1, struct player *player2, struct ScoreBoard winners[5])
{
	int x, y, a = 7, b = 15;
	int PlayersTurn = 0, PositionUnavailable = 0, P1U, P2U;
	int loop = 0, loop2, loop3;
	int blackcount = 2, whitecount = 2;
	int help = 0;
	char border = '|', space = ' ';
	
	int TopRightA, TopA, TopLeftA, LeftA, BottomLeftA, BottomA, BottomRightA, RightA;

	for (x = 0; x < 8; x++) // Loop to assign border and space into all arrays
	{
		for (y = 0; y < 17; y++)
		{
			if (y % 2 == 0)
			{
				sboard[x][y] = border;
				gboard[x][y] = border;
				hboard[x][y] = border;
			}
			else
			{
				sboard[x][y] = space;
				gboard[x][y] = space;
				hboard[x][y] = space;
			} 
		}
	}	   	   
	
	gboard[3][7] = (*player1).symbol;
	gboard[3][9] = (*player2).symbol;
	gboard[4][9] = (*player1).symbol;
	gboard[4][7] = (*player2).symbol;
	
	
	while (loop == 0)
	{
		TopRightA = 0;
		TopA = 0;
		TopLeftA = 0;
		LeftA = 0;
		BottomLeftA = 0;
		BottomA = 0;
		BottomRightA = 0;
		RightA = 0;
		P1U = 2;
		P2U = 2;
		loop2 = 0, loop3 = 0;
		
		while (loop2 == 0)
		{	 	 
		
			system("cls"); // Clear Screen
			//system("color F0");
												
			for (x = 0; x < 8; x++) 
			{
				for (y = 0; y < 17; y++)
				{
					sboard[x][y] = gboard[x][y];
				}
			}
		
			sboard[a][b] = 'X'; // Assign 'X'to a specific location everytime
			
				
			for (x = 0; x < 8; x++) // Print show board
			{
				for (y = 0; y < 17; y++)
				{
					printf("%2c", sboard[x][y]);
				}
				
				printf("\n\n");
			}
			
			printf("\n");
			
			ShowHelp(gboard, hboard, &a, &b, &(*player1), &(*player2), help, &PlayersTurn, &TopRightA, &TopA, &TopLeftA, &LeftA, &BottomLeftA, &BottomA, &BottomRightA, &RightA);
							
			if (PositionUnavailable == 1) // If 'X' position is not available for any token
			{
				printf("!!!!!Position Not Available!!!!!\n\n");
			}
			else if (PositionUnavailable == 0)
			{
				// Nothing happens
			}
			else // If user/s press any other key than the key provided
			{
				printf("!!!!!Invalid Action!!!!!\n\n");
			}
			
			if (PlayersTurn == 0) // Notify players turn and token
			{
				printf("It's your turn, %s (Token %c)\n", (*player1).name, (*player1).symbol);
			}
			else if (PlayersTurn == 1)
			{
				printf("It's your turn, %s (Token %c)\n", (*player2).name, (*player2).symbol);
			}
			
			printf("\nTotal token collected by %s is: %i\n", (*player1).name, (*player1).score);  // Shows number of token
			printf("\nTotal token collected by %s is: %i\n", (*player2).name, (*player2).score);  // that both players have
			
			printf("\n!Note!-- The 'X' will always at the bottom right   --!Note! \n!Note!-- corner after everytime you insert a token --!Note!\n"); // Note for user/s
		
			printf("\n:____ Instruction ____:\n\n"); // Show instruction and key available to user/s
			printf("%5c = up\n", 'w');
			printf("%5c = down\n", 's');
			printf("%5c = left\n", 'a');
			printf("%5c = right\n", 'd');
			printf("%5c = insert token\n", '5');
			printf("\n%5c = Show Help", 'H');
			printf("\n%5c = Quit Game\n", 'Q');
			printf(":_____________________:\n");
			
			/* printf("%i", P1U); Testing */
			/* printf("%i", P2U); Testing */
			
			movement(&PlayersTurn, sboard, gboard, hboard, &loop, &a, &b, &(*player1), &(*player2), &help, &TopRightA, &TopA, &TopLeftA, &LeftA, &BottomLeftA, &BottomA, &BottomRightA, &RightA, &PositionUnavailable, &loop2);
					
			CheckBoard(gboard, hboard, &(*player1), &(*player2), &PlayersTurn, &TopRightA, &TopA, &TopLeftA, &LeftA, &BottomLeftA, &BottomA, &BottomRightA, &RightA);
			
			CountToken(gboard, &(*player1), &(*player2)); // Count token of both players
		
		}
				
		if (PlayersTurn == 0) // Switch player 
		{
			PlayersTurn = 1;
		}
		else if (PlayersTurn == 1)
		{
			PlayersTurn = 0;
		}
		
		/* printf("%i", PlayersTurn); Testing */
		
		while (loop3 == 0) // loop to check if any more movement for both players
		{
			AnyMoreMovement(gboard, hboard, &PlayersTurn, &(*player1), &(*player2), &TopRightA, &TopA, &TopLeftA, &LeftA, &BottomLeftA, &BottomA, &BottomRightA, &RightA, &P1U, &P2U, &loop3);	  
			/* printf("%i\n", P1U); Testing */
			/* printf("%i", P2U); Testing */
			
			if (P1U == 1 && P2U == 1)
			{
				loop3 = 1;
			}
			/* printf("%i\n", P1U); Testing */
			/* printf("%i", P2U); Testing */
		}
		
		CheckWinner(&P1U, &P2U, &(*player1), &(*player2), winners, &loop);
	}
	
}

void ShowScoreBoard(struct ScoreBoard winners[5])
{

	FILE *winnersboard;
	int x = 0, y = 0, i = 0, loop = 0;
	char *line[10];
	char slot[20];
	char input;
	
	system("cls");
		
	// Open File in read mode
	winnersboard = fopen("WinnersBoard.txt", "r");
	
	if (winnersboard == NULL)
	{
		//Close File
		fclose(winnersboard);
		
		//Open File in write mode
		winnersboard = fopen("WinnersBoard.txt", "w");
		
		for (x = 0; x < 10; x++)
		{
			if (x == 0)
			{
				fprintf(winnersboard, "-");
			}
			else
			{
				fprintf(winnersboard, "\n-");
			}
		}
		
		//Close File
		fclose(winnersboard);
		
		//Open File in read mode
		winnersboard = fopen("WinnersBoard.txt", "r");
	} 

	while (!feof(winnersboard)) // Read until end of the file
	{
		char *slot = malloc(20); // Allocate memory
		
		if ( fgets( slot, 20, winnersboard)) // Assign name and score into the array
		{
			line[i] = slot;
		}
		
		i++;
	}	 
	
	for (x = 0; x < 5; x++) // Copy name and score from array into another array
	{			
		strcpy(winners[x].name, line[y]);
		y++;			   
		winners[x].score = atoi(line[y]);
		y++;		
	}
	
	free(slot);
/*	
	for (x = 0; x < 5; x++){
	fscanf(winnersboard, "%s %i", winners[x].name, winners[x].score);
	}
*/	  	  
	fclose(winnersboard); // Close file
	
	while (loop == 0)
	{	 
	
		printf("\n\nPrevious matches victors: \n");  // Show names
		printf("\n%3s %15s\n\n", "Scores", "Names"); // and scores
		
		for (x = 0; x < 5; x++) 
		{
			printf("%4i %13c %s", winners[x].score, ' ', winners[x].name);
		}
		
		printf("\nPress 'Q' to quit Score Board: "); // Ask user/s to quit scoreboard
		fflush(stdin);
		input = getch();
		
		if (input == 'Q') 
		{
			loop = 1;
			system("cls");
		}
		else
		{
			system("cls");
			printf("Wrong action");
		}
	
	}
	
}

void UpdateScoreBoard(struct ScoreBoard winners[5], struct player *player1, struct player *player2)
{

	FILE *winnersboard;
	int x;
	
	for (x = 4; x > 0; x--) // Move name and score down 1 step
	{
		strcpy(winners[x].name, winners[x - 1].name);
		winners[x].score = winners[x - 1].score;
	}
	
	if ((*player1).win == 1)
	{
		strcpy(winners[0].name, (*player1).name);
		winners[0].score = (*player1).score;
	}
	else if ((*player2).win == 1)
	{
		strcpy(winners[0].name, (*player2).name);
		winners[0].score = (*player2).score;
	}
	
	winnersboard = fopen("WinnersBoard.txt", "w"); // Open txt file
	
	for (x = 0; x < 5; x++) // Print name and score into the txt file
	{
		if (x == 0)
		{
			fprintf(winnersboard, "%s\n", winners[x].name);
			fprintf(winnersboard, "%i", winners[x].score);
		}
		else
		{
			fprintf(winnersboard, "\n%s", winners[x].name);
			fprintf(winnersboard, "%i", winners[x].score);
		}
	}
	
	fclose(winnersboard); // Close file
	
}

void ShowHelp(char gboard[8][17], char hboard[8][17], int *a, int *b, struct player *player1, struct player *player2, int help, int *PlayersTurn, int *TopRightA, int *TopA, int *TopLeftA, int *LeftA, int *BottomLeftA, int *BottomA, int *BottomRightA, int *RightA)
{

	int x, y, flip;
	
	flip = 0; // Cancel flip
		
	CheckBoard(gboard, hboard, &(*player1), &(*player2), &(*PlayersTurn), &(*TopRightA), &(*TopA), &(*TopLeftA), &(*LeftA), &(*BottomLeftA), &(*BottomA), &(*BottomRightA), &(*RightA));
	
	if (help == 1) // Print help board
	{
		for (x = 0; x < 8; x++)
		{
			for (y = 0;y < 17; y++)
			{
				printf("%c", hboard[x][y]);
			}
			
			printf("\n");
		}
		
		printf("\n'A' = Available\n");
		printf("'*' = Not Available\n\n");
	}

}

char CountToken(char gboard[8][17], struct player *player1, struct player *player2)
{

	int x, y;
	
	(*player1).score = 0; // Assign initial value
	(*player2).score = 0; // to 0
	
	for (x = 0; x < 8; x++)
	{
		for (y = 0; y < 17; y++)
		{
			if (gboard[x][y] == (*player1).symbol)
			{
				(*player1).score++;
			}
			else if (gboard[x][y] == (*player2).symbol)
			{
				(*player2).score++;
			}
		}
	}
	
}

char movement(int *PlayersTurn, char sboard[8][17], char gboard[8][17], char hboard[8][17], int *loop, int *a, int *b, struct player *player1, struct player *player2, int *help, int *TopRightA, int *TopA, int *TopLeftA, int *LeftA, int *BottomLeftA, int *BottomA, int *BottomRightA, int *RightA, int *PositionUnavailable, int *loop2)
{   
	char input;
	
	
	printf("\nPlease enter the action you want: "); 
	fflush(stdin);
	input = getch();	
		
	if (input == 'w') // Up
	{
		if (*a > 0)
		{
			*a = *a - 1;
		}
		
		*PositionUnavailable = 0;
	}
	else if (input == 's') // Down
	{
		if (*a < 7)
		{
			*a = *a + 1;
		}
		
		*PositionUnavailable = 0;
	}
	else if (input == 'a') // Left
	{
		if (*b > 1)
		{
			*b = *b - 2;
		}
		
		*PositionUnavailable = 0;
	}
	else if (input == 'd') // Right
	{
		if (*b < 15)
		{
			*b = *b + 2;
		}
		
		*PositionUnavailable = 0;
	}
	else if (input == '5') // Insert token 
	{
		checkslotavailability(gboard, hboard, &(*PlayersTurn), &(*a), &(*b), &(*player1), &(*player2), &(*TopRightA), &(*TopA), &(*TopLeftA), &(*LeftA), &(*BottomLeftA), &(*BottomA), &(*BottomRightA), &(*RightA));
		
		if (*TopRightA == 1 || *TopA == 1 || *TopLeftA == 1 || *LeftA == 1 || *BottomLeftA == 1 || *BottomA == 1 || *BottomRightA == 1 || *RightA == 1)
		{	 
			if (*PlayersTurn == 0)
			{
				gboard[*a][*b] = (*player1).symbol;
			}
			else if (*PlayersTurn == 1)
			{
				gboard[*a][*b] = (*player2).symbol;
			}
			
			*loop2 = 2;
			
			*a = 7;
			*b = 15;
			sboard[*a][*b] = 'X';
						
			*PositionUnavailable = 0;
		}
		else
		{
			*PositionUnavailable = 1;
		}
	}
	else if (input == 'Q')
	{
		*loop = 1; 
		*loop2 = 1;
		*PositionUnavailable = 0;
	}
	else if (input == 'H') // To show help board
	{
		if (*help == 0)
		{
			*help = 1;
		}
		else
		{
			*help = 0;
		}
		
		*PositionUnavailable = 0;
	}
	else
	{
		*PositionUnavailable = 2;
	}
	
}

char checkslotavailability(char gboard[8][17], char hboard[8][17], int *PlayersTurn, int *a, int *b, struct player *player1, struct player *player2, int *TopRightA, int *TopA, int *TopLeftA, int *LeftA, int *BottomLeftA, int *BottomA, int *BottomRightA, int *RightA)
{

	int flip;
	
	flip = 1; // Approve flip
		
	if (*PlayersTurn == 0)
	{
		checkpositionTopRight(gboard, hboard, &(*a), &(*b), &(*player1).symbol, &(*player2).symbol, &(*TopRightA), &flip);
		checkpositionTop(gboard, hboard, &(*a), &(*b), &(*player1).symbol, &(*player2).symbol, &(*TopA), &flip);
		checkpositionTopLeft(gboard, hboard, &(*a), &(*b), &(*player1).symbol, &(*player2).symbol, &(*TopLeftA), &flip);
		checkpositionLeft(gboard, hboard, &(*a), &(*b), &(*player1).symbol, &(*player2).symbol, &(*LeftA), &flip);
		checkpositionBottomLeft(gboard, hboard, &(*a), &(*b), &(*player1).symbol, &(*player2).symbol, &(*BottomLeftA), &flip);
		checkpositionBottom(gboard, hboard, &(*a), &(*b), &(*player1).symbol, &(*player2).symbol, &(*BottomA), &flip);
		checkpositionBottomRight(gboard, hboard, &(*a), &(*b), &(*player1).symbol, &(*player2).symbol, &(*BottomRightA), &flip);
		checkpositionRight(gboard, hboard, &(*a), &(*b), &(*player1).symbol, &(*player2).symbol, &(*RightA), &flip);
	}
	else if (*PlayersTurn == 1)
	{
		checkpositionTopRight(gboard, hboard, &(*a), &(*b), &(*player2).symbol, &(*player1).symbol, &(*TopRightA), &flip);
		checkpositionTop(gboard, hboard, &(*a), &(*b), &(*player2).symbol, &(*player1).symbol, &(*TopA), &flip);
		checkpositionTopLeft(gboard, hboard, &(*a), &(*b), &(*player2).symbol, &(*player1).symbol, &(*TopLeftA), &flip);
		checkpositionLeft(gboard, hboard, &(*a), &(*b), &(*player2).symbol, &(*player1).symbol, &(*LeftA), &flip);
		checkpositionBottomLeft(gboard, hboard, &(*a), &(*b), &(*player2).symbol, &(*player1).symbol, &(*BottomLeftA), &flip);
		checkpositionBottom(gboard, hboard, &(*a), &(*b), &(*player2).symbol, &(*player1).symbol, &(*BottomA), &flip);
		checkpositionBottomRight(gboard, hboard, &(*a), &(*b), &(*player2).symbol, &(*player1).symbol, &(*BottomRightA), &flip);
		checkpositionRight(gboard, hboard, &(*a), &(*b), &(*player2).symbol, &(*player1).symbol, &(*RightA), &flip);
	}
	
	flip = 0; // Cancel flip 

}

char AnyMoreMovement(char gboard[8][17], char hboard[8][17], int *PlayersTurn, struct player *player1, struct player *player2, int *TopRightA, int *TopA, int *TopLeftA, int *LeftA, int *BottomLeftA, int *BottomA, int *BottomRightA, int *RightA, int *P1U, int *P2U, int *loop3)
{

	int x ,y;
	
	CheckBoard(gboard, hboard, &(*player1), &(*player2), &(*PlayersTurn), &(*TopRightA), &(*TopA), &(*TopLeftA), &(*LeftA), &(*BottomLeftA), &(*BottomA), &(*BottomRightA), &(*RightA));
	
	if (*PlayersTurn == 0)
	{	 
		for (x = 0; x < 8; x++)
		{
			for (y = 1; y < 17; y = y + 2)
			{
				if (hboard[x][y] == 'A') // Search for any available slot for token
				{
						*P1U = 0;
						*loop3 = 1;
						break;
				}
			}	 
		}
		
		if (*P1U == 2)
		{
			*P1U = 1;
			*PlayersTurn = 1;
		}
	}
	else if (*PlayersTurn == 1)
	{
		for (x = 0; x < 8; x++)
		{
			for (y = 1; y < 17; y = y + 2)
			{
				if (hboard[x][y] == 'A') // Search for any available slot for token
				{
						*P2U = 0;
						*loop3 = 1;
						break;
				}
			}	 
		}
		
		if (*P2U == 2)
		{
			*P2U = 1;
			*PlayersTurn = 0;
		}
	}

}

void CheckBoard(char gboard[8][17], char hboard[8][17], struct player *player1, struct player *player2, int *PlayersTurn, int *TopRightA, int *TopA, int *TopLeftA, int *LeftA, int *BottomLeftA, int *BottomA, int *BottomRightA, int *RightA)
{

	int x, y, flip;
	
	flip = 0; // Cancel flip
		
	for (x = 0; x < 8; x++)
	{
		for (y = 1; y < 17; y = y + 2)
		{
			hboard[x][y] = '*';
			
			if (gboard[x][y] == (*player1).symbol || gboard[x][y] == (*player2).symbol)
			{
				hboard[x][y] = '*';
			}
			else 
			{
				if (*PlayersTurn == 0)
				{
					checkpositionTopRight(gboard, hboard, &x, &y, &(*player1).symbol, &(*player2).symbol, &(*TopRightA), &flip);
					checkpositionTop(gboard, hboard, &x, &y, &(*player1).symbol, &(*player2).symbol, &(*TopA), &flip);
					checkpositionTopLeft(gboard, hboard, &x, &y, &(*player1).symbol, &(*player2).symbol, &(*TopLeftA), &flip);
					checkpositionLeft(gboard, hboard, &x, &y, &(*player1).symbol, &(*player2).symbol, &(*LeftA), &flip);
					checkpositionBottomLeft(gboard, hboard, &x, &y, &(*player1).symbol, &(*player2).symbol, &(*BottomLeftA), &flip);
					checkpositionBottom(gboard, hboard, &x, &y, &(*player1).symbol, &(*player2).symbol, &(*BottomA), &flip);
					checkpositionBottomRight(gboard, hboard, &x, &y, &(*player1).symbol, &(*player2).symbol, &(*BottomRightA), &flip);
					checkpositionRight(gboard, hboard, &x, &y, &(*player1).symbol, &(*player2).symbol, &(*RightA), &flip);
				}
				else if (*PlayersTurn == 1)
				{
					checkpositionTopRight(gboard, hboard, &x, &y, &(*player2).symbol, &(*player1).symbol, &(*TopRightA), &flip);
					checkpositionTop(gboard, hboard, &x, &y, &(*player2).symbol, &(*player1).symbol, &(*TopA), &flip);
					checkpositionTopLeft(gboard, hboard, &x, &y, &(*player2).symbol, &(*player1).symbol, &(*TopLeftA), &flip);
					checkpositionLeft(gboard, hboard, &x, &y, &(*player2).symbol, &(*player1).symbol, &(*LeftA), &flip);
					checkpositionBottomLeft(gboard, hboard, &x, &y, &(*player2).symbol, &(*player1).symbol, &(*BottomLeftA), &flip);
					checkpositionBottom(gboard, hboard, &x, &y, &(*player2).symbol, &(*player1).symbol, &(*BottomA), &flip);
					checkpositionBottomRight(gboard, hboard, &x, &y, &(*player2).symbol, &(*player1).symbol, &(*BottomRightA), &flip);
					checkpositionRight(gboard, hboard, &x, &y, &(*player2).symbol, &(*player1).symbol, &(*RightA), &flip);
				}
			}
		}	 
	}

}

char CheckWinner(int *P1U, int *P2U, struct player *player1, struct player *player2, struct ScoreBoard winners[5], int *loop)
{
	
	int x, y, TotalToken;
	
	(*player1).win = 0;
	(*player2).win = 0;
		
	TotalToken = (*player1).score + (*player2).score;
	
	printf("\n");
	
	if (TotalToken == 64)
	{
		if ((*player1).score > (*player2).score)
		{
			(*player1).win = 1;
			*loop = 1;
		}
		else if ((*player2).score > (*player1).score)
		{
			(*player2).win = 1;
			*loop = 1;
		}
		else if ((*player2).score == (*player1).score)
		{
			printf("It's a Tie, %s and %s", (*player1).name, (*player2).name);
		}
	}
	else if (*P1U == 1 && *P2U == 1)
	{
		if ((*player1).score > (*player2).score)
		{
			(*player1).win = 1;
			*loop = 1;
		}
		else if ((*player2).score > (*player1).score)
		{
			(*player2).win = 1;
			*loop = 1;
		}
		else if ((*player2).score == (*player1).score)
		{
			printf("It's a Tie, %s and %s", (*player1).name, (*player2).name);
		}
	}
	
	if ((*player1).win == 1)
	{
		printf("You Win, %s with your score %i", (*player1).name, (*player1).score);
		UpdateScoreBoard(winners, &(*player1), &(*player2));
	}
	else if ((*player2).win == 1)
	{
		printf("You Win, %s with your score %i", (*player2).name, (*player2).score);
		UpdateScoreBoard(winners, &(*player1), &(*player2));
	}
	
}

char checkpositionTopRight(char gboard[8][17], char hboard[8][17], int *a, int *b, char *Ftoken, char *Stoken, int *TopRightA, int *flip)
{

	int c, d, e, f, x, y;
	
	if (gboard[*a][*b] == ' ')
	{
		if (gboard[*a - 1][*b + 2] == *Stoken)
		{
			d = *b + 4;
			
			for (c = *a - 2; c >= 0; c--)
			{
				if (gboard[c][d] == ' ')
				{
					break;	  
				}
				else if (gboard[c][d] == *Ftoken)
				{
					if (*flip == 1)
					{
						f = *b;
						
						for (e = *a - 1; e >= 0; e--)
						{
							f = f + 2;
							
							if (gboard[e][f] == *Ftoken)
							{
								break;
							}
							else if (gboard[e][f] == *Stoken)
							{
								gboard[e][f] = *Ftoken;
								*TopRightA = 1;
							}
						}
					}
					else
					{
						hboard[*a][*b] = 'A';
						break;
					}
				}
				
				d = d + 2;
			}
		}
	}
}

char checkpositionTop(char gboard[8][17], char hboard[8][17], int *a, int *b, char *Ftoken, char *Stoken, int *TopA, int *flip)
{

	int c, d, e, x, y;
	
	if (gboard[*a][*b] == ' ')
	{
		if (gboard[*a - 1][*b] == *Stoken)
		{
			d = *b;
			
			for (c = *a - 2; c >= 0; c--)
			{
				if (gboard[c][d] == ' ')
				{
					break;
				}
				else if (gboard[c][d] == *Ftoken)
				{	 	 	 	 
					if (*flip == 1)
					{
						for (e = *a - 1; e >= 0; e--)
						{
							if (gboard[e][d] == *Ftoken)
							{
								break;
							}
							else if (gboard[e][d] == *Stoken)
							{
								gboard[e][d] = *Ftoken;
								*TopA = 1;
							}
						}
					}
					else
					{
						hboard[*a][*b] = 'A';
						break;
					}
				}
			}
		}
	}
}

char checkpositionTopLeft(char gboard[8][17], char hboard[8][17], int *a, int *b, char *Ftoken, char *Stoken, int *TopLeftA, int *flip)
{

	int c, d, e, f, x, y;
	
	if (gboard[*a][*b] == ' ')
	{
		if (gboard[*a - 1][*b - 2] == *Stoken)
		{
			d = *b - 4;
			
			for (c = *a - 2; c >= 0; c--)
			{
				if (gboard[c][d] == ' ')
				{
					break;	  
				}
				else if (gboard[c][d] == *Ftoken)
				{
					if (*flip == 1)
					{
						f = *b;
						
						for (e = *a - 1; e >= 0; e--)
						{
							f = f - 2;
							
							if (gboard[e][f] == *Ftoken)
							{
								break;
							}
							else if (gboard[e][f] == *Stoken)
							{
								gboard[e][f] = *Ftoken;
								*TopLeftA = 1;
							}
						}
					}
					else
					{
						hboard[*a][*b] = 'A';
						break;
					}
				}
				
				d = d - 2;
			}
		}
	}
}

char checkpositionLeft(char gboard[8][17], char hboard[8][17], int *a, int *b, char *Ftoken, char *Stoken, int *LeftA, int *flip)
{

	int c, d, f, x, y;
	
	if (gboard[*a][*b] == ' ')
	{
		if (gboard[*a][*b - 2] == *Stoken)
		{
			c = *a;
			
			for (d = *b - 4; d >= 0; d--)
			{
				if (gboard[c][d] == ' ')
				{
					break;
				}
				else if (gboard[c][d] == *Ftoken)
				{	 	 
					if (*flip == 1)
					{	 	 
						for (f = *b - 1; f >= 0; f--)
						{
							if (gboard[c][f] == *Ftoken)
							{
								break;
							}
							else if (gboard[c][f] == *Stoken)
							{
								gboard[c][f] = *Ftoken;
								*LeftA = 1;
							}
						}
					}
					else
					{
						hboard[*a][*b] = 'A';
						break;
					}
				}
			}
		}
	}
}

char checkpositionBottomLeft(char gboard[8][17], char hboard[8][17], int *a, int *b, char *Ftoken, char *Stoken, int *BottomLeftA, int *flip)
{

	int c, d, e, f, x, y;
	
	if (gboard[*a][*b] == ' ')
	{
		if (gboard[*a + 1][*b - 2] == *Stoken)
		{
			d = *b - 4;
			
			for (c = *a + 2; c <= 7; c++)
			{
				if (gboard[c][d] == ' ')
				{
					break;	  
				}
				else if (gboard[c][d] == *Ftoken)
				{
					if (*flip == 1)
					{
						f = *b;
						
						for (e = *a + 1; e <= 7; e++)
						{
							f = f - 2;
							
							if (gboard[e][f] == *Ftoken)
							{
								break;
							}
							else if (gboard[e][f] == *Stoken)
							{
								gboard[e][f] = *Ftoken;
								*BottomLeftA = 1;
							}
						}
					}
					else
					{
						hboard[*a][*b] = 'A';
						break;
					}
				}
				
				d = d - 2;
			}
		}
	}
}

char checkpositionBottom(char gboard[8][17], char hboard[8][17], int *a, int *b, char *Ftoken, char *Stoken, int *BottomA, int *flip)
{

	int c, d, e, x, y;
	
	if (gboard[*a][*b] == ' ')
	{
		if (gboard[*a][*b] == ' ')
		{
			if (gboard[*a + 1][*b] == *Stoken)
			{
				d = *b;
				
				for (c = *a + 2; c <= 7; c++)
				{
					if (gboard[c][d] == ' ')
					{
						break;
					}
					else if (gboard[c][d] == *Ftoken)
					{	 
						if (*flip == 1)
						{	 	 	 
							for (e = *a + 1; e <= 7; e++)
							{
								if (gboard[e][d] == *Ftoken)
								{
									break;
								}
								else if (gboard[e][d] == *Stoken)
								{
									gboard[e][d] = *Ftoken;
									*BottomA = 1;
								}
							}
						}
						else
						{
							hboard[*a][*b] = 'A';
							break;
						}
					}
				}
			}
		}
	}
}

char checkpositionBottomRight(char gboard[8][17], char hboard[8][17], int *a, int *b, char *Ftoken, char *Stoken, int *BottomRightA, int *flip)
{

	int c, d, e, f, x, y;
	
	if (gboard[*a][*b] == ' ')
	{
		if (gboard[*a + 1][*b + 2] == *Stoken)
		{
			d = *b + 4;
			
			for (c = *a + 2; c <= 7; c++)
			{
				if (gboard[c][d] == ' ')
				{
					break;	  
				}
				else if (gboard[c][d] == *Ftoken)
				{
					if (*flip == 1)
					{
						f = *b;
						
						for (e = *a + 1; e <= 7; e++)
						{
							f = f + 2;
							
							if (gboard[e][f] == *Ftoken)
							{
								break;
							}
							else if (gboard[e][f] == *Stoken)
							{
								gboard[e][f] = *Ftoken;
								*BottomRightA = 1;
							}
						}
					}
					else
					{
						hboard[*a][*b] = 'A';
						break;
					}
				}
				
				d = d + 2;
			}
		}
	}
}

char checkpositionRight(char gboard[8][17], char hboard[8][17], int *a, int *b, char *Ftoken, char *Stoken, int *RightA, int *flip)
{

	int c, d, f, x, y;
	
	if (gboard[*a][*b] == ' ')
	{
		if (gboard[*a][*b + 2] == *Stoken)
		{
			c = *a;
			
			for (d = *b + 4; d <= 17; d++)
			{
				if (gboard[c][d] == ' ')
				{
					break;
				}
				else if (gboard[c][d] == *Ftoken)
				{	 	
					if (*flip == 1)
					{ 	  	  
						for (f = *b + 1; f <= 17; f++)
						{
							if (gboard[c][f] == *Ftoken)
							{
								break;
							}
							else if (gboard[c][f] == *Stoken)
							{
								gboard[c][f] = *Ftoken;
								*RightA = 1;
							}
						}
					}
					else
					{
						hboard[*a][*b] = 'A';
						break;
					}
				}
			}
		}
	}
}

