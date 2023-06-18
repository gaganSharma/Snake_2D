#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>

#define ROW 20
#define COL 20

int screen[ROW][COL];

typedef struct node NODE;
typedef struct node *PNODE;
struct node
{
    int x, y;
    PNODE link;
};
PNODE list = NULL;

void spawnfeed();
void reset();
void displayScreen();
int nextlist(int ii, int jj);
int moveup();
int movedown();
int moveleft();
int moveright();

int main(int argc, char const *argv[])
{
    char key = 'w';
    int quit = 0;
    NODE z;
    z.x = 5;
    z.y = 10;
    z.link = NULL;
    list = &z;
    // newscreen();
    spawnfeed();
    while (1)
    {
        system("cls");
        reset();
        if (kbhit())
        {
            char new = getch();
            switch (new)
            {
            case 'w':
                if (key != 's')
                    key = new;
                break;

            case 's':
                if (key != 'w')
                    key = new;
                break;

            case 'a':
                if (key != 'd')
                    key = new;
                break;

            case 'd':
                if (key != 'a')
                    key = new;
                break;

            case 'e':
                displayScreen();
                printf("\n\t\tYou Quit");
                return 0;
                break;
            case ' ':
                key = new;
                break;

            default:
                break;
            }
        }
        if (key == 'w')
            quit = moveup();
        else if (key == 'a')
            quit = moveleft();
        else if (key == 's')
            quit = movedown();
        else if (key == 'd')
            quit = moveright();
        if (quit)
        {
            displayScreen();
            printf("\n\t\tYOU LOSE");
            return 0;
        }
        displayScreen();
        Sleep(120);
    }
    /* code */
    return 0;
}
void spawnfeed()
{
    time_t t;
    srand((unsigned)time(&t));
    while (1)
    {
        int ii = rand() % ROW;
        int jj = rand() % COL;
        if (screen[ii][jj] == 0)
        {
            screen[ii][jj] = 2;
            return;
        }
    }
}
void reset()
{
    for (int i = 0; i < ROW; i++)
    {
        for (int j = 0; j < COL; j++)
        {
            if (screen[i][j] != 2)
                screen[i][j] = 0;
        }
    }
    PNODE temp = list;
    while (temp != NULL)
    {
        screen[temp->x][temp->y] = 1;
        temp = temp->link;
    }
}

void displayScreen()
{
    for (int i = 0; i < COL + 1; i++)
    {
        printf("---");
    }
    printf("-\n");
    for (int i = 0; i < ROW; i++)
    {
        printf("||");
        for (int j = 0; j < COL; j++)
        {
            switch (screen[i][j])
            {
            case 0:
                printf("   ");
                break;

            case 1:
                printf(" 0 ");
                break;

            case 2:
                printf(" X ");
                break;
            default:
                break;
            }
        }
        printf("||\n");
    }
    for (int i = 0; i < COL + 1; i++)
    {
        printf("---");
    }
    printf("-\n");
    // PNODE temp = list;
    // while (temp != NULL)
    // {
    //     printf("x = %d\ty = %d\n", temp->x, temp->y);
    //     temp = temp->link;
    // }
}
int nextlist(int ii, int jj)
{
    PNODE temp = list;
    if (screen[ii][jj] == 1)
    {
        return 1;
    }
    if (screen[ii][jj] == 2)
    {
        PNODE temp = list;
        while (temp->link != NULL)
        {
            temp = temp->link;
        }
        temp->link = (PNODE)malloc(sizeof(NODE));
        temp = temp->link;
        temp->x = ii;
        temp->y = jj;
        temp->link = NULL;
        screen[ii][jj] = 1;
        spawnfeed();
    }
    else
    {
        while (temp->link != NULL)
        {
            temp->x = temp->link->x;
            temp->y = temp->link->y;
            temp = temp->link;
        }
        temp->x = ii;
        temp->y = jj;
    }
    return 0;

    // system("pause");
}
int moveup()
{
    PNODE temp = list;
    while (temp->link != NULL)
        temp = temp->link;
    int x = temp->x - 1;
    if (x < 0)
        x = ROW - 1;
    return nextlist(x, temp->y);
}
int movedown()
{
    PNODE temp = list;
    while (temp->link != NULL)
        temp = temp->link;
    int x = temp->x + 1;
    if (x >= ROW)
        x = 0;
    return nextlist(x, temp->y);
}
int moveleft()
{
    PNODE temp = list;
    while (temp->link != NULL)
        temp = temp->link;
    int x = temp->y - 1;
    if (x < 0)
        x = COL - 1;
    return nextlist(temp->x, x);
}

int moveright()
{
    PNODE temp = list;
    while (temp->link != NULL)
        temp = temp->link;
    int x = temp->y + 1;
    if (x >= COL)
        x = 0;
    return nextlist(temp->x, x);
}