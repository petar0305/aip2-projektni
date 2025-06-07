#include <iostream>
#include <algorithm>
#include <chrono>
// #include <thread>
using namespace std;
const string emoji = "●";
const string emoji2 = "○";
int brojac1 = 0, brojac2 = 0;
const string susjedi[24][5] = {
    {"A", "B", "J", "", ""},
    {"B", "A", "C", "E", ""},
    {"C", "B", "O", "", ""},
    {"D", "E", "K", "", ""},
    {"E", "B", "D", "F", "H"},
    {"F", "E", "N", "", ""},
    {"G", "H", "L", "", ""},
    {"H", "E", "G", "I", ""},
    {"I", "H", "M", "", ""},
    {"J", "A", "K", "V", ""},
    {"K", "D", "J", "L", "S"},
    {"L", "G", "K", "P", ""},
    {"M", "I", "N", "R", ""},
    {"N", "F", "M", "O", "U"},
    {"O", "C", "N", "X", ""},
    {"P", "L", "Q", "", ""},
    {"Q", "P", "R", "T", ""},
    {"R", "M", "Q", "", ""},
    {"S", "K", "T", "", ""},
    {"T", "Q", "S", "U", "W"},
    {"U", "N", "T", "", ""},
    {"V", "J", "W", "", ""},
    {"W", "T", "V", "X", ""},
    {"X", "O", "W", "", ""}};
struct Mlin
{
  const char *a, *b, *c;
};
const Mlin sviMlinovi[16] = {
    {"A", "B", "C"}, {"D", "E", "F"}, {"G", "H", "I"}, 
    {"J", "K", "L"}, {"M", "N", "O"}, {"P", "Q", "R"}, 
    {"S", "T", "U"}, {"V", "W", "X"}, {"A", "J", "V"}, 
    {"D", "K", "S"}, {"G", "H", "I"}, {"B", "E", "H"}, 
    {"C", "F", "I"}, {"L", "M", "N"},
    {"O", "R", "U"}, {"X", "W", "V"}};
