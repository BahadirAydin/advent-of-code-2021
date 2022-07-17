#include <fstream> 
#include <algorithm>
#include "inputsToVector.h"
#define SegmentsFor_1 2
#define SegmentsFor_4 4
#define SegmentsFor_7 3
#define SegmentsFor_8 7


// 8 : a,b,c,d,e,f,g

int signalCounter(std::string inputFileName){
  std::string line;
  std::ifstream Input(inputFileName);
  int result = 0;
  while (std::getline (Input, line)){
    std::vector<std::string> outputSignals = inputsToVector_output(line);
    for(std::string curr : outputSignals){
      if(curr.size() == SegmentsFor_1 || curr.size() == SegmentsFor_4 || curr.size() == SegmentsFor_7 || curr.size() == SegmentsFor_8)
        result++;
    }
  }
  return result;
}
int main(){
  std::cout << signalCounter("input.txt") << std::endl;
  return 0;
}
