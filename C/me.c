#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Map dimensions
#define MAP_WIDTH 15
#define MAP_HEIGHT 10

// Map characters
#define EMPTY '.'
#define WALL  '^'
#define PLAYER 'P'
#define TREASURE 'T'

void clear_screen() {
    printf("\033[2J\033[H");  // Clear screen and move cursor to top-left
}

// Draw the current game map
void draw_map(char map[MAP_HEIGHT][MAP_WIDTH]) {
    for (int i = 0; i < MAP_HEIGHT; i++) {
        for (int j = 0; j < MAP_WIDTH; j++) {
            printf("%c", map[i][j]);
        }
        printf("\n");
    }
}

void initialize_map(char map[MAP_HEIGHT][MAP_WIDTH], int *player_x, int *player_y, int *treasure_x, int *treasure_y) {
    for (int i = 0; i < MAP_HEIGHT; i++)
        for (int j = 0; j < MAP_WIDTH; j++)
            map[i][j] = EMPTY;

    for (int i = 0; i < MAP_WIDTH; i++) {
        map[2][i] = WALL;
        map[7][i] = WALL;
    }
    for (int i = 0; i < MAP_HEIGHT; i++) {
        map[i][3] = WALL;
        map[i][10] = WALL;
    }

    do {
        *player_x = rand() % MAP_WIDTH;
        *player_y = rand() % MAP_HEIGHT;
    } while (map[*player_y][*player_x] == WALL);
    map[*player_y][*player_x] = PLAYER;

    do {
        *treasure_x = rand() % MAP_WIDTH;
        *treasure_y = rand() % MAP_HEIGHT;
    } while (map[*treasure_y][*treasure_x] == WALL || (*treasure_x == *player_x && *treasure_y == *player_y));
    map[*treasure_y][*treasure_x] = TREASURE;
}

void load_new_map_section(char map[MAP_HEIGHT][MAP_WIDTH], int *player_x, int *player_y, int *treasure_x, int *treasure_y) {
    printf("\n Orun awaits you. Find my mask chosen one!! \n");

    for (int i = 0; i < MAP_HEIGHT; i++)
        for (int j = 0; j < MAP_WIDTH; j++)
            map[i][j] = EMPTY;

    for (int i = 0; i < MAP_HEIGHT && i < MAP_WIDTH; i++)
        map[i][i] = WALL;

    *player_x = MAP_WIDTH - 1;
    *player_y = MAP_HEIGHT - 1;
    map[*player_y][*player_x] = PLAYER;

    do {
        *treasure_x = rand() % MAP_WIDTH;
        *treasure_y = rand() % MAP_HEIGHT;
    } while (map[*treasure_y][*treasure_x] == WALL || (*treasure_x == *player_x && *treasure_y == *player_y));
    map[*treasure_y][*treasure_x] = TREASURE;
}

// Move the player and check for wall collisions
int move_player(char map[MAP_HEIGHT][MAP_WIDTH], int *player_x, int *player_y, char move) {
    int new_x = *player_x;
    int new_y = *player_y;

    if (move == 'w' || move == 'W') new_y--;
    else if (move == 's' || move == 'S') new_y++;
    else if (move == 'a' || move == 'A') new_x--;
    else if (move == 'd' || move == 'D') new_x++;
    else return 0;

    if (new_x >= 0 && new_x < MAP_WIDTH && new_y >= 0 && new_y < MAP_HEIGHT && map[new_y][new_x] != WALL) {
        map[*player_y][*player_x] = EMPTY;
        *player_x = new_x;
        *player_y = new_y;
        map[*player_y][*player_x] = PLAYER;
        return 1;
    }
    return 0;
}

