#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <conio.h>
#include <unistd.h>

#define MAX_X 15
#define MAX_Y 15

#define UP 1
#define LEFT 2
#define DOWN 3
#define RIGHT 4

typedef struct tail_t{
    int x;
    int y;
    } tail_t;

typedef struct snake_t{
    int x;
    int y;
    int direction;
    struct tail_t * tail;
    size_t tsize;
    }  snake_t;

struct snake_t initSnake(int x, int y, size_t tsize){
    struct snake_t snake;
    snake.x = x;
    snake.y = y;
    snake.tsize = tsize;
    snake.tail = (tail_t *) malloc (sizeof(tail_t) * 100);
    for (int i =0; i < tsize; ++i){
        snake.tail[i].x = x + i +1;
        snake.tail[i].y = y;
        }
    return snake;
}

int checkDirection(snake_t snake, int32_t key)
{
    if((key == 'a' && snake.x > 0) ||
        (key == 'd' && snake.x < MAX_X - 1) ||
        (key == 'w' && snake.y > 0) ||
        (key == 's' && snake.y < MAX_Y - 1))
    {
        switch(key)
        {
            case 'a':
                snake.direction = LEFT;
                break;
            case 'd':
                snake.direction = RIGHT;
                break;
            case 'w':
                snake.direction = UP;
                break;
            case 's':
                snake.direction = DOWN;
                break;
        }
        return 1;
    }
    return 0;
}
    
    

// @**
void printSnake(struct snake_t snake)
{
        char matrix[MAX_X][MAX_Y];
        for (int i = 0; i < MAX_X; ++i)
            for (int j = 0; j < MAX_Y; ++j)
                matrix[i][j] = ' ';
        matrix[snake.x][snake.y] = '@';
        
        for (int i = 0; i < snake.tsize; ++i)
            matrix[snake.tail[i].x][snake.tail[i].y] = '*';
        
        for (int j = 0; j < MAX_Y; ++j)
            for (int i = 0; i < MAX_X; ++i)
                printf("%c", matrix[i][j]);
        printf("\n");
}

bool isInCorner(const snake_t snake)
{
    return snake.x == 0 || snake.y == 0 ||
           snake.x == MAX_X - 1 || snake.y == MAX_Y - 1;
}

snake_t moveSnake(snake_t snake, int32_t key)
{
    snake.direction = checkDirection(snake, key) ? snake.direction : DOWN;
    
    if(!checkDirection(snake, key) && !isInCorner(snake))
    {
		snake.x += snake.direction;
		snake.y += snake.direction;
    }
    
    for (int i = snake.tsize - 1; i > 0; i++)
    {
        if(snake.tail[i].x == snake.x && snake.tail[i].y == snake.y)
            break;
        if(snake.x < 0 || snake.x >= MAX_X || snake.y < 0 || snake.y >= MAX_Y)
            break;
    }
    return snake;
}

snake_t moveLeft(snake_t snake){
	for (int i = snake.tsize - 1; i > 0; i--){
		snake.tail[i] = snake.tail[i-1];
		}
	snake.tail[0].x = snake.x;
	snake.tail[0].y = snake.y;
	
	snake.x = snake.x - 1;	
	if (snake.x < 0){
		snake.x = MAX_X - 1;
		}
	return snake;
	}	

int main()
{
    struct snake_t snake = initSnake( 10, 5, 5);
    
    while(1)
    {
		printSnake(snake);
        snake = moveLeft(snake);
        char key = getch();
        snake = moveSnake(snake, key);
        checkDirection(snake, key);
        sleep(1);
        system("cls");
        printSnake(snake);
    }
    return 0;
}
