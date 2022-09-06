#include <fstream> 
#include <algorithm>
#include "read_input.h"

std::vector<Cube> getData(std::string inputFileName){
  
  std::vector<Cube> cubes;
  std::string line;
  std::ifstream Input(inputFileName);
  while(std::getline(Input,line))
    cubes.push_back(read_input(line));
  return cubes;
}
pair comparePairs(const pair &p1, const pair &p2){
  if(p1.second >= p2.first && p2.second >= p1.second){
    if(p2.first >= p1.first)
      return pair(p2.first,p1.second);
    else
      return pair(p1.first,p1.second);
  }
  else if(p2.second >= p1.first && p1.second >= p2.second){
    if(p1.first >= p2.first)
      return pair(p1.first,p2.second);
    else
      return pair(p2.first,p2.second);
  }

  else if(p1.first >= p2.first && p2.second >= p1.first){
    if(p1.second >= p2.second)
      return pair(p1.first,p2.second);
    else
      return pair(p1.first,p1.second);
  }
  else if(p2.first >= p1.first && p1.second >= p2.first){
    if(p2.second >= p1.second)
      return pair(p2.first,p1.second);
    else
      return pair(p2.first,p2.second);
  }
  else
    return pair(-1,-1);
}
Cube compareCubes(const Cube &c1, const Cube &c2){
  Cube result;
  pair c1_x = c1.x_coords;
  pair c2_x = c2.x_coords;
  pair c1_y = c1.y_coords;
  pair c2_y = c2.y_coords;
  pair c1_z = c1.z_coords;
  pair c2_z = c2.z_coords;

  pair compare_x = comparePairs(c1_x,c2_x);
  pair compare_y = comparePairs(c1_y,c2_y);
  pair compare_z = comparePairs(c1_z,c2_z);
  pair _def = std::make_pair(-1,-1);
  if(compare_x == _def || compare_y == _def || compare_z == _def)
    return Cube();
  result.x_coords = compare_x;
  result.y_coords = compare_y;
  result.z_coords = compare_z;
  return result;
}
void printCube(const Cube &c){
  pair x = c.x_coords;
  pair y = c.y_coords;
  pair z = c.z_coords;
  std::cout << "X: (" << x.first << "," << x.second << ") Y: (" << y.first << "," << y.second <<  ") Z: (" << z.first << "," << z.second << ") " << std::endl;
  std::cout << "STATUS: " << c.status << std::endl;
}
long int calculateVolume(const Cube &cube){
  long x = abs(cube.x_coords.first-cube.x_coords.second)+1;
  long y = abs(cube.y_coords.first-cube.y_coords.second)+1;
  long z = abs(cube.z_coords.first-cube.z_coords.second)+1;
  return x*y*z;
}
long long int calculateSum(const std::vector<std::pair<Cube,int>> &v){
  long long int sum=0;
  for(int i = 0;i < v.size();i++){
    long long int volume = calculateVolume(v[i].first)*v[i].second;
    sum += volume;
  }
  return sum;
}
long long int day22(){
  std::vector<Cube> cubes= getData("input.txt");
  std::vector<std::pair<Cube,int>> addedCubes;
  int limit = cubes.size();
  for(int i=0;i<limit;i++){
    Cube currentCube = cubes[i];
    if(addedCubes.empty()){
      if(currentCube.status)
        addedCubes.push_back(std::make_pair(currentCube,1));
    }
    else{
      int comparisons = addedCubes.size();
      if(currentCube.status)
        addedCubes.push_back({currentCube,1});
      for(int j=0;j<comparisons;j++){
        std::pair<Cube,int> cubePair = addedCubes[j];
        Cube compared = compareCubes(currentCube,cubePair.first);
        if(calculateVolume(compared) == 1)
          continue;
        bool cubePairStatus;
        if(cubePair.second == 1)
          cubePairStatus = true;
        else
          cubePairStatus = false;
        if(currentCube.status && cubePairStatus)
          addedCubes.push_back({compared,-1});
        else if(!currentCube.status && cubePairStatus)
          addedCubes.push_back({compared,-1});
        else if(!currentCube.status && !cubePairStatus)
          addedCubes.push_back({compared,1});
        else
          addedCubes.push_back({compared,1});
      }
    }
  }
  return calculateSum(addedCubes);
}
int main() {
  std::cout << day22() << std::endl;
  return 0;
} 