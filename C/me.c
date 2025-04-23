#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include <ctype.h>
#include <ncurses.h>
#include <string.h>

#define MAP_HEIGHT 20
#define MAP_WIDTH 80

#define PLAYER '@'
#define TREASURE '%'
#define EMPTY ' '

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
    int logo_height = sizeof(logo) / sizeof(logo[0]);
    int logo_start_y = 1;
    for (int i = 0; i < logo_height; i++) {
        int start_x = (screen_width - strlen(logo[i])) / 2;
        mvprintw(logo_start_y + i, start_x, "%s", logo[i]);
    }
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

int show_dialogue_choices(const char *question, const char *choices[], int num_choices) {
    int highlight = 0;
    int ch;
    int screen_width, screen_height;
    getmaxyx(stdscr, screen_height, screen_width);

    while (1) {
        clear();
        mvprintw(screen_height / 2 - num_choices / 2 - 2, (screen_width - strlen(question)) / 2, "%s", question);
        for (int i = 0; i < num_choices; i++) {
            int len = strlen(choices[i]);
            int x = (screen_width - len - 4) / 2;
            if (i == highlight)
                mvprintw(screen_height / 2 - num_choices / 2 + i, x, "> %s <", choices[i]);
            else
                mvprintw(screen_height / 2 - num_choices / 2 + i, x + 2, "%s", choices[i]);
        }
        refresh();

        ch = getch();
        if (ch == KEY_UP)
            highlight = (highlight - 1 + num_choices) % num_choices;
        else if (ch == KEY_DOWN)
            highlight = (highlight + 1) % num_choices;
        else if (ch == 10 || ch == KEY_ENTER)
            return highlight;
    }
}

char map[MAP_HEIGHT][MAP_WIDTH + 1] = {
"~~~~~~~~~~~~~~~~~~~~~~~~~ +----------------------+",
"~~N~~~~/‾‾‾‾‾‾‾‾‾\\~~~~~~~ |        San        |",
"~W+E‾‾‾           ‾‾‾\\~~~ +----------------------+",
"~~S\\          %        \\~~ |                   |",
"~~~~|                 |~~ |   Use your new vessel|",
"~~~~|       @         |~~ |   to move and pickup |",
"~~~~|            _____/~~ |   the artifact       |",
"~~~~\\___        |~~~~~~~~ |                     |",
"~~~~~~~~\\_______/~~~~~~~~ |                     |",
"~~~~~~~~~~~~~~~~~~~~~~~~~ |                      |",
"~~~~~~~~~~~~~~~~~~~~~~~~~ |                      |",
"~~~~~~~~~~~~~~~~~~~~~~~~~ |                      |",
"~~~~~~~~~~~~~~~~~~~~~~~~~ |                      |",
"~~~~~~~~~~~~~~~~~~~~~~~~~ |                      |",
"~~~~~~~~~~~~~~~~~~~~~~~~~ +----------------------+",
};

int player_x = -1, player_y = -1;

void draw_map() {
    for (int i = 0; i < MAP_HEIGHT; i++)
        printf("%s\n", map[i]);
}

void locate_player() {
    for (int y = 0; y < MAP_HEIGHT; y++)
        for (int x = 0; x < MAP_WIDTH; x++)
            if (map[y][x] == PLAYER) {
                player_x = x;
                player_y = y;
                return;
            }
}

int is_walkable(int y, int x) {
    if (x < 0 || x >= MAP_WIDTH || y < 0 || y >= MAP_HEIGHT) return 0;
    char dest = map[y][x];
    return dest == EMPTY || dest == TREASURE;
}

int move_player(int dx, int dy) {
    int new_x = player_x + dx;
    int new_y = player_y + dy;

    if (!is_walkable(new_y, new_x)) return 0;

    char dest = map[new_y][new_x];
    map[player_y][player_x] = EMPTY;
    map[new_y][new_x] = PLAYER;
    player_x = new_x;
    player_y = new_y;
    return (dest == TREASURE) ? 2 : 1;
}

int main() {
    initscr(); noecho(); cbreak(); curs_set(0); keypad(stdscr, TRUE);
    int highlight = 0, ch;
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
            if (highlight == 0) break;
            else if (highlight == 1) {
                clear(); mvprintw(screen_height/2, (screen_width - 30)/2, "Use arrows to navigate. Press Enter to select."); refresh(); getch();
            } else {
                endwin(); return 0;
            }
        }
    }
    endwin();

    initscr(); noecho(); cbreak(); curs_set(0); keypad(stdscr, TRUE);
    const char *intro_choices[] = {"Yes, I am worthy", "No, I am not"};
    int decision = show_dialogue_choices("Are you worthy to see Olun?", intro_choices, 2);
    if (decision != 0) {
        endwin();
        printf("\nOlun has denied you.\n");
        return 0;
    }

    const char *prologue_continue[] = {"Continue"};
    show_dialogue_choices("Darkness grows. The gods are angry...\nFind my mask and help save Olun.", prologue_continue, 1);
    endwin();

    locate_player();
    while (1) {
        system("clear");
        draw_map();

        printf("\nMove (W/A/S/D): ");
        struct termios oldt, newt;
        char input;
        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
        input = getchar();
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
        input = tolower(input);

        int dx = 0, dy = 0;
        if (input == 'w') dy = -1;
        else if (input == 's') dy = 1;
        else if (input == 'a') dx = -1;
        else if (input == 'd') dx = 1;
        else continue;

        int result = move_player(dx, dy);
        if (result == 2) {
            system("clear");
            draw_map();
            initscr(); noecho(); cbreak(); curs_set(0); keypad(stdscr, TRUE);
            const char *mid_scene[] = {"Continue"};
            show_dialogue_choices("My warrior, Well done!\nYour task doesn't end here, I'm afraid. Continue on, find my mask!", mid_scene, 1);
            endwin();
            endwin();
            // Load new map here
            printf("Next Chapter Begins..");
            // You can call a function here to load and run the second map
        }
    }
    return 0;
}
