#ifndef __SNAKE_H
#define __SNAKE_H
#include <stdio.h>

#define WIDTH 60
#define LENGTH 23
#define SNAKE_MAX_SISE 1200
#define SNAKE_SPEED 100000

#define STAR_MAX 15

#define KEY_RIGHT 'd'
#define KEY_LEFT 'a'
#define KEY_UPWARD 'w'
#define KEY_DOWNWARD 's'
#define KEY_QUIT 'q'
#define KEY_RESTART 'r'

#define MOVE_RIGHT 'r'
#define MOVE_LEFT 'l'
#define MOVE_UPWARD 'u'
#define MOVE_DOWNWARD 'd'

#define clrscr() puts("\e[2J\e[1;1H")
#define gotoxy(x, y) printf("\e[%d;%dH", y, x)

typedef struct SNAKE {
    int len;
    int x[SNAKE_MAX_SISE];
    int y[SNAKE_MAX_SISE];
    char dir;
    int score;
    int dead;
    int speed;
} snake_t;

typedef struct MAP {
    char grid[LENGTH + 1][WIDTH + 1];
} map_t;

void reset_snake(snake_t *s);
void add_star(map_t *m);
void reset_map(snake_t *s, map_t *m);
snake_t *init_snake();
map_t *init_map(snake_t *s);
void draw_map(map_t *m);
void eat_star(snake_t *s, map_t *m, int grow_x, int grow_y);
void show_score(snake_t *s);
void update_map(snake_t *s, map_t *m);
void game_over(map_t *m);
void reset(snake_t *s, map_t *m);

#endif
