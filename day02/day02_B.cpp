#include <iostream>
#include <fstream> 
#include <sstream>

int depthNavigator(std::string inputFileName){

  std::string line, inputKey, inputNumberString;
  std::ifstream Input(inputFileName);
  int inputNumber,horizontal=0, depth=0,aim=0;

  while (std::getline (Input, line)) {
    std::stringstream ss(line);
    ss >> inputKey >> inputNumberString;
    inputNumber = std::stoi(inputNumberString);
    if(inputKey == "forward"){
      horizontal += inputNumber;
      depth += inputNumber*aim;
    }
    else if(inputKey == "up")
      aim -= inputNumber;
    else if(inputKey == "down")
      aim += inputNumber;
    else{
      std::cout << "INVALID" << std::endl;
      return -1;
    }
  }
  Input.close(); 
  return horizontal*depth;
}

int main(){
  std::cout << depthNavigator("input.txt") << std::endl;
  return 0;
}