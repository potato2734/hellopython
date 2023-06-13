
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<windows.h> //GotoXY(int x,int y)�Լ�,CorsorView(char show)�Լ�,COORD getCursor()�Լ� [Ŀ�� ����] || system("cls")�Լ�, Sleep()�Լ� [�ܼ�â ��ü �����, ����] || SetConsoleTextAttribute()�Լ� [�ܼ� ��� �� ����]
#include<conio.h> //_kbhit()�Լ�,_getch()�Լ� [Ű���� ����]
#include<time.h> // rand()�Լ� [���� ����]
#include<stdlib.h> // rand()�Լ� [���� ����]          //c���� ���� ���뿡 �־� ��ǥ���� �Լ�����.
#include <string.h>

#define MAX_LENGTH 50
#define LEFT 75 //�·� �̵�    //Ű���尪��(�ƽ�Ű�ڵ�)
#define RIGHT 77 //��� �̵� 
#define UP 72 //ȸ�� 
#define DOWN 80 //soft drop
#define SPACE 32 //hard drop
#define p 112 //�Ͻ����� 
#define P 80 //�Ͻ�����
#define ESC 27 //�������� 

#define false 0
#define true 1

#define SBLOCK -3 // �׸��� ���. ���� '��'
#define ACTIVE_BLOCK -2 // �����ǹ迭�� ����� ����� ���µ� 
#define CEILLING -1     // ����� �̵��� �� �ִ� ������ 0 �Ǵ� ���� ������ ǥ�� 
#define EMPTY 0         // ����� �̵��� �� ���� ������ ����� ǥ�� 
#define WALL 1
#define INACTIVE_BLOCK 2 // �̵��� �Ϸ�� ��ϰ� 

//#define MAIN_X 11 //������ ����ũ��
//#define MAIN_Y 23 //������ ����ũ�� 
#define MAIN_X_ADJ 3 //������ ��ġ���� 
#define MAIN_Y_ADJ 1 //������ ��ġ���� 

#define STATUS_X_ADJ MAIN_X_ADJ+MAIN_X+1 //��������ǥ�� ��ġ���� 

typedef struct personscore {
    char name[MAX_LENGTH];
    int score;
    char time[MAX_LENGTH];
} pscore;


char fname[] = "score.dat";
char fstore[] = "data.txt";
char player_name[MAX_LENGTH];
char curr_time[MAX_LENGTH];
time_t current_time;
int change_flag = 0;

int MAIN_X; //�� �Ҵ��� ���� �������� �ϴ� �۷ι��� ����. �׷��� ���߿� argv�� �ް� �����ؼ� �ڵ� ��𿡼��� ���� ����
int MAIN_Y;

int STATUS_Y_GOAL; //GOAL ����ǥ����ġY ��ǥ ���� 
int STATUS_Y_LEVEL; //LEVEL ����ǥ����ġY ��ǥ ����
int STATUS_Y_SCORE; //SCORE ����ǥ����ġY ��ǥ ����

int blocks[7][4][4][4] = {//[��� ����][ȸ������(4ȸ)][��][��]
{{0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0},{0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0},
 {0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0},{0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0}},//�׸� 4��
{{0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0},{0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0},
 {0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0},{0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0}},//¦��� 4��
{{0,0,0,0,1,1,0,0,0,1,1,0,0,0,0,0},{0,0,0,0,0,0,1,0,0,1,1,0,0,1,0,0},
 {0,0,0,0,1,1,0,0,0,1,1,0,0,0,0,0},{0,0,0,0,0,0,1,0,0,1,1,0,0,1,0,0}},//�� 4��
{{0,0,0,0,0,1,1,0,1,1,0,0,0,0,0,0},{0,0,0,0,1,0,0,0,1,1,0,0,0,1,0,0},
 {0,0,0,0,0,1,1,0,1,1,0,0,0,0,0,0},{0,0,0,0,1,0,0,0,1,1,0,0,0,1,0,0}},//�� �� 4��
{{0,0,0,0,0,0,1,0,1,1,1,0,0,0,0,0},{0,0,0,0,1,1,0,0,0,1,0,0,0,1,0,0},
 {0,0,0,0,0,0,0,0,1,1,1,0,1,0,0,0},{0,0,0,0,0,1,0,0,0,1,0,0,0,1,1,0}},//�� �� 4��
{{0,0,0,0,1,0,0,0,1,1,1,0,0,0,0,0},{0,0,0,0,0,1,0,0,0,1,0,0,1,1,0,0},
 {0,0,0,0,0,0,0,0,1,1,1,0,0,0,1,0},{0,0,0,0,0,1,1,0,0,1,0,0,0,1,0,0}},//�� �� �� 4��
{{0,0,0,0,0,1,0,0,1,1,1,0,0,0,0,0},{0,0,0,0,0,1,0,0,0,1,1,0,0,1,0,0},
 {0,0,0,0,0,0,0,0,1,1,1,0,0,1,0,0},{0,0,0,0,0,1,0,0,1,1,0,0,0,1,0,0}}//�� 4��
}; //��ϸ�� ���� 4*4������ ����� ǥ�� blcoks[b_type][b_rotation][i][j]�� ��� 

int b_type; //��� ������ ���� [!][][][] // �������� ����
int b_rotation; //��� ȸ���� ���� [][!][][] // ��.�� Ű�� ���� ���Ұ�
int b_type_next; //���� ��ϰ� ���� [!][][][] -> ���� [b_type_next][b_rotation][?][?] -> [b_type][b_rotation][?][?]

int main_org[50][50]; // ����� ū ũ��� �ϴ� ����, ���߿� �� ������ main���� �Է¹ް� ����
int main_cpy[50][50];
//int main_org[MAIN_Y][MAIN_X]; //�������� ������ �����ϴ� �迭 ����Ϳ� ǥ���Ŀ� main_cpy�� ����� 
//int main_cpy[MAIN_Y][MAIN_X]; //�� maincpy�� �������� ����Ϳ� ǥ�õǱ� ���� ������ ������ ���� 
//main�� ��ü�� ��� ����Ϳ� ǥ������ �ʰ�(�̷��� �ϸ� ����Ͱ� �����Ÿ�) 
//main_cpy�� �迭�� ���ؼ� ���� �޶��� ���� ����Ϳ� ��ħ 
int bx, by; //�̵����� ����� �����ǻ��� x,y��ǥ�� ���� 

int key; //Ű����� �Է¹��� Ű���� ���� 

int speed; //��������ӵ� 
int level; //���� level 
int level_goal; //���������� �Ѿ�� ���� ��ǥ���� 
int cnt; //���� �������� ������ �� ���� ���� 
int score; //���� ���� 
int last_score = 0; //�������������� 
int best_score = 0; //�ְ�������� 

int new_block_on = 0; //���ο� ���� �ʿ����� �˸��� flag 
int crush_on = 0; //���� �̵����� ����� �浹�������� �˷��ִ� flag 
int level_up_on = 0; //���������� ����(���� ������ǥ�� �Ϸ�Ǿ�����) �˸��� flag 
int space_key_on = 0; //hard drop�������� �˷��ִ� flag 

