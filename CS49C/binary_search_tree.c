// CS49C p2

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <io.h>
#define	BST_DELETE 1

struct student
{
  int	ID;
  char	name[20];
  struct student *left;
  struct student *right;
};

int	id_counter;   /* Global ID counter */

int insert (struct student *current, struct student *new)
{
  int test = 0;

  if ( (test = _stricmp( new->name, current->name )) == 0)
  {
    free(new);  /* skip duplicate */
    return 0;  
  }
  else if (test < 0)
  {
    if (current->left == NULL)
    {
      current->left = new;
      return 1;
    }
    else
      return insert(current->left, new);
  } 
  else /* must be greater than 0 */
  {
    if (current->right == NULL)
    {
      current->right = new;
      return 1;
    }
    else
      return insert(current->right, new);
  }
  return 0;
}

struct student * bst_search (struct student *clist, char* token)
{
  /* don't modify the function signature, make sure you return the struct pointer or NULL */
  int test = 0;

  if (clist == NULL)
    return clist;

  /*  INSERT CODE HERE */


  if ((test = _stricmp(token,clist->name)) == 0)			//compare token and clist
  { 
	  return clist;		//if equal return clist
  }
  else if (test < 0)				//if less 
  {
	  if (clist->left == NULL)			//go to left 
	  {
		  clist = clist->left;
		  return clist;
	  }
	  else
		  return bst_search(clist->left,token);		//search when clist is its left
  }
  else /* must be greater than 0 */
  {
	  if (clist->right == NULL)			//if greater
	  {
		  clist = clist->right;		//go to right
		  return clist;
	  }
	  else
		  return bst_search(clist->right,token);		//search when clist is its right
  }
  return NULL;
}

struct student * bst_delete(struct student *clist, char* token, struct student **parent)
{
	/* don't modify the function signature,
	make sure you return the struct pointer or NULL */
	int test = 0;			//integer test
	struct student *child = NULL; // reference for child 
	struct student *current = NULL; // reference for current

	if (clist == NULL)			// if list is null exit
		return clist;

	/*  INSERT CODE HERE */
	if ((test = stricmp(token, clist->name)) == 0)   //compare token
	{     
		if (clist->left == NULL && clist->right == NULL)			
		{
			if ((*parent)->left == clist)	
			{
				(*parent)->left = NULL;			//set deleted pointer to null
			}
			else if ((*parent)->right == clist)
			{
				(*parent)->right = NULL;			//set deleted pointer to null
			}
		}
		else if (clist->left == NULL || clist->right == NULL)		//if one of the child is null
		{
			if ((*parent)->left == clist) 
			{
				if (clist->left != NULL)
				{
					child = clist->left;			//go one step down on left
					(*parent)->left = child;        //child is clist
				}
				else if (clist->right != NULL)
				{
					child = clist->right;         //go one step down on right
					(*parent)->left = child;	//child is clist
				}
			}
			else if ((*parent)->right == clist)
			{
				if (clist->left != NULL) 
				{
					child = clist->left;			//go one step down on left
					(*parent)->right = child;//child is clist
				}
				else if (clist->right != NULL)
				{
					child = clist->right;			//go one step down on right
					(*parent)->right = child;		//child is clist
				}
			}
		}
		else if (clist->left != NULL && clist->right != NULL) 
		{  //The current node has two Children.
			current = clist;
			if ((*parent)->left == clist) {   //If the Node is on left side of tree.
				child = clist->right;				//get smallest from right side of clist
				if (child->left == NULL){
					(*parent)->left = child;
					child->left = clist->left;
				}
				else {
					while (child->left != NULL) {
						child = child->left;			//go down till left of child is not null
					}
					(*parent)->left = child;
					child->left = clist->left;
				}
			}
			else if ((*parent)->right == clist)  //If the Node is in right of parent.
			{
				child = clist->right;				//get to largest on the right
				if (child->left == NULL) 
				{
					(*parent)->right = child;
					child->left = clist->left;
				}
				else {
					current = child;
					while (child->left != NULL) 
					{
						current = child;
						child = child->left;				//go down till left of child is not null
					}
					current->left = NULL;
					(*parent)->right = child;
					child->right = current;
					child->left = clist->left;
				}
			}
			else if ((*parent) == clist) {  //If the root node is to be deleted.
				child = clist->right;				//go to right and find if left is null, if it is parent is right child
				if (child->left == NULL) {
					(*parent) = child;
				}
				else {
					current = child;						//if left is not null go to end of left sub tree
					while (child->left != NULL)
					{
						current = child;
						child = child->left;
					}
					current->left = NULL;					//found successor, put left to null
					(*parent) = child;						// parent is this child
					child->left = clist->left;			//left of new child is clist left
					child->right = clist->right;		//left of new child is clist right
				}
			}
		}
	}
	else if (test < 0) {
		parent = &clist;
		return bst_delete(clist->left, token, parent);			//go to left is token is less 
	}
	else {
		parent = &clist;
		return bst_delete(clist->right, token, parent);		//go to left is token is less
	}
	return clist;
}