// Olun intro splash screen
void show_olun_intro() {
    clear_screen();
    printf(
           "░░█░░               ░░░▓░▒▒▒▒▒▒▒▓▒░▒▓▓▓▒▒░▒▒▒▒░▓░░░▓▒▒▒▓▓▓▓▒▒▒▒▒▒▒▒▒▒▒\n"
        "░░▒░░               ░▒▓▓░▒▒▒▒▒▒▓▒▒▒▓▒▒▓█▓█▒░░█░▒█░░░▓▒▒▒▓▓▓▓▒▒▒▒▒▒▒▒▒▒\n"
        "▒░▒▒░               ░░▓▓░▒▒▒▒▒▒▓▒▒▒▓▒▒▒▒▒▒▒▓░▒░▒░▓▒░░▒▒▒▒▓▓▓▓▒▒▒▒▒▒▒▒▒\n"
        "░░░▒░               ░▒▓█▒▒▒▒▒▒▒▒▒▒▒░▒▓▒▒▒░▒▒▒▓░░▓▒▓▒▒▒▒▒▒▒▓▓▓░▒▒▒▒▒▒▒▒\n"
        "░▒░▒░               ▒▓▓█▒▒▒▒▒▒▒▒▓▒▒▓█▓▒▒▒▒▒▒▒▓▓░▒▒▒▓░▒░▒▒▒▒▒▓▓▒▒▒▒▒▒▒▒\n"
        "▒▒▒▒░               ░▓▓█░░▒▒▒▒▓▓████▓█▓▒▒░▒▒▒▒▒▓▒░▒▒▓▒▒▒▒▒▒▒▒▓▒▒▒▒▒▒▒▒\n"
        "▒░▒█▒░              ░▓▓█▒▒▒▒▒▒▒█▓▓█▓▓▓▓▒▒░▒▒▒░▒▒▓░▒▒▓▓▒▒▓▒▒▓▓▓▒▓▒▒▒▒▒▒\n"
        "░▒█▓▒░              ░▓▓░░▒▒▒▒▒▓█████▒▓█▓▒▒▒▒▒██▒▒▓▒▒▓▒▒▓▓▒▒▒▓▓▓▓▓▒▒▒▒▓\n"
        "░░░█▒░             ░▒▓█░▒▒▒▒▒▒████░█▓▓██▓██████▓▒▒▓▒▓▓█▓▓▒▒▒▒▒▓▓▓▓▒▒▓▓\n"
        "░░░░▓▒             ░░▓█░▒▒▒▒▒▒███████▓█▓▓▓▓█████▓▒▒▓▓▒▒▒▒▒▒▒▒▒▒▓▓▒▒▓▓█\n"
        "▓░▒░░▒░            ░▒▓▒▒▒░▒▒▒▒█████▓█▓█▓▓█▓█████▓▓▒▒▒▒▓▓▓▒▒▓▒▒▒▒▓▓▒▒▓█\n"
        "░░░▒░▒░            ░▓█░▒▒▒▒▒▒▓██████▓░█▒▓▓▒██████▓▒▓▓███▓▓▓▒▓▒░▓▒▒▒▒▓█\n"
        "░░░░░░░░          ░▒▓█▒░▒▒▒▒▒█▓▓▓████▓▓▓█▓▓█▓█▓▓█▒▒▓██████▓▓▓▓▓▓▓▓▓▒▓█\n"
        "░░░░░█▓░          ░▒█▒▒░▒▒▒▒▓█▓░▒▓██▒▓███████▓░█▓▒▒▓███████▓▓▒▒▓▓▒▓▓▓▓\n"
        "▒▒░░░█▓▒░         ▒▓▒▒▒▒░▒▒▒█▓▒  ▓██▓████████▓██▓▒▒▒▒▓▓▓▓▓▓▓▒▒▒▒▒▒▒▓▒▒\n"
        "▒▒▒░▒█▓▓░░       ░▒▒▒▒▒▒░▒▒█▓▓▓▓▓▓█▓▓███▓███████▓▒▒▒▒░░░░▒▒▒▒▒▒▓▒▒▒▒▓▒\n"
        "▒▒░░███▓▒░       ░▓▓░▒▒░▒░▒█▓▒▓▓▓█▓▓███▒▒▒▓█████▒▒▒▒░▒▒▒▒▒▒▓▓▒▒▓▓▒▒▒▒▒\n"
        "▒░░████▓▓▒░     ░▒▓▓ ▒▒▒▒▒▒█▓▓▓▓██▓███▓   ▒▓█████▓▓▓▓▒▓▒▓▓▓▓▓▒▒▓▓▒▒▒▒▒\n"
        "░░█████▓▓▓▒░░ ░░░▓▓ ▒▒▒▒░▒▒██▓▓███▓██▓▓▒▒  ▓▓█████▒▓▓▓▓▓▓▓▒▓▓▓▓▓▓▓▓▓▓▒\n"
        "░░█████▓▓▓▓▒▒▒▒▒▒▓▓▓▒▒░░▒▒▒█████▓▒███▓▓▓▓▓▒█▓█████▒▒▒▒▒▓▒▒▒▒▓▓▓▓▓▓▓█▓▓\n"
        "░░█████▓██▓▓▓▒▒▓▓▓██▒▓░▒▒▒░█████▒▓███▓▓▓▓▓▓▓██████▒▒▒▒▒▒▒▒▓▓▓▓▓▓▓▓▓▓▓█\n"
        "▒░█████████▓▓▓▓▓▓▓██░▒▒▒▒▓▓██████████▓▓▓▒▓▓▓███████▓▒▒▒▒▓▓█████▓██▓▓▓▓\n"
        "░▒██████████▓▓▓▓███▓▒▒▒▒▒░░▓█████████▓▓▓▓▓▓▓████████▒▓▒▓█████▓▓██▓▒▒▓▓\n"
        "▒▒█████▓▓█▓▓▓▓▓████▒▒▒▒░░▒░▒████▓████▓▓▓▓▓▓███████████▓█▓█▓▓▓▓▓███▓▒▒▒\n"
        "░░▒████▓▓█▓▓▓▓█████▒░░░▒▒▒▒▒███▓██████▓▓▓████████████████▓▓▓▓▓▓█▓█▓▓▒▒\n"
        "░░░████▓▓███▓██████▒▒░░▒▒▒▒▒██▓▒▒░███████████████▓█████▓▓▓▒▓▓▓▓▓▓▓▓▓▒▒\n"
        "░▒░▓███████████████▒░░░▒▒░░░██████▒▓█████████████▒▓███▓▓▓▒▒▒▒▓▓▓█▓▓▓▓▒\n"
        "░░░░███████████████▒░░░░▒░░░▓██▒▒▓▓██████████████▒▓██▓▓▓▒▒▒▒▒▒▒▒█▓▓▓▓▒\n"
        "░░░░███████████████▓▒░▒░▒▒░▒░██▓░▒▒██████████████▒░█▓▓▓▓▒▒▒▒▒▒▒▒██▓▒▒▒\n"
        "▒░░░███████████████▒░░░░▒░░▒▒███████████████████▒▒░▒█▓▓▒▒▒▒▒▒░░████▒▒▒\n"
        "░░░▒▒▒▒▒▒▓▓████████▒░░░░░░▒░░▒█▓▓▓█████████████▓░░░▒██▓▒░░▒▒▒▒▒█████▓▒\n"
        "░░▒▒▓█▓▓▒▒▓▒███████▒░░░░▒░░░░▒█▓▓▓██████████████▒▓░▒▓█▓▒░▒▒▒▒▒▒█████▓▓\n"
        "░░▒███████░▒▓██▓▓██▒░▒░▒░░▒░░░░█▓████████████████▓▓█▓▓▒▒▒▒▒▒▒▒██████▓▓\n"
        "\nAre you worthy to see Olun? (y/n): "
    );
}

