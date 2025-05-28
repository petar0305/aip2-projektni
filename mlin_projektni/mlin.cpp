#include <iostream>
#include <algorithm>
#include <chrono>
#include <thread>
using namespace std;
void clearConsole()
{
  cout << "\033[2J\033[1;1H";
}
void ispisPloce()
{
  for (int i = 0; i < 9; i++)
  {
    for (int j = 0; j < 17; j++)
      cout << "j";
  }
}

int slova_u_koordinate(char figura)
{
  if (figura ==)
}

int figure_igrac1()
{
  if (ploca[0][0] != emoji2 && ploca[0][0] != emoji)
  {
    clearConsole();
    ploca[0][0] = emoji;
    brojac1++;
    // ispisi_plocu(ploca);
    krivi_unos = 0;
    if (ploca[0][0] == ploca[0][8] && ploca[0][0] == ploca[0][16])
      igrac1_uzima(ploca, emoji2);
    if (ploca[0][0] == ploca[4][0] && ploca[0][0] == ploca[8][0])
      igrac1_uzima(ploca, emoji2);
  }
}
int figure_igrac2()
{
  if (ploca[0][0] != emoji2 && ploca[0][0] != emoji)
  {
    clearConsole();
    ploca[0][0] = emoji;
    brojac1++;
    // ispisi_plocu(ploca);
    krivi_unos = 0;
    if (ploca[0][0] == ploca[0][8] && ploca[0][0] == ploca[0][16])
      igrac1_uzima(ploca, emoji2);
    if (ploca[0][0] == ploca[4][0] && ploca[0][0] == ploca[8][0])
      igrac1_uzima(ploca, emoji2);
  }
}

int main()
{
  int izbor;

  while (1)
  {
    cout << "1. Pravila igre" << endl;
    cout << "2. Igraj" << endl;
    cout << "3. Ispis leaderboarda" << endl;
    cout << "4. Izlaz" << endl;

    cin >> izbor;

    if (izbor == 1)
    {
      cout << "Tu upisati pravila igre" << endl;
    }

    else if(izbor==2)
    {
      
    }
  }
  for (int i = 0; i < 18; i++)
  {
    if (!i % 2)
    {
      cout << "igrac 1 je na redu.";
    }
    if (i % 2)
    {
      cout << "igrac 1 je na redu.";
    }
  }
}
