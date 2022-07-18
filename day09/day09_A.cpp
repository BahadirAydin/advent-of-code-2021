#include <fstream> 
#include "checkers.h"

int snakeZone(std::string inputFileName){
  std::vector<std::string> lines;
  std::string line;
  std::ifstream Input(inputFileName);
  int sumRiskPoints=0;
  while(std::getline(Input,line))
    lines.push_back(line);
  for(int depth = 0; depth < NUM_LINES; depth++){
    for(int horizontal = 0; horizontal < LINE_LEN; horizontal++ )
      if(checkAll(lines,depth,horizontal))
        sumRiskPoints += lines[depth][horizontal] - '0' + 1;
  }
  return sumRiskPoints;
}
int main(){
  std::cout << snakeZone("input.txt") << std::endl;
  return 0;
}