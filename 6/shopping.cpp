#include <cstdlib>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
using namespace std;

struct Product {
  short int id;
  string name;

  void operator()(string line) {
    int space = line.find(" ");
    id = stoi(line.substr(0, space));
    name = line.substr(space + 1, line.length() - space);
  }
};

int main() {
  ifstream readFile("./list.txt");

  string line;
  short int lastId = 0;
  map<string, short int> products;
  while (getline(readFile, line)) {
    Product newP;
    newP(line);
    lastId = newP.id;

    bool in = false;
    for (auto p : products) {
      if (p.first == newP.name) {
        products[newP.name]++;
        in = true;
      }
    }

    if (!in)
      products[newP.name] = 1;
  }

  readFile.close();

	ofstream writeFile("./out.txt");
  for (auto p : products) {
    writeFile << p.first << " " << 100 / lastId * p.second << "%"<< endl;
  }
	writeFile.close();
}
