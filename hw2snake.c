
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <unistd.h>
#include <windows.h>
#include <stdbool.h>

#define MAX_X 15
#define MAX_Y 15

char dir;

typedef struct tail_t
{
    int x, y;
} tail_t;

typedef struct snake_t
{
    int x, y;
    struct tail_t * tail;
    size_t tsize;
} snake_t;

bool GameOver;

struct snake_t init_Snake(int x, int y, size_t tsize)
{
    struct snake_t snake;
    snake.x = x;
    snake.y = y;
    snake.tsize = tsize;
    snake.tail = (tail_t*) malloc(sizeof(tail_t) * 100);

    for(int i = 0; i < (int)tsize; i++)
    {
        snake.tail[i].x = x + i + 1;
        snake.tail[i].y = y;
    }
    return snake;
}

void print_Snake(struct snake_t snake)
{
    char matrix[MAX_X][MAX_Y];

    for(int i = 0; i < MAX_X; ++i)
        for(int j = 0; j < MAX_Y; ++j)
            matrix[i][j] = ' ';
    matrix[snake.x][snake.y] = '@';
    
    for(int i = 0; i < (int)snake.tsize; ++i)
        matrix[snake.tail[i].x][snake.tail[i].y] = '*';
    
    for(int j = 0; j < MAX_Y; ++j)
        for(int i = 0; i < MAX_X; ++i)
                printf("%c", matrix[i][j]);
}

snake_t move_Snake(snake_t snake)
{
    int prevX = snake.tail[0].x;
    int prevY = snake.tail[0].y;
    int nextX, nextY;

    snake.tail[0].x = snake.x;
    snake.tail[0].y = snake.y;

    for(int i = 1; i < (int)snake.tsize; i++)
    {
        nextX = snake.tail[i].x;
        nextY = snake.tail[i].y;
        snake.tail[i].x = prevX;
        snake.tail[i].y = prevY;
        prevX = nextX;
        prevY = nextY;
    }

    for(int i = 0; i < (int)snake.tsize; i++)
    {
        if(snake.tail[i].x == snake.x && snake.tail[i].y == snake.y)
            GameOver = true;
    }

    switch (dir)
    {
    case 'L':
        snake.x--;
        break;
    case 'R':
        snake.x++;
        break;
    case 'U':
        snake.y--;
        break;
    case 'D':
        snake.y++;
        break;
    }
    return snake;
}

void Input()
{
    if(_kbhit())
    {
        switch (_getch())
        {
        case 'a':
            dir = 'L';
            break;
        case 'd':
            dir = 'R';
            break;
        case 'w':
            dir = 'U';
            break;
        case 's':
            dir = 'D';
            break;
        }
    }
}

int main(void)
{
    struct snake_t snake = init_Snake(10,5,3);
    print_Snake(snake);

    while(!GameOver)
    {
        Input();
        snake = move_Snake(snake);
        system("cls");
        print_Snake(snake);
        sleep(1);
    }
    return 0;
}