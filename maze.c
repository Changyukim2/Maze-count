#include <stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAZE_SIZE 12
int count = 0;
int bcount = 0;

typedef struct {
	short r;
	short c;
}element;

typedef struct {
	element data[MAZE_SIZE];
	int top;
}Stacktype;

void init_stack(Stacktype* s) {

	s->top = -1;
}

int is_empty(Stacktype* s) {

	return (s->top == -1);

}
int is_full(Stacktype* s) {
	return (s->top == (MAZE_SIZE - 1));
}


void push(Stacktype* s, element item) {
	if (is_full(s)) {
		fprintf(stderr, "스택 포화 에러\n");
		return;
	}
	else s->data[++(s->top)] = item;

}

element pop(Stacktype* s) {
	if (is_empty(s)) {
		fprintf(stderr, "스택 공백 에러\n");
		exit(1);
	}
	else return s->data[(s->top)--];
}

element peek(Stacktype* s) {
	if (is_empty(s)) {
		fprintf(stderr, "스택 공백 에러\n");
		exit(1);
	}
	else return s->data[s->top];
}

element here = { 1,0 }, entry = { 1,0 };

char maze[MAZE_SIZE][MAZE_SIZE] = {
        {'1','1','1','1','1','1','1','1','1','1'},

		{'e','1','0','1','0','0','0','1','0','1'},

		{'0','0','0','1','0','0','0','1','0','1'},

		{'0','1','0','0','0','1','1','0','0','1'},

		{'1','0','0','0','1','0','0','0','0','1'},

		{'1','0','0','0','1','0','0','0','0','1'},

		{'1','0','0','0','0','0','1','0','1','1'},

		{'1','0','1','1','1','0','1','1','0','1'},

		{'1','1','0','0','0','0','0','0','0','x'},

		{'1','1','1','1','1','1','1','1','1','1'} };

void push_loc(Stacktype* s, int r, int c)
{
	if (r < 0 || c < 0)
		return;
	if (maze[r][c] != '1' && maze[r][c] != '.') {
		element tmp;
		tmp.r = r;
		tmp.c = c;
		push(s, tmp);
	}
	else { count++; }
	if (count == 4) { bcount++; }
		
	

}

void maze_print(char maze[MAZE_SIZE][MAZE_SIZE])
{
	printf("\n");
	for (int r = 0; r < MAZE_SIZE; r++) {
		for (int c = 0; c < MAZE_SIZE; c++) {
			printf("%c", maze[r][c]);
		}
		printf("\n");
	}
}

int main(void) {

	int r, c;
	
	Stacktype s;

	init_stack(&s);
	here = entry;
	while (maze[here.r][here.c] != 'x') {
		r = here.r;
		c = here.c;
		maze[r][c] = '.';
		maze_print(maze);
		 count = 0;
		push_loc(&s, r - 1, c);
		push_loc(&s, r + 1, c);
		push_loc(&s, r, c - 1);
		push_loc(&s, r, c + 1);
		

		if (is_empty(&s)) {
			printf("실패\n");
			return;
		}
		else
			here = pop(&s);

	}
	printf("성공\n");
	printf("돌아온 경로의 횟수:%d\n",bcount);
	return 0;
}