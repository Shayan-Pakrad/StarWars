#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>

// TODO: use rand_range instead of rand

using namespace std;

/**
 * Determines number of rows and columns.
 */
const int SIZE = 10;

/**
 * Minimum number of enemies spawned.
 */
const int MIN_ENEMIES = SIZE;

/**
 * Maximum number of enemies spawned.
 */
const int MAX_ENEMIES = SIZE + 5;

/**
 * Represents a 2-dimensional vector.
 */
struct Point {
  int x;
  int y;
};

/**
 * Stores game state.
 */
struct Game {
  int num_enemies;
  int health;
  Point spaceship;
  bool (*map)[10];
};

/**
 * Returns a random number in range [a, b).
 */
int rand_range(int a, int b);

/**
 * Generates n enemies on the map randomly.
 */
void generate_enemies(bool map[SIZE][SIZE], int n);

/**
 * Checks whether map contains any full row.
 */
bool contains_full_row(bool map[SIZE][SIZE]);

/**
 * Checks whether map contains any full column.
 */
bool contains_full_col(bool map[SIZE][SIZE]);

/**
 * Initializes the game object with either zero values or randomly generated
 * values.
 */
Game init_game(bool map[SIZE][SIZE]);

/**
 * Clears the terminal screen.
 */
void clear();

/**
 * Prints the state of game on the screen.
 */
void render(const Game &game);

/**
 * Handles user inputs infinitely until user quits.
 */
void handle_input(Game &game);

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

int rand_range(int a, int b) { return rand() % (b - a) + a; }

void generate_enemies(bool map[SIZE][SIZE], int n) {
  int num_inserted_enemies = 0;

  while (num_inserted_enemies < n) {
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
  int num_enemies = rand_range(MIN_ENEMIES, MAX_ENEMIES + 1);

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
      .health = 3,
      .spaceship = spaceship,
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
        --game.num_enemies;
      }

      return;
    }
    case 'a': {
      char dir;
      cout << "Choose a direction (a|d): ";
      cin >> dir;

      switch (dir) {
      case 'a':
        for (int j = game.spaceship.x - 1; j >= 0; --j) {
          if (game.map[game.spaceship.y][j]) {
            game.map[game.spaceship.y][j] = false;
            --game.num_enemies;
            break;
          }
        }
        break;
      case 'd':
        for (int j = game.spaceship.x + 1; j < SIZE; ++j) {
          if (game.map[game.spaceship.y][j]) {
            game.map[game.spaceship.y][j] = false;
            --game.num_enemies;
            break;
          }
        }
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
