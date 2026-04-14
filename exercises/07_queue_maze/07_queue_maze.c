#include <stdio.h>

#define MAX_ROW 5
#define MAX_COL 5

struct point {int row, col;}  statck[512];
int top = 0;

struct point local_patch[MAX_ROW][MAX_COL] ={
	{{-1, -1}, {-1, -1}, {-1, -1},{-1, -1},{-1, -1}},
	{{-1, -1}, {-1, -1}, {-1, -1},{-1, -1},{-1, -1}},
	{{-1, -1}, {-1, -1}, {-1, -1},{-1, -1},{-1, -1}},
	{{-1, -1}, {-1, -1}, {-1, -1},{-1, -1},{-1, -1}},
	{{-1, -1}, {-1, -1}, {-1, -1},{-1, -1},{-1, -1}}
};

void push(struct point p){
	statck[top++] = p;
}
struct point pop(void){
	return statck[--top];
}

int is_empty(void) {
	return top == 0;
}
int maze[MAX_ROW][MAX_COL] = {
	0, 1, 0, 0, 0,
	0, 1, 0, 1, 0,
	0, 0, 0, 0, 0,
	0, 1, 1, 1, 0,
	0, 0, 0, 1, 0,
};

void visit(int row, int col, struct point p)
{
	struct point current = {row, col};
	local_patch[row][col] = p;
	maze[row][col] = 2;
	push(current);
}

int main(void)
{
	// TODO: 在这里添加你的代码
    struct  point p = {0,0};
	maze[0][0] = 2;
	push(p);
	while (! is_empty()){
		p = pop();

		if (p.row == MAX_ROW - 1 && p.col == MAX_COL - 1)
			break;


		if(p.col - 1 >= 0 && maze[p.row][p.col - 1] == 0)
			visit(p.row , p.col - 1, p);//up
		if(p.row + 1 < MAX_ROW && maze[p.row + 1][p.col] == 0)
			visit(p.row+ 1, p.col, p); //right
		if(p.row - 1 >= 0 && maze[p.row - 1][p.col] == 0)
			visit(p.row - 1, p.col, p);//left
		if(p.col + 1 < MAX_COL && maze[p.row][p.col + 1] == 0)
			visit(p.row, p.col + 1, p);//down
	}

	if (p.col == MAX_COL - 1 && p.row == MAX_ROW -1){
		printf("(%d, %d)\n", p.row, p.col);
		while(local_patch[p.row][p.col].col != -1){
			p = local_patch[p.row][p.col];
			printf("(%d, %d)\n", p.row, p.col);

		}
	}

	return 0;
}