int main() {
    srand(time(NULL));

    char map[MAP_HEIGHT][MAP_WIDTH];
    int player_x, player_y, treasure_x, treasure_y;
    char input[8];

    // Splash screen
    show_olun_intro();
    fgets(input, sizeof(input), stdin);
    if (input[0] != 'y' && input[0] != 'Y') {
        printf("\nOlun has denied you.\n");
        return 0;
    }

    // Start the game
    initialize_map(map, &player_x, &player_y, &treasure_x, &treasure_y);

    while (1) {
        clear_screen();
        draw_map(map);
        printf("\nMove (W/A/S/D): ");

        if (fgets(input, sizeof(input), stdin) != NULL) {
            char move = input[0];
            int moved = move_player(map, &player_x, &player_y, move);

            clear_screen();
            draw_map(map);

            if (!moved) {
                printf("\n\033[1;31m❌ Can't move there!\033[0m\n");
            }

            if (player_x == 0 && player_y == 0) {
                load_new_map_section(map, &player_x, &player_y, &treasure_x, &treasure_y);
                continue;
            }

            if (player_x == treasure_x && player_y == treasure_y) {
                clear_screen();
                draw_map(map);
                printf("\n🎉 You found the treasure! Well done!\n");
                break;
            }
        } else {
            printf("⚠️ Input error.\n");
            break;
        }
    }

    return 0;
}
