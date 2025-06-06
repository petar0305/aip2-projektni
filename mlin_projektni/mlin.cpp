#include <iostream>
#include <algorithm>
#include <chrono>
//#include <thread>
using namespace std;
const string emoji = "●";
const string emoji2 = "○";
int brojac1 = 0, brojac2 = 0;
struct Mlin
{
  const char *a, *b, *c;
};
const Mlin sviMlinovi[16] = {
    {"A", "B", "C"}, {"D", "E", "F"}, {"G", "H", "I"},
    {"J", "K", "L"}, {"M", "N", "O"}, {"P", "Q", "R"},
    {"S", "T", "U"}, {"V", "W", "X"},
    {"A", "J", "V"}, {"D", "K", "S"}, {"G", "H", "I"},
    {"B", "E", "H"}, {"C", "F", "I"},
    {"L", "M", "N"}, {"O", "R", "U"}, {"X", "W", "V"}
};
struct Koordinata {
  const char* oznaka;
  int i, j;
};
const Koordinata pozicije[24] = {
  {"A", 0, 0}, {"B", 0,10}, {"C", 0,20},
  {"D", 1, 2}, {"E", 1,10}, {"F", 1,18},
  {"G", 2, 4}, {"H", 2,10}, {"I", 2,16},
  {"J", 4, 0}, {"K", 4, 2}, {"L", 4, 4},
  {"M", 4,16}, {"N", 4,18}, {"O", 4,20},
  {"P", 6, 4}, {"Q", 6,10}, {"R", 6,16},
  {"S", 7, 2}, {"T", 7,10}, {"U", 7,18},
  {"V", 8, 0}, {"W", 8,10}, {"X", 8,20}
};
bool provjera_mlina(const string &polje, const string ploca[9][21], const string &figura)
{
  for (int i = 0; i < 16; ++i)
  {
    const Mlin &m = sviMlinovi[i];
    if (polje == m.a || polje == m.b || polje == m.c)
    {
      int found = 0;
      int coords[3][2];
      const char *oznake[3] = {m.a, m.b, m.c};
      for (int k = 0; k < 3; ++k)
      {
        for (int j = 0; j < 24; ++j)
        {
          if (oznake[k] == pozicije[j].oznaka)
          {
            coords[k][0] = pozicije[j].i;
            coords[k][1] = pozicije[j].j;
            break;
          }
        }
      }
      if (
          ploca[coords[0][0]][coords[0][1]] == figura &&
          ploca[coords[1][0]][coords[1][1]] == figura &&
          ploca[coords[2][0]][coords[2][1]] == figura)
      {
        return true;
      }
    }
  }
  return false;
}

void clearScreen()
{
  cout << string(100, '\n');
}
void ispisPloce(string ploca[9][21])
{
  for (int i = 0; i < 9; i++)
  {
    for (int j = 0; j < 21; j++)
    {
      cout << ploca[i][j];
    }
    cout << endl;
  }
}
bool jePrazno(string ploca[9][21])
{
  for (int i = 0; i < 9; i++)
  {
    for (int j = 0; j < 21; j++)
    {
      if (ploca[i][j] != emoji2 && ploca[i][j] != emoji)
      {
        return true;
      }
    }
  }
}
bool slova_u_koordinate(string figura, string ploca[9][21], int *x, int *y)
{
  for (int i = 0; i < 9; i++)
  {
    for (int j = 0; j < 21; j++)
    {
      if (ploca[i][j] == figura)
      {
        *x = i;
        *y = j;
        return true;
      }
    }
  }
}

bool provjera_mlina(){

}
void figure_igrac1(string ploca[9][21], string figura, int *x, int *y)
{
  //int krivi_unos;
  if (jePrazno(ploca))
  {
    slova_u_koordinate(figura, ploca, x, y);
    clearScreen();
    ploca[*x][*y] = emoji;
    brojac1++;
    //krivi_unos = 0;
    if(provjera_mlina(figura, ploca, emoji))
      cout << "mlin\n";

    // if (ploca[0][0] == ploca[0][8] && ploca[0][0] == ploca[0][16])
    // igrac1_uzima(ploca, emoji2);
  }
  else{
    //krivi_unos = 1;
    cout << "Krivi unos.\nUnesite ponovno: ";
  }
}

