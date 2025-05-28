#include <iostream>
#include <algorithm>
#include <chrono>
#include <thread>
using namespace std;
void clearScreen()
{
  cout << string(100, '\n');
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
  if (figura =='A'){

  }
}
/*
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
*/



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

    else if(izbor==2)
    {
      string igrac1, igrac2;
      cout << "Unesite ime 1. igrača: ";
      cin >> igrac1;
      cout << "Unesite ime 2. igrača: ";
      cin >> igrac2;
      clearScreen();
      string ploca = {'A','-','-','-','-','-','-','-','B','-','-','-','-','-','-','-','C'};
      /*A---------B---------C
      | D-------E-------F |
      | | G-----H-----I | |
      | | |           | | |
      J-K-L           M-N-O
      | | |           | | |
      | | P-----Q-----R | |
      | S-------T-------U |
      V---------W---------X*/

      cout << ploca;
    }
    else if(izbor==3){

    }
    else if(izbor==4)
      break;
  }
  /*for (int i = 0; i < 18; i++)
  {
    if (!i % 2)
    {
      cout << "igrac 1 je na redu.";
    }
    if (i % 2)
    {
      cout << "igrac 1 je na redu.";
    }
  }*/
}
