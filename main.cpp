#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;


struct Point{ // Point struct to handle the x and y of enemies and spaceship
  int x;
  int y;
};

// defining some settings of the game
const int HEIGHT = 10;
const int WIDTH = 10;
const int NUMBER_OF_ENEMIES = 10;

// functions prototypes
void render(int map[HEIGHT][WIDTH]);
char cell_to_string(int cell);
vector<Point> generate_enemies();
bool is_point_valid(vector<Point> points, Point point);
bool enemies_in_a_row(int map[HEIGHT][WIDTH]);
Point generate_spaceship(vector<Point> enemies);



int main() {

  int map[HEIGHT][WIDTH] = {}; // defining the map array
  do{

    vector<Point> enemies = generate_enemies();

    for (Point enemy : enemies){ // putting enemies on the map
      map[enemy.y][enemy.x] = 2;
    }

    Point spaceship = generate_spaceship(enemies);

    map[spaceship.y][spaceship.x] = 1;

  }while(enemies_in_a_row(map));

  render(map);
}

void render(int map[HEIGHT][WIDTH]) {

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

vector<Point> generate_enemies(){

  srand(time(0));

  vector<Point> enemies;

  while (enemies.size() < NUMBER_OF_ENEMIES){
    Point enemy;
    
    // randomly set the positions of the enemies
    enemy.x = rand() % WIDTH;
    enemy.y = rand() % HEIGHT;

    if (is_point_valid(enemies, enemy)){ // checks if the enemy is new
      enemies.push_back(enemy);
    }

  }

  return enemies;

}

bool is_point_valid(vector<Point> points, Point point){

  for (Point p : points){
    if (p.x == point.x && p.y == point.y){
      return false;
    }
  }
  return true;
}

bool enemies_in_a_row(int map[HEIGHT][WIDTH]){

  int enemy_counter;

  for (int i=0; i < HEIGHT; i++){

    enemy_counter = 0;

    for (int j=0; j < WIDTH; j++){

      if (map[i][j] == 2){
        enemy_counter++;
      }
    }

    if (enemy_counter == WIDTH){
      return true;
    }

  }

  return false;

}

Point generate_spaceship(vector<Point> enemies){

  Point spaceship;

  do{
    spaceship.x = rand() % WIDTH;
    spaceship.y = rand() % HEIGHT;
  }while(!is_point_valid(enemies, spaceship));

  return spaceship;  

}