void title(void); //���ӽ���ȭ�� 
void reset(void); //������ �ʱ�ȭ 
void reset_main(void); //���� ������(main_org[][]�� �ʱ�ȭ)
void reset_main_cpy(void); //copy ������(main_cpy[][]�� �ʱ�ȭ)
void draw_map(void); //���� ��ü �������̽��� ǥ�� 
void draw_main(void); //�������� �׸� 
void new_block(void); //���ο� ����� �ϳ� ���� 
void check_key(void); //Ű����� Ű�� �Է¹��� 
void drop_block(void); //����� �Ʒ��� ����Ʈ�� 
int check_crush(int bx, int by, int rotation); //bx, by��ġ�� rotationȸ������ ���� ��� �浹 �Ǵ� 
void move_block(int dir); //dir�������� ����� ������ 
void check_line(void); //���� ����á������ �Ǵ��ϰ� ���� 
void check_level_up(void); //������ǥ�� �޼��Ǿ������� �Ǵ��ϰ� levelup��Ŵ 
void check_game_over(void); //���ӿ������� �Ǵ��ϰ� ���ӿ����� ���� 
void pause(void);//������ �Ͻ�������Ŵ 
// ���� �߰��� �Լ��� �Ǵ� ����
void choosing_level(void);// ���� ����
void levelup_color(void);// �������� ������ ���� ����
void shadow_maker(void); // �׸��� �׸��� �Լ�
void shadow_remover(void); // �̵��ϸ� ���� �׸��ڸ� �����ִ� �Լ�
void puang_show(void); // Ǫ���� �׸��� �Լ�
void puang_draw_happy_1(void); // Ǫ���� �����̱�1
void puang_draw_happy_2(void); // Ǫ���� �����̱�2
void puang_draw_sad(void); // ���ӿ��� ���� �� ����
void puang_talk(void); // combo�� �Ͼ �� ���� ����. �� �Լ� ������ �޺��� ���������� �ٲ��� ����
void check_mess_block(void); // ���߱� ���� ��� �迭�� ��ĵ ���� ����ڿ��� �˷���
void typeNickname1();
void typeNickname2();

int combo = 0;
int empty_space = 0;
int empty_space_max = 0;
int fix = 0;
int score_arr[MAX_LENGTH];

char player_name[MAX_LENGTH];

int people_num;
pscore tem[100];

