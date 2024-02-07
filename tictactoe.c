#define _CRT_SECURE_NO_WARNINGS
#define STR_LEN 20
#include <windows.h>
#include <stdio.h>
#include <time.h>
void move_cursor(int, int);
void print_board();
void computer_mod();
int check_win();
void get_input();
void repaste(int, int);
void dumber(int);
void dumb(int);
void smart(int);
int count(int, int, int, int);
void comp_paste(int, int, int);
void hum_paste(int, int);
int f_comp, s_comp;
int command;
int level;
int fill_board[3][3];
int heuristics[3][3];
int ai_level = 1;
char ai_names[3][STR_LEN] = { "dumber", "dumb", "smart" };

int main() {
    system("cls");


    get_input();
    move_cursor(45, 26);
    printf(" ");


    return 0;
}
void repaste(int r, int c) {
    if ((r + c) % 2 == 0) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_GREEN);
    }
    else
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY);
}
void move_cursor(int x, int y) {
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(console, &csbi);
    COORD coord = { x, y };
    SetConsoleCursorPosition(console, coord);
}
void print_board() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            fill_board[i][j] = -1;
            heuristics[i][j] = 0;
        }
    }
    move_cursor(60, 4);
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    if (command == 3) {
        printf("      ###   Tic-Tac-Toe   ###      ");
        move_cursor(64, 6);
        printf("AI level %d(X), AI level %d(O)", f_comp, s_comp);
    }
    else {
        printf("      ###   Tic-Tac-Toe   ###      ");
        move_cursor(57, 6);
        printf("Player 1 : Human(X), Player 2 : Computer(O)");
    }

    move_cursor(65, 8);
    char board[18][27];

    for (int i = 0; i < 15; i++) {
        for (int j = 0; j < 27; j++) {
            board[i][j] = ' ';
        }
    }
    for (int i = 0; i < 15; i++) {
        for (int j = 0; j < 27; j++) {
            if ((i / 5 + j / 9) % 2 == 0) {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_GREEN);
            }
            else {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY);
            }
            printf("%c", board[i][j]);
        }
        move_cursor(65, 9 + i);
    }
    SetConsoleTextAttribute(console, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE);
}
int check_win() {
    // 직선 부분
    for (int r = 0; r < 3; r++) {
        if (fill_board[r][0] == fill_board[r][1] && fill_board[r][1] == fill_board[r][2]) {
            if (fill_board[r][0] == 1) {
                move_cursor(45, 26);
                return 1;
            }
            else if (fill_board[r][0] == 2) {
                move_cursor(45, 26);
                return 2;
            }
        }
        if (fill_board[0][r] == fill_board[1][r] && fill_board[1][r] == fill_board[2][r]) {
            if (fill_board[0][r] == 1) {
                move_cursor(45, 26);
                return 1;
            }
            else if (fill_board[0][r] == 2) {
                move_cursor(45, 26);
                return 2;
            }
        }
    }
    // 대각선 부분
    if (fill_board[0][0] == fill_board[1][1] && fill_board[1][1] == fill_board[2][2]) {
        if (fill_board[0][0] == 1) {
            move_cursor(45, 26);
            printf("You won!!");
            return 1;
        }
        if (fill_board[0][0] == 2) {
            move_cursor(45, 26);
            printf("Computer won!!");
            return 2;
        }
    }
    if (fill_board[0][2] == fill_board[1][1] && fill_board[1][1] == fill_board[2][0] && fill_board[0][2] == 1) {
        if (fill_board[0][2] == 1) {
            move_cursor(45, 26);
            printf("You won!!");
            return 1;
        }
        if (fill_board[0][2] == 2) {
            move_cursor(45, 26);
            printf("Computer won!!");
            return 2;
        }
    }
}
void get_input() {
    while (1) {
        HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
        int cnt = 0;
        int layer = 0;
        int turn = 0;
        int user_R, user_C;

        move_cursor(10, 10);
        printf("### Tic-Tac-Toe ###");
        move_cursor(10, 11);
        printf("1 : Play first(You are X)");
        move_cursor(10, 12);
        printf("2 : Play second(You are X)");
        move_cursor(10, 13);
        printf("3 : Computer vs Computer");
        move_cursor(10, 14);
        printf("4 : Select AI (current : %s)", ai_names[ai_level - 1]);
        move_cursor(10, 15);
        printf("0 : Exit");
        move_cursor(10, 16);
        printf("Enter command : ");
        scanf_s("%d", &command);
        switch (command) {
        case 1:
            turn = 1;
            break;
        case 2:
            turn = 2;
            break;
        case 3:
            computer_mod();
            break;
        case 4:
            system("cls");
            move_cursor(10, 10);
            printf("Select the level(1:dumber, 2:dumb, 3:smart)");
            scanf_s("%d", &ai_level);
            break;
        case 0:
            exit(0);

        }
        system("cls");
        if (command < 3) {
            print_board();
            while (1) {
                if (cnt == 9) {
                    move_cursor(45, 26);
                    printf(" IIt's a draw...good game.");
                    Sleep(1000);
                    break;
                }
                if (check_win() == 1) {
                    move_cursor(45, 26);
                    printf("You win!!!");
                    Sleep(1000);
                    break;
                }
                if (check_win() == 2) {
                    move_cursor(45, 26);
                    printf("Computer win!!!");
                    Sleep(1000);
                    break;
                }
                int out = 0;

                if ((turn + cnt) % 2 == 1) { // human start, X is equal to 1
                    while (1) {
                        while (getchar() != '\n');
                        move_cursor(0, 4 + layer); printf("Your turn ! :"); scanf_s("%d%d", &user_R, &user_C);
                        if (fill_board[user_R][user_C] == -1) {
                            hum_paste(user_R, user_C);
                            out = 1;
                        }
                        if (out) break;
                        move_cursor(0, 4 + ++layer);
                        printf("Choose another square");
                        layer++;
                    }
                }
                else { // computer start, O is equal to 2
                    if (ai_level == 1) {
                        dumber(2);
                    }
                    else if (ai_level == 2) {
                        dumb(2);
                    }
                    else {
                        smart(2);
                    }
                    layer++;
                }
                cnt++;
                SetConsoleTextAttribute(console, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE);
            }
            system("cls");
        }
    }
}
void computer_mod() {
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    int cnt = 0;
    int turn = 1;
    system("cls");
    move_cursor(0, 10);
    printf("Select first computer, second computer's intelligence level. First computer will go first.");
    scanf_s("%d%d", &f_comp, &s_comp);
    system("cls");
    print_board();
    while (1) {
        if (cnt == 9) {
            move_cursor(45, 26);
            printf(" IIt's a draw...good game by both computers^^.");
            Sleep(1000);
            break;
        }
        if (check_win() == 1) {
            move_cursor(45, 26);
            printf("First computer win!!!");
            Sleep(1000);
            break;
        }
        if (check_win() == 2) {
            move_cursor(45, 26);
            printf("Second computer win!!!");
            Sleep(1000);
            break;
        }

        if ((turn + cnt) % 2 == 1) {
            Sleep(2000);
            if (f_comp == 1) {
                dumber(1);
            }
            else if (f_comp == 2) {
                dumb(1);
            }
            else {
                smart(1);
            }
        }
        else {
            Sleep(2000);
            if (s_comp == 1) {
                dumber(2);
            }
            else if (s_comp == 2) {
                dumb(2);
            }
            else {
                smart(2);
            }
        }
        cnt++;
        SetConsoleTextAttribute(console, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE);
    }
    system("cls");
}
void dumber(int flag) {
    srand(time(NULL));
    while (1) {
        int Row = rand() % 3;
        int Col = rand() % 3;
        if (fill_board[Row][Col] == -1) {
            comp_paste(Row, Col, flag);
            break;
        }
    }
}
void dumb(int flag) {
    // 가로, 세로줄
    int comp, human;
    for (int i = 0; i < 3; i++) {
        comp = count(fill_board[0][i], fill_board[1][i], fill_board[2][i], 2);
        human = count(fill_board[0][i], fill_board[1][i], fill_board[2][i], 1);
        if (comp == 2 || human == 2) {
            for (int j = 0; j < 3; j++) {
                if (fill_board[j][i] == -1) {
                    comp_paste(j, i, flag);
                    return;
                }
            }
        }
        comp = count(fill_board[i][0], fill_board[i][1], fill_board[i][2], 2);
        human = count(fill_board[i][0], fill_board[i][1], fill_board[i][2], 1);
        if (comp == 2 || human == 2) {
            for (int j = 0; j < 3; j++) {
                if (fill_board[i][j] == -1) {
                    comp_paste(i, j, flag);
                    return;
                }
            }
        }

    }
    // 대각
    comp = count(fill_board[0][0], fill_board[1][1], fill_board[2][2], 2);
    human = count(fill_board[0][0], fill_board[1][1], fill_board[2][2], 1);
    if (comp == 2 || human == 2) {
        for (int j = 0; j < 3; j++) {
            if (fill_board[j][j] == -1) {
                comp_paste(j, j, flag);
                return;
            }
        }
    }
    comp = count(fill_board[2][0], fill_board[1][1], fill_board[0][2], 2);
    human = count(fill_board[2][0], fill_board[1][1], fill_board[0][2], 1);
    if (comp == 2 || human == 2) {
        for (int j = 0; j < 3; j++) {
            if (fill_board[2 - j][j] == -1) {
                comp_paste(2 - j, j, flag);
                return;
            }
        }
    }
    if (fill_board[1][1] == -1) {
        comp_paste(1, 1, flag);
        return;
    }
    int repo2468[4][2] = { {0,1},{1,0}, {1,2}, {2,1} };
    while (1) {
        srand(time(NULL));
        int idx = rand() % 4;
        if (fill_board[repo2468[idx][0]][repo2468[idx][1]] == -1) {
            comp_paste(repo2468[idx][0], repo2468[idx][1], flag);
            return;
        }
    }
    int repo1379[4][2] = { {0,0},{0,2}, {2,0}, {2, 2} };
    while (1) {
        srand(time(NULL));
        int idx = rand() % 4;
        if (fill_board[repo1379[idx][0]][repo1379[idx][1]] == -1) {
            comp_paste(repo1379[idx][0], repo1379[idx][1], flag);
            return;
        }
    }
}
void comp_paste(int r, int c, int flag) {
    fill_board[r][c] = flag;
    move_cursor(60 + (c + 1) * 9, 5 + 5 * (r + 1));
    repaste(r, c);
    if (flag == 2)
        printf("O");
    else
        printf("X");
}
void hum_paste(int r, int c) {
    fill_board[r][c] = 1;
    move_cursor(60 + (c + 1) * 9, 5 + 5 * (r + 1));
    repaste(r, c);
    printf("X");
}
int count(int a, int b, int c, int target) {
    int arr[3] = { a,b,c };
    int cnt_2 = 0;
    int cnt_1 = 0;

    if (target == 2) {
        for (size_t i = 0; i < 3; i++)
        {
            if (arr[i] == 2)
                cnt_2++;
            if (arr[i] == 1)
                cnt_1++;
        }
        if (cnt_1) return 0;
        return cnt_2;
    }
    if (target == 1) {
        for (size_t i = 0; i < 3; i++)
        {
            if (arr[i] == 1)
                cnt_1++;
            if (arr[i] == 2)
                cnt_2++;
        }
        if (cnt_2) return 0;
        return cnt_1;
    }
}
void smart(int flag) {
    int comp, human;
    if (fill_board[1][1] == -1) {
        comp_paste(1, 1, flag);
        return;
    }
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            heuristics[i][j] = 0;
        }
    }
    for (int i = 0; i < 3; i++) {
        comp = count(fill_board[0][i], fill_board[1][i], fill_board[2][i], 2);
        human = count(fill_board[0][i], fill_board[1][i], fill_board[2][i], 1);
        if (comp >= 1 || human >= 1) {
            for (int j = 0; j < 3; j++) {
                if (fill_board[j][i] == -1 && comp == 2) {
                    heuristics[j][i] += 1000;
                }
                else if (fill_board[j][i] == -1 && comp == 1) {
                    heuristics[j][i] += 15;
                }
                if (fill_board[j][i] == -1 && human == 2) {
                    heuristics[j][i] += 100;
                }
                else if (fill_board[j][i] == -1 && human == 1) {
                    heuristics[j][i] += 10;
                }
            }
        }
        comp = count(fill_board[i][0], fill_board[i][1], fill_board[i][2], 2);
        human = count(fill_board[i][0], fill_board[i][1], fill_board[i][2], 1);
        if (comp >= 1 || human >= 1) {
            for (int j = 0; j < 3; j++) {
                if (fill_board[i][j] == -1 && comp == 2) {
                    heuristics[i][j] += 1000;
                }
                else if (fill_board[i][j] == -1 && comp == 1) {
                    heuristics[i][j] += 15;
                }
                if (fill_board[i][j] == -1 && human == 2) {
                    heuristics[i][j] += 100;
                }
                else if (fill_board[i][j] == -1 && human == 1) {
                    heuristics[i][j] += 10;
                }
            }
        }

    }

    comp = count(fill_board[2][0], fill_board[1][1], fill_board[0][2], 2);
    human = count(fill_board[2][0], fill_board[1][1], fill_board[0][2], 1);
    if (comp >= 1 || human >= 1) {
        for (int i = 0; i < 3; i++) {
            if (fill_board[2 - i][i] == -1 && comp == 2) {
                heuristics[2 - i][i] += 1000;
            }
            else if (fill_board[2 - i][i] == -1 && comp == 1) {
                heuristics[2 - i][i] += 15;
            }
            if (fill_board[2 - i][i] == -1 && human == 2) {
                heuristics[2 - i][i] += 100;
            }
            else if (fill_board[2 - i][i] == -1 && human == 1) {
                heuristics[2 - i][i] += 10;
            }
        }
    }
    comp = count(fill_board[0][0], fill_board[1][1], fill_board[2][2], 2);
    human = count(fill_board[0][0], fill_board[1][1], fill_board[2][2], 1);
    if (comp >= 1 || human >= 1) {
        for (int i = 0; i < 3; i++) {
            if (fill_board[i][i] == -1 && comp == 2) {
                heuristics[i][i] += 1000;
            }
            else if (fill_board[i][i] == -1 && comp == 1) {
                heuristics[i][i] += 15;
            }
            if (fill_board[i][i] == -1 && human == 2) {
                heuristics[i][i] += 100;
            }
            else if (fill_board[i][i] == -1 && human == 1) {
                heuristics[i][i] += 10;
            }
        }
    }
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (heuristics[i][j] == 0)
                heuristics[i][j]++;
        }
    }
    int max = -1;
    int max_info[2] = { 0,0 };
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (max < heuristics[i][j]) {
                max = heuristics[i][j];
                max_info[0] = i, max_info[1] = j;
            }
        }
    }
    comp_paste(max_info[0], max_info[1], flag);

}