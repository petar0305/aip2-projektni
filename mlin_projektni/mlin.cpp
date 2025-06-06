#include <iostream>
#include <algorithm>
#include <chrono>
#include <thread>
using namespace std;
const string emoji = "●";
const string emoji2 = "○";
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

int slova_u_koordinate(string figura, string ploca[9][21], int *x, int *y)
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

int figure_igrac1(string ploca[9][21], string figura, int *x, int *y)
{
  if (jePrazno(ploca))
  {
    slova_u_koordinate(figura, ploca, x, y);
    clearScreen();
    ploca[*x][*y] = emoji;
    brojac1++;
    // krivi_unos = 0;
    // if (ploca[0][0] == ploca[0][8] && ploca[0][0] == ploca[0][16])
    // igrac1_uzima(ploca, emoji2);
    // if (ploca[0][0] == ploca[4][0] && ploca[0][0] == ploca[8][0])
    // igrac1_uzima(ploca, emoji2);
  }
}

int figure_igrac2(string ploca[9][21], string figura, int *x, int *y)
{
  if (jePrazno(ploca))
  {
    slova_u_koordinate(figura, ploca, x, y);
    clearScreen();
    ploca[*x][*y] = emoji;
    brojac1++;
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
          {"|", " ", "|", " ", "G", "-", "-", "-", "-", "-", "H", "-", "-", "-", "-", "-", "-", "-", "I", " ", "|"},
          {"|", " ", "|", " ", "|", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", "|", " ", "|", " ", "|"},
          {"J", "-", "K", "-", "L", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", "M", "-", "N", "-", "O"},
          {"|", " ", "|", " ", "|", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", "|", " ", "|", " ", "|"},
          {"|", " ", "|", " ", "P", "-", "-", "-", "-", "-", "Q", "-", "-", "-", " ", " ", "-", "-", "R", " ", "|"},
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
          //figure_igrac1(ploca, figura, &x, &y);
          //ispisPloce(ploca);
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