void swap(pscore* a, pscore* b) {
    pscore temp = *a;
    *a = *b;
    *b = temp;
}
int partition1(pscore arr[], int low, int high) {
    int pivot = arr[high].score;
    int i = low - 1;

    for (int j = low; j <= high - 1; j++) {
        if (arr[j].score >= pivot) { // Change comparison to >= for minimum score sorting
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}
void quicksort1(pscore arr[], int low, int high) {
    if (low < high) {
        int pivotIndex = partition1(arr, low, high);
        quicksort1(arr, low, pivotIndex - 1);
        quicksort1(arr, pivotIndex + 1, high);
    }
}
void data_output() {
    char ch[MAX_LENGTH];
    int i = 0;
    int flag;

    FILE* f = fopen(fstore, "r");
    if (f != NULL) {
        while (!feof(f)) {
            fscanf(f, "%s %s %s\n", tem[i].name, ch, tem[i].time);
            tem[i].score = atoi(ch);
            i++;
        }
        fclose(f);
        people_num = i;

        printf("%s\n", "----------------------------------------------------");
        printf("%s%14s%11s%15s\n", "����", "�̸�", "����", "Time");
        printf("%s\n", "----------------------------------------------------");

        if (people_num < 5)
            flag = people_num;
        else
            flag = 5;

        for (int i = 0; i < flag; i++)  // Print the sorted list
            printf("%d: %15s %10d | %18s\n", i + 1, tem[i].name, tem[i].score, tem[i].time);

        printf("----------------------------------------------------");
        printf("\n\n");
        typeNickname2();
    }

    else {
        printf("You are the first player.\n");
        typeNickname1();
    }


}
void typeNickname1() {
    printf("\nTYPE YOUR NICKNAME \n WITHOUT SPACE(less than 10 characters): "); scanf("%s", &player_name);
    player_name[strcspn(player_name, "\n")] = '\0'; // Remove the trailing newline character
}

void typeNickname2() {
    printf("TYPE YOUR NICKNAME: "); scanf("%s", &player_name);
    player_name[strcspn(player_name, "\n")] = '\0';

    for (int i = 0; i < people_num; i++) {
        if (strcmp(tem[i].name, player_name) == 0) {
            printf("\nNickname is already exist,...\n ");
            typeNickname2();
        }

    }
}

//==========================�Լ� 14��, ���� 3��===========================

void gotoxy(int x, int y) { //gotoxy�Լ� 
    COORD pos = { 2 * x,y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}// �ܼ�â�� ���ϴ� ��ǥ ���� GotoXY�� �Ű������� x,y���� ������ �ش� ��ǥ�� �̵��� / COORD(GotoXY�Լ� �ȿ��� X,Y���� ����)(���� pos�� COORD����ü �ȿ� �ִ� ���� X,Y�� �����ڸ� ���� ��� ����. ���� ��� pos.X=12; pos.Y=2;)
//�ᱹ �ܼ�â���� ���� ���ϴ� ���� ��ǥ���� x,y�� �ѱ�� pos.X pos.Y�� ���� ���� -> SetConsoleCursorPosition�Լ�(���� �� �ܼ� ȭ�� ���ۿ��� Ŀ�� ��ġ�� �������ִ� �Լ�)  �ܼ� ȭ�� ���ۿ� ���� ǥ�� ��� �ڵ�GetStdHandle(STD_OUTPUT_HANDLE) ��, x,y�� ��ǥ ������ ����ִ� Pos�� �Ű������� �޾Ƽ� �ش� Pos�� x, y ��ǥ������ Ŀ����ġ�� �������ش�.
void puang_talk(void) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    WORD saved_attributes;

    // Get the current console color attributes
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    saved_attributes = consoleInfo.wAttributes;
    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);
    gotoxy(50, 8); printf(" combo!! ");
    Sleep(500);
    gotoxy(50, 8); printf("            ");
    SetConsoleTextAttribute(hConsole, saved_attributes);
}
void check_mess_block(void)
{
    int scanx = 1;
    empty_space_max = 0;

    while (scanx < MAIN_X - 1)// ���� �������� ��� �˻�. x�����: (1+MAIN_X_ADJ ~ MAIN_X+2+MAIN_X_ADJ)[���� -> ������], y�����: (MAIN_Y-1 ~ MAIN_Y_ADJ+4)[�Ʒ� -> ��]
    {
        int scany = MAIN_Y;
        empty_space = 0; // ��� �ٸ� ���� �˻��ϹǷ� �ʱ�ȭ
        while (scany >= MAIN_Y_ADJ + 4)
        {
            if ((main_cpy[scany - 1][scanx] == 2 && main_cpy[scany - 2][scanx] == 0) || (main_cpy[scany - 1][scanx] == 0 && main_cpy[scany - 2][scanx] == 2)) // incactive block, empty �����ؼ� ������ ������ main_cpy ���� �ٸ��� ����
            {
                empty_space++;
            }
            scany--;
            if (empty_space >= empty_space_max) // empty_space_max ����
            {
                empty_space_max = empty_space;
            }
        }
        if (empty_space_max >= 2) // ��� ���̵� ��ĭ()�� 1�� �̻� ������ ��
        {
            gotoxy(2, MAIN_Y + 3); printf("You are in trouble!!!!");
        }
        else if (empty_space_max < 2)
            gotoxy(2, MAIN_Y + 3); printf("                       "); // empty_space_max ���ŵǸ� ���� ���ڿ�(You are in trouble!!!!) ����
        //gotoxy(3+scanx, MAIN_Y+5);  printf("%d",empty_space); Ȯ�� ���� �ڵ�
        scanx++;
    }
}


void puang_draw_happy_1(void)
{
    gotoxy(MAIN_X + 19, 1); printf("              ||         ||     ");
    gotoxy(MAIN_X + 19, 2); printf("            ||             ||     ");
    gotoxy(MAIN_X + 19, 3); printf("        ��     ||         ||       ");
    gotoxy(MAIN_X + 19, 4); printf("   ��       ^|''''''''''''''''|^   ");
    gotoxy(MAIN_X + 19, 5); printf("     ��    |                   |   ");
    gotoxy(MAIN_X + 19, 6); printf("         |      ��       ��      |  ");
    gotoxy(MAIN_X + 19, 7); printf("        |  ~~///         ///~~  | ");
    gotoxy(MAIN_X + 19, 8); printf("         |          ?          |  ");
    gotoxy(MAIN_X + 19, 9); printf("          |                   |   ");
    gotoxy(MAIN_X + 19, 10); printf("          |_________________|    ");
    gotoxy(MAIN_X + 19, 11); printf("                                 ");// ���� ������ ���ļ� ������

}
void puang_draw_happy_2(void)
{
    gotoxy(MAIN_X + 19, 1); printf("                                 ");// ���� ������ ���ļ� ������
    gotoxy(MAIN_X + 19, 2); printf("              ||         ||     ");
    gotoxy(MAIN_X + 19, 3); printf("            ||             ||   ");
    gotoxy(MAIN_X + 19, 4); printf("        ��     ||         ||     ");
    gotoxy(MAIN_X + 19, 5); printf("   ��       ^|''''''''''''''''|^   ");
    gotoxy(MAIN_X + 19, 6); printf("     ��    |                   |   ");
    gotoxy(MAIN_X + 19, 7); printf("         |      ��       ��      |  ");
    gotoxy(MAIN_X + 19, 8); printf("        |  ~~///         ///~~  | ");
    gotoxy(MAIN_X + 19, 9); printf("         |          ?          |  ");
    gotoxy(MAIN_X + 19, 10); printf("          |                   |  ");
    gotoxy(MAIN_X + 19, 11); printf("           |_________________|   ");
}
void puang_draw_sad(void)
{
    gotoxy(MAIN_X + 19, 1); printf("              ||         ||     ");
    gotoxy(MAIN_X + 19, 2); printf("            ||             ||   ");
    gotoxy(MAIN_X + 19, 3); printf("              ||         ||     ");
    gotoxy(MAIN_X + 19, 4); printf("          ^ |''''''''''''''''|^   ");
    gotoxy(MAIN_X + 19, 5); printf("          |                   |  ");
    gotoxy(MAIN_X + 19, 6); printf("         |      ��     ��       | ");
    gotoxy(MAIN_X + 19, 7); printf("        |  ~~///         ///~~  |");
    gotoxy(MAIN_X + 19, 8); printf("         |          ?          | ");
    gotoxy(MAIN_X + 19, 9); printf("          |                   |  ");
    gotoxy(MAIN_X + 19, 10); printf("           |_________________|   ");
    gotoxy(MAIN_X + 19, 11); printf("                                 ");// ���� ������ ���ļ� ������
}
void puang_show(void)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    WORD saved_attributes;
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    saved_attributes = consoleInfo.wAttributes;
    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE);
    switch (level) {
    case 100:
        puang_draw_sad();
        break;
    default:
        puang_draw_happy_1();
        Sleep(50);
        puang_draw_happy_2();
        Sleep(50);
        break;

    }


    SetConsoleTextAttribute(hConsole, saved_attributes);


}

void shadow_maker(void) {
    int shy = 0; // shadow_y�� ����. õ�忡������ �׸��ڸ� ��� ���̿������� �����ؾ� �Ǵ��� �˷��ִ� ô��
    while (1) {
        if (check_crush(bx, shy, b_rotation) == true)// ����==shy �� �� ����� ���𰡿� ���� ���°� �ƴϴ�-> ���� �� ĭ �߰�
        {
            shy++;
        }
        if (check_crush(bx, shy, b_rotation) == false) // �Ʒ��� ���� �ִٸ�...
        {
            for (int y = 0; y < 4; y++)
            {
                for (int x = 0; x < 4; x++)
                {// �ٷ� �Ʒ��� �ִ� ����� ��� �ְų�(EMPTY) ���� ����� ��(INACTIVE BLOCK) �׸��� ���(SBLOCK) ����
                    if (blocks[b_type][b_rotation][y][x] == 1 && (main_cpy[shy - 1 + y][bx + x] == EMPTY || main_cpy[shy - 1 + y][bx + x] == INACTIVE_BLOCK))
                    {
                        main_org[shy - 1 + y][bx + x] = SBLOCK;
                    }
                }
            }
            return; // �Լ� Ż��
        }
    }


}
void shadow_remover(void) {
    for (int y = 0; y < MAIN_Y; y++)
    {
        for (int x = 0; x < MAIN_X; x++)
        {
            if ((main_org[y][x] == SBLOCK) && _kbhit())// �� �� �����ϴ� ��� SBLOCK ����
            {
                main_org[y][x] = EMPTY;
            }

            else
                continue;

        }
    }
}

typedef enum { NOCURSOR, SOLIDCURSOR, NORMALCURSOR } CURSOR_TYPE; //Ŀ������� �Լ��� ���Ǵ� ������ 
void setcursortype(CURSOR_TYPE c) { //Ŀ������� �Լ� 
    CONSOLE_CURSOR_INFO CurInfo;

    switch (c) {
    case NOCURSOR:
        CurInfo.dwSize = 1;
        CurInfo.bVisible = FALSE;
        break;
    case SOLIDCURSOR:
        CurInfo.dwSize = 100;
        CurInfo.bVisible = TRUE;
        break;
    case NORMALCURSOR:
        CurInfo.dwSize = 20;
        CurInfo.bVisible = TRUE;
        break;
    }
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &CurInfo);
}

