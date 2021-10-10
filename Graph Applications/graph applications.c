#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Alaaddin Goktug Ayar


struct node{
	char searched[30];
	int search_num;
	struct node* next;
};

struct Graph {
  int numVertices;
  struct node** adjLists;
};

struct Graph* create_graph(int vertices);
struct node* createNode(char searched[30]);
int find_string(char name[30],struct Graph* graph);
void printGraph(struct Graph* graph);
int add_edge(struct Graph* graph, char searched_1[30] , char searched_2[30]);
struct Graph* merge_graphs(struct Graph* graph1,struct Graph * graph2,int v1 , int v2,int);
int is_intersect(char searched[30], struct Graph* graph_2, int v2);
int increase_searched(struct Graph* merged_graph,char searched[30],int m_size);
int find_smallest(struct node** list);
void find_3_max(struct Graph*merged_graph,char searched[30]);

int main()
{
	int vertice_1,vertice_2;
	int i,j,k,flag=0,merged_size,intersect=0;
	char search[30];
	char search2[30];
	
	struct node* vertex;
	
	printf("Enter the vertice numbers for graph 1 and graph 2 : \n");
	
	printf("Graph 1 : ");
	scanf("%d",&vertice_1);
	
	printf("\nGraph 2 : ");
	scanf("%d",&vertice_2);
	
	struct Graph * graph_1 =  create_graph(vertice_1);
	struct Graph * graph_2 =  create_graph(vertice_2);
	struct Graph * merged;
	
	printf("Enter node values for graph 1\n");
	for(i=0 ; i<vertice_1 ; i++)
	{
		printf("Node %d: ",i);
		scanf("%s",search);
		vertex = createNode(search);
		graph_1->adjLists[i] = vertex;
	}
	
	printf("Enter node values for graph 2\n");
	for(i=0 ; i<vertice_2 ; i++)
	{
		printf("Node %d: ",i);
		scanf("%s",search);
		vertex = createNode(search);
		graph_2->adjLists[i] = vertex;
	}
	
	printf("Enter the number of neighbors of '%s': ",(graph_1->adjLists[0])->searched);
	scanf("%d",&j);
	for(k=0 ; k<j; k++)
	{
		printf("Enter neighbor %d: ",k+1);
		scanf("%s",search2);
		flag = add_edge(graph_1,(graph_1->adjLists[0])->searched,search2);
		if(flag == -1)
		{
			printf("This name not in graph, please enter again.\n");
			k--;
		}
	}
	
	printf("Enter the number of neighbors of '%s': ",(graph_2->adjLists[0])->searched);
	scanf("%d",&j);
	for(k=0 ; k<j; k++)
	{
		printf("Enter neighbor %d: ",k+1);
		scanf("%s",search2);
		flag = add_edge(graph_2,(graph_2->adjLists[0])->searched,search2);
		if(flag == -1)
		{
			printf("This name not in graph, please enter again.\n");
			k--;
		}
	}
	
	for(i = 0 ; i<vertice_1 ; i++)
		for(j = 0; j<vertice_2; j++)
		{
			if(strcmp(((graph_1->adjLists[i])->searched),(graph_2->adjLists[j])->searched) == 0)
				intersect++;
		}
		
	merged = merge_graphs(graph_1,graph_2,vertice_1,vertice_2,intersect);
	merged_size = vertice_1 + vertice_2 - intersect;
	printf("\n\nMerged Graph \n\n");
	printGraph(merged);
	
	printf("\nSearch some string('end' will terminate program) : ");
	scanf("%s",search);
	while(strcmp(search,"end") != 0)
	{
		if(increase_searched(merged,search,merged_size))
		{
			find_3_max(merged,search);
		}
		else
			printf("This string not in graph\n");
			
		printf("\nSearch some string('end' will terminate program) : ");
		scanf("%s",search);
	}
	
	return 0;
	
}

int increase_searched(struct Graph* merged_graph,char searched[30],int m_size)
{
	int i=0;
	struct node* temp;
	int flag = 0;
	for(i=0 ; i< m_size; i++)
	{
		temp = merged_graph->adjLists[i];
    	while (temp != NULL) 
		{
			if(strcmp(temp->searched,searched) == 0)
			{
				(temp->search_num)++;
				flag++;
			}
      		temp = temp->next;
    	}
	}
	if(flag)
		return 1;
	else
		return -1;
}

