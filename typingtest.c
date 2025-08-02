#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>

#define WORD_MAX_LEN 20
#define WORD_DISPLAY_LIMIT 20
#define LINE_WORD_COUNT 10
#define TIME_LIMIT 60

int current_y, current_x;


int initialize_ncurses();
int load_words(char all_word_list[][WORD_MAX_LEN], int *count);
char get_game_mode();
int select_random_words(char all_word_list[][WORD_MAX_LEN], int count, char random_word_list[][WORD_MAX_LEN],
                        int rand_word_count, int min_length, int max_length);
int display_words(char random_word_list[][WORD_MAX_LEN], int start, int limit, int total);
int start_typing_test(char random_word_list[][WORD_MAX_LEN], int rand_word_count);

int main()
{
    initialize_ncurses();

    char all_word_list[357][WORD_MAX_LEN];
    int count = 0;
    load_words(all_word_list, &count);
    attron(COLOR_PAIR(4));
    printw("Welcome!!! This is a simple typing game made in C.\n\n");
    printw("Press Enter to start the game or Escape twice to exit\n");
    attroff(COLOR_PAIR(4));
    move(4, 0);
    int placement1 = 4;
    int ch;
    while (placement1)
    {
        ch = getch();
        if (ch == '\n' || ch == 27)
            break;
        else
        {
            move(placement1, 0);
            printw("Invalid Input. Please Press Enter to start the game\n");
            placement1++;
            if (placement1 >= 30)
            {
                clear();
                attron(COLOR_PAIR(4));
                printw("Welcome!!!This is a simple typing game made in C.\n\n");
                printw("Press Enter to start the game or Escape to exit\n");
                attroff(COLOR_PAIR(4));
                placement1 = 4;
            }
        }
    }

    bool play_again = true;

    if (ch == 27)
    {
        endwin();
        return 0;
    }
    do
    {
        clear();
        char mode = get_game_mode();

        int rand_word_count = (mode == '1') ? 20 : (mode == '2') ? 40
                                                                 : 60;
        int min_length = (mode == '1') ? 1 : (mode == '2') ? 5
                                                           : 8;
        int max_length = (mode == '1') ? 4 : (mode == '2') ? 7
                                                           : WORD_MAX_LEN;

        char random_word_list[rand_word_count][WORD_MAX_LEN];
        select_random_words(all_word_list, count, random_word_list, rand_word_count, min_length, max_length);

        start_typing_test(random_word_list, rand_word_count);

        clear();
        attron(COLOR_PAIR(4));
        printw("Play again? Press R or r or y to restart, escape or n or N to quit: ");
        attroff(COLOR_PAIR(4));
        move(2, 0);
        refresh();
        char choice;
        int placement3 = 2;
        while (1)
        {
            choice = getch();
            if (choice == 'y' || choice == 'r' || choice == 'R' || choice == 'n' || choice == 27 || choice == 'N')
            {
                break;
            }
            else
            {
                move(placement3, 0);
                printw("Invalid Input. Please press a valid key.\n");
                placement3++;
                 if (placement3 >= 30)
                {
                    clear();
                    attron(COLOR_PAIR(4));
                    printw("Play again? Press R or r or y to restart, escape or n or N to quit: ");
                    attroff(COLOR_PAIR(4));
                    placement3 = 2;
                }
            }
        }

        if (choice == 'n' || choice == 27 || choice == 'N')
        {
            play_again = false;
        }
        else if (choice == 'y' || choice == 'r' || choice == 'R')
        {
            play_again = true;
        }

    } while (play_again);

    endwin();
    return 0;
}

