#include <iostream>
#include <algorithm>
#include <chrono>
// #include <thread>
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
    {"S", "T", "U"}, {"V", "W", "X"}, {"A", "J", "V"}, 
    {"D", "K", "S"}, {"G", "H", "I"}, {"B", "E", "H"}, {"C", "F", "I"}, 
    {"L", "M", "N"}, {"O", "R", "U"}, {"X", "W", "V"}};
struct Koordinata
{
  const char *oznaka;
  int i, j;
};
const Koordinata pozicije[24] = {
    {"A", 0, 0}, {"B", 0, 10}, {"C", 0, 20}, {"D", 1, 2}, {"E", 1, 10}, {"F", 1, 18}, {"G", 2, 4}, {"H", 2, 10}, {"I", 2, 16}, {"J", 4, 0}, {"K", 4, 2}, {"L", 4, 4}, {"M", 4, 16}, {"N", 4, 18}, {"O", 4, 20}, {"P", 6, 4}, {"Q", 6, 10}, {"R", 6, 16}, {"S", 7, 2}, {"T", 7, 10}, {"U", 7, 18}, {"V", 8, 0}, {"W", 8, 10}, {"X", 8, 20}};
bool provjera_mlina(const string &polje, const string ploca[9][21], const string &figura)
{
  for (int i = 0; i < 16; i++)
  {
    const Mlin &m = sviMlinovi[i];
    if (polje == m.a || polje == m.b || polje == m.c)
    {
      int koordinate[3][2];
      const char *oznake[3] = {m.a, m.b, m.c};
      for (int k = 0; k < 3; k++)
      {
        for (int j = 0; j < 24; j++)
        {
          if (oznake[k] == pozicije[j].oznaka)
          {
            koordinate[k][0] = pozicije[j].i;
            koordinate[k][1] = pozicije[j].j;
            break;
          }
        }
      }
      if (
          ploca[koordinate[0][0]][koordinate[0][1]] == figura &&
          ploca[koordinate[1][0]][koordinate[1][1]] == figura &&
          ploca[koordinate[2][0]][koordinate[2][1]] == figura)
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
bool jePrazno(string ploca[9][21], string polje)
{
  for (int i = 0; i < 9; i++)
  {
    for (int j = 0; j < 21; j++)
    {
      if (ploca[i][j] == polje)
      {
        if (ploca[i][j] != emoji2 && ploca[i][j] != emoji)
          return true;
        else
          return false;
      }
    }
  }
  return false;
}
bool slova_u_koordinate(string polje, string ploca[9][21], int &x, int &y)
{
  for (int i = 0; i < 9; i++)
  {
    for (int j = 0; j < 21; j++)
    {
      if (ploca[i][j] == polje)
      {
        x = i;
        y = j;
        return true;
      }
    }
  }
  return false;
}

void igrac1_uzima(string ploca[9][21], string pocetna[9][21], int &x, int &y)
{
  string unos;//figura koju igrac jede(uzima)
  ispisPloce(ploca);
  while(1){
    cout << "Igrač 1, unesi polje figure koju želiš uzeti: ";
    cin >> unos;
    transform(unos.begin(), unos.end(), unos.begin(), ::toupper);
    slova_u_koordinate(unos, pocetna, x, y);
    if (ploca[x][y] == "○"){
      ploca[x][y] = pocetna[x][y];
      clearScreen();
      brojac1--;
      break;
    }
    else{
      cout << "Na tom polju nije protivnička figura. Pokušaj ponovno." << endl;
    }
  }
}
void igrac2_uzima(string ploca[9][21], string pocetna[9][21], int &x, int &y){
  string unos;
  ispisPloce(ploca);
  while(1){
    cout << "Igrač 2, unesi polje figure koju želiš uzeti: ";
    cin >> unos;
    transform(unos.begin(), unos.end(), unos.begin(), ::toupper);
    slova_u_koordinate(unos, pocetna, x, y);
    if (ploca[x][y] == "●"){
      ploca[x][y] = pocetna[x][y];
      clearScreen();
      brojac2--;
      break;
    }
    else{
      cout << "Na tom polju nije protivnička figura. Pokušaj ponovno." << endl;
    }
  }
}

void figure_igrac1(string ploca[9][21], string polje, int &x, int &y, string pocetna[9][21])
{
  slova_u_koordinate(polje, ploca, x, y);
  clearScreen();
  ploca[x][y] = emoji;
  brojac1++;
  if (provjera_mlina(polje, ploca, emoji))
    igrac1_uzima(ploca, pocetna, x, y);
}

void figure_igrac2(string ploca[9][21], string polje, int &x, int &y, string pocetna[9][21])
{ 
  slova_u_koordinate(polje, ploca, x, y);
  clearScreen();
  ploca[x][y] = emoji2;
  brojac2++;
  if (provjera_mlina(polje, ploca, emoji2))
    igrac2_uzima(ploca, pocetna, x, y);
}

int main()
{
  int izbor;

  while (1)
  {
    cout << "\t\t1. Pravila igre" << endl;
    cout << "\t\t2. Igraj" << endl;
    cout << "\t\t3. Ispis leaderboarda" << endl;
    cout << "\t\t4. Spremi igru" << endl;
    cout << "\t\t5. Izlaz" << endl;
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
      string pocetna[9][21];
      for (int i = 0; i < 9; ++i)
        for (int j = 0; j < 21; ++j)
          pocetna[i][j] = ploca[i][j];
      ispisPloce(ploca);
      for (int i = 0; i < 18; i++)
      {
        string polje;
        int x, y;
        if (i % 2 == 0)
        {
          bool dobra_pozicija = true;
          cout << "Igrac 1(●, " << igrac1 << ") je na redu. \nUnesite slovo na koje želite postaviti figuru: ";
          do
          {
            dobra_pozicija = true;
            cin >> polje;
            transform(polje.begin(), polje.end(), polje.begin(), ::toupper);
            if (jePrazno(ploca, polje))
            {
              figure_igrac1(ploca, polje, x, y, pocetna);
              ispisPloce(ploca);
            }
            else
            {
              dobra_pozicija = false;
              cout << "Krivi unos\nUnesite ponovno: ";
            }
          } while (dobra_pozicija == false);
        }
        if (i % 2 == 1)
        {
          bool dobra_pozicija = true;
          cout << "Igrac 2(○, " << igrac2 << ") je na redu.\nUnesite slovo na koje želite postaviti figuru: ";
          do
          {
            dobra_pozicija = true;
            cin >> polje;
            transform(polje.begin(), polje.end(), polje.begin(), ::toupper);
            if (jePrazno(ploca, polje))
            {
              figure_igrac2(ploca, polje, x, y, pocetna);
              ispisPloce(ploca);
            }
            else
            {
              dobra_pozicija = false;
              cout << "Krivi unos\nUnesite ponovno: ";
            }
          } while (dobra_pozicija == false);
        }
      }
    }
    else if (izbor == 3)
    {

    }
    else if(izbor == 4){

    }
    else if (izbor == 5)
      break;
  }
}
