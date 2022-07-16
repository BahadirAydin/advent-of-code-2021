#include <iostream>
#include <fstream> 
#include <vector>
#include <math.h>

int diagnosticReport(std::string inputFileName){

  std::string line;
  std::vector<int> positions;
  std::ifstream Input(inputFileName);
  int gammaRate=0, epsilonRate=0, line_size;
  // I did not hardcoded the line_size so that my program can work on inputs with different line lengths than the given one.
  while (std::getline (Input, line)) {
    if(positions.empty()){
      line_size = line.size();
      for(int i = 0; i<line_size;i++)
        positions.push_back(0);
    }
    for(int i = 0; i<line_size;i++){
      if(line[i] == '1')
        positions[i] += 1;
      else
        positions[i] -= 1;
    }
  }
  for(std::string::size_type i = 0;i<positions.size();i++){
    if(positions[i] > 0)
      gammaRate += pow(2,line_size-1-i);
  }
  epsilonRate = pow(2,line_size) - 1 - gammaRate;
  Input.close(); 
  return gammaRate*epsilonRate;
}
int main(){
  std::cout << diagnosticReport("input.txt") << std::endl;
  return 0;
}