#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>

using namespace std;

// defining some settings of the game
const int SIZE = 10;
const int NUMBER_OF_ENEMIES = 10;

struct Point { // Point struct to handle the x and y of enemies and spaceship
  int x;
  int y;
};

struct Game {
  int num_enemies;
  Point spaceship;
  int health;
  bool (*map)[10];
};

void generate_enemies(bool map[SIZE][SIZE], int num_enemies) {
  int num_inserted_enemies = 0;

  while (num_inserted_enemies < num_enemies) {
    Point p = {
        .x = rand() % SIZE,
        .y = rand() % SIZE,
    };

    if (!map[p.y][p.x]) {
      map[p.y][p.x] = true;
      ++num_inserted_enemies;
    }
  }
}

bool contains_full_row(bool map[SIZE][SIZE]) {
  for (int i = 0; i < SIZE; ++i) {
    bool full = true;
    for (int j = 0; j < SIZE; ++j) {
      if (!map[i][j]) {
        full = false;
      }
    }

    if (full) {
      return true;
    }
  }

  return false;
}

bool contains_full_col(bool map[SIZE][SIZE]) {
  for (int i = 0; i < SIZE; ++i) {
    bool full = true;
    for (int j = 0; j < SIZE; ++j) {
      if (!map[j][i]) {
        full = false;
      }
    }

    if (full) {
      return true;
    }
  }

  return false;
}

Game init_game(bool map[SIZE][SIZE]) {
  int num_enemies = SIZE + rand() % 5;

  do {
    generate_enemies(map, num_enemies);
  } while (contains_full_row(map) || contains_full_col(map));

  Point spaceship;
  do {
    spaceship.y = rand() % SIZE;
    spaceship.x = rand() % SIZE;
  } while (map[spaceship.y][spaceship.x]);

  Game game = {
      .num_enemies = num_enemies,
      .spaceship = spaceship,
      .health = 3,
      .map = map,
  };

  return game;
}

void clear() {
#ifdef __linux__
  system("clear");
#else
  system("cls");
#endif
}

void render(const Game &game) {
  clear();

  cout << "health: " << game.health << "\n\n";

  for (int ifor = 0; ifor < 2 * SIZE; ++ifor) {
    if (ifor % 2 == 0) {
      for (int j = 0; j < SIZE; ++j) {
        cout << " ---";
      }

      cout << endl;
      continue;
    }

    int i = ifor / 2;
    for (int j = 0; j < SIZE; ++j) {
      char ch = ' ';
      if (game.spaceship.y == i && game.spaceship.x == j) {
        ch = 'O';
      } else if (game.map[i][j]) {
        ch = '*';
      }

      cout << "| " << ch << " ";
    }

    cout << "|" << endl;
  }

  for (int j = 0; j < SIZE; ++j) {
    cout << " ---";
  }
  cout << endl;
}

void handle_input(Game &game) {
  while (true) {
    char cmd;
    cout << "[M]ove, [A]ttack, or [Q]uit (m|a|q): ";
    cin >> cmd;

    switch (tolower(cmd)) {
    case 'm': {
      char dir;
      cout << "Choose a direction (w|a|s|d): ";
      cin >> dir;

      switch (dir) {
      case 'w':
        if (game.spaceship.y > 0)
          --game.spaceship.y;
        break;
      case 'a':
        if (game.spaceship.x > 0)
          --game.spaceship.x;
        break;
      case 's':
        if (game.spaceship.y < SIZE - 1)
          ++game.spaceship.y;
        break;
      case 'd':
        if (game.spaceship.x < SIZE - 1)
          ++game.spaceship.x;
        break;
      }

      if (game.map[game.spaceship.y][game.spaceship.x]) {
        game.map[game.spaceship.y][game.spaceship.x] = false;
        --game.health;
      }

      return;
    }
    case 'a': {
      char dir;
      cout << "Choose a direction (a|d): ";
      cin >> dir;

      switch (dir) {
      case 'a':
        // TODO
        break;
      case 'd':
        // TODO
        break;
      }

      return;
    }
    case 'q':
      exit(0);
    default:
      cout << "error: invalid input\n\n";
    }
  }
}

int main() {
  srand(time(0));

  bool map[SIZE][SIZE] = {};
  Game game = init_game(map);

  while (true) {
    render(game);

    if (game.health == 0) {
      clear();

      cout << " --------------------\n";
      cout << "|     YOU LOSE!      |\n";
      cout << "|  Better luck next  |\n";
      cout << "|       time!        |\n";
      cout << " --------------------\n";

      char c;
      cin >> c;

      exit(0);
    }
    if (game.num_enemies == 0) {
      clear();

      cout << " --------------------\n";
      cout << "|      YOU WON!      |\n";
      cout << "|  Congratulations!  |\n";
      cout << " --------------------\n";

      char c;
      cin >> c;

      exit(0);
    }

    handle_input(game);
  }
}
