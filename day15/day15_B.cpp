#include <fstream> 
#include <vector>
#include <algorithm>
#include <iostream>
#include <queue>
#define SIZE 500
#define INF 10000
//DIJKSTRA'S ALGORITHM 

std::vector<std::pair<int,int>> findNeighbors(int y_pos,int x_pos,bool visited[SIZE][SIZE]){
  std::vector<std::pair<int,int>> neighbors;
  if(x_pos > 0 && visited[y_pos][x_pos-1] == false)
    neighbors.push_back(std::make_pair(y_pos,x_pos-1));
  if(x_pos < SIZE-1 && visited[y_pos][x_pos+1] == false)
    neighbors.push_back(std::make_pair(y_pos,x_pos+1));
  if(y_pos > 0 && visited[y_pos-1][x_pos] == false)
    neighbors.push_back(std::make_pair(y_pos-1,x_pos));
  if(y_pos < SIZE-1 && visited[y_pos+1][x_pos] == false)
    neighbors.push_back(std::make_pair(y_pos+1,x_pos));
  return neighbors;
}
std::pair<int,int> eraseMinElement(std::vector<int> &v1,std::vector<std::pair<int,int>> &v2){
  while (v1.size()) {
    size_t ind = 0;
    for (size_t i = 1; i < v1.size(); i++){
      if (v1[i] < v1[ind]){
        ind = i;
      }
    }
    v1.erase(v1.begin() + ind);
    std::pair<int,int> x(v2[ind]);
    v2.erase(v2.begin() + ind);
    return x;
  }
  return std::pair<int,int>(-1,-1);
}
long int riskPoints(std::string inputFileName){
  std::string line;
  std::ifstream Input(inputFileName);
  int Board[SIZE][SIZE];
  int originalSize = SIZE / 5;
  int BoardSafe[originalSize][originalSize];
  int y_pos = 0;
  while(std::getline(Input,line)){
    for(unsigned int x_pos=0;x_pos<line.size();x_pos++){
      BoardSafe[y_pos][x_pos] = line[x_pos] - '0'; //minus '0' to convert char to string. look at ascii table.
    }
    y_pos++;
  }
  for(int i = 0;i<SIZE;i++){
    for(int j=0;j<SIZE;j++){
      int newData = BoardSafe[i%originalSize][j%originalSize] + i/originalSize + j/originalSize;
      if(newData > 9)
        newData -=9;
      Board[i][j] = newData ;
    }
  }
  bool visited[SIZE][SIZE];
  int distances [SIZE][SIZE];
  for(int i=0;i<SIZE;i++){
    for(int j=0;j<SIZE;j++){
      distances[i][j] = INF;
      visited[i][j] = false;
    }
  }
  distances[0][0] = 0;
  std::vector<int> distancesOfNeighbors; // I got frustrated with std::priority_queue
  std::vector<std::pair<int,int>> coordinates;
  std::pair<int,int> curr(0,0);
  while(!visited[SIZE-1][SIZE-1]){
    //std::cout << "VISITING:" << curr.first << " " << curr.second <<  " DISTANCE" << distances[curr.first][curr.second] << std::endl;
    visited[curr.first][curr.second] = true;
    std::vector<std::pair<int,int>> neighbors = findNeighbors(curr.first,curr.second,visited);
    for(std::pair<int,int> pair : neighbors){
      int newDistance = distances[curr.first][curr.second] + Board[pair.first][pair.second];
      if(newDistance < distances[pair.first][pair.second])
        distances[pair.first][pair.second] = newDistance;
      distancesOfNeighbors.push_back(distances[pair.first][pair.second]);
      coordinates.push_back(std::make_pair(pair.first,pair.second));
    }
    if(curr.first == SIZE-1 && curr.second == SIZE-1)
      break;
    while(visited[curr.first][curr.second]){
      std::pair<int,int> newCoords = eraseMinElement(distancesOfNeighbors,coordinates);
      curr.first = newCoords.first;
      curr.second = newCoords.second;
    }
  }
  return distances[SIZE-1][SIZE-1];
}
int main(){
  std::cout << riskPoints("input.txt") << std::endl;
  return 0;
}