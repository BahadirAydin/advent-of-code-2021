#include <fstream> 
#include "inputsToVector.h"
#define TOTAL_DAYS 80

unsigned long long int lanternfishNumber(std::string inputFileName){
  std::string line;
  std::ifstream Input(inputFileName);
  std::getline (Input, line);
  int daysPassed=0;
  std::vector<int> initialState = inputsToVector(line);
  unsigned long long int numbers[9] = {0};
  for(int lanternship : initialState)
    numbers[lanternship]++;
  while(daysPassed<TOTAL_DAYS){
    unsigned long long int newBorn = numbers[0];
    for(int i = 0;i<8;i++)
      numbers[i] = numbers[i+1];
    numbers[8] = newBorn;
    numbers[6] += newBorn;
    daysPassed++;
  }
  unsigned long long int sum=0;
  for(long long int x : numbers){
    sum += x;
  }  
  return sum;
}
int main(){
  std::cout << lanternfishNumber("input.txt") << std::endl;
  return 0;
}