int initialize_ncurses()
{
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    start_color();
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    init_pair(2, COLOR_RED, COLOR_BLACK);
    init_pair(3, COLOR_YELLOW, COLOR_BLACK);
    init_pair(4, COLOR_BLACK, COLOR_WHITE);
    init_pair(5, COLOR_BLUE, COLOR_BLACK);
    init_pair(6, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(7, COLOR_CYAN, COLOR_BLACK);
}

int load_words(char all_word_list[][WORD_MAX_LEN], int *count)
{
    while (*count < 357 && fscanf(stdin, "%19s", all_word_list[*count]) == 1)
    {
        (*count)++;
    }
    freopen("/dev/tty", "r", stdin);
}

char get_game_mode()
{
    clear();
    attron(COLOR_PAIR(4));
    printw("Select Mode:\n\n");
    attroff(COLOR_PAIR(4));
    attron(COLOR_PAIR(3));
    printw("1.Easy\n\n");
    attroff(COLOR_PAIR(3));
    attron(COLOR_PAIR(2));
    printw("2.Medium\n\n");
    attroff(COLOR_PAIR(2));
    attron(COLOR_PAIR(6));
    printw("3.Hard\n\n");
    attroff(COLOR_PAIR(6));
    attron(COLOR_PAIR(4));
    printw("Press 1, 2, or 3:\n\n");
    attroff(COLOR_PAIR(4));
    char mode;
    int placement2 = 10;
    while (placement2)
    {
        mode = getch();
        if (mode == '1' || mode == '2' || mode == '3')
        {
            break;
        }
        else
        {
            move(placement2, 0);
            printw("Invalid Input. Please Press 1, 2 or 3 to select difficulty:");
            placement2++;
            if (placement2 >= 30)
            {
                clear();
                attron(COLOR_PAIR(4));
                printw("Select Mode:\n\n");
                attroff(COLOR_PAIR(4));
                attron(COLOR_PAIR(3));
                printw("1.Easy\n\n");
                attroff(COLOR_PAIR(3));
                attron(COLOR_PAIR(2));
                printw("2.Medium\n\n");
                attroff(COLOR_PAIR(2));
                attron(COLOR_PAIR(6));
                printw("3.Hard\n\n");
                attroff(COLOR_PAIR(6));
                attron(COLOR_PAIR(4));
                printw("Press 1, 2, or 3\n\n");
                attroff(COLOR_PAIR(4));
                placement2 = 10;
            }
        }
    }

    return mode;
}

int select_random_words(char all_word_list[][WORD_MAX_LEN], int count, char random_word_list[][WORD_MAX_LEN], int rand_word_count, int min_length, int max_length)
{
    srand(time(NULL));
    int selected_count = 0;
    while (selected_count < rand_word_count)
    {
        int random_index = rand() % count;
        int word_length = strlen(all_word_list[random_index]);
        if (word_length >= min_length && word_length <= max_length)
        {
            strcpy(random_word_list[selected_count], all_word_list[random_index]);
            selected_count++;
        }
    }
}

int display_words(char random_word_list[][WORD_MAX_LEN], int start, int limit, int total)
{

    clear();
    attron(COLOR_PAIR(4));
    printw("Words to Type:\n");
    attroff(COLOR_PAIR(4));
    printw("-------------------------------------------------------------------------------------------------");
    refresh();
    move(2, 0);
    for (int i = start; i < start + limit && i < total; i++)
    {
        if (i == start + limit / 2)
        {
            printw("\n");
        }
        attron(COLOR_PAIR(3));
        attron(A_BOLD);
        printw("%s ", random_word_list[i]);
        attroff(COLOR_PAIR(3));
        attroff(A_BOLD);
    }
    printw("\n-------------------------------------------------------------------------------------------------\n");
    printw("\n");
    refresh();
}

int start_typing_test(char random_word_list[][WORD_MAX_LEN], int rand_word_count)
{
    char input_word_list[rand_word_count][WORD_MAX_LEN];
    char wordBuffer[WORD_MAX_LEN];
    int wordcount = 0, char_index = 0, correct_letter = 0, wrong_letter = 0, character_count = 0;
    time_t start_time = time(NULL);
    int display_index = WORD_DISPLAY_LIMIT;
    int input;
    double time_left = TIME_LIMIT - difftime(time(NULL), start_time);

    display_words(random_word_list, 0, WORD_DISPLAY_LIMIT, rand_word_count);
    refresh();
    move(5, 0);
    int total_keystrokes = 0;
    while (wordcount < rand_word_count)
    {
        time_left = TIME_LIMIT - difftime(time(NULL), start_time);
        if (difftime(time(NULL), start_time) >= TIME_LIMIT)
            break;
        input = getch();
        getyx(stdscr, current_y, current_x);

        attron(COLOR_PAIR(5) | A_BOLD);
        mvprintw(0, COLS - 30, "Time: %3.0fs ", time_left);
        attroff(COLOR_PAIR(5) | A_BOLD);

        move(current_y, current_x);
        refresh();              if (input == 27)
            break;

        char *target = random_word_list[wordcount];
        int target_len = strlen(target);

        if (input == ' ' || input == '\n')
        {
            if (char_index > 0)
            {
                wordBuffer[char_index] = '\0';
                strcpy(input_word_list[wordcount], wordBuffer);
                if (char_index < target_len)
                    wrong_letter += (target_len - char_index);
                wordcount++;
                char_index = 0;
                printw(" ");

                if (wordcount % LINE_WORD_COUNT == 0)
                {
                    getyx(stdscr, current_y, current_x);
                    move(current_y + 1, 0);
                }

                if (wordcount % WORD_DISPLAY_LIMIT == 0 && display_index < rand_word_count)
                {
                    display_words(random_word_list, wordcount, WORD_DISPLAY_LIMIT, rand_word_count);
                    display_index += WORD_DISPLAY_LIMIT;
                }
            }
        }
        else if (input == KEY_BACKSPACE || input == 127 || input == 8)
        {
            character_count++;
            if (char_index > 0)
            {
                char_index--;
                int current_y, current_x;
                getyx(stdscr, current_y, current_x);

                if (current_x == 0 && current_y > 5)
                {
                    move(current_y - 1, COLS - 1);
                }
                else
                {
                    move(current_y, current_x - 1);
                }

                delch();
                refresh();
                if (wordBuffer[char_index] != target[char_index] && wrong_letter > 0)
                    wrong_letter--;
            }
        }
        else if (((input >= 'A' && input <= 'Z') || (input >= 'a' && input <= 'z')))
        {
            character_count++;
            if (char_index < target_len)
            {
                if (input == target[char_index])
                {
                    attron(COLOR_PAIR(1));
                    correct_letter++;
                }
                else
                {
                    attron(COLOR_PAIR(2));
                    wrong_letter++;
                }
            }
            else
            {
                attron(COLOR_PAIR(2));
            }
            addch(input);
            attroff(COLOR_PAIR(1) | COLOR_PAIR(2));
            wordBuffer[char_index++] = input;
        }
        else
        {
            continue;
        }


        refresh();
    }

    float accuracy = (correct_letter + wrong_letter) ? ((float)correct_letter / character_count) * 100 : 0;
    double time_used = difftime(time(NULL), start_time);
    float cps = time_used > 0.1 ? (character_count / time_used) : 0;
    float wpm = time_used > 0.1 ? (wordcount / (time_used / 60.0)) : 0;
    
    clear();
    int stat_line = 1;
    if (time_used >= TIME_LIMIT)
    {
        attron(COLOR_PAIR(4));
        mvprintw(stat_line++, 0, "Time's up!\n\n");
        attroff(COLOR_PAIR(4));
    }
    else
    {
        attron(COLOR_PAIR(4));
        mvprintw(stat_line++, 0, "Thanks for playing!!!\n\n");
        attroff(COLOR_PAIR(4));
    }

    stat_line++;
    mvprintw(stat_line++, 0, "Accuracy: ");
    attron(COLOR_PAIR(7));
    printw("%.2f%%", accuracy);
    attroff(COLOR_PAIR(7));

    mvprintw(stat_line++, 0, "Time: ");
    attron(COLOR_PAIR(7));
    printw("%.1fs", time_used >= TIME_LIMIT ? TIME_LIMIT : time_used);
    attroff(COLOR_PAIR(7));
    printw(" | Words: ");
    attron(COLOR_PAIR(7));
    printw("%d", wordcount);
    attroff(COLOR_PAIR(7));
    printw(" | WPM: ");
    attron(COLOR_PAIR(7));
    printw("%.1f", wpm);
    attroff(COLOR_PAIR(7));
    printw(" | CPS: ");
    attron(COLOR_PAIR(7));
    printw("%.1f", cps);
    attroff(COLOR_PAIR(7));

    mvprintw(stat_line++, 0, "Correct characters: ");
    attron(COLOR_PAIR(1));
    printw("%d", correct_letter);
    attroff(COLOR_PAIR(1));
    printw(" | Incorrect characters: ");
    attron(COLOR_PAIR(2));
    printw("%d", wrong_letter);
    attroff(COLOR_PAIR(2));
    printw(" | Total keystrokes: ");
    attron(COLOR_PAIR(7));
    printw("%d", character_count);
    attroff(COLOR_PAIR(7));

    stat_line += 2;
    int continue_line = stat_line;
    attron(COLOR_PAIR(4));
    mvprintw(continue_line, 0, "Press Enter to continue\n\n");
    attroff(COLOR_PAIR(4));
    
    int placement_continue = continue_line + 1;
    int final_input;
    while(1)
    {
        final_input = getch();
        if (final_input == '\n')
            break;
        else
        {
            mvprintw(placement_continue++, 0, "Invalid Input. Please press Enter to continue.");
            if (placement_continue >= 30)
            {
                clear();
                // Redraw stats
                stat_line = 1;
                if (time_used >= TIME_LIMIT) {
                    attron(COLOR_PAIR(4));
                    mvprintw(stat_line++, 0, "Time's up!\n\n");
                    attroff(COLOR_PAIR(4));
                } else {
                    attron(COLOR_PAIR(4));
                    mvprintw(stat_line++, 0, "Thanks for playing!!!\n\n");
                    attroff(COLOR_PAIR(4));
                }
                stat_line++;
                mvprintw(stat_line++, 0, "Accuracy: ");
                attron(COLOR_PAIR(7));
                printw("%.2f%%", accuracy);
                attroff(COLOR_PAIR(7));
                mvprintw(stat_line++, 0, "Time: ");
                attron(COLOR_PAIR(7));
                printw("%.1fs", time_used >= TIME_LIMIT ? TIME_LIMIT : time_used);
                attroff(COLOR_PAIR(7));
                printw(" | Words: %d | WPM: %.1f | CPS: %.1f", wordcount, wpm, cps);
                mvprintw(stat_line++, 0, "Correct characters: ");
                attron(COLOR_PAIR(1));
                printw("%d", correct_letter);
                attroff(COLOR_PAIR(1));
                printw(" | Incorrect characters: %d | Total keystrokes: %d", wrong_letter, character_count);
                // Redraw prompt
                stat_line += 2;
                continue_line = stat_line;
                attron(COLOR_PAIR(4));
                mvprintw(continue_line, 0, "Press Enter to continue\n\n");
                attroff(COLOR_PAIR(4));
                placement_continue = continue_line + 1;
            }
        }
    }
    return 0;
}