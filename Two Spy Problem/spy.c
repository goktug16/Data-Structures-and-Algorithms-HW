#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 100


struct stack{
	char items[MAXSIZE];
	int top;
	
};

void initialize(struct stack *s)
{
	s->top = 0;
}

int is_full( struct stack *s)
{
	if(s->top == MAXSIZE)
		return 1;
	else
		return 0;
}

int is_empty(struct stack *s)
{
	if(s->top == 0)
		return 1;
	else
		return 0;
}

int push(char x, struct stack *s)
{
	if(is_full(s))
		return 0;
	else
	{
		s->items[s->top] = x;
		s->top++;
		return 1;
	}
}

int pop(struct stack *s, char *x)
{
	if(is_empty(s))
		return 0;
	else
	{
		--s->top;
		*x = s->items[s->top] ;
		return 1;
	}
}

void print_stack(struct stack * s)
{
	int top = s->top;
	int i=0;
	while(i<top)
	{
		printf("%c",s->items[i]);
		i++;
	}
	printf("\n");
	return;
}

int is_number(char e)
{
	if(e >= '0' && e<='9')
		return 1;
	else
		return 0;	
}

int push_to_stack(char kod[100], struct stack *stk)
{
	char *e;
	char op,temp;
	int top;
	int num;
	e = kod;
	while(*e != '\0')
	{
		if(!is_number(*e))
			push(*e,stk);
		else
		{
			op = *e;
			op = op -'0';
			if((stk->top)-op >= 0)
			{
				while(op>0)
				{
					pop(stk,&temp);
					op--;
				}
			}
			else
				return -1;
		}
		e++;
	}
	return 1;
}
int cmp_two_stacks(struct stack* s1, struct stack* s2)
{
	int flag=0,top;
	if(s1 -> top != s2->top) // toplar esit degil ise kelimeler farkli uzunluktadir
		return -1;
	else
	{
		top = s1->top-1;
		while(top >= 0 && flag == 0)
		{
			if(s1->items[top] == s2->items[top])
				top--;
			else
				flag =1;
		}
	}
	if(top==-1 && flag ==0)
		return 1;
	else
		return -1;
}
int main()
{
	char kod[100];
	char kod2[100];
	char *e,x;
	int ret,ret2;
	struct stack *stk = (struct stack *) malloc(sizeof(struct stack));
	struct stack *stk2 = (struct stack *) malloc(sizeof(struct stack));
	if(stk == NULL || stk2 == NULL)
		printf("Hafiza Acilamadi");
	else
	{
		initialize(stk);
		initialize(stk2);
		printf("Kod 1 giriniz : ");
		scanf("%s",kod);
		printf("Kod 2 giriniz : ");
		scanf("%s",kod2);
		ret = push_to_stack(kod,stk);
		ret2 = push_to_stack(kod2,stk2);
		printf("\n");
		if(ret == -1)
			printf("Kod 1 , Verilen rakamla silinebilecek karakter sayisi yok\n");
		if(ret2 == -1)
			printf("Kod 2 , Verilen rakamla silinebilecek karakter sayisi yok\n");
		if(ret == 1 && ret2 ==1)
		{
			printf("Cozulmus kod 1: ");
			print_stack(stk);
			printf("\n");
			printf("Cozulmus kod 2 : ");
			print_stack(stk2);
		}
		ret = cmp_two_stacks(stk,stk2);
		if(ret == 1)
			printf("Bu iki casus iletisime gecebilir ");
		else
			printf("Casuslar iletisime gecemez");		
	}
	free(stk);
	free(stk2);
	return 0;
}
