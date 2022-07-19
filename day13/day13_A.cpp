#include <fstream> 
#include <set>
#include "inputsToVector.h"

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

int fold(std::string inputFileName){
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
  char axis = foldLines[0].first;
  int location = foldLines[0].second;
  foldHelper(axis,location,allPoints);

  return removeDuplicates(allPoints).size();
}
int main(){
  std::cout << fold("input.txt") << std::endl;
  return 0;
}