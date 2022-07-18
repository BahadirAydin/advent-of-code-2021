#include <fstream> 
#include <algorithm>
#include "checkers.h"

void checkBasins(std::vector<std::string> &lines,int depth,int horizontal,std::vector<std::pair<int,int>> &vect){
  std::pair<int,int> current(depth,horizontal);
  if(std::find(vect.begin(), vect.end(), current) != vect.end())
    return;
  vect.push_back(current);
  for(int i = horizontal+1;i<LINE_LEN;i++){
    if(lines[depth][i]-'0' == 9)
      break;;
    checkBasins(lines,depth,i,vect);
  }
  for(int i = horizontal-1;0<=i;i--){
    if(lines[depth][i]-'0' == 9 )
      break;
    checkBasins(lines,depth,i,vect);
  }
  for(int i = depth+1;i<NUM_LINES;i++){
    if(lines[i][horizontal]-'0' == 9 )
      break;
    checkBasins(lines,i,horizontal,vect);
  }
  for(int i = depth-1;0<=i;i--){
    if(lines[i][horizontal]-'0' == 9 )
      break;
    checkBasins(lines,i,horizontal,vect);
  }
}
int snakeZone(std::string inputFileName){
  std::vector<std::string> lines;
  std::string line;
  std::ifstream Input(inputFileName);
  long unsigned int basinSizes[3] = {0};
  while(std::getline(Input,line))
    lines.push_back(line);
  for(int depth = 0; depth < NUM_LINES; depth++){
    for(int horizontal = 0; horizontal < LINE_LEN; horizontal++ ){
      if(checkAll(lines,depth,horizontal)){
        std::vector<std::pair<int,int>> basinCoordinates;
        checkBasins(lines,depth,horizontal,basinCoordinates);
        if(basinCoordinates.size() > basinSizes[0]){
          int tmp = basinSizes[0], tmp_2 = basinSizes[1];
          basinSizes[0] = basinCoordinates.size();
          basinSizes[1] = tmp;
          basinSizes[2] = tmp_2;
        }
        else if(basinCoordinates.size() > basinSizes[1]){
          int tmp = basinSizes[1];
          basinSizes[1] = basinCoordinates.size();
          basinSizes[2] = tmp;
        }
        else if(basinCoordinates.size() > basinSizes[2])
          basinSizes[2] = basinCoordinates.size();
      }
    }
  }
  return basinSizes[0]*basinSizes[1]*basinSizes[2];
}
int main(){
  std::cout << snakeZone("input.txt") << std::endl;
  return 0;
}