void levelup_color(void) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    WORD saved_attributes;
    switch (level) { //�������� �ӵ��� ������ ��������. 
    case 2:
        SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);// 2�ܰ�: �ʷϻ�, 1�ܰ�� ���(speed=100)
        speed = 80;
        break;
    case 3:
        SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_GREEN); //3�ܰ�: ���� �Ķ���
        speed = 60;
        break;
    case 4:
        SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_INTENSITY); //4�ܰ�: �� ���� �Ķ���
        speed = 40;
        break;
    case 5:
        SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE); //5�ܰ�: �Ķ���
        speed = 30;
        break;
    case 6:
        SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_RED);//6�ܰ�: �����
        speed = 25;
        break;
    case 7:
        SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_RED);//7�ܰ�: �����
        speed = 20;
        break;
    case 8:
        SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY);//8�ܰ�: ȸ��
        speed = 15;
        break;
    case 9:
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED);//9�ܰ�: ������
        speed = 10;
        break;
    case 10:
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED);// 10�ܰ�: ������
        speed = 5;
        break;
    }
}

int main(int argc, char* argv[]) {
    printf("argc: %d\n", argc);
    for (int i = 0; i < argc; i++) {
        printf("argv[%d]: %s\n", i, argv[i]);
    }

    if (argc == 1) { // main �Լ��� �߰����� �μ��� ���޵��� �ʾ��� ��
        MAIN_X = 11; // default value
        MAIN_Y = 23; // default value
    }
    else { // main �Լ��� �μ��� ���޵Ǿ��� �� (ex. *****.exe 12, 15)
        MAIN_X = atoi(argv[1]); // �Ű������� �� �Ҵ�
        MAIN_Y = atoi(argv[2]);
    }


    if (MAIN_X <= 100 && MAIN_Y <= 100) {// ����� �ʿ��� �迭���� �� �Ҵ�
        for (int ii = MAIN_X; ii >= 0; ii--) {
            for (int jj = MAIN_Y; jj >= 0; jj--) {
                main_org[jj][ii] = 0; //EMPTY ������� �ʱ�ȭ
            }
        }
    }
    if (MAIN_X <= 100 && MAIN_Y <= 100) {// ����� �ʿ��� �迭���� �� �Ҵ�
        for (int ii = MAIN_X; ii >= 0; ii--) {
            for (int jj = MAIN_Y; jj >= 0; jj--) {
                main_cpy[jj][ii] = 0; // EMPTY ������� �ʱ�ȭ
            }
        }
    }

    Sleep(100);
    srand((unsigned)time(NULL)); //����ǥ���� 
    setcursortype(NOCURSOR); //Ŀ�� ���� 

    system("cls");
    title(); //����Ÿ��Ʋ ȣ�� 
    system("cls");
    data_output();
    //typeNickname();
    //gotoxy(0, 15); printf("TYPE YOUR NICKNAME WITHOUT SPACE(less than 10 characters): "); scanf("%s", &player_name);
    //player_name[strcspn(player_name, "\n")] = '\0'; // Remove the trailing newline character


    reset(); //������ ���� 

    while (1) { // ������ �� ������ �� Ȱ���ϴ� ����
        int i;
        check_mess_block();

        for (i = 0; i < 5; i++) { //����� ��ĭ�������µ��� 5�� Ű�Է¹��� �� ���� 
            check_key(); //Ű�Է�Ȯ��            
            draw_main(); //ȭ���� �׸� 
            Sleep(speed); //���Ӽӵ�����
            shadow_maker(); // sblock�� org�� �Ҵ�
            if (space_key_on == 1) { //�����̽��ٸ� �������(hard drop) �߰��� �̵� �� ȸ���Ҽ� ���� break; 

                space_key_on = 0;
                break;
            }
            shadow_remover(); // sblock�� ���� ����
            if (crush_on && check_crush(bx, by + 1, b_rotation) == false) {
                Sleep(100);

                //����� �浹���ΰ�� �߰��� �̵��� ȸ���� �ð��� ����
            }
        }
        puang_show();
        drop_block(); // ����� ��ĭ ���� 
        shadow_remover(); // sblock�� ���� ����
        check_level_up(); // �������� üũ(���󺯰� ��ġ)
        check_game_over(); //���ӿ����� üũ 



        if (new_block_on == 1) new_block(); // �� �� flag�� �ִ� ��� ���ο� �� ���� 
    }
}

void choosing_level(void) {

    time_t currentTime;
    struct tm* timeInfo;
    char buffer[100];
    char curr_time[100];
    char str[MAX_LENGTH];
    char ch[MAX_LENGTH];

    int chooselevel;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    WORD saved_attributes;
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    saved_attributes = consoleInfo.wAttributes;
    gotoxy(6, 2); printf("WHAT MODE DO YOU WANT? TYPE THE NUMBER NEXT  TO THE DIFFICULTY");
    gotoxy(6, 4); printf("Block speed and possibility will change depanding on the level");
    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
    gotoxy(6, 6); printf("EASY(type 1) "); SetConsoleTextAttribute(hConsole, saved_attributes); printf("  [start from level 1]");
    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_RED);
    gotoxy(6, 8); printf("NORMAL(type 2) "); SetConsoleTextAttribute(hConsole, saved_attributes); printf("[start from level 3]");
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
    gotoxy(6, 10); printf("HARD(type 3) "); SetConsoleTextAttribute(hConsole, saved_attributes); printf("  [start from level 5]");
    gotoxy(6, 12); printf("exit (type 0) "); SetConsoleTextAttribute(hConsole, saved_attributes); printf(" [To exit from the game]");
    gotoxy(6, 14); printf("Level > ");
    gotoxy(10, 14); scanf("%d", &chooselevel);
    switch (chooselevel) {

    case 1:
        level = 1;
        break;
    case 2:
        level = 3;
        break;
    case 3:
        level = 5;
        break;
    case 0:

        currentTime = time(NULL);               // Convert the time_t value to a struct tm for formatting
        timeInfo = localtime(&currentTime);     // Format the time according to a specific format
        strftime(buffer, sizeof(buffer), "%Y-%m-%d(%H:%M:%S)", timeInfo);

        sprintf(str, "%s", buffer);             //printf("%s\n", str);
        strcpy(curr_time, str);

        int player_sscore = score_arr[0];

        for (int i = 1; i < fix; i++)
        {
            if (score_arr[i] > player_sscore)
                player_sscore = score_arr[i];
        }

        FILE* file = fopen(fstore, "a");

        fprintf(file, "%s %d %s\n", player_name, player_sscore, curr_time);

        fclose(file);//���� ����

        pscore temp[100];
        int k = 0;
        FILE* f = fopen(fstore, "r");
        if (f != NULL) {
            while (!feof(f)) {
                fscanf(f, "%s %s %s\n", temp[k].name, ch, temp[k].time);
                temp[k].score = atoi(ch);
                k++;
            }
        }
        int fsize = k;
        quicksort1(temp, 0, fsize - 1);

        f = fopen(fstore, "w");
        for (int i = 0; i < fsize; i++) {
            fprintf(f, "%s %d %s\n", temp[i].name, temp[i].score, temp[i].time);
        }
        fclose(f);
        printf("\n");
        int rank;
        int i;
        for (i = 0; i < fsize; i++) {
            if ((strcmp(temp[i].name, player_name)) == 0) {
                gotoxy(10, 18); printf("Your Nickname  ");
                gotoxy(20, 18); printf(":   %s", temp[i].name);
                gotoxy(10, 19); printf("Your Best Score  ");
                gotoxy(20, 19); printf(":   %d", temp[i].score);
                rank = i;
            }
        }
        gotoxy(10, 20); printf("Your Rank  ");
        gotoxy(20, 20); printf(":   %d / %d", rank + 1, i);

        Sleep(5000);
        system("cls");
        exit(0);
        break;
    default:
        level = 1;
        break;
    }
    levelup_color();
}

