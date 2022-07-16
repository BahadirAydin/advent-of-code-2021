#include <iostream>
#include <fstream> 
#include <vector>
#include <math.h>

int lifeSupportRating(std::string inputFileName){

  std::string line;
  std::vector<std::string> allLines,copyAllLines;
  std::ifstream Input(inputFileName);
  int position=0,majority;
  int oxygen_generator_rating,co2_scrubber_rating;
  while (std::getline (Input, line)){

    allLines.push_back(line);
    copyAllLines.push_back(line);
  }
  while(allLines.size() > 1){
    majority = 0;
    for(std::string line : allLines){
      if(line[position] == '1')
        majority +=1;
      else
        majority -=1;
    }
      if(majority >= 0){
        for(std::string::size_type j = 0;j<allLines.size();j++){
          if(allLines[j][position] == '0'){
            allLines.erase(allLines.begin()+j);
            j--; //beware of shifting
          }
        }
      }
      else{
        for(std::string::size_type j = 0;j<allLines.size();j++){
          if(allLines[j][position] == '1'){
            allLines.erase(allLines.begin()+j);
            j--;
          }
        }        
      }
      position++;
    }
  for(std::string::size_type i=0; i<allLines[0].size();i++){
    if(allLines[0][i] == '1')
      oxygen_generator_rating += pow(2,allLines[0].size()-1-i);
  }
  position = 0;
  while(copyAllLines.size() > 1){
    majority = 0;
    for(std::string line : copyAllLines){
      if(line[position] == '1')
        majority +=1;
      else
        majority -=1;
    }
      if(majority >= 0){
        for(std::string::size_type j = 0;j<copyAllLines.size();j++){
          if(copyAllLines[j][position] == '1'){
            copyAllLines.erase(copyAllLines.begin()+j);
            j--;
          }
        }
      }
      else{
        for(std::string::size_type j = 0;j<copyAllLines.size();j++){
          if(copyAllLines[j][position] == '0'){
            copyAllLines.erase(copyAllLines.begin()+j);
            j--;
          }
        }        
      }
      position++;
    }
  for(std::string::size_type i=0; i<copyAllLines[0].size();i++){
    if(copyAllLines[0][i] == '1')
      co2_scrubber_rating += pow(2,copyAllLines[0].size()-1-i);
  }
  //std::cout << oxygen_generator_rating << std::endl;
  return oxygen_generator_rating*co2_scrubber_rating;
}
int main(){
  std::cout << lifeSupportRating("input.txt") << std::endl;
  return 0;
}