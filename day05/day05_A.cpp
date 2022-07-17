#include <fstream> 
#include <algorithm>
#include "inputsToVector.h"

int hydrothermalVents(std::string inputFileName){
  int result=0;
  int ventDiagram[1000][1000] = {0}; // since all the numbers are guaranteed to be 3 digit numbers.
  std::string line;
  std::ifstream Input(inputFileName);
  while (std::getline (Input, line)){
    std::vector<int> coordinates = inputsToVector(line);
    int x1 = coordinates[0];
    int y1 = coordinates[1];
    int x2 = coordinates[2];
    int y2 = coordinates[3];
    int less;
    if(x1 == x2){
      if(y1>y2)
        less = y2;
      else
        less = y1;
      for(int i=0;i<std::abs(y1-y2)+1;i++){
        if(ventDiagram[x1][less+i] == 1)
          result++;
        ventDiagram[x1][less+i]++;
      }
    }
    else if(y1 == y2){
      if(x1>x2)
        less = x2;
      else
        less = x1;
      for(int i=0;i<std::abs(x1-x2)+1;i++){
        if(ventDiagram[less+i][y1] == 1)
          result++;
        ventDiagram[less+i][y1]++;
      }
    }
  }
  return result;
}
int main(){
  std::cout << hydrothermalVents("input.txt") << std::endl;
  return 0;
}