void title(void) {
    int x = 5; //Ÿ��Ʋȭ���� ǥ�õǴ� x��ǥ 
    int y = 4; //Ÿ��Ʋȭ���� ǥ�õǴ� y��ǥ 
    int cnt; //Ÿ��Ʋ �������� ���� ����  

    gotoxy(x, y + 0); printf("����������������"); Sleep(100);
    gotoxy(x, y + 1); printf("�����  ����    ������"); Sleep(100);
    gotoxy(x, y + 2); printf("�����              ���  ��"); Sleep(100);
    gotoxy(x, y + 3); printf("������  ��  ��  ������"); Sleep(100);
    gotoxy(x, y + 4); printf("���  �������������"); Sleep(100);
    gotoxy(x, y + 5); printf("      blog.naver.com/azure0777"); Sleep(100);
    gotoxy(x + 5, y + 2); printf("T E T R I S"); Sleep(100);
    gotoxy(x, y + 7); printf("Please Enter Any Key to Start..");
    gotoxy(x, y + 9); printf("  ��   : Shift");
    gotoxy(x, y + 10); printf("��  �� : Left / Right");
    gotoxy(x, y + 11); printf("  ��   : Soft Drop");
    gotoxy(x, y + 12); printf(" SPACE : Hard Drop");
    gotoxy(x, y + 13); printf("   P   : Pause");
    gotoxy(x, y + 14); printf("  ESC  : Quit");
    gotoxy(x, y + 16); printf("BONUS FOR HARD DROPS / COMBOS");
    gotoxy(x, y + 18); printf("!!You can choose the size of your gaming board.");
    gotoxy(x, y + 20); printf("However the height must be under 29 and the width must be over 10");

    for (cnt = 0;; cnt++) { //cnt�� 1�� ������Ű�鼭 ��� �ݺ�    //�ϳ��� ���߿��� �� ��¦�̴� �ִϸ��̼�ȿ�� 
        if (_kbhit()) break; //Ű�Է��� ������ ���ѷ��� ���� 
        if (cnt % 200 == 0) { gotoxy(x + 4, y + 1); printf("��"); }       //cnt�� 200���� ������ �������� ���� ǥ�� 
        if ((cnt % 200 - 100) == 0) { gotoxy(x + 4, y + 1); printf("  "); } //�� ī��Ʈ���� 100ī��Ʈ �������� ���� ���� 
        if ((cnt % 350) == 0) { gotoxy(x + 13, y + 2); printf("��"); } //������ ������ �ð����� ���� 
        if ((cnt % 350 - 100) == 0) { gotoxy(x + 13, y + 2); printf("  "); }
        Sleep(10); // 00.1�� ������  
    }

    while (_kbhit()) _getch(); //���ۿ� ��ϵ� Ű���� ���� 

}

void reset(void) {

    FILE* file = fopen(fname, "rt"); // score.dat������ ���� 
    if (file == 0) { best_score = 0; } //������ ������ �� �ְ������� 0�� ���� 
    else {
        fscanf(file, "%d", &best_score); // ������ ������ �ְ������� �ҷ��� 
        fclose(file); //���� ���� 
    }

    level = 1; //�������� �ʱ�ȭ 
    score = 0;
    level_goal = 1000;
    key = 0;
    crush_on = 0;
    cnt = 0;
    speed = 100;

    system("cls"); //ȭ������(���� ���� ȭ������ ��ȯ) 
    reset_main(); // main_org�� �ʱ�ȭ 
    choosing_level(); // ������ ȭ�鿡 ǥ��
    system("cls"); // ���� ���� â ����� ���������� �Ѿ�� 
    draw_map(); // ����ȭ���� �׸�
    draw_main(); // �������� �׸� 

    b_type_next = rand() % 7; //�������� ���� ��� ������ �����ϰ� ���� 
    new_block(); //���ο� ����� �ϳ� ����



}

void reset_main(void) { //�������� �ʱ�ȭ  
    int i, j;
    for (i = 0; i < MAIN_Y; i++) { // �������� 0���� �ʱ�ȭ  
        for (j = 0; j < MAIN_X; j++) {
            main_org[i][j] = 0;
            main_cpy[i][j] = 100;
        }
    }
    for (j = 1; j < MAIN_X; j++) { //y���� 3�� ��ġ�� õ���� ���� 
        main_org[3][j] = CEILLING;
    }
    for (i = 1; i < MAIN_Y - 1; i++) { //�¿� ���� ����  
        main_org[i][0] = WALL;
        main_org[i][MAIN_X - 1] = WALL;
    }
    for (j = 0; j < MAIN_X; j++) { //�ٴں��� ���� 
        main_org[MAIN_Y - 1][j] = WALL;
    }
}

void reset_main_cpy(void) { //main_cpy�� �ʱ�ȭ 
    int i, j;

    for (i = 0; i < MAIN_Y; i++) {         //�����ǿ� ���ӿ� ������ �ʴ� ���ڸ� ���� 
        for (j = 0; j < MAIN_X; j++) {  //�̴� main_org�� ���� ���ڰ� ���� �ϱ� ���� 
            main_cpy[i][j] = 100;
        }
    }

}

