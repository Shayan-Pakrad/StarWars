#include <iostream>

using namespace std;

const int HEIGHT = 4;
const int WIDTH = 4;

void render(int map[WIDTH][HEIGHT]);
char cell_to_string(int cell);

int main() {
  int map[WIDTH][HEIGHT] = {};

  render(map);
}

void render(int map[WIDTH][HEIGHT]) {
  for (int ifor = 0; ifor < 2 * HEIGHT; ++ifor) {
    if (ifor % 2 == 0) {
      for (int j = 0; j < WIDTH; ++j) {
        cout << " ---";
      }

      cout << endl;
      continue;
    }

    int i = ifor / 2;
    for (int j = 0; j < WIDTH; ++j) {
      cout << "| " << cell_to_string(map[i][j]) << " ";
    }

    cout << "|" << endl;
  }

  for (int j = 0; j < WIDTH; ++j) {
    cout << " ---";
  }
  cout << endl;
}

char cell_to_string(int cell) {
  switch (cell) {
  case 1:
    return 'O';
  case 2:
    return '*';
  default:
    return ' ';
  }
}
