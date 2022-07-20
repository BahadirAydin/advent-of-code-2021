#include <fstream> 
#include <set>
#include "inputsToVector.h"
#include <algorithm>

void foldHelper(char axis, int location,std::vector<std::pair<int,int>> &points){
  if(axis == 'x'){
   for(unsigned int i=0;i<points.size();i++){
    int diff = points[i].first - location;
    if(diff > 0)
      points[i].first = location - diff;
    }   
  }
  else if(axis == 'y'){
   for(unsigned int i=0;i<points.size();i++){
    int diff = points[i].second - location;
    if(diff > 0)
      points[i].second = location - diff;
    }   
  }
}
std::set<std::pair<int,int>> removeDuplicates(std::vector<std::pair<int,int>> &points){
  std::set<std::pair<int,int>> result;
  unsigned size = points.size();
  for( unsigned i = 0; i < size; ++i ) result.insert( points[i] );
  points.assign(result.begin(), result.end());
  return result;
}
void fold(std::string inputFileName){
  std::string line;
  std::ifstream Input(inputFileName);
  std::vector<std::pair<int,int>> allPoints;
  std::vector<std::pair<char,int>> foldLines;
  while(std::getline(Input,line)){
    if(line[0] != 'f' && line.size() > 0) // line.size() check to account for blank lines.
      allPoints.push_back(inputsToPairXY(line)); // xy coordinates
    else if(line[0] == 'f')
      foldLines.push_back(inputsToPair(line)); // first position holds the axis and the corresponding line location.
  }
  for(std::pair<char,int> foldLine : foldLines){
    char axis = foldLine.first;
    int location = foldLine.second;    
    foldHelper(axis,location,allPoints);
    std::set<std::pair<int,int>> result = removeDuplicates(allPoints);
    int max=0;
    for(std::pair<int,int> pair : result){
      if(pair.first > max) max = pair.first;
      if(pair.second > max) max = pair.second;
    }
    if(location == 6){ // Last input. Hardcoded. Does not necessary.
      for(int i = 0; i< max+1; i++){ 
        for(int j=0; j<max+1;j++){
          if(std::find(result.begin(),result.end(),std::pair<int,int>(j,i)) != result.end())
            std::cout << "#";
          else
            std::cout << "-";
        }
        std::cout << std::endl;
      }
    }
  }
}
int main(){
  fold("input.txt");
  return 0;
}