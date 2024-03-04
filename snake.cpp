
//Header Files
#include "iostream"
#include "conio.h"
#include "chrono"
#include "thread"

// Define Function
#define CursorPos(x, y) cout << "\033[" << x + 2 << ";" << 2 * y + 3 << "H"

// Define Colors
#define TextHead "\033[31;41m"
#define TextTail "\033[37;47m"
#define TextDefault "\033[0m"

// Symbols used and others
#define Food "()"
#define DoubleDash "--"
#define DoubleBar "||"
#define EmptySpace "  "

#define TopBorder DoubleDash
#define BottomBorder DoubleDash
#define LeftBorder DoubleBar
#define RightBorder DoubleBar
#define Head cout << TextHead << EmptySpace << TextDefault
#define Tail cout << TextTail << EmptySpace << TextDefault


using namespace std;

// Constants
const int ROW = 20;
const int COL = 40;

int screen[ROW][COL];
int duration = 120;

// typedefs for linked list
typedef struct node NODE;
typedef struct node *PNODE;
struct node
{
  int x, y;
  PNODE link;
};
PNODE list = NULL;


// sleep function for frame rates
void Sleep(int n)
{
  this_thread::sleep_for(chrono::milliseconds(n));
}

// all function definitions and body
void spawnfeed();
void setScreen();
void displayScreen();
int nextlist(int ii, int jj);
int moveup();
int movedown();
int moveleft();
int moveright();

void displayScreen()
{
  system("cls");
  for (int i = 0; i < COL + 4; i++)
  {
    cout << TopBorder;
  }
  cout << endl;
  for (int i = 0; i < ROW; i++)
  {
    cout << LeftBorder;
    for (int j = 0; j < COL; j++)
    {
      cout << EmptySpace;
    }
    cout << RightBorder << endl;
  }
  for (int i = 0; i < COL + 4; i++)
  {
    cout << BottomBorder;
  }
  cout << endl;
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
      CursorPos(ii, jj);
      cout << Food;
      return;
    }
  }
}
void setScreen()
{
  for (int i = 0; i < ROW; i++)
  {
    for (int j = 0; j < COL; j++)
    {
      screen[i][j] = 0;
    }
  }
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
    while (temp->link != NULL)
    {
      temp = temp->link;
    }
    CursorPos(temp->x, temp->y);
    Tail;
    temp->link = (PNODE)malloc(sizeof(NODE));
    temp = temp->link;
    temp->x = ii;
    temp->y = jj;
    temp->link = NULL;
    screen[ii][jj] = 1;
    spawnfeed();
    CursorPos(temp->x, temp->y);
    Head;
  }
  else
  {
    CursorPos(temp->x, temp->y);
    cout << EmptySpace;
    screen[temp->x][temp->y] = 0;
    while (temp->link != NULL)
    {
      temp->x = temp->link->x;
      temp->y = temp->link->y;
      temp = temp->link;
    }
    CursorPos(temp->x, temp->y);
    Tail;
    temp->x = ii;
    temp->y = jj;
    CursorPos(temp->x, temp->y);
    Head;
    screen[temp->x][temp->y] = 1;
  }
  CursorPos(ROW + 3, 0);
  return 0;
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

// Main function for C++
int main(int argc, char const *argv[])
{
  char key = 'w';
  int quit = 0;
  NODE z, tail;
  z.x = 5;
  z.y = 10;
  tail.x = 6;
  tail.y = 10;
  tail.link = NULL;
  z.link = &tail;
  list = &z;

  setScreen();
  displayScreen();
  spawnfeed();
  while (1)
  {
    duration = 120;
    if (kbhit())
    {
      char newkey = getch();
      if (newkey == key)
      {
        duration = 180;
      }
      switch (newkey)
      {
      case 'w':
        if (key != 's')
          key = newkey;
        break;

      case 's':
        if (key != 'w')
          key = newkey;
        break;

      case 'a':
        if (key != 'd')
          key = newkey;
        break;

      case 'd':
        if (key != 'a')
          key = newkey;
        break;

      case 'e':
        cout << "\n\t\tYou Quit";
        return 0;
        break;
      case ' ':
        key = newkey;
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
      cout << "\n\t\tYOU LOSE";
      return 0;
    }
    Sleep(duration);
  }
  return 0;
}