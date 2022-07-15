#include <iostream>
#include <fstream> 

int incrementCounter(std::string inputFileName)
{
  std::string line;
  std::ifstream Input(inputFileName);
  int previous = -1, current;
  int result = -1; // Result starts from -1 to deal with the first measurement that should not be counted as an increment. (Our while loop increments by 1 in every first line of every valid input.)

  while (std::getline (Input, line)) {
    current = std::stoi(line);
    if(current > previous )
      result++;
    previous = current;  
  }
  Input.close(); 
  return result;
}

int main() {
  std::cout << incrementCounter("input.txt") << std::endl;
} 