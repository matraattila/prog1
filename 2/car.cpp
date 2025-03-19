#include <iostream>
#include <string>

using namespace std;

struct Auto {
    string rendszam;
};

int main (int argc, char *argv[]) {
  // Autók tömb feltöltése
  Auto autok[10];
  for (int i = 0; i < 10; i++)
  {
    autok[i].rendszam = "ABC-11" + to_string(i);
  }
  
  // Autó keresése rendszám alapján
  string keresett_rendszam;
  cout << "Add meg a keresendő autó rendszámát (ABC-113): ";
  cin >> keresett_rendszam;

  bool megtalalva = false;
  for (Auto car : autok)
  {
    if (car.rendszam == keresett_rendszam) {
      megtalalva = true;
      break;
    }
  }

  if (megtalalva) {
    cout << "Autó megtalálva" << endl;
  } else {
    cout << keresett_rendszam << " rendszámú autó nem található" << endl;
  }
  
}