struct Koordinata
{
  const char *oznaka;
  int i, j;
};
const Koordinata pozicije[24] = {
    {"A", 0, 0}, {"B", 0, 10}, {"C", 0, 20}, 
    {"D", 1, 2}, {"E", 1, 10}, {"F", 1, 18}, 
    {"G", 2, 4}, {"H", 2, 10}, {"I", 2, 16}, 
    {"J", 4, 0}, {"K", 4, 2}, {"L", 4, 4}, 
    {"M", 4, 16}, {"N", 4, 18}, {"O", 4, 20}, 
    {"P", 6, 4}, {"Q", 6, 10}, {"R", 6, 16}, 
    {"S", 7, 2}, {"T", 7, 10}, {"U", 7, 18}, 
    {"V", 8, 0}, {"W", 8, 10}, {"X", 8, 20}};
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
bool figura_je_u_mlinu(int &x, int &y, string ploca[9][21])
{
  string f = ploca[x][y];
  if (f != "○" && f != "●")
    return false;
  string oznaka = "";
  for (int i = 0; i < 24; i++)
  {
    if (pozicije[i].i == x && pozicije[i].j == y)
    {
      oznaka = pozicije[i].oznaka;
      break;
    }
  }
  if (oznaka == "")
    return false;
  for (int i = 0; i < 16; i++)
  {
    Mlin m = sviMlinovi[i];
    if (oznaka == m.a || oznaka == m.b || oznaka == m.c)
    {
      Koordinata ka, kb, kc;
      bool foundA = false, foundB = false, foundC = false;
      for (int j = 0; j < 24; j++)
      {
        if (pozicije[j].oznaka == m.a)
        {
          ka = pozicije[j];
          foundA = true;
        }
        if (pozicije[j].oznaka == m.b)
        {
          kb = pozicije[j];
          foundB = true;
        }
        if (pozicije[j].oznaka == m.c)
        {
          kc = pozicije[j];
          foundC = true;
        }
      }
      if (foundA && foundB && foundC)
      {
        if (ploca[ka.i][ka.j] == f &&
            ploca[kb.i][kb.j] == f &&
            ploca[kc.i][kc.j] == f)
        {
          return true;
        }
      }
    }
  }
  return false;
}
int n_figura_izvan_mlina(string ploca[9][21], string protivnik)
{
  int n = 0;
  for (int i = 0; i < 24; i++)
  {
    int x = pozicije[i].i;
    int y = pozicije[i].j;
    if (ploca[x][y] == protivnik && !figura_je_u_mlinu(x, y, ploca))
      n++;
  }
  return n;
}
void igrac1_uzima(string ploca[9][21], string pocetna[9][21], int &x, int &y)
{
  if (n_figura_izvan_mlina(ploca, emoji2) == 0)
  {
    cout << "Sve protivničke figure su u mlinu. Možeš uzeti bilo koju." << endl;
    string unos;
    ispisPloce(ploca);
    while (1)
    {
      cout << "Igrač 1, unesi polje figure koju želiš uzeti: ";
      cin >> unos;
      transform(unos.begin(), unos.end(), unos.begin(), ::toupper);
      slova_u_koordinate(unos, pocetna, x, y);
      if (ploca[x][y] == "○")
      {
        ploca[x][y] = pocetna[x][y];
        clearScreen();
        brojac2--;
        break;
      }
      else
        cout << "Na tom polju nije protivnička figura. Pokušaj ponovno." << endl;
    }
    return;
  }
  string unos; // figura koju igrac jede(uzima)
  ispisPloce(ploca);
  while(1){
    cout << "Igrač 1, unesi polje figure koju želiš uzeti: ";
    cin >> unos;
    transform(unos.begin(), unos.end(), unos.begin(), ::toupper);
    slova_u_koordinate(unos, pocetna, x, y);
    if (ploca[x][y] == "○"){
      if(figura_je_u_mlinu(x, y, ploca)){
        cout << "Ta figura je u mlinu. Pokušaj ponovno" << endl;
        continue;
      }
      ploca[x][y] = pocetna[x][y];
      clearScreen();
      brojac2--;
      break;
    }
    else
      cout << "Na tom polju nije protivnička figura. Pokušaj ponovno." << endl;
  }
}
void igrac2_uzima(string ploca[9][21], string pocetna[9][21], int &x, int &y){
  if (n_figura_izvan_mlina(ploca, emoji) == 0)
  {
    cout << "Sve protivničke figure su u mlinovima. Ne možeš ništa uzeti.\n";
    string unos;
    ispisPloce(ploca);
    while (1)
    {
      cout << "Igrač 2, unesi polje figure koju želiš uzeti: ";
      cin >> unos;
      transform(unos.begin(), unos.end(), unos.begin(), ::toupper);
      slova_u_koordinate(unos, pocetna, x, y);
      if (ploca[x][y] == "●")
      {
        ploca[x][y] = pocetna[x][y];
        clearScreen();
        brojac1--;
        break;
      }
      else
        cout << "Na tom polju nije protivnička figura. Pokušaj ponovno." << endl;
    }
    return;
  }
  string unos;
  ispisPloce(ploca);
  while(1){
    cout << "Igrač 2, unesi polje figure koju želiš uzeti: ";
    cin >> unos;
    transform(unos.begin(), unos.end(), unos.begin(), ::toupper);
    slova_u_koordinate(unos, pocetna, x, y);
    if (ploca[x][y] == "●"){
      if (figura_je_u_mlinu(x, y, ploca))
      {
        cout << "Ta figura je u mlinu. Pokušaj ponovno" << endl;
        continue;
      }
      ploca[x][y] = pocetna[x][y];
      clearScreen();
      brojac1--;
      break;
    }
    else
      cout << "Na tom polju nije protivnička figura. Pokušaj ponovno." << endl;
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
bool susjedna_polja(const string &a, const string &b)
{
  for (int i = 0; i < 24; i++) {
    if (susjedi[i][0] == a)
    {
      for (int j = 1; j<=5 && susjedi[i][j] != ""; j++){
        if (susjedi[i][j] == b)
          return true;
      }
    }
  }
  return false;
}
bool ima_slobodno_susjedno_polje(const string &polje, string ploca[9][21], string pocetna[9][21])
{
  for (int i = 0; i < 24; i++)
  {
    if (susjedi[i][0] == polje)
    {
      for (int j = 1; j < 5 && susjedi[i][j] != ""; j++)
      {
        string susjed = susjedi[i][j];
        int x, y;
        if (slova_u_koordinate(susjed, pocetna, x, y))
          if (ploca[x][y] == pocetna[x][y])
            return true;
      }
      break;
    }
  }
  return false;
}
void pomicanje_igrac1(string ploca[9][21], string pocetna[9][21], int &x, int &y)
{
  string odakle, kamo;
  int x1, y1, x2, y2;
  while (true)
  {
    ispisPloce(ploca);
    cout << "Igrač 1, unesi polje s kojeg želiš pomaknuti figuru: ";
    cin >> odakle;
    transform(odakle.begin(), odakle.end(), odakle.begin(), ::toupper);
    if (!ima_slobodno_susjedno_polje(odakle, ploca, pocetna))
    {
      clearScreen();
      cout << "Figura na tom polju nema nijedno slobodno susjedno polje za pomicanje." << endl;
      continue;
    }
    if (!slova_u_koordinate(odakle, pocetna, x1, y1))
    {
      clearScreen();
      cout << "To polje ne postoji. Pokušaj ponovno.\n";
      continue;
    }
    if (ploca[x1][y1] != emoji)
    {
      clearScreen();
      cout << "Na tom polju nije tvoja figura. Pokušaj ponovno.\n";
      continue;
    }
    cout << "Unesi polje na koje želiš pomaknuti figuru: ";
    cin >> kamo;
    transform(kamo.begin(), kamo.end(), kamo.begin(), ::toupper);
    if (!slova_u_koordinate(kamo, pocetna, x2, y2))
    {
      clearScreen();
      cout << "To polje ne postoji. Pokušaj ponovno.\n";
      continue;
    }
    if (ploca[x2][y2] != kamo)
    {
      clearScreen();
      cout << "To polje nije prazno. Pokušaj ponovno.\n";
      continue;
    }
    if (!susjedna_polja(odakle, kamo))
    {
      clearScreen();
      cout << "Polja nisu susjedna. Pomicanje nije dozvoljeno.\n";
      continue;
    }
    ploca[x2][y2] = emoji;
    ploca[x1][y1] = pocetna[x1][y1];
    x = x2;
    y = y2;
    clearScreen();
    break;
  }
  if (provjera_mlina(kamo, ploca, emoji))
    igrac1_uzima(ploca, pocetna, x, y);
}
void pomicanje_igrac2(string ploca[9][21], string pocetna[9][21], int &x, int &y)
{
  string odakle, kamo;
  int x1, y1, x2, y2;
  while (true)
  {
    ispisPloce(ploca);
    cout << "Igrač 2, unesi polje s kojeg želiš pomaknuti figuru: ";
    cin >> odakle;
    transform(odakle.begin(), odakle.end(), odakle.begin(), ::toupper);
    if (!ima_slobodno_susjedno_polje(odakle, ploca, pocetna))
    {
      clearScreen();
      cout << "Figura na tom polju nema nijedno slobodno susjedno polje za pomicanje." << endl;
      continue;
    }
    if (!slova_u_koordinate(odakle, pocetna, x1, y1))
    {
      clearScreen();
      cout << "To polje ne postoji. Pokušaj ponovno.\n";
      continue;
    }
    if (ploca[x1][y1] != emoji2)
    {
      clearScreen();
      cout << "Na tom polju nije tvoja figura. Pokušaj ponovno.\n";
      continue;
    }
    cout << "Unesi polje na koje želiš pomaknuti figuru: ";
    cin >> kamo;
    transform(kamo.begin(), kamo.end(), kamo.begin(), ::toupper);
    if (!slova_u_koordinate(kamo, pocetna, x2, y2))
    {
      clearScreen();
      cout << "To polje ne postoji. Pokušaj ponovno.\n";
      continue;
    }
    if (ploca[x2][y2] != kamo)
    {
      clearScreen();
      cout << "To polje nije prazno. Pokušaj ponovno.\n";
      continue;
    }
    if (!susjedna_polja(odakle, kamo))
    {
      clearScreen();
      cout << "Polja nisu susjedna. Pomicanje nije dozvoljeno.\n";
      continue;
    }
    ploca[x2][y2] = emoji2;
    ploca[x1][y1] = pocetna[x1][y1];
    x = x2;
    y = y2;
    clearScreen();
    break;
  }
  if (provjera_mlina(kamo, ploca, emoji2))
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
      clearScreen();
      while(brojac1>2 || brojac2>2){
        int x, y;
        int i = 0;
        if (i % 2 == 0)
        {
          pomicanje_igrac1(ploca, pocetna, x, y);
        }
        i++;
        if (i % 2 == 1)
        {
          pomicanje_igrac2(ploca, pocetna, x, y);
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
