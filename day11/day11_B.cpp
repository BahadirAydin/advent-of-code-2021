#include <fstream> 
#include <vector>
#include <iostream>
#define BOARD_SIZE 10

void flash(int Board[BOARD_SIZE][BOARD_SIZE],int y_pos,int x_pos,int &flashes){
  if(Board[y_pos][x_pos] == 0)
    return;
  std::vector<std::pair<int,int>> positions =
   {std::pair<int,int>(y_pos+1,x_pos),
    std::pair<int,int>(y_pos+1,x_pos+1),                                 
    std::pair<int,int>(y_pos,x_pos+1), 
    std::pair<int,int>(y_pos-1,x_pos+1),
    std::pair<int,int>(y_pos-1,x_pos),
    std::pair<int,int>(y_pos-1,x_pos-1),
    std::pair<int,int>(y_pos,x_pos-1),
    std::pair<int,int>(y_pos+1,x_pos-1),                    
  };
  for(std::pair<int,int> curr : positions){
    if(curr.first >= 0 && curr.second >= 0 && curr.first < BOARD_SIZE && curr.second < BOARD_SIZE){
      if(Board[curr.first][curr.second] == 9){
        flashes++;
        Board[curr.first][curr.second] = -1; //I used -1 to show that a point has flashed in that particular turn. After the turn I will convert them to 0s.
        flash(Board,curr.first,curr.second,flashes);
      }
      else if(Board[curr.first][curr.second] > -1)
        Board[curr.first][curr.second]++;
    }
  }
}

int octopusFlash(std::string inputFileName){
  int Board[BOARD_SIZE][BOARD_SIZE];
  std::string line;
  std::ifstream Input(inputFileName);
  int y_pos=0;
  while(std::getline(Input,line)){
    int x_pos=0;
    for(char x : line){
      Board[y_pos][x_pos] = x - '0';
      x_pos++;
    }
    y_pos++;
  }
  int step = 0;
  while(1)
  {
    step++;
    int flashes = 0;
    for(int i = 0;i<BOARD_SIZE;i++){
      for(int j=0;j<BOARD_SIZE;j++){
        if(Board[i][j] == 9){
          Board[i][j] = -1;
          flashes++;
          flash(Board,i,j,flashes);
        }
        else if(Board[i][j] > -1)
          Board[i][j]++;
      }
    }
    for(int i = 0;i<BOARD_SIZE;i++){
      for(int j=0;j<BOARD_SIZE;j++){
        if(Board[i][j] == -1)
          Board[i][j] = 0;
      }
    }
    if(flashes == 100)
      return step;
  }
  return -1;
}
int main(){
  std::cout << octopusFlash("input.txt") << std::endl;
  return 0;
}