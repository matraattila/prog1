#include <fstream>
#include <iostream>
#include <list>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

vector<string> split(const string &s, char delim) {
  vector<string> props;
  // split the line by commas
  stringstream ss(s);
  string line;
  while (std::getline(ss, line, delim)) {
    // add each part to the vector
    props.push_back(line);
  }

  return props;
}

struct Dog {
  string name;
  string breed;
  int age;
  string color;
  int weight;

  void operator()(string l) {
    auto props = split(l, ',');

    // assign the values to the struct
    name = props[0];
    breed = props[1];
    age = stoi(props[2]);
    color = props[3];
    weight = stoi(props[4]);
  }
};

Dog searchForDogByName(const vector<Dog> &dogs, const string &name) {
  for (Dog dog : dogs) {
    if (dog.name == name) {
      return dog;
    }
  }

  // return empty dog
  return Dog();
}

int main() {
  vector<Dog> dogs;
  ifstream reader("dogs.csv");

  string line;
  // skip first line
  getline(reader, line);
  // read the rest of the file
  while (getline(reader, line)) {
    Dog dog;
    dog(line);

    dogs.push_back(dog);
  }

  // Search for a dog by name
  string dogName;
  cout << "Enter the name of the dog you want to search for: ";
  cin >> dogName;

  Dog dog = searchForDogByName(dogs, dogName);

  if (!dog.name.empty()) {
    cout << "Name: " << dog.name << endl;
    cout << "Breed: " << dog.breed << endl;
    cout << "Age: " << dog.age << endl;
    cout << "Color: " << dog.color << endl;
    cout << "Weight: " << dog.weight << endl;
    cout << endl;
  } else {
    cout << "Dog named *" << dogName << "* wasn't found" << endl;
  }
}
