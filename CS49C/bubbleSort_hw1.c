/* CS49C HW#1 - Template */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <io.h>

int sorter (int list[], int count, int opcode)
{
  int x,y,temp; 

	/** Insert your code here **/
  int swap=1;								// variable swap to keep track of the number of swaps already occured.
  while (swap != 0)							// condition of while loop checks that continue till there are swaps. Because when no swap occurs list is sorted.
  {
	  swap = 0;								// no swap in the beginning.

	  for (int i = 0; i <count-1; i++)     // iterate through the array 
	  {

		  x = list[i];					  // x and y equals two consecutive elements of the array.
		  y = list[i + 1];

		  if (opcode == 1)				// for ascending if opcode is 1 and right number > left number, then swap
		  {
			  if (x > y)
			  {
				  temp = y;						 // store one value to some variable temporary variable temp
				  list[i + 1] = list[i];		// assign left element to right element
				  list[i] = temp;				// assign temp to left element
				  swap++;						// increment swap
			  }
		  }

		  if (opcode == 2)				// for descending if opcode is 2 and right number < left number, then swap
		  {
			  if (y > x)
			  {

				  temp = y;						 //store one value to some variable temporary variable temp
				  list[i + 1] = list[i];		// assign left element to right element
				  list[i] = temp;				// assign temp to left element
				  swap++;						// increment swap
			  }
		  }
	  }
  }
  

  return 0;
}

int main(int argc, char** argv)
{
	int numlist[1000], asc;
	FILE *fptr;

	int i = 0, j;
	
	if (argc != 3)
	{
		printf("Usage: %s filename asc_des\n", argv[0]);
		return 1;
	}

	asc = atoi (argv[2]);
	asc = (asc == 1) ? 1 : 2;

	printf("\n");

	fptr = fopen((argv[1]), "rtc");
	if (fptr == NULL)
      printf( "File %s was not opened\n",argv[1] );
	else
   {
      /* Set pointer to beginning of file: */
      fseek( fptr, 0L, SEEK_SET );

      /* Read data from file: */
	  while ( fscanf(fptr, "%d", &numlist[i]) != EOF )
	  {
          printf( "%d ", numlist[i] );
		  i++;
	  }

      printf( "\n\nNumber of integer = %d\n", i );
      printf( "Ascend_or_Descend = %d\n\n", asc );
      fclose( fptr );
   }

   sorter( numlist, i, asc);

   for (j = 0; j < i; j++)
          printf( "%d ", numlist[j] );

   printf("\n");

   return 0;
}



	


