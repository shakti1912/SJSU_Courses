

#include "stdafx.h"

int connect_4[6][7];  /* make this global – declared outside of main */

int insert_board(int column, int value);
int next_move();
void printBoard();
int dummy = 0;

int main(int argc, char** argv)
{
	
	int NumberofPlayers = 0;
	int player1 = 0; //can be human player or computer
	int player2 = 0;
	printf("This is the Connect Four Game. Any player who gets 4 connected 1's or 2's wins the game.\n");
	scanf("%i", &NumberofPlayers);
	printf("Number of players: %i\n", NumberofPlayers);
	printf("Initial connect four board\n");
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			connect_4[i][j] = 0;
			printf("%i ",connect_4[i][j]);
		}
		printf("\n");

	}
	if (NumberofPlayers == 1)
	{
		player1 = 1;  //computer
		player2 = 2; //human player
		int move = 0;
		int win = 0;
		int turn = 1;
		printf("This is a 1 player game. Player 1 is computer. Player 2 is you.\n");
		win = insert_board(next_move(), player1);
		dummy = 1;
		turn = 2;
		
		printBoard();
		printf("Player 2 - Its your turn.Please make a move on the column # (1 - 7)\n");
		while (win != 1)
		{
			if (turn == 1)
			{
				win = insert_board(next_move(), player1);
			}
			else
			{
				scanf("%i", &move);
				win = insert_board(move - 1, player2);
			}
			printBoard();

			
			if (win == 0 && turn == 1)
			{
				printf("Player 2 - Its your turn.Please make a move on the column # (1 - 7)\n");
				turn = 2;
			}
			
			else if (win == 0 && turn == 2)
			{
				printf("Afer computers turn.\n");
				turn = 1;
			}		

		}
		if (turn == 1)
		{
			printf("Player 1 is the winner");

		}
		else
		{
			printf("Player 2 is the winner");

		}
		}

	else if (NumberofPlayers == 2)
	{
		player1 = 1;  //human player 1
		player2 = 2; //human player2
		int move = 0;
		int win = 0;
		int turn = 0;
		printf("This is a 2 player game. Player 1 - Its your turn. Please make a move on the column # (1-7)\n");
		turn = 1;
		while (win != 1)
		{
			scanf("%i", &move);
			if (turn == 1)
			{
				win = insert_board(move-1, player1);
			}
			else
			{
				win = insert_board(move-1, player2);
			}
			printBoard();
			if (win == 0 && turn == 1 )
			{
				printf("Player 2 - Its your turn. Please make a move on the column # (1 - 7)\n");
				turn = 2;
			}
			else if(win == 0 && turn == 2)
			{
				printf("Player 1 - Its your turn. Please make a move on the column # (1-7)\n");
				turn = 1;
			}

		}
		if (turn == 1)
		{
			printf("Player 1 is the winner");
			
		}
		else
		{
			printf("Player 2 is the winner");
			
		}


	}
	else
	{
		printf("This is either one or two player game. Run the game again.\n");
	}
}

int insert_board(int column, int value)
{
	
	for (int i = 5; i >= 0;i--)
	{
		if (connect_4[i][column] == 0)
		{	
			connect_4[i][column] = value;
			
			break;
		}		
	}

	//horizontal test
	
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 4; j++)
		{

			if ( connect_4[i][j] == 1 && connect_4[i][j+1] == 1 && connect_4[i][j+2] == 1 && connect_4[i][j+3] == 1)
			{
				return 1;
			}
			if (connect_4[i][j] == 2 && connect_4[i][j + 1] == 2 && connect_4[i][j + 2] == 2 && connect_4[i][j + 3] == 2)
			{
				return 1;
			}
			
		}
		
	}
	//vertical test
	for (int i = 5; i >= 3; i--)
	{
		for (int j = 0; j < 7; j++)
		{
			if (connect_4[i][j] == 1 && connect_4[i - 1][j] == 1 && connect_4[i - 2][j] == 1 && connect_4[i - 3][j] == 1)
			{
				return 1;
			}
			if (connect_4[i][j] == 2 && connect_4[i - 1][j] == 2 && connect_4[i - 2][j] == 2 && connect_4[i - 3][j] == 2)
			{
				return 1;
			}
		}
	}
	//diagonal test

	for (int i = 0;  i < 4; i++)
	{
		for (int j = 0; j < 3; j++)
		{

			if (connect_4[i][j] == 1 && connect_4[i+1][j+1] == 1 && connect_4[i +2][j+2] == 1 && connect_4[i +3][j+3] == 1)
			{
				return 1;
			}
			if (connect_4[i][j] == 2 && connect_4[i+1][j+1] == 2 && connect_4[i +2][j+2] == 2 && connect_4[i +3][j+3] == 2)
			{
				return 1;
			}
			

		}
	}
	//diagonal test 2
	for (int i = 3; i < 6; i++)
	{
		for (int j = 0; j < 4; j++)
		{

			if (connect_4[i][j] == 1 && connect_4[i -1][j + 1] == 1 && connect_4[i - 2][j + 2] == 1 && connect_4[i - 3][j + 3] == 1)
			{
				return 1;
			}
			if (connect_4[i][j] == 2 && connect_4[i - 1][j + 1] == 2 && connect_4[i - 2][j + 2] == 2 && connect_4[i - 3][j + 3] == 2)
			{
				return 2;
			}


		}
	}
	return 0;	
}

int next_move()
{
	if (dummy == 0)
	{
		return 3;
	}
	int start = 0;


	//Defensive move
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 4; j++)
		{

			if (connect_4[i][j] == 2 && connect_4[i][j + 1] == 2 && connect_4[i][j + 2] == 2)
			{
				return (j + 3);
			}

		}


	}
	
	for (int i = 5; i >= 3; i--)
	{
		for (int j = 0; j < 7; j++)
		{
			if (connect_4[i][j] == 2 && connect_4[i - 1][j] == 2 && connect_4[i - 2][j] == 2 )
			{
				return (i-3);
			}
			
		}
	}

	return start;
}
void printBoard()
{
	
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			
			printf("%d ", connect_4[i][j]);
		}
		printf("\n");

	}
	
}
