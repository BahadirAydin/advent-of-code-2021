#include <fstream> 
#include <algorithm>
#include "inputsToVector.h"
int calculateFuel(std::vector<int> &positions,int &finalPos){
  int sum = 0;
  int n;
  for(int pos : positions){
    n = abs(finalPos-pos);
    sum+= n*(n+1)/2;
  }
  return sum;
}
int minFuel(std::string inputFileName){
  std::string line;
  std::ifstream Input(inputFileName);
  std::getline (Input, line);
  std::vector<int> positions = inputsToVector(line);
  int leftEnd=*std::min_element(positions.begin(), positions.end()),rightEnd=*std::max_element(positions.begin(), positions.end());
  while(abs(leftEnd-rightEnd)>1){
    int middle = (leftEnd+rightEnd)/2;
    int leftCalc = calculateFuel(positions,leftEnd);
    int rightCalc = calculateFuel(positions,rightEnd);
    int middleCalc = calculateFuel(positions,middle);
    if(leftCalc < middleCalc || rightCalc > leftCalc)
      rightEnd = middle;
    else if(rightCalc < middleCalc || leftCalc > middleCalc)
      leftEnd = middle;
    else
      return calculateFuel(positions,middle);
  }
  return std::min(calculateFuel(positions,leftEnd),calculateFuel(positions,rightEnd));
}
int main(){
  std::cout << minFuel("input.txt") << std::endl;
  return 0;
}
