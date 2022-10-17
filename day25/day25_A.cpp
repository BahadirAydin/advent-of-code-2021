#include <fstream>
#include <iostream>
#include <vector>

typedef std::vector<std::vector<char>> Board;
struct Point {
  int y;
  int x;
};
Board readInput() {

  std::string line;
  std::ifstream Input("input.txt");
  Board result;
  int y_pos = 0;
  while (std::getline(Input, line)) {
    result.push_back(std::vector<char>());
    for (unsigned int x_pos = 0; x_pos < line.size(); x_pos++) {
      result[y_pos].push_back(line[x_pos]); // minus '0' to convert char to string. look at ascii table.
    }
    y_pos++;
  }
  return result;
}
int moveRight(Board &b) {
  std::vector<Point> move;
  int y_size = b.size();
  int x_size = b[0].size();
  for (int i = 0; i < y_size; i++) {
    for (int j = 0; j < x_size; j++) {
      if (b[i][j] == '>' && ((j != x_size - 1 && b[i][j + 1] == '.') || (j == x_size - 1 && b[i][0] == '.'))) {
        Point p;
        p.y = i;
        p.x = j;
        move.push_back(p);
      }
    }
  }
  for (Point p : move) {
    int y = p.y;
    int x = p.x;
    b[y][x] = '.';
    if (x == x_size - 1) {
      b[y][0] = '>';
    } else {
      b[y][x + 1] = '>';
    }
  }
  return move.size();
}
int moveDown(Board &b) {
  std::vector<Point> move;
  int y_size = b.size();
  int x_size = b[0].size();
  for (int i = 0; i < y_size; i++) {
    for (int j = 0; j < x_size; j++) {
      if (b[i][j] == 'v' && ((i != y_size - 1 && b[i + 1][j] == '.') || (i == y_size - 1 && b[0][j] == '.'))) {
        Point p;
        p.y = i;
        p.x = j;
        move.push_back(p);
      }
    }
  }
  for (Point p : move) {
    int y = p.y;
    int x = p.x;
    b[y][x] = '.';
    if (y == y_size - 1) {
      b[0][x] = 'v';
    } else {
      b[y + 1][x] = 'v';
    }
  }
  return move.size();
}
int execute(Board &b) {
  int count = 0;
  int check = 1;
  while (check > 0) {
    check = 0;
    check += moveRight(b);
    check += moveDown(b);
    count++;
  }
  return count;
}
int main() {
  Board arr = readInput(); // Done
  int count = execute(arr);
  std::cout << count << std::endl;
  return 0;
}