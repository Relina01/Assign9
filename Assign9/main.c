#include <stdio.h>

#define STACK_MAX_SIZE 100
#define MAX_SIZE 10
typedef struct
{
	short r;
	short c;
} element;

typedef struct
{
	element data[STACK_MAX_SIZE];
	int top;
	int count;
} StackType;

void init_stack(StackType* s)
{
	s->top = -1;
	s->count = 0;
}

int is_empty(StackType* s)
{
	return (s->top == -1);
}

int is_full(StackType* s)
{
	return (s->top == (STACK_MAX_SIZE - 1));
}

void push(StackType* s, element item)
{
	if (is_full(s))
	{
		fprintf(stderr, "Error : Full\n");
		return;
	}
	else s->data[++(s->top)] = item;
}

element pop(StackType* s)
{
	if (is_empty(s))
	{
		fprintf(stderr, "Error : Empty\n");
		return;
	}
	else
	{
		s->count++;
		return s->data[(s->top)--];
	}
}

element here = { 1,0 }, entry = { 1,0 };


char maze[MAX_SIZE][MAX_SIZE] = {
	{'1','1','1','1','1','1','1','1','1','1'},
	{'e','1','0','1','0','0','0','1','0','1'},
	{'0','0','0','1','0','0','0','1','0','1'},
	{'0','1','0','0','0','1','1','0','0','1'},
	{'1','0','0','0','1','0','0','0','0','1'},
	{'1','0','0','0','1','0','0','0','0','1'},
	{'1','0','0','0','0','0','1','0','1','1'},
	{'1','0','1','1','1','0','1','1','0','1'},
	{'1','1','0','0','0','0','0','0','0','x'},
	{'1','1','1','1','1','1','1','1','1','1'}
};

void push_loc(StackType* s, int r, int c)
{
	if (r < 0 || c < 0) return;
	if (maze[r][c] != '1' && maze[r][c] != '.')
	{
		element tmp;
		tmp.r = r;
		tmp.c = c;
		push(s, tmp);
	}
}

void maze_print(char maze[MAX_SIZE][MAX_SIZE])
{
	printf("\n");
	for (int r = 0; r < MAX_SIZE; r++)
	{
		for (int c = 0; c < MAX_SIZE; c++)
		{
			printf("%c", maze[r][c]);
		}
		printf("\n");
	}
}

int main()
{
	int r, c;
	StackType s;

	init_stack(&s);
	here = entry;
	while (maze[here.r][here.c] != 'x')
	{
		r = here.r;
		c = here.c;
		maze[r][c] = '.';
		maze_print(maze);
		push_loc(&s, r - 1, c);
		push_loc(&s, r + 1, c);
		push_loc(&s, r, c - 1);
		push_loc(&s, r, c + 1);
		if (is_empty(&s))
		{
			printf("Failure\n");
			return;
		}
		else
		{
			here = pop(&s);
		}
	}
	printf("Success\n");
	printf("Return count : %d\n", s.count - 1);
	return 0;
}