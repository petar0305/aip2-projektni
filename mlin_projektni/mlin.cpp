#include <iostream>
#include <algorithm>
#include <chrono>
#include <fstream>
#include <sstream>
using namespace std;
string inicijalizirana[9][21] = {
    {"A", "-", "-", "-", "-", "-", "-", "-", "-", "-", "B", "-", "-", "-", "-", "-", "-", "-", "-", "-", "C"},
    {"|", " ", "D", "-", "-", "-", "-", "-", "-", "-", "E", "-", "-", "-", "-", "-", "-", "-", "F", " ", "|"},
    {"|", " ", "|", " ", "G", "-", "-", "-", "-", "-", "H", "-", "-", "-", "-", "-", "I", " ", "|", " ", "|"},
    {"|", " ", "|", " ", "|", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", "|", " ", "|", " ", "|"},
    {"J", "-", "K", "-", "L", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", "M", "-", "N", "-", "O"},
    {"|", " ", "|", " ", "|", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", "|", " ", "|", " ", "|"},
    {"|", " ", "|", " ", "P", "-", "-", "-", "-", "-", "Q", "-", "-", "-", "-", "-", "R", " ", "|", " ", "|"},
    {"|", " ", "S", "-", "-", "-", "-", "-", "-", "-", "T", "-", "-", "-", "-", "-", "-", "-", "U", " ", "|"},
    {"V", "-", "-", "-", "-", "-", "-", "-", "-", "-", "W", "-", "-", "-", "-", "-", "-", "-", "-", "-", "X"}};
const string emoji = "●";
const string emoji2 = "○";
struct PlocaStruct{
  string ploca[9][21];
};
struct stanjeIgre
{
  int brojac1;
  int brojac2;
  int trenutni_igrac;
  int korak_postavljanja;
  bool postavljanje_gotovo;
};
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
    {"A", "B", "C"},
    {"D", "E", "F"}, 
    {"G", "H", "I"}, 
    {"J", "K", "L"},
    {"M", "N", "O"},
    {"P", "Q", "R"}, 
    {"S", "T", "U"},
    {"V", "W", "X"},
    {"A", "J", "V"}, 
    {"D", "K", "S"},
    {"G", "L", "P"},
    {"B", "E", "H"}, 
    {"Q", "T", "W"},
    {"I", "M", "R"},
    {"F", "N", "U"},
    {"C", "O", "X"}};
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
void spremiPlocuTxt(const string ploca[9][21], const string &imeDatoteke = "ploca.txt")
{
  ofstream datoteka(imeDatoteke);
  if (!datoteka)
  {
    cout << "Greška pri otvaranju datoteke!" << endl;
    return;
  }
  for (int i = 0; i < 9; i++)
  {
    for (int j = 0; j < 21; j++)
    {
      datoteka << ploca[i][j];
    }
    datoteka << '\n';
  }
  datoteka.close();
  cout << "Ploca spremljena" << endl;
}
void ucitajPlocuIzTeksta(string ploca[9][21], const string &imeDatoteke = "ploca.txt")
{
  ifstream datoteka(imeDatoteke);
  if (!datoteka)
  {
    cout << "Greška pri otvaranju datoteke!" << endl;
    return;
  }
  string linija;
  for (int i = 0; i < 9 && getline(datoteka, linija); i++)
  {
    istringstream iss(linija);
    for (int j = 0; j < 21; j++)
    {
      iss >> ploca[i][j];
    }
  }
  datoteka.close();
}
void spremanje_igre(stanjeIgre &StanjeIgre)
{
  ofstream datoteka("igra.bin", ios::binary);
  if (!datoteka)
  {
    cout << "Greska pri otvaranju datoteke!" << endl;
    return;
  }
  datoteka.write((char *)&StanjeIgre, sizeof(stanjeIgre));
  datoteka.close();
  cout << "Igra spremljena!" << endl;
}
void ucitavanje_igre(stanjeIgre &StanjeIgre)
{
  ifstream datoteka("igra.bin", ios::binary);
  if (!datoteka)
  {
    cout << "Greska pri otvaranju datoteke!" << endl;
    return;
  }
  datoteka.read((char *)&StanjeIgre, sizeof(stanjeIgre));
  datoteka.close();
}
bool provjera_mlina(const string &polje, string ploca[9][21], const string &figura)
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
void igrac1_uzima(string ploca[9][21], string pocetna[9][21], int &x, int &y, int &brojac2)
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
      if (unos == "0")
      {
        stanjeIgre StanjeIgre;
        PlocaStruct plocaStruktura;
        spremiPlocuTxt(plocaStruktura.ploca);
        spremanje_igre(StanjeIgre);
      }
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
    if (unos == "0")
    {
      stanjeIgre StanjeIgre;
      PlocaStruct plocaStruktura;
      spremiPlocuTxt(plocaStruktura.ploca);
      spremanje_igre(StanjeIgre);
    }
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
void igrac2_uzima(string ploca[9][21], string pocetna[9][21], int &x, int &y, int &brojac1){
  if (n_figura_izvan_mlina(ploca, emoji) == 0)
  {
    cout << "Sve protivničke figure su u mlinovima. Ne možeš ništa uzeti.\n";
    string unos;
    ispisPloce(ploca);
    while (1)
    {
      cout << "Igrač 2, unesi polje figure koju želiš uzeti: ";
      cin >> unos;
      if (unos == "0")
      {
        stanjeIgre StanjeIgre;
        PlocaStruct plocaStruktura;
        spremiPlocuTxt(plocaStruktura.ploca);
        spremanje_igre(StanjeIgre);
      }
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
    if (unos == "0")
    {
      stanjeIgre StanjeIgre;
      PlocaStruct plocaStruktura;
      spremiPlocuTxt(plocaStruktura.ploca);
      spremanje_igre(StanjeIgre);
    }
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
void figure_igrac1(string ploca[9][21], string polje, int &x, int &y, string pocetna[9][21], int &brojac2, int &brojac1)
{
  slova_u_koordinate(polje, ploca, x, y);
  clearScreen();
  ploca[x][y] = emoji;
  brojac1++;
  if (provjera_mlina(polje, ploca, emoji))
    igrac1_uzima(ploca, pocetna, x, y, brojac2);
}
void figure_igrac2(string ploca[9][21], string polje, int &x, int &y, string pocetna[9][21], int &brojac1, int &brojac2)
{ 
  slova_u_koordinate(polje, ploca, x, y);
  clearScreen();
  ploca[x][y] = emoji2;
  brojac2++;
  if (provjera_mlina(polje, ploca, emoji2))
    igrac2_uzima(ploca, pocetna, x, y, brojac1);
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
void pomicanje_igrac1(string ploca[9][21], string pocetna[9][21], int &x, int &y, int &brojac2)
{
  string odakle, kamo;
  int x1, y1, x2, y2;
  while (true)
  {
    ispisPloce(ploca);
    cout << "Igrač 1, unesi polje s kojeg želiš pomaknuti figuru: ";
    cin >> odakle;
    if (odakle == "0")
    {
      stanjeIgre StanjeIgre;
      PlocaStruct plocaStruktura;
      spremiPlocuTxt(plocaStruktura.ploca);
      spremanje_igre(StanjeIgre);
    }
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
    if (kamo == "0")
    {
      stanjeIgre StanjeIgre;
      PlocaStruct plocaStruktura;
      spremiPlocuTxt(plocaStruktura.ploca);
      spremanje_igre(StanjeIgre);
    }
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
    igrac1_uzima(ploca, pocetna, x, y, brojac2);
}
void pomicanje_igrac2(string ploca[9][21], string pocetna[9][21], int &x, int &y, int &brojac1)
{
  string odakle, kamo;
  int x1, y1, x2, y2;
  while (true)
  {
    ispisPloce(ploca);
    cout << "Igrač 2, unesi polje s kojeg želiš pomaknuti figuru: ";
    cin >> odakle;
    if (odakle == "0")
    {
      stanjeIgre StanjeIgre;
      PlocaStruct plocaStruktura;
      spremiPlocuTxt(plocaStruktura.ploca);
      spremanje_igre(StanjeIgre);
    }
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
    if (kamo == "0")
    {
      stanjeIgre StanjeIgre;
      PlocaStruct plocaStruktura;
      spremiPlocuTxt(plocaStruktura.ploca);
      spremanje_igre(StanjeIgre);
    }
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
    igrac2_uzima(ploca, pocetna, x, y, brojac1);
}
int main()
{
  int izbor;
  while (1)
  {
    cout << "\t\t1. Pravila igre" << endl;
    cout << "\t\t2. Igraj novu igru" << endl;
    cout << "\t\t3. Igraj spremljenu igru" << endl;
    cout << "\t\t4. Izlaz" << endl;
    cout << "\t\tUnesite vaš izbor: ";
    cin >> izbor;
    clearScreen();

    if (izbor == 1)
    {
      cout << "Igra mlin se igra na ploči koja se sastoji od tri koncentrična polja povezana crtama od sredine svake stranice unutarnjeg polja do sredine stranice odgovarajućeg vanjskog polja. Dijelovi se igraju na kutnim točkama i na točkama gdje se linije sijeku tako da postoje 24 točke za igru. Uz ploču treba biti 9 crnih i 9 bijelih figura obično u obliku okruglih brojača. Osnovni cilj igre mlin je napraviti mlinove - okomite ili vodoravne linije od tri u nizu. Svaki put kad se to postigne, protivnička figura se uklanja, a opći cilj je smanjiti broj protivničkih figura na manje od tri ili onemogućiti protivnika da igra. Za početak tabla je prazna."<< endl << endl;
    }

    else if (izbor == 2)
    {
      stanjeIgre StanjeIgre;
      PlocaStruct plocaStruktura;
      string igrac1, igrac2;
      cout << "Unesite ime 1. igrača: ";
      cin >> igrac1;
      cout << "Unesite ime 2. igrača: ";
      cin >> igrac2;
      clearScreen();
      string pocetna[9][21];
      for (int i = 0; i < 9; ++i){
        for (int j = 0; j < 21; ++j){
          pocetna[i][j] = inicijalizirana[i][j];
          plocaStruktura.ploca[i][j] = inicijalizirana[i][j];
        }
      }
      ispisPloce(plocaStruktura.ploca);
      for (int i = 0; i < 18; i++)
      {
        StanjeIgre.korak_postavljanja = i;
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
            if (polje == "0")
            {
              spremiPlocuTxt(plocaStruktura.ploca);
              spremanje_igre(StanjeIgre);
            }
            transform(polje.begin(), polje.end(), polje.begin(), ::toupper);
            if (jePrazno(plocaStruktura.ploca, polje))
            {
              figure_igrac1(plocaStruktura.ploca, polje, x, y, pocetna, StanjeIgre.brojac2, StanjeIgre.brojac1);
              ispisPloce(plocaStruktura.ploca);
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
            if (polje == "0")
            {
              spremiPlocuTxt(plocaStruktura.ploca);
              spremanje_igre(StanjeIgre);
            }
            transform(polje.begin(), polje.end(), polje.begin(), ::toupper);
            if (jePrazno(plocaStruktura.ploca, polje))
            {
              figure_igrac2(plocaStruktura.ploca, polje, x, y, pocetna, StanjeIgre.brojac1, StanjeIgre.brojac2);
              ispisPloce(plocaStruktura.ploca);
            }
            else
            {
              dobra_pozicija = false;
              cout << "Krivi unos\nUnesite ponovno: ";
            }
          } while (dobra_pozicija == false);
        }
      }
      StanjeIgre.postavljanje_gotovo = true;
      clearScreen();
      StanjeIgre.trenutni_igrac = 1;
      while (StanjeIgre.brojac1 > 2 && StanjeIgre.brojac2 > 2)
      {
        int x, y;
        if (StanjeIgre.trenutni_igrac == 1)
        {
          pomicanje_igrac1(plocaStruktura.ploca, pocetna, x, y, StanjeIgre.brojac2);
          StanjeIgre.trenutni_igrac = 2;
        }
        else
        {
          pomicanje_igrac2(plocaStruktura.ploca, pocetna, x, y, StanjeIgre.brojac1);
          StanjeIgre.trenutni_igrac = 1;
        }
      }
      if (StanjeIgre.brojac1 == 2)
      {
        cout << "Igra je gotova\nIgrac 2 " << emoji2 << "je pobijedio";
      }
      else
        cout << "Igra je gotova\nIgrac 1 " << emoji << "je pobijedio";
    }
    else if (izbor == 3)
    {
      
      stanjeIgre StanjeIgre;
      PlocaStruct plocaStruktura;
      ucitajPlocuIzTeksta(plocaStruktura.ploca);
      ucitavanje_igre(StanjeIgre);
      ispisPloce(plocaStruktura.ploca);
      string pocetna[9][21];
      for (int i = 0; i < 9; ++i)
      {
        for (int j = 0; j < 21; ++j)
        {
          pocetna[i][j] = inicijalizirana[i][j];
          plocaStruktura.ploca[i][j] = inicijalizirana[i][j];
        }
      }
      if(!StanjeIgre.postavljanje_gotovo){
        for (int i = StanjeIgre.korak_postavljanja; i < 18; i++)
        {
          string polje;
          int x, y;
          if (i % 2 == 0)
          {
            bool dobra_pozicija = true;
            cout << "Igrac 1(" << emoji << ") je na redu. \nUnesite slovo na koje želite postaviti figuru: ";
            do
            {
              dobra_pozicija = true;
              cin >> polje;
              if (polje == "0")
              {
                spremiPlocuTxt(plocaStruktura.ploca);
                spremanje_igre(StanjeIgre);
              }
              transform(polje.begin(), polje.end(), polje.begin(), ::toupper);
              if (jePrazno(plocaStruktura.ploca, polje))
              {
                figure_igrac1(plocaStruktura.ploca, polje, x, y, pocetna, StanjeIgre.brojac2, StanjeIgre.brojac1);
                ispisPloce(plocaStruktura.ploca);
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
            cout << "Igrac 2(" << emoji2 << ") je na redu.\nUnesite slovo na koje želite postaviti figuru: ";
            do
            {
              dobra_pozicija = true;
              cin >> polje;
              if (polje == "0")
              {
                spremiPlocuTxt(plocaStruktura.ploca);
                spremanje_igre(StanjeIgre);
              }
              transform(polje.begin(), polje.end(), polje.begin(), ::toupper);
              if (jePrazno(plocaStruktura.ploca, polje))
              {
                figure_igrac2(plocaStruktura.ploca, polje, x, y, pocetna, StanjeIgre.brojac1, StanjeIgre.brojac2);
                ispisPloce(plocaStruktura.ploca);
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
      clearScreen();
      StanjeIgre.trenutni_igrac = 1;
      while (StanjeIgre.brojac1 > 2 && StanjeIgre.brojac2 > 2)
      {
        int x, y;
        if (StanjeIgre.trenutni_igrac == 1)
        {
          pomicanje_igrac1(plocaStruktura.ploca, pocetna, x, y, StanjeIgre.brojac2);
          StanjeIgre.trenutni_igrac = 2;
        }
        else
        {
          pomicanje_igrac2(plocaStruktura.ploca, pocetna, x, y, StanjeIgre.brojac1);
          StanjeIgre.trenutni_igrac = 1;
        }
      }
      if(StanjeIgre.brojac1 == 2){
        cout << "Igra je gotova\nIgrac 2 " << emoji2 << "je pobijedio";
      }
      else
        cout << "Igra je gotova\nIgrac 1 " << emoji << "je pobijedio";
    }
    else if (izbor == 4)
      break;
  }
}
