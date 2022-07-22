#include <fstream> 
#include <vector>
#include <algorithm>
#include <iostream>
#define UPPER_X 155
#define LOWER_X 135
#define UPPER_Y -78
#define LOWER_Y -102
typedef std::pair<std::pair<int,int>,std::pair<int,int>> pairOfPairs;
typedef std::pair<int,int> intPair;

pairOfPairs step(int initialVX , int initialVY, int xPos,int yPos){
  intPair newCoordinates(xPos+initialVX,yPos+initialVY);
  if(initialVX < 0) initialVX++;
  else if(initialVX >0) initialVX--;
  initialVY--;
  intPair newVelocities(initialVX,initialVY);
  return pairOfPairs(newVelocities,newCoordinates);
}
bool inZone(int x,int y){
  if(x <= UPPER_X && x >= LOWER_X && y <= UPPER_Y && y >= LOWER_Y)
    return true;
  return false;
}
int simulate(){
  int sum = 0;
  for(int i = -200; i < 200; i++){
    for(int j = -200; j < 200; j++){
      int x=0,y=0,vx=i,vy=j;
      if(vx > UPPER_X || vy < LOWER_Y)
        continue;
      while(1){
        pairOfPairs newData = step(vx,vy,x,y);
        intPair v(newData.first);
        intPair pos(newData.second);
        x=pos.first; y=pos.second;
        vx=v.first; vy=v.second;
        if(inZone(x,y)){
          sum++;
          break;
        }
        else if((y < LOWER_Y && vy <= 0) || (x > UPPER_X && vx >= 0) || (x < LOWER_X && vx <= 0)){
          break;
        }
      }
    }
  }
  return sum;
}
int main(){
  std::cout << simulate() << std::endl;
  return 0;
}