void draw_map(void) { //���� ���� ǥ�ø� ��Ÿ���� �Լ�  
    int y = 3;             // level, goal, score�� �����߿� ���� �ٲ�� �� ���� �� y���� ���� �����ص� 
    // �׷��� Ȥ�� ���� ���� ǥ�� ��ġ�� �ٲ� �� �Լ����� �ȹٲ㵵 �ǰ�.. 

    gotoxy(STATUS_X_ADJ, STATUS_Y_LEVEL = y); printf(" LEVEL : %5d", level);
    gotoxy(STATUS_X_ADJ, STATUS_Y_GOAL = y + 1); printf(" GOAL  : %5d", 3 - cnt);
    gotoxy(STATUS_X_ADJ, y + 2); printf("+-  N E X T  -+ ");
    gotoxy(STATUS_X_ADJ, y + 3); printf("|             | ");
    gotoxy(STATUS_X_ADJ, y + 4); printf("|             | ");
    gotoxy(STATUS_X_ADJ, y + 5); printf("|             | ");
    gotoxy(STATUS_X_ADJ, y + 6); printf("|             | ");
    gotoxy(STATUS_X_ADJ, y + 7); printf("+-- -  -  - --+ ");
    gotoxy(STATUS_X_ADJ, y + 8); printf(" YOUR SCORE :");
    gotoxy(STATUS_X_ADJ, STATUS_Y_SCORE = y + 9); printf("        %6d", score);
    gotoxy(STATUS_X_ADJ, y + 10); printf(" LAST SCORE :");
    gotoxy(STATUS_X_ADJ, y + 11); printf("        %6d", last_score);
    gotoxy(STATUS_X_ADJ, y + 12); printf(" BEST SCORE :");
    gotoxy(STATUS_X_ADJ, y + 13); printf("        %6d", best_score);
    gotoxy(STATUS_X_ADJ, y + 15); printf("  ��   : Shift.SPACE: Hard Drop");
    gotoxy(STATUS_X_ADJ, y + 16); printf("��   �� : Left / Right");
    gotoxy(STATUS_X_ADJ, y + 17); printf("  ��   : Soft Drop");
    gotoxy(STATUS_X_ADJ, y + 18); printf("         P  : Pause + ESC : Quit");
    gotoxy(STATUS_X_ADJ, y + 20); printf("blog.naver.com/azure0777");
}

void draw_main(void) { //������ �׸��� �Լ� 
    int i, j;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    WORD saved_attributes;

    // Get the current console color attributes
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    saved_attributes = consoleInfo.wAttributes;
    for (j = 1; j < MAIN_X - 1; j++) { //õ���� ��� ���ο���� �������� �������� ���� �׷��� 
        if (main_org[3][j] == EMPTY) main_org[3][j] = CEILLING;
    }
    for (i = 0; i < MAIN_Y; i++) {
        for (j = 0; j < MAIN_X; j++) {
            if (main_cpy[i][j] != main_org[i][j]) { //cpy�� ���ؼ� ���� �޶��� �κи� ���� �׷���.
                //�̰� ������ ��������ü�� ��� �׷��� �������� ��¦�Ÿ�
                gotoxy(MAIN_X_ADJ + j, MAIN_Y_ADJ + i);
                switch (main_org[i][j]) { // main_org�� �������� �׸�
                case EMPTY: //��ĭ��� 
                    printf("  ");
                    break;
                case CEILLING: //õ���� 
                    printf(". ");
                    break;
                case WALL: //����� 
                    printf("��");
                    break;
                case INACTIVE_BLOCK: //���� �� ���  
                    printf("��");
                    break;
                case ACTIVE_BLOCK: //�����̰��ִ� �� ��� 
                    printf("��");
                    break;
                case SBLOCK:
                    SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);// ������ �ٸ� ��ϰ��� ������ ����� �� �򰥸�
                    printf("��");
                    // Restore the original console color attributes
                    SetConsoleTextAttribute(hConsole, saved_attributes); // ���� �ʱ�ȭ. �̰��� �����ָ� �ٸ� ��ϵ���� ������ ������ 
                    break;
                }
            }
        }

    }
    for (i = 0; i < MAIN_Y; i++) { //�������� �׸� �� main_cpy�� ����  
        for (j = 0; j < MAIN_X; j++) {
            main_cpy[i][j] = main_org[i][j];
        }
    }
}

void new_block(void) { //���ο� ��� ����  
    int i, j;

    bx = (MAIN_X / 2) - 1; //��� ���� ��ġx��ǥ(�������� ���) 
    by = 0;  //��� ������ġ y��ǥ(���� ��) 
    b_type = b_type_next; //���������� ������ 
    b_type_next = rand() % 7; //���� ���� ���� 
    b_rotation = 0;  //ȸ���� 0������ ������ 

    new_block_on = 0; //new_block flag�� ��  

    for (i = 0; i < 4; i++) { //������ bx, by��ġ�� ������  
        for (j = 0; j < 4; j++) {
            if (blocks[b_type][b_rotation][i][j] == 1) main_org[by + i][bx + j] = ACTIVE_BLOCK;
        }
    }
    for (i = 1; i < 3; i++) { //���ӻ���ǥ�ÿ� ������ ���ú��� �׸� 
        for (j = 0; j < 4; j++) {
            if (blocks[b_type_next][0][i][j] == 1) {
                gotoxy(STATUS_X_ADJ + 2 + j, i + 6);
                printf("��");
            }
            else {
                gotoxy(STATUS_X_ADJ + 2 + j, i + 6);
                printf("  ");
            }
        }
    }
}

void check_key(void) {
    key = 0; //Ű�� �ʱ�ȭ  

    if (_kbhit()) { //Ű�Է��� �ִ� ���  
        key = _getch(); //Ű���� ����
        if (key == 224) { //����Ű�ΰ�� 
            do { key = _getch(); } while (key == 224);//����Ű���ð��� ���� 
            switch (key) {
            case LEFT: //����Ű ��������  
                if (check_crush(bx - 1, by, b_rotation) == true) move_block(LEFT);
                break;                            //�������� �� �� �ִ��� üũ �� �����ϸ� �̵�
            case RIGHT: //������ ����Ű ��������- ���� �����ϰ� ó���� 
                if (check_crush(bx + 1, by, b_rotation) == true) move_block(RIGHT);
                break;
            case DOWN: //�Ʒ��� ����Ű ��������-���� �����ϰ� ó���� 
                if (check_crush(bx, by + 1, b_rotation) == true) move_block(DOWN);
                break;
            case UP: //���� ����Ű �������� 
                if (check_crush(bx, by, (b_rotation + 1) % 4) == true) move_block(UP);
                //ȸ���� �� �ִ��� üũ �� �����ϸ� ȸ��
                else if (crush_on == 1 && check_crush(bx, by - 1, (b_rotation + 1) % 4) == true) move_block(100);
            }                    //�ٴڿ� ���� ��� �������� ��ĭ����� ȸ���� �����ϸ� �׷��� ��(Ư������)
        }
        else { //����Ű�� �ƴѰ�� 
            switch (key) {
            case SPACE: //�����̽�Ű �������� 
                space_key_on = 1; //�����̽�Ű flag�� ��� 
                while (crush_on == 0) { //�ٴڿ� ���������� �̵���Ŵ 
                    drop_block();
                    score += level; // hard drop ���ʽ�
                    gotoxy(STATUS_X_ADJ, STATUS_Y_SCORE); printf("        %6d", score); //���� ǥ��  
                }
                break;
            case P: //P(�빮��) �������� 
            case p: //p(�ҹ���) �������� 
                pause(); //�Ͻ����� 
                break;
            case ESC: //ESC�������� 
                system("cls"); //ȭ���� ����� 
                exit(0); //�������� 
            }
        }
    }
    while (_kbhit()) _getch(); //Ű���۸� ��� 
}

