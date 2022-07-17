#include <fstream> 
#include <algorithm>
#include <cmath>
#include "inputsToVector.h"
#define SegmentsFor_1 2
#define SegmentsFor_4 4
#define SegmentsFor_7 3
#define SegmentsFor_8 7


// 8 : a,b,c,d,e,f,g

bool checkIfCharInStr(char x,std::string &str){
  for(char a : str){
    if(a == x) return true;
  }
  return false;
}

int signalCounter(std::string inputFileName){
  std::string line;
  std::ifstream Input(inputFileName);
  std::pair<char,char> CandF,BandD;
  int sum = 0;
  while (std::getline (Input, line)){
    std::vector<std::string> mixedSignals = inputsToVector_signals(line);
    std::vector<std::string> outputSignals = inputsToVector_output(line);
    for(std::string curr : mixedSignals){
      if(curr.size() == SegmentsFor_1){
        CandF.first = curr[0];
        CandF.second = curr[1];
        break;
      }
    }
    for(std::string curr : mixedSignals){
      if(curr.size() == SegmentsFor_4){
        for(char x : curr){
          if(CandF.first != x && CandF.second != x){BandD.first = x; break;}
        } 
        for(char x : curr){
          if(CandF.first != x && CandF.second != x && BandD.first != x){BandD.second = x; break;}
        }
        break;
      }
    }

    int exponent = 3,decodedInt=0;
    for(std::string curr: outputSignals){
      if(curr.size() == SegmentsFor_1)
        decodedInt += pow(10,exponent)*1; //Found 1
      else if(curr.size() == 5){ // 2,3,5
        if(checkIfCharInStr(CandF.first,curr) && checkIfCharInStr(CandF.second,curr))
          decodedInt += pow(10,exponent)*3; // Found 3
        else if(checkIfCharInStr(BandD.first,curr) && checkIfCharInStr(BandD.second,curr)) 
          decodedInt += pow(10,exponent)*5; // Found 5
        else
          decodedInt += pow(10,exponent)*2; // Found 2
      }
      else if(curr.size() == SegmentsFor_4)
        decodedInt += pow(10,exponent)*4; //Found 4
      else if(curr.size() == SegmentsFor_7)
        decodedInt += pow(10,exponent)*7; //Found 7
      else if(curr.size() == SegmentsFor_8)
        decodedInt += pow(10,exponent)*8; //Found 8
      else{ //0,6,9
        if(!checkIfCharInStr(BandD.first,curr) || !checkIfCharInStr(BandD.second,curr))
          ; //Found 0;
        else if(checkIfCharInStr(CandF.first,curr) && checkIfCharInStr(CandF.second,curr))
        decodedInt += pow(10,exponent)*9; //Found 9
        else
          decodedInt += pow(10,exponent)*6; //Found 6
      }
      exponent--;
    }
    sum += decodedInt;
  }
  return sum;
}
int main(){
  std::cout << signalCounter("input.txt") << std::endl;
  return 0;
}
