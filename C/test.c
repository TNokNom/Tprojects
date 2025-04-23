#include <ncurses.h>
#include <string.h>

const char *logo[] = {
"   ,----..                                      ",
"  /   /   \\    ,--,                             ",
" /   .     : ,--.'|                             ",
".   /   ;.  \\|  | :            ,--,      ,---,  ",
".   ;   /  ` ;:  : '          ,'_ /|  ,-+-. /  | ",
";   |  ; \\ ; ||  ' |     .--. |  | : ,--.'|'   |",
"|   :  | ; | ''  | |   ,'_ /| :  . ||   |  ,\"' |",
".   |  ' ' ' :|  | :   |  ' | |  . .|   | /  | |",
"'   ;  \\; /  |'  : |__ |  | ' |  | ||   | |  | |",
" \\   \\  ',  / |  | '.'|:  | : ;  ; ||   | |  |/ ",
"  ;   :    /  ;  :    ;'  :  `--'   \\   | |--'  ",
"   \\   \\ .'   |  ,   / :  ,      .-./   |/      ",
"    `---`      ---`-'   `--`----'   '---'       "
};

const char *menu_items[] = {"START GAME", "info", "exit"};
#define MENU_SIZE 3

void draw_centered_menu(int highlight, int screen_width, int screen_height) {
    clear();

    // Draw logo
    int logo_height = sizeof(logo) / sizeof(logo[0]);
    int logo_start_y = 1;
    for (int i = 0; i < logo_height; i++) {
        int start_x = (screen_width - strlen(logo[i])) / 2;
        mvprintw(logo_start_y + i, start_x, "%s", logo[i]);
    }

    // Draw menu
    int menu_start_y = logo_start_y + logo_height + 2;
    for (int i = 0; i < MENU_SIZE; i++) {
        int len = strlen(menu_items[i]);
        int start_x = (screen_width - len - 4) / 2;
        if (i == highlight)
            mvprintw(menu_start_y + i, start_x, "> %s <", menu_items[i]);
        else
            mvprintw(menu_start_y + i, start_x + 2, "%s", menu_items[i]);
    }

    refresh();
}

int main() {
    initscr();
    noecho();
    cbreak();
    curs_set(0);
    keypad(stdscr, TRUE);

    int highlight = 0;
    int ch;
    int screen_width, screen_height;
    getmaxyx(stdscr, screen_height, screen_width);

    while (1) {
        draw_centered_menu(highlight, screen_width, screen_height);
        ch = getch();
        if (ch == KEY_UP)
            highlight = (highlight - 1 + MENU_SIZE) % MENU_SIZE;
        else if (ch == KEY_DOWN)
            highlight = (highlight + 1) % MENU_SIZE;
        else if (ch == 10 || ch == KEY_ENTER) {
            if (highlight == 0) {
                endwin();
                printf("Starting game...\n");
                break; // or call your game loop here
            } else if (highlight == 1) {
                clear();
                mvprintw(screen_height/2, (screen_width - 20)/2, "Info screen goes here.");
                refresh();
                getch();
            } else if (highlight == 2) {
                break;
            }
        }
    }

    endwin();
    return 0;
}
