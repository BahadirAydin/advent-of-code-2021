#include <iostream>
#include <fstream> 
#include <sstream>

int navigator(std::string inputFileName){

  std::string line, inputKey, inputNumberString;
  std::ifstream Input(inputFileName);
  int inputNumber,horizontal=0, depth=0;

  while (std::getline (Input, line)) {
    std::stringstream ss(line);
    ss >> inputKey >> inputNumberString;
    inputNumber = std::stoi(inputNumberString);
    if(inputKey == "forward")
      horizontal += inputNumber;
    else if(inputKey == "up")
      depth -= inputNumber;
    else if(inputKey == "down")
      depth += inputNumber;
    else{
      std::cout << "INVALID" << std::endl;
      return -1;
    }
  }
  Input.close(); 
  return horizontal*depth;
}

int main(){
  std::cout << navigator("input.txt") << std::endl;
  return 0;
}