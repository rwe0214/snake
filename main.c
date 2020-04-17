#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/select.h>
#include <termios.h>
#include <time.h>
#include <unistd.h>

#include "snake.h"

struct termios orig_termios;

void reset_terminal_mode()
{
    tcsetattr(0, TCSANOW, &orig_termios);
}

void set_conio_terminal_mode()
{
    struct termios new_termios;

    tcgetattr(0, &orig_termios);
    memcpy(&new_termios, &orig_termios, sizeof(new_termios));

    atexit(reset_terminal_mode);
    cfmakeraw(&new_termios);
    tcsetattr(0, TCSANOW, &new_termios);
}

int kbhit()
{
    struct timeval tv = {0L, 0L};
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(0, &fds);
    return select(1, &fds, NULL, NULL, &tv);
}

int getch()
{
    int r;
    unsigned char c;
    if ((r = read(0, &c, sizeof(c))) < 0) {
        return r;
    } else {
        return c;
    }
}

void restart(snake_t *s, map_t *m)
{
    reset_terminal_mode();
    s->dead = 0;
    reset(s, m);
    draw_map(m);
    set_conio_terminal_mode();
}

int main()
{
    srand(time(NULL));
    snake_t *snake = init_snake();
    map_t *map = init_map(snake);
    draw_map(map);
    int count = 0;
    char key_press = ' ';
    set_conio_terminal_mode();

    while (key_press != KEY_QUIT) {
        if (kbhit())
            key_press = getch();
        if (key_press == KEY_RESTART)
            restart(snake, map);
        while (key_press != KEY_QUIT && !snake->dead) {
            if (count == snake->speed) {
                update_map(snake, map);
                count = 0;
                if (kbhit())
                    key_press = getch();
            }
            count++;
            gotoxy(1, 1);
            if (snake->dead) {
                game_over(map);
                break;
            }

            switch (key_press) {
            case KEY_RIGHT:
                if (snake->dir != MOVE_LEFT && snake->dir != MOVE_RIGHT) {
                    snake->dir = MOVE_RIGHT;
                }
                break;
            case KEY_LEFT:
                if (snake->dir != MOVE_RIGHT && snake->dir != MOVE_LEFT) {
                    snake->dir = MOVE_LEFT;
                }
                break;
            case KEY_UPWARD:
                if (snake->dir != MOVE_DOWNWARD && snake->dir != MOVE_UPWARD) {
                    snake->dir = MOVE_UPWARD;
                }
                break;
            case KEY_DOWNWARD:
                if (snake->dir != MOVE_UPWARD && snake->dir != MOVE_DOWNWARD) {
                    snake->dir = MOVE_DOWNWARD;
                }
                break;
            }
        }
    }
    clrscr();
    free(map);
    free(snake);
    return 0;
}
