#include <iostream>
#include <fstream> 
#include <vector>

int incrementCounterTriple(std::string inputFileName)
{
  std::vector<int> data;
  std::string line;
  std::ifstream Input(inputFileName);
  int result = 0; 

  while (std::getline (Input, line)) {
    data.push_back(std::stoi(line));
  }
  Input.close(); 
  
  for(int i = 0;i<data.size()-3;i++)
  {
    if(data[i+3] > data[i])
      result++;
  }
  return result;
}

int main() {
  std::cout << incrementCounterTriple("input.txt") << std::endl;
} 