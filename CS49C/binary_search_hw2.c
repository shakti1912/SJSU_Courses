// CS49C hw#2: b_search.c ==> b_search.dll

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <io.h>

struct student				
{
	int	ID;
	char	name[20];
};

__declspec(dllexport) int b_search(char* list, int count, char* token, int* num_found)
{
	int i;
	int start = 0;
	struct student *clist = (struct student*)list;

	/**** Fill in your code HERE ****/

	// binary search
	if (start > count)						//check if there are no elements in the given list
	{
		return 0;							//exit function if no elements in the array
	}
	int last = count - 1;				//variable last shows the last index of the stucture at the end of array
	int middle;							// middle variable to store middle index of the array
	while (start <= last)						//check if there are still elements in the array
	{
		middle = (start + last) / 2;				//calculate middle

		int z = stricmp(token, clist[middle].name);		//compare token with the student name at the middle index of the array
		
		if (z > 0)										// if above comparison returns positive value than required element is in the right side
		{
			start = middle + 1;
		}
		else if (z == 0)								// if above comparison returns 0 than we have found the required element 
		{
			*num_found += 1;							//increment value in the variable pointed by num_found address
			//search in left
			int i = middle - 1;							// variable i points to one before middle to start search on the left
			int a = 0;									//variable a for counter
			while (stricmp(token, clist[i].name) == 0)	// keep comparing token with ones left of middle till no match found
			{
				a++;									// increment counter
				*num_found += 1;						//increment num_found when match found
				i--;									// decrement loop counter
				
			}
			//search in right
			int j = middle + 1;								//variable j points to one after middle to start search on the right
			while (stricmp(token, clist[j].name) == 0)		//keep comparing token with ones right of middle till no match found
			{

				*num_found += 1;							//increment num_found when match found
				j++;										// increment loop counter
			}
			if (a != 0)										//return index of the first occurrence of required element which is i+2.
			{
				return (i + 2);
			}
			else                                           // return middle index if only one match found
			{
				return middle + 1;
			}

		}
		else                                                  //if comparison returns negative value than required element is on the left side
		{
			last = middle - 1;
		}
	}
	return 0;
}