void drop_block(void) {
    int i, j;

    if (crush_on && check_crush(bx, by + 1, b_rotation) == true) crush_on = 0; //���� ��������� crush flag �� 
    if (crush_on && check_crush(bx, by + 1, b_rotation) == false) { //���� ��������ʰ� crush flag�� ���������� 
        for (i = 0; i < MAIN_Y; i++) { //���� �������� ���� ���� 
            for (j = 0; j < MAIN_X; j++) {
                if (main_org[i][j] == ACTIVE_BLOCK)
                    main_org[i][j] = INACTIVE_BLOCK;
            }
        }
        crush_on = 0; //flag�� �� 
        check_line(); //����üũ�� �� 
        new_block_on = 1; //���ο� ������ flag�� ��    
        return; //�Լ� ���� 
    }
    if (check_crush(bx, by + 1, b_rotation) == true) move_block(DOWN); //���� ��������� ������ ��ĭ �̵� 
    if (check_crush(bx, by + 1, b_rotation) == false) crush_on++; //������ �̵��� �ȵǸ�  crush flag�� ��
}

int check_crush(int bx, int by, int b_rotation) { //������ ��ǥ�� ȸ�������� �浹�� �ִ��� �˻� 
    int i, j;

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) { //������ ��ġ�� �����ǰ� ������� ���ؼ� ��ġ�� false�� ���� 
            if (blocks[b_type][b_rotation][i][j] == 1 && main_org[by + i][bx + j] > 0) return false;
        }
    }
    return true; //�ϳ��� �Ȱ�ġ�� true���� 
};

void move_block(int dir) { //����� �̵���Ŵ 
    int i, j;
    switch (dir) {
    case LEFT: //���ʹ��� 
        for (i = 0; i < 4; i++) { //������ǥ�� ���� ���� 
            for (j = 0; j < 4; j++) {
                if (blocks[b_type][b_rotation][i][j] == 1) main_org[by + i][bx + j] = EMPTY;
            }
        }
        for (i = 0; i < 4; i++) { //�������� ��ĭ���� active block�� ���� 
            for (j = 0; j < 4; j++) {
                if (blocks[b_type][b_rotation][i][j] == 1) main_org[by + i][bx + j - 1] = ACTIVE_BLOCK;
            }
        }
        bx--; //��ǥ�� �̵� 
        break;

    case RIGHT:    //������ ����. ���ʹ����̶� ���� ������ ���� 
        for (i = 0; i < 4; i++) {
            for (j = 0; j < 4; j++) {
                if (blocks[b_type][b_rotation][i][j] == 1) main_org[by + i][bx + j] = EMPTY;
            }
        }
        for (i = 0; i < 4; i++) {
            for (j = 0; j < 4; j++) {
                if (blocks[b_type][b_rotation][i][j] == 1) main_org[by + i][bx + j + 1] = ACTIVE_BLOCK;
            }
        }
        bx++;
        break;

    case DOWN:    //�Ʒ��� ����. ���ʹ����̶� ���� ������ ����
        for (i = 0; i < 4; i++) {
            for (j = 0; j < 4; j++) {
                if (blocks[b_type][b_rotation][i][j] == 1) main_org[by + i][bx + j] = EMPTY;
            }
        }
        for (i = 0; i < 4; i++) {
            for (j = 0; j < 4; j++) {
                if (blocks[b_type][b_rotation][i][j] == 1) main_org[by + i + 1][bx + j] = ACTIVE_BLOCK;
            }
        }
        by++;
        break;

    case UP: //Ű���� ���� �������� ȸ����Ŵ. 
        for (i = 0; i < 4; i++) { //������ǥ�� ���� ����  
            for (j = 0; j < 4; j++) {
                if (blocks[b_type][b_rotation][i][j] == 1) main_org[by + i][bx + j] = EMPTY;
            }
        }
        b_rotation = (b_rotation + 1) % 4; //ȸ������ 1������Ŵ(3���� 4�� �Ǵ� ���� 0���� �ǵ���) 
        for (i = 0; i < 4; i++) { //ȸ���� ����� ���� 
            for (j = 0; j < 4; j++) {
                if (blocks[b_type][b_rotation][i][j] == 1) main_org[by + i][bx + j] = ACTIVE_BLOCK;
            }
        }
        break;

    case 100: //����� �ٴ�, Ȥ�� �ٸ� ��ϰ� ���� ���¿��� ��ĭ���� �÷� ȸ���� ������ ��� 
        //�̸� ���۽�Ű�� Ư������ 
        for (i = 0; i < 4; i++) {
            for (j = 0; j < 4; j++) {
                if (blocks[b_type][b_rotation][i][j] == 1) main_org[by + i][bx + j] = EMPTY;
            }
        }
        b_rotation = (b_rotation + 1) % 4;
        for (i = 0; i < 4; i++) {
            for (j = 0; j < 4; j++) {
                if (blocks[b_type][b_rotation][i][j] == 1) main_org[by + i - 1][bx + j] = ACTIVE_BLOCK;
            }
        }
        by--;
        break;
    }
}

