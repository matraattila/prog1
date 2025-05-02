#include <iostream>
using namespace std;

struct pair_t {
  int first;
  int second;
};

void sort_pairs_by_first(pair_t *pairs, int size) {
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size - 1; j++) {
      if (pairs[j].first > pairs[j + 1].first) {
        swap(pairs[j], pairs[j + 1]);
      }
    }
  }
}

void print_separator(const string &separator) {
  cout << separator << endl;
}

void process_and_print_pairs(const pair_t *pairs, int size) {
  for (int i = 0; i < size; i++) {
    int first = pairs[i].first;
    int second = pairs[i].second;
    int result;

    if (first % 2 == 0) {
      result = (second % 2 == 0) ? first * second : first + second;
    } else {
      result = (second % 2 == 0) ? first - second : first;
    }

    cout << result << endl;
  }
}

void process_pairs(pair_t *pairs, int size) {
  sort_pairs_by_first(pairs, size);
  print_separator("===");
  print_separator("Output:");
  print_separator("---");
  process_and_print_pairs(pairs, size);
}

int main() {
  pair_t pairs[5] = {
      {5, 1},
      {2, 4},
      {3, 7},
      {1, 6},
      {4, 5},
  };

  process_pairs(pairs, 5);
  return 0;
}
