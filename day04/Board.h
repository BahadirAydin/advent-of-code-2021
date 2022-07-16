#include <iostream>
#include <fstream> 
#include <vector>
#include <math.h>
#include <sstream>
#include <algorithm>
#define BOARD_SIZE 5
class Board{
  public:
    void addRow(std::string &line);
    void show();
    void mark(int);
    bool check();
    int sumAllExceptMarked();
  private:
    int BoardArray[BOARD_SIZE][BOARD_SIZE];
    int current_row = 0;
};

void Board::addRow(std::string &line){
  std::stringstream ss(line);
  std::string tmp;
  int position = 0;

  while(ss >> tmp){
    BoardArray[current_row][position] = std::stoi(tmp);
    position++;
  }
  current_row++;
}
void Board::show(){
  for(int j=0;j<BOARD_SIZE;j++){
    for(int k = 0; k<BOARD_SIZE;k++){
      std::cout << BoardArray[j][k] << " ";
    }
    std::cout << std::endl;
  }
}
void Board::mark(int x){
  for(int i = 0 ; i<BOARD_SIZE;i++){
    for(int j=0; j<BOARD_SIZE;j++){
      if(BoardArray[i][j] == x){
        BoardArray[i][j] = -1;
      }
    }
  }
}
bool Board::check(){
  bool flag1 = true;
  bool flag2 = true;
  for(int i = 0 ; i<BOARD_SIZE;i++){
    flag1 = true;
    flag2 = true;
    for(int j=0; j<BOARD_SIZE;j++){
      if(BoardArray[i][j] != -1)
        flag1 = false;
      if(BoardArray[j][i] != -1)
        flag2 = false;
      if(!flag1 && !flag2)
        break;
    }
    if(flag1 || flag2)
      return true;
  }
  return false;
}
int Board::sumAllExceptMarked(){
  int sum=0;
  for(int i = 0 ; i<BOARD_SIZE;i++){
    for(int j=0; j<BOARD_SIZE;j++){
      if(BoardArray[i][j] != -1)
        sum+= BoardArray[i][j];
    }
  }
  return sum;
}
std::vector<int> inputsToVector(std::string &inputs){
    std::vector<int> vect;
    std::stringstream ss(inputs);
    for (int i; ss >> i;) {
        vect.push_back(i);    
        if (ss.peek() == ',')
            ss.ignore();
    }
    return vect;
}
int winnerChecker(std::vector<Board*> &Boards){

  for(unsigned int i = 0; i<Boards.size();i++){
    if(Boards[i]->check())
      return i;
  }
  return -1;
}
int winnerChecker(std::vector<Board*> &Boards,std::vector<int> &winners){

  bool flag;
  for(unsigned int i = 0; i<Boards.size();i++){
    if(Boards[i]->check()){
      flag = true;
      for(int winner : winners){
        if(winner == i){
          flag = false;
          break;
        }
      }
      if(flag)
        return i;
    }
  }
  return -1;
}
