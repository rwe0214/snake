#include "snake.h"

#include <stdlib.h>
#include <time.h>

void reset_snake(snake_t *s)
{
    s->len = 5;
    s->dir = MOVE_RIGHT;
    for (int i = 0; i < s->len; i++) {
        s->x[i] = 31 - i;
        s->y[i] = 10;
    }
    s->score = 0;
    s->dead = 0;
    s->speed = SNAKE_SPEED;
}

void add_star(map_t *m)
{
    int x, y;
    do {
        x = rand() % (WIDTH - 2) + 2;
        y = rand() % (LENGTH - 2) + 2;
    } while (m->grid[y][x] != ' ');
    m->grid[y][x] = '*';
    gotoxy(x, y);
    printf("*");
}

void reset_map(snake_t *s, map_t *m)
{
    m->grid[1][1] = '+';
    m->grid[1][WIDTH] = '+';
    m->grid[LENGTH][1] = '+';
    m->grid[LENGTH][WIDTH] = '+';

    for (int y = 2; y < LENGTH; y++)
        m->grid[y][1] = m->grid[y][WIDTH] = '|';

    for (int x = 2; x < WIDTH; x++) {
        m->grid[1][x] = m->grid[LENGTH][x] = '-';
        for (int y = 2; y < LENGTH; y++)
            m->grid[y][x] = ' ';
    }

    for (int i = 0; i < s->len; i++)
        m->grid[s->y[i]][s->x[i]] = 'o';

    for (int i = 0; i < STAR_MAX; i++) {
        add_star(m);
    }
}

snake_t *init_snake()
{
    snake_t *s = malloc(sizeof(snake_t));
    reset_snake(s);
    return s;
}

map_t *init_map(snake_t *s)
{
    map_t *m = malloc(sizeof(map_t));
    reset_map(s, m);
    return m;
}

void draw_map(map_t *m)
{
    clrscr();
    gotoxy(1, 1);
    for (int y = 1; y <= LENGTH; y++) {
        for (int x = 1; x <= WIDTH; x++)
            printf("%c", m->grid[y][x]);
        printf("\n");
    }
    gotoxy(65, 14);
    puts("PRESS Q TO EXIT");
}

void eat_star(snake_t *s, map_t *m, int grow_x, int grow_y)
{
    s->len++;
    s->x[s->len - 1] = grow_x;
    s->y[s->len - 1] = grow_y;
    s->score += 2;
    s->speed -= 500;
    add_star(m);
}

void show_score(snake_t *s)
{
    gotoxy(65, 8);
    puts("SCORE BOX");
    gotoxy(65, 9);
    puts("+-------+");
    char score[8];
    sprintf(score, "%7d", s->score);
    gotoxy(65, 10);
    puts("|");
    gotoxy(73, 10);
    puts("|");
    gotoxy(66, 10);
    puts(score);
    gotoxy(65, 11);
    puts("+-------+");
}

void update_map(snake_t *s, map_t *m)
{
    for (int i = 0; i < s->len; i++) {
        gotoxy(s->x[i], s->y[i]);
        puts(" ");
    }

    int prev_x = s->x[s->len - 1], prev_y = s->y[s->len - 1];
    for (int i = s->len - 1; i > 0; i--) {
        s->x[i] = s->x[i - 1];
        s->y[i] = s->y[i - 1];
    }
    switch (s->dir) {
    case MOVE_RIGHT:
        s->x[0]++;
        break;
    case MOVE_LEFT:
        s->x[0]--;
        break;
    case MOVE_UPWARD:
        s->y[0]--;
        break;
    case MOVE_DOWNWARD:
        s->y[0]++;
        break;
    }
    if (s->x[0] >= WIDTH)
        s->x[0] = 2;
    if (s->x[0] <= 1)
        s->x[0] = WIDTH - 1;
    if (s->y[0] >= LENGTH)
        s->y[0] = 2;
    if (s->y[0] <= 1)
        s->y[0] = LENGTH - 1;

    if (m->grid[s->y[0]][s->x[0]] == '*')
        eat_star(s, m, prev_x, prev_y);

    if (m->grid[s->y[0]][s->x[0]] == 'o')
        s->dead = 1;

    m->grid[prev_y][prev_x] = ' ';
    gotoxy(prev_x, prev_y);
    puts(" ");
    for (int i = 0; i < s->len; i++) {
        m->grid[s->y[i]][s->x[i]] = 'o';
        gotoxy(s->x[i], s->y[i]);
        puts("o");
    }
    show_score(s);
}

void game_over(map_t *m)
{
    gotoxy(21, 9);
    puts("==== GAME OVER ====");
    gotoxy(23, 10);
    puts("PRESS Q TO EXIT");
    gotoxy(22, 11);
    puts("PRESS R TO RESTART");
}

void reset(snake_t *s, map_t *m)
{
    reset_snake(s);
    reset_map(s, m);
}