void figure_igrac2(string ploca[9][21], string figura, int *x, int *y)
{
  if (jePrazno(ploca))
  {
    slova_u_koordinate(figura, ploca, x, y);
    clearScreen();
    ploca[*x][*y] = emoji2;
    brojac2++;
    // ispisi_plocu(ploca);
    //krivi_unos = 0;
    //if (ploca[0][0] == ploca[0][8] && ploca[0][0] == ploca[0][16])
      //igrac1_uzima(ploca, emoji2);
    //if (ploca[0][0] == ploca[4][0] && ploca[0][0] == ploca[8][0])
      //igrac1_uzima(ploca, emoji2);
  }
}


int main()
{
  int izbor;

  while (1)
  {
    cout << "\t\t1. Pravila igre" << endl;
    cout << "\t\t2. Igraj" << endl;
    cout << "\t\t3. Ispis leaderboarda" << endl;
    cout << "\t\t4. Izlaz" << endl;
    cout << "\t\tUnesite vaš izbor: ";
    cin >> izbor;
    clearScreen();

    if (izbor == 1)
    {
      cout << "Tu upisati pravila igre" << endl;
    }

    else if (izbor == 2)
    {
      string igrac1, igrac2;
      cout << "Unesite ime 1. igrača: ";
      cin >> igrac1;
      cout << "Unesite ime 2. igrača: ";
      cin >> igrac2;
      clearScreen();
      string ploca[9][21] = {
          {"A", "-", "-", "-", "-", "-", "-", "-", "-", "-", "B", "-", "-", "-", "-", "-", "-", "-", "-", "-", "C"},
          {"|", " ", "D", "-", "-", "-", "-", "-", "-", "-", "E", "-", "-", "-", "-", "-", "-", "-", "F", " ", "|"},
          {"|", " ", "|", " ", "G", "-", "-", "-", "-", "-", "H", "-", "-", "-", "-", "-", "I", " ", "|", " ", "|"},
          {"|", " ", "|", " ", "|", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", "|", " ", "|", " ", "|"},
          {"J", "-", "K", "-", "L", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", "M", "-", "N", "-", "O"},
          {"|", " ", "|", " ", "|", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", "|", " ", "|", " ", "|"},
          {"|", " ", "|", " ", "P", "-", "-", "-", "-", "-", "Q", "-", "-", "-", "-", "-", "R", " ", "|", " ", "|"},
          {"|", " ", "S", "-", "-", "-", "-", "-", "-", "-", "T", "-", "-", "-", "-", "-", "-", "-", "U", " ", "|"},
          {"V", "-", "-", "-", "-", "-", "-", "-", "-", "-", "W", "-", "-", "-", "-", "-", "-", "-", "-", "-", "X"}};
      ispisPloce(ploca);
      for (int i = 0; i < 18; i++)
      {
        string figura;
        int x, y;
        if (i % 2 == 0)
        {
          cout << "Igrac 1(●, "<<igrac1<<") je na redu. \nUnesite slovo na koje želite postaviti figuru: ";
          cin >> figura;
          figure_igrac1(ploca, figura, &x, &y);
          ispisPloce(ploca);
        }
        if (i % 2==1)
        {
          cout << "Igrac 2(○, " << igrac2 << ") je na redu.\nUnesite slovo na koje želite postaviti figuru: ";
          cin >> figura;
          figure_igrac2(ploca, figura, &x, &y);
          ispisPloce(ploca);
        }
      }
    }
    else if (izbor == 3)
    {
    }
    else if (izbor == 4)
      break;
  }
}
