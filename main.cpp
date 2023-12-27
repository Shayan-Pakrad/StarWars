#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>

using namespace std;

struct Point { // Point struct to handle the x and y of enemies and spaceship
  int x;
  int y;
};

// defining some settings of the game
const int SIZE = 10;
const int NUMBER_OF_ENEMIES = 10;

// functions prototypes
void render(int map[SIZE][SIZE], int health);
char cell_to_string(int cell);
vector<Point> generate_enemies();
bool is_point_valid(vector<Point> points, Point point);
bool enemies_in_a_row(int map[SIZE][SIZE]);
Point generate_spaceship(vector<Point> enemies);
void game_over();

int main() {

  int map[SIZE][SIZE] = {}; // defining the map array
  Point spaceship;
  vector<Point> enemies;

  do {

    enemies = generate_enemies();

    for (Point enemy : enemies) { // putting enemies on the map
      map[enemy.y][enemy.x] = 2;
    }

  } while (enemies_in_a_row(map));

  spaceship = generate_spaceship(enemies);

  map[spaceship.y][spaceship.x] = 1;


  int health = 3;

  int enemy_number = NUMBER_OF_ENEMIES;

  render(map, health);


  while (health > 0 && enemy_number > 0) {

    char move_or_fire;
    cout << "Move or Fire or Quit(m, f, q) : ";
    cin >> move_or_fire;

    switch (move_or_fire) {

    case 'm': {


      char move;
      cout << "which direction(a, w, s, d) : ";
      cin >> move;

      int x, y;

      x = spaceship.x;
      y = spaceship.y;

      switch (move) {
      case 'w':
        if (spaceship.y > 0)
          y--;
        break;

      case 'a':
        if (spaceship.x > 0)
          x--;
        break;

      case 's':
        if (spaceship.y < SIZE - 1)
          y++;
        break;

      case 'd':
        if (spaceship.x < SIZE - 1)
          x++;
        break;
      }

      if (map[y][x] == 0){
        map[spaceship.y][spaceship.x] = 0;
        map[y][x] = 1;
        spaceship.x = x;
        spaceship.y = y;
      }

      else if (map[y][x] == 2){

        health --;
        cout << "You lose one health, try again!";
        render(map, health);
        continue; // go back to the start of the loop

      }
      

      break;
    }

    case 'f': {

      char shot_direction;
      cout << "left or right(a, d) : ";
      cin >> shot_direction;

      switch (shot_direction){

      case 'a':{
        for (int i = spaceship.x; i >= 0; i--){
          if (map[spaceship.y][i] == 2){
            map[spaceship.y][i] = 0;
            enemy_number--;
            break;
          }
        }
        break;
      }

      case 'd':{
        for (int i = spaceship.x; i <= SIZE - 1; i++){
          if (map[spaceship.y][i] == 2){
            map[spaceship.y][i] = 0;
            enemy_number--;
            break;
          }
        }
        break;
      }
      
      default:
        break;
      }


      break;
    }

    case 'q':
      exit(0);

    }

    map[spaceship.y][spaceship.x] = 1;

    render(map, health);
  }

  game_over();
}

void render(int map[SIZE][SIZE], int health) {
#ifdef __linux__
  system("clear");
#else
  system("cls");
#endif

  cout << "health : " << health << endl;

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
      cout << "| " << cell_to_string(map[i][j]) << " ";
    }

    cout << "|" << endl;
  }

  for (int j = 0; j < SIZE; ++j) {
    cout << " ---";
  }
  cout << endl;
}

char cell_to_string(int cell) { // decide which character should be displayed

  switch (cell) {
  case 1:
    return 'O';
  case 2:
    return '*';
  default:
    return ' ';
  }
}

vector<Point> generate_enemies() {

  srand(time(0));

  vector<Point> enemies;

  while (enemies.size() < NUMBER_OF_ENEMIES) {
    Point enemy;

    // randomly set the positions of the enemies
    enemy.x = rand() % SIZE;
    enemy.y = rand() % SIZE;

    if (is_point_valid(enemies, enemy)) { // checks if the enemy is new
      enemies.push_back(enemy);
    }
  }

  return enemies;
}

bool is_point_valid(vector<Point> points, Point point) {

  for (Point p : points) {
    if (p.x == point.x && p.y == point.y) {
      return false;
    }
  }
  return true;
}

bool enemies_in_a_row(int map[SIZE][SIZE]) {

  int enemy_counter;

  for (int i = 0; i < SIZE; i++) {

    enemy_counter = 0;

    for (int j = 0; j < SIZE; j++) {

      if (map[i][j] == 2) {
        enemy_counter++;
      }
    }

    if (enemy_counter == SIZE) {
      return true;
    }
  }

  return false;
}

Point generate_spaceship(vector<Point> enemies) {

  Point spaceship;

  do {
    spaceship.x = rand() % SIZE;
    spaceship.y = rand() % SIZE;
  } while (!is_point_valid(enemies, spaceship));

  return spaceship;
}


void game_over(){
#ifdef __linux__
  system("clear");
#else
  system("cls");
#endif 


  cout << "---------------------\n";
  cout << "|    GAME OVER!      |\n";
  cout << "|  Better luck next  |\n";
  cout << "|       time!        |\n";
  cout << "---------------------\n";


  getc(stdin);

}