void find_3_max(struct Graph*merged_graph,char searched[30])
{
	struct node *temp;
	struct node *temp_array;
	struct node *temp_2 = (struct node*) malloc(sizeof(struct node));
	
	int i,j,num_ne=0,index;
	int m_size = merged_graph->numVertices;
	
	
	for(i=0 ; i<m_size; i++)
	{
		temp = (merged_graph->adjLists[i]);
		if(strcmp(temp->searched,searched) == 0)
		{
			index = i;
			while(temp != NULL)
			{
				temp = temp->next;	
				num_ne++;	
			}
		}
	}
	num_ne--;
	
	temp = (struct node*) malloc(num_ne * sizeof(struct node));
	if(num_ne < 3)
	{
		temp = (merged_graph->adjLists[index])->next;
		printf("Recommendations : \n");
		while(temp != NULL)
		{
			printf("	%s \n",temp->searched);
			temp = temp->next;
		}	
	}
	else
	{
		temp = (merged_graph->adjLists[index])->next;
		temp_array = (struct node*) malloc(num_ne * sizeof(struct node));
		i = 0;
		while(temp != NULL)
		{
			strcpy(temp_array[i].searched , temp->searched);
			temp_array[i].search_num = temp->search_num;
			temp = temp->next;
			i++;		
		}	
		for(i=0 ; i<num_ne; i++)
		{
			for(j=0 ; j<num_ne-i-1; j++)
			{
				if(temp_array[j].search_num > temp_array[j+1].search_num)
				{
					strcpy(temp_2->searched , temp_array[j+1].searched);
					temp_2->search_num = temp_array[j+1].search_num;
					strcpy(temp_array[j+1].searched , temp_array[j].searched);
					temp_array[j+1].search_num = temp_array[j].search_num;
					strcpy(temp_array[j].searched, temp_2->searched);
					temp_array[j].search_num = temp_2->search_num;
				}
			}
		}
		i = num_ne-1;
		j = num_ne - 3;
		printf("Recommendations : \n");
		while(i >= j)
		{
			
			printf("	%s \n",temp_array[i].searched);
			i--;
		}
	}
}

int find_smallest(struct node** list)
{
	int i,x;
	int smallest = 0;
	
	for(i=1 ; i<3; i++)
	{
		if(list[i]->search_num < smallest )
			smallest = i;
	}
	return smallest;	
}

struct Graph* merge_graphs(struct Graph* graph1,struct Graph * graph2,int v1 , int v2,int intersect)
{
	int i,j,size,index;
	struct Graph* merged_graph;
	struct node* newNode;
		
	size = v1 + v2 - intersect;
	
	merged_graph = create_graph(size);
	
	for(i=0; i<v1; i++)
		merged_graph->adjLists[i] = graph1->adjLists[i];
		
	for(j=0; j<v2; j++)
	{
		index = is_intersect((graph2->adjLists[j]->searched),graph1,v1);
		if(index == 0)
		{
			merged_graph->adjLists[i] = graph2->adjLists[j];
			i++;
		}
		else
		{
			newNode = createNode((graph2->adjLists[j]->next->searched));
			newNode->next = (merged_graph->adjLists[index])->next;
			(merged_graph->adjLists[index])->next = newNode;
		}
	}
			
	return merged_graph;
}

int is_intersect(char searched[30], struct Graph* graph_2, int v2)
{
	int i=0;
	
	for(i=0; i<v2; i++)
	{
		if((strcmp(searched,(graph_2->adjLists[i])->searched) == 0))
			return i;
	}
	return 0;
}

void printGraph(struct Graph* graph) 
{
	int v;
	struct node* temp;
	for (v = 0; v < graph->numVertices; v++)
	{
    	temp = graph->adjLists[v];
    	while (temp != NULL) 
		{
      		printf("%s(%d) -> ", temp->searched,temp->search_num);
      		temp = temp->next;
    	}
    	printf("\n");
	}
}

int find_string(char name[30],struct Graph* graph)
{
	int i;
	int num = graph->numVertices;
	
	for(i=0; i<num; i++)
	{
		if(strcmp(name,(graph->adjLists[i])->searched) == 0)
			return i;
	}
	return -1;
}


int add_edge(struct Graph* graph, char searched_1[30] , char searched_2[30])
{
	struct node* newNode = createNode(searched_2);
	int s1_index = find_string(searched_1,graph);
	int s2_index = find_string(searched_2,graph);

	if(s1_index >= 0 && s2_index >= 0)
	{		
		newNode->next = (graph->adjLists[s1_index])->next;
		(graph->adjLists[s1_index])->next = newNode;
	
		newNode = createNode(searched_1);
		newNode->next = (graph->adjLists[s2_index])->next;
		(graph->adjLists[s2_index])->next = newNode;
	}
	else
		return -1;
	
	return 1;
}


struct node* createNode(char searched[30]) {
  struct node* newNode = malloc(sizeof(struct node));
  strcpy(newNode->searched,searched);
  newNode->search_num = 0;
  newNode->next = NULL;
  return newNode;
}

struct Graph* create_graph(int vertices)
{
	struct Graph* graph = malloc(sizeof(struct Graph));
 	graph->numVertices = vertices;

  	graph->adjLists = malloc(vertices * sizeof(struct node*));

  	int i;
  	for (i = 0; i < vertices; i++)
   		graph->adjLists[i] = NULL;

  	return graph;
}
