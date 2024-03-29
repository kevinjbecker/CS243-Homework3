/// http://www.dreamincode.net/forums/topic/55572-conways-game-of-life/
/// downloaded by copy-paste on 8/19/2015 and modified to use an infinite loop.
///
/// This code needs serious work in these areas:
/// <ol>
/// <li>  syntax: there are a number of warnings that cause errors.
/// </li>
/// <li>  semantics: the game algorithm implementation is incorrect.
/// </li>
/// <li>  design: the implementation needs function and value refactoring.
/// </li>
/// <li>  style: formatting is poor; e.g. mix of TAB and spaces indentation
/// </li>
/// <li>  documentation: documentation is non-existent except for this block.
/// </li>
/// </ol>
///

#include <stdio.h>
#include <stdlib.h>

	void header(void) /*function for program header*/
   {
	  printf("\n\t..Welcome to the Game of life..\n");
   }
	
	void survivalRule(char life[][20], int x, int y)
   {
	  int row, col;
	  int neighbors = 0;
	  for(row = 1; row<19; row++)
	  {
		 for(col = 1; col<19; col++)
		 {
			if(life[row][col] == '*')
			{
			   if(life[row - 1][col - 1] == '*')
				  ++neighbors;
			   if(life[row - 1][col] == '*')
				  ++neighbors;
			   if(life[row - 1][col + 1] == '*')
				  ++neighbors;
			   if(life[row][col - 1] == '*')
				  ++neighbors;
			   if(life[row][col + 1] == '*')
				  ++neighbors;
			   if(life[row + 1][col - 1] == '*')
				  ++neighbors;
			   if(life[row + 1][col] == '*')
				  ++neighbors;
			   if(life[row + 1][col + 1] == '*')
				  ++neighbors;
			   if(neighbors == 2 || neighbors == 3)
			   {
				  life[row][col] = '*';
			   }
			}
		 }
	  }
	  return;
   }
	
	void birthRule(char life[][20], int x, int y)
   {
	  int row, col;
	  int neighbors = 0;
	  for(row = 1; row<19; row++)
	  {
		 for(col = 1; col<19; col++)
		 {
			if(&life[row][col]== " ")
			{
			   if(life[row - 1][col - 1] == '*')
				  neighbors++;
			   if(life[row - 1][col] == '*')
				  neighbors++;
			   if(life[row - 1][col + 1] == '*')
				  neighbors++;
			   if(life[row][col - 1] == '*')
				  neighbors++;
			   if(life[row][col + 1] == '*')
				  neighbors++;
			   if(life[row + 1][col - 1] == '*')
				  neighbors++;
			   if(life[row + 1][col] == '*')
				  neighbors++;
			   if(life[row + 1][col + 1] == '*')
				  neighbors++;
			   if(neighbors == 3)
			   {
			   	life[row][col] = '*';
			   }
			}
		 }
	  }

	  return;
   }
	
	void deathRule(char life[][20], int x, int y)
   {	
	  int row, col;
	  int neighbors = 0;
	  for(row = 1; row<19; row++)
	  {
		 for(col = 1; col<19; col++)
		 {
			if(life[row][col] == '*')
			{
			   if(life[row - 1][col - 1] == '*')
				  neighbors++;
			   if(life[row - 1][col] == '*')
				  neighbors++;
			   if(life[row - 1][col + 1] == '*')
				  neighbors++;
			   if(life[row][col - 1] == '*')
				  neighbors++;
			   if(life[row][col + 1] == '*')
				  neighbors++;
			   if(life[row + 1][col - 1] == '*')
				  neighbors++;
			   if(life[row + 1][col] == '*')
				  neighbors++;
			   if(life[row + 1][col + 1] == '*')
				  neighbors++;
			   if(neighbors < 2 || neighbors > 4)
			   {
				  life[row][col] = ' ';
			   }
			}
		 }
	  }
	  return;
   }

   	
int main(void)
   {
	  char life[20][20];
	  int orgs, gens;
	  int i, a, b, row, col;
	  int count = 0;
	  int x = 19;
	  int y = 19;
	  char ans;
   	
	  header();

		 printf("\nPlease enter the initial number of organisms: ");
		 scanf("%i", &orgs);
	  
		 srand( 31 );
			  
		 for(i = 0; i<orgs; i++)
		 {
			row = rand();
			row %= 20;
			col = rand();
			col %= 20;
			life[row][col] = '*';
		 }
		 
		 for(row = 0; row<20; row++)
		 {
			for(col = 0; col<20; col++)
			{
			   if(life[row][col] != '*')
			   	life[row][col] = ' ';
			}
		 }
			  
		 for(row = 0; row<20; row++)
		 {
			  for(col = 0; col<20; col++)
			  {
				  printf("%c", life[row][col]);
			  }
			  puts(" ");
		  }
			 
		 while ( 1 ) {
			birthRule(life, x, y);
			survivalRule(life, x, y);
			deathRule(life, x, y);
				for(row = 0; row<20; row++)
		 	{
				  for(col = 0; col<20; col++)
				  {
					  printf("%c", life[row][col]);
				  }
				  puts(" ");
		 	}
		  printf("\ngeneration: %d\n", count);
			count++;
		 }
		  
   	
	  return 0;
   }
			
