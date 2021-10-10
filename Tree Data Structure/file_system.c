#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct node{
	char name[30];
	struct node *next;
	struct node *child;
	struct node *up;
};

int is_dir(struct node* , char []);
void rmdir(struct node* , char []);
struct node* chdir(struct node* , char []);
int mkdir(struct node *,char []);
void dir(struct node * );
int count(struct node*);


int main()
{
	struct node *root = (struct node*)malloc(sizeof(struct node));
	struct node *current = root;
	int test;
	strcpy(root->name,"root");
	root->next = NULL;
	root->child = NULL;
	root->up = NULL;
	char command[30];
	char input[30];
	
	
	printf("System has 5 function.\n\n-mkdir-rmdir-chdir-dir-count-\n\n");
	printf("System will halt, if we enter 'end' to the system\n\n");
	
	scanf("%s",command);
	
	if((strcmp(command,"end") != 0) && (strcmp(command,"dir") != 0) && (strcmp(command,"count") != 0))
		scanf("%s",input);
	
	while(strcmp(command,"end") != 0)
	{
		if(strcmp(command,"mkdir") == 0)
			mkdir(current,input);
			
		else if(strcmp(command,"rmdir") == 0)
			rmdir(current,input);
			
		else if(strcmp(command,"chdir") == 0)
			current = chdir(current,input);
			
		else if(strcmp(command,"dir") == 0)
			dir(current);
			
		else if(strcmp(command,"count") == 0)
			printf("Count : %d \n",count(current));
		else
			printf("Unknown command : '%s'\n",command);
		
		scanf("%s",command);
		if((strcmp(command,"end") != 0) && (strcmp(command,"dir") != 0) && (strcmp(command,"count") != 0))
			scanf("%s",input);	
	}

	return 0;
	
}

int is_dir(struct node* current, char input[])
{
	struct node* dir = current->child;
	int i = 1;
	if(dir == NULL)
		return 0;
	else
	{
		while(dir != NULL)
		{
			if(strcmp(dir->name,input) == 0)
			{
				return i;
			}
				
			i++;
			dir = dir->next;
		}		
	}
	return 0;
}

void rmdir(struct node* current, char input[])
{
	struct node* temp = current->child;
	struct node* temp_bef =NULL ;
	int flag = 0;
	if(temp == NULL)
	{
		printf("There is no subdirectory called: '%s'\n",input);
		flag++;
	}
	else
	{
		while(temp != NULL)
		{
			if(strcmp(temp->name,input) == 0)
			{
				if(temp->child != NULL)
				{
					printf("Cannot delete folder. The directory is not empty. \n");
					return;
				}
				else
				{
					if(temp_bef == NULL)
					{
						current->child = temp->next;
						free(temp);
						return;
					}
					else
					{
						temp_bef->next = temp->next;
						free(temp);
						return;
					}
				}
			}
			else
			{
				 temp_bef = temp;
				 temp = temp->next;
			}
		}
	}
	if(flag == 0)
		printf("The directory does not exist : %s\n",input);
}


struct node* chdir(struct node* current, char input[])
{
	int flag = -1;
	struct node* dir;
	struct node* temp;
	if(strcmp(input,"..") == 0)
	{
		if(strcmp(current->name,"root") == 0)
		{
			printf("You are already in root. \n");
			return current;
		}
		else
		{
			printf("Cursor shifted upper to : %s\n",current->up);
			return current->up;
		}
	}
	else
	{
		flag = is_dir(current,input);

		if(flag == 0)
		{
			printf("Can't change directory. The directory does not exist :  '%s' \n",input);
			return current;
		}
		else
		{
			dir = current->child;
			while(flag > 1)
			{
				dir = dir->next;
				flag--;
			}
			printf("Cursor shifted to  : %s\n",dir->name);
		}
	}
	return dir;
}

int mkdir(struct node *current,char input[])
{
	struct node* temp = (struct node*)malloc(sizeof(struct node));
	struct node *dir = current->child;
	temp->child = NULL;
	temp->next = NULL;
	temp->up = current;
	int value;
	strcpy(temp->name,input);
	
	value = is_dir(current,input);
	
	if(value == 0)
	{	
		if(dir== NULL)
		{
			current->child = temp;
		}	
		else
		{
			while(dir->next != NULL)
				dir = dir->next;
			dir->next = temp;
		}
	}
	else
	{
		printf("Duplicate directory error: '%s' \n",input);
		return value;
	}
	return 1;
}

void dir(struct node* current)
{
	printf("\n");
	struct node* temp= current->child;
	while(temp != NULL)
	{
		printf("%s\n",temp->name);
		temp = temp->next;
	}
	printf("\n");
	return;
}

int count(struct node* current)
{
	int ret= 0;
	struct node* temp= current->child;
	while(temp != NULL)
	{
		ret++;
		temp = temp->next;
	}
	return ret;
	
}
