// CS49C p1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <io.h>

struct student
{
  int	ID;
  char	name[20];
  struct student *left;
  struct student *right;
};

int l_search (char* list, int count, char* token, int* num_found)
{
	int i;
	int start = 0;
	struct student *clist = (struct student*)list;
	
	/**** PUT YOUR CODE HERE ****/

	i = 0;							//initialize i to 0
	while (i<count)					// loop till count is less than i
	{
		i++;										// increment i
		if (stricmp(clist->name, token) == 0)		//compare name with token, if equals change start and i variables
		{
			if (start == 0)							// change start only when i equals to 0
			{
				start = i;
			}
			*num_found = *num_found + 1;			// increment num_found if token equals to name

		}
		clist = clist->right;						// point clist to next node
	}

	return start;									// return the index of the first occurrence of the token

}

int main(int argc, char** argv)
{
	char *token;
	FILE *fptr;
	int id = 0;
	int i = 0;
	int num_found = 0;
        struct student *list, *lptr1, *lptr2;
	char iname[20];
	int id_counter = 0;
	
	if (argc != 3)
	{
		printf("Usage: %s filename token\n", argv[0]);
		return 1;
	}

	token = argv[2];

	printf("\n");

	fptr = fopen((argv[1]), "rtc");
	if (fptr == NULL)
          printf( "File %s was not opened\n",argv[1] );
	else
        {
         /* Set pointer to beginning of file: */
          fseek( fptr, 0L, SEEK_SET );

          list = lptr1 = NULL;

          /* Read data from file: */
	  while ( fscanf(fptr, "%s", iname) != EOF )
	  {
 	    lptr1 = (struct student*) malloc(sizeof(struct student));
            lptr1->right = lptr1->left = NULL;
	    strcpy (lptr1->name, iname);
            lptr1->ID = ++id_counter;

	    if (list == NULL)
	    {
		list = lptr1;
            }
	    else
            {
	      lptr2 = list;

	      while (lptr2->right != NULL)
		lptr2 = lptr2->right;

	      /* add new element at the end of the list */
		lptr2->right = lptr1;
	    }

            printf( "%s ", lptr1->name );
	  }

      printf( "\n\nNumber of names = %d\n", id_counter );
      printf( "Search Token = %s\n", token );
      fclose( fptr );
   }

   id = l_search( (char*)list, id_counter, token, &num_found);

   if (id)
	{
	   printf( "Number of Student found is %d.\n", num_found );
	   printf( "Student ID starts from %d to %d.\n", id, id+num_found-1 );
	}
   else
     printf( "Student is not found.\n");

   return 0;
}



	


	