/* Given a binary tree, print its nodes in inorder*/
void printInorder(struct student *node)
{
     if (node == NULL)
          return;
 
     /* first recur on left child */
     printInorder(node->left);
 
     /* then print the data of node */
     printf("%s ", node->name);  
 
     /* now recur on right child */
     printInorder(node->right);
}
 
/* Given a binary tree, print its nodes according to the
  "bottom-up" postorder traversal. */
void printPostorder(struct student* node)
{
     if (node == NULL)
        return;
 
     // first recur on left subtree
     printPostorder(node->left);
 
     // then recur on right subtree
     printPostorder(node->right);
 
     // now deal with the node
     printf("%s ", node->name);  
}

/* Given a binary tree, print its nodes in preorder*/
void printPreorder(struct student* node)
{
     if (node == NULL)
          return;
 
     /* first print data of node */
     printf("%s ", node->name);  
 
     /* then recur on left sutree */
     printPreorder(node->left);  
 
     /* now recur on right subtree */
     printPreorder(node->right);
}
 
int main(int argc, char** argv)
{
	char *token;
	FILE *fptr;
	int id = 0;
	int i = 0;
	int test =0;
	int num_found = 0;
	int opcode = 0;
	char iname[21];
        struct student *root, *lptr1, *lptr2;
	
	id_counter = 1;

	if (argc != 4)
	{
		printf("Usage: %s filename token opcode\n", argv[0]);
		return 1;
	}

	token = argv[2];
	opcode = atoi(argv[3]);

	printf("\n");

	fptr = fopen((argv[1]), "rtc");
	if (fptr == NULL)
      printf( "File %s was not opened\n",argv[1] );
	else
   {
      /* Set pointer to beginning of file: */
      fseek( fptr, 0L, SEEK_SET );

      root = lptr1 = NULL;

       /* Read data from file: */
	  while ( fscanf(fptr, "%s", iname) != EOF )
	  {
 	    lptr1 = (struct student*) malloc(sizeof(struct student));
            lptr1->right = lptr1->left = NULL;
	    strcpy (lptr1->name, iname);
            lptr1->ID = id_counter++;

   	    if (root == NULL)
	    {
		root = lptr1;   /* First time is the root node */
	    }
	    else
            {
		insert(root, lptr1);
	    }
            printf( "%s ", lptr1->name );
	  }

      printf( "\n\nNumber of names = %d\n", id_counter - 1 );
      printf( "Input Token = %s\n", token );
      printf( "Opcode = %d\n\n", opcode );
      fclose( fptr );
   }

   printPreorder(root);
   printf("\n");
   printInorder(root);
   printf("\n");
   printPostorder(root);
   printf("\n\n");

   if (opcode == BST_DELETE)
   {
     lptr1 = bst_delete(root, token, &root);
     printPreorder(root);
     printf("\n");
     printInorder(root);
     printf("\n");
     printPostorder(root);
     printf("\n\n");
   }
   else
     lptr1 = bst_search(root, token);

   if (lptr1)
   {
     printf( "Found Student ID = %d\n", lptr1->ID );
     if (opcode == BST_DELETE)
       if (lptr1)
         free(lptr1);
   }
   else
     printf( "Student is not found.\n");

   return 0;
}



	


	