void check_line(void) {
    int i, j, k, l;

    int    block_amount; //������ ��ϰ����� �����ϴ� ���� 
    combo = 0; //�޺����� �����ϴ� ���� ������ �ʱ�ȭ 

    for (i = MAIN_Y - 2; i > 3;) { //i=MAIN_Y-2 : ���ʺ��� ��ĭ����,  i>3 : õ��(3)�Ʒ����� �˻� 
        block_amount = 0; //��ϰ��� ���� ���� �ʱ�ȭ 
        for (j = 1; j < MAIN_X - 1; j++) { //���� �������� ��ϰ��縦 �� 
            if (main_org[i][j] > 0) block_amount++;
        }
        if (block_amount == MAIN_X - 2) { //����� ���� �� ��� 
            if (level_up_on == 0) { //���������°� �ƴ� ��쿡(�������� �Ǹ� �ڵ� �ٻ����� ����) 
                score += 100 * level; //�����߰� 
                cnt++; //���� �� ���� ī��Ʈ ���� 
                combo++; //�޺��� ����  
            }
            for (k = i; k > 1; k--) { //������ ��ĭ�� ��� ����(������ õ���� �ƴ� ��쿡��) 
                for (l = 1; l < MAIN_X - 1; l++) {
                    if (main_org[k - 1][l] != CEILLING) main_org[k][l] = main_org[k - 1][l];
                    if (main_org[k - 1][l] == CEILLING) main_org[k][l] = EMPTY;
                    //������ õ���� ��쿡�� õ���� ��ĭ ������ �ȵǴϱ� ��ĭ�� ���� 
                }
            }
        }
        else i--;
    }
    if (combo) { //�� ������ �ִ� ��� ������ ���� ��ǥ�� ���� ǥ���� 
        if (combo == 1) {
            puang_talk();
        }
        if (combo > 1) { //2�޺��̻��� ��� ��� ���ʽ��� �޼����� �����ǿ� ����ٰ� ���� 
            gotoxy(MAIN_X_ADJ + (MAIN_X / 2) - 1, MAIN_Y_ADJ + by - 2); printf("%d COMBO!", combo);
            Sleep(500);
            score += (combo * level * 100);
            reset_main_cpy(); //�ؽ�Ʈ�� ����� ���� main_cpy�� �ʱ�ȭ.
            //(main_cpy�� main_org�� ���� �ٸ��Ƿ� ������ draw()ȣ��� ������ ��ü�� ���� �׸��� ��) 
        }
        gotoxy(STATUS_X_ADJ, STATUS_Y_GOAL); printf(" GOAL  : %5d", (cnt <= 3) ? 3 - cnt : 0);
        gotoxy(STATUS_X_ADJ, STATUS_Y_SCORE); printf("        %6d", score);
    }
}
void check_level_up(void) {
    int i, j;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    WORD saved_attributes;

    // Get the current console color attributes
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    saved_attributes = consoleInfo.wAttributes;
    if (cnt >= 3) { //�������� 10�پ� ���־���. 10���̻� ���� ��� 
        draw_main();
        draw_map(); // ���� ������ GetConsoleScreenBufferInfo�� �ް� draw_map���� ���� �׸��鵵 ���� ä���ֱ�. ���� �̰��� �����ָ� draw_main�� ��ĥ�� ���·� ��� ��
        level_up_on = 1; //������ flag�� ��� 
        level += 1; //������ 1 �ø� 
        cnt = 0; //���� �ټ� �ʱ�ȭ   

        for (i = 0; i < 4; i++) {
            gotoxy(MAIN_X_ADJ + (MAIN_X / 2) - 3, MAIN_Y_ADJ + 4);
            printf("             ");
            gotoxy(MAIN_X_ADJ + (MAIN_X / 2) - 2, MAIN_Y_ADJ + 6);
            printf("             ");
            Sleep(200);

            gotoxy(MAIN_X_ADJ + (MAIN_X / 2) - 3, MAIN_Y_ADJ + 4);
            printf("��LEVEL UP!��");
            gotoxy(MAIN_X_ADJ + (MAIN_X / 2) - 2, MAIN_Y_ADJ + 6);
            printf("��SPEED UP!��");
            Sleep(200);
        }
        reset_main_cpy(); //�ؽ�Ʈ�� ����� ���� main_cpy�� �ʱ�ȭ.
        //(main_cpy�� main_org�� ���� �ٸ��Ƿ� ������ draw()ȣ��� ������ ��ü�� ���� �׸��� ��) 

        for (i = MAIN_Y - 2; i > MAIN_Y - 2 - (level - 1); i--) { //�������������� �� ����-1�� ����ŭ �Ʒ��� ���� ������ 
            for (j = 1; j < MAIN_X - 1; j++) {
                main_org[i][j] = INACTIVE_BLOCK; // ���� ������� ��� ä��� 
                gotoxy(MAIN_X_ADJ + j, MAIN_Y_ADJ + i); // ���� �����.. �̻����̰� 
                printf("��");
                Sleep(20);
            }
        }
        Sleep(100); //�������� �����ֱ� ���� delay 
        check_line(); //������� ��� ä��� �����
        //.check_line()�Լ� ���ο��� level up flag�� �����ִ� ��� ������ ����.     
        levelup_color();// �������� ���� ���� ����� �ӵ� ������ �� �ȿ� ���Ե�

        level_up_on = 0; //������ flag����
        draw_map();

    }
}

void check_game_over(void) {
    int i;
    int x = 5;
    int y = 5;

    for (i = 1; i < MAIN_X - 2; i++) {
        if (main_org[3][i] > 0) { //õ��(������ ����° ��)�� inactive�� �����Ǹ� ���� ����
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
            WORD saved_attributes;
            level = 100;
            puang_show();
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // ���� ���� â�� ���Ӻ��� ����� �����ϰ� �׻� ���
            gotoxy(x, y + 0); printf("�ǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢ�"); //���ӿ��� �޼��� 
            gotoxy(x, y + 1); printf("��                              ��");
            gotoxy(x, y + 2); printf("��  +-----------------------+   ��");
            gotoxy(x, y + 3); printf("��  |  G A M E  O V E R..   |   ��");
            gotoxy(x, y + 4); printf("��  +-----------------------+   ��");
            gotoxy(x, y + 5); printf("��   YOUR SCORE: %6d         ��", score);
            gotoxy(x, y + 6); printf("��                              ��");
            gotoxy(x, y + 7); printf("��  Press any key to restart..  ��");
            gotoxy(x, y + 8); printf("��                              ��");
            gotoxy(x, y + 9); printf("�ǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢ�");
            last_score = score; //���������� �ű�

            score_arr[fix] = score;
            fix++;

            if (score > best_score) { //�ְ��� ���Ž� 
                change_flag = 1;
                FILE* file = fopen(fname, "wt"); //score.dat�� ���� ����                

                gotoxy(x, y + 6); printf("��  �ڡڡ� BEST SCORE! �ڡڡ�   ��  ");

                if (file == 0) { //���� �����޼���  
                    gotoxy(0, 0);
                    printf("FILE ERROR: SYSTEM CANNOT WRITE BEST SCORE ON \"SCORE.DAT\"");
                }
                else {
                    fprintf(file, "%d", score);
                    fclose(file);
                }
            }

            Sleep(1000);
            while (_kbhit()) _getch();
            key = _getch();
            reset();
        }
    }
}

void pause(void) { //���� �Ͻ����� �Լ� 
    int i, j;

    int x = 5;
    int y = 5;

    for (i = 1; i < MAIN_X - 2; i++) { //���� �Ͻ����� �޼��� 
        gotoxy(x, y + 0); printf("�ǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢ�");
        gotoxy(x, y + 1); printf("��                              ��");
        gotoxy(x, y + 2); printf("��  +-----------------------+   ��");
        gotoxy(x, y + 3); printf("��  |       P A U S E       |   ��");
        gotoxy(x, y + 4); printf("��  +-----------------------+   ��");
        gotoxy(x, y + 5); printf("��  Press any key to resume..   ��");
        gotoxy(x, y + 6); printf("��                              ��");
        gotoxy(x, y + 7); printf("�ǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢ�");
    }
    _getch(); //Ű�Է½ñ��� ��� 

    system("cls"); //ȭ�� ����� ���� �׸� 
    reset_main_cpy();
    draw_main();
    draw_map();

    for (i = 1; i < 3; i++) { // ������� �׸� 
        for (j = 0; j < 4; j++) {
            if (blocks[b_type_next][0][i][j] == 1) {
                gotoxy(MAIN_X + MAIN_X_ADJ + 3 + j, i + 6);
                printf("��");
            }
            else {
                gotoxy(MAIN_X + MAIN_X_ADJ + 3 + j, i + 6);
                printf("  ");
            }
        }
    }
} //��! 