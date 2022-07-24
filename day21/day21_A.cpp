#include <iostream>
#include <fstream> 
#define START_1 7
#define START_2 1

int rollTheDiceThreeTimes(int dice,int &roll_time){
  dice+=3;
  roll_time +=3;
  if(dice>100)
    dice -= 100;
  return dice;
}
int moveThePlayer(int current_position,int sum){
  int new_position = current_position + sum;
  while(new_position>10)
    new_position-=10;
  return new_position;
}
int day21(){
  int point1=0;
  int point2=0;
  int pos1 = START_1;
  int pos2 = START_2;
  bool turnOfOne=true;
  int dice = 0;
  int roll_time = 0;
  while(point1 < 1000 && point2 < 1000){
    if(turnOfOne){
      dice = rollTheDiceThreeTimes(dice,roll_time);
      int sum = 3*dice-3;
      pos1 = moveThePlayer(pos1,sum);
      point1+=pos1;
      turnOfOne = false;
      if(point1 > 1000)
        break;
    }
    else{
      dice = rollTheDiceThreeTimes(dice,roll_time);
      int sum = 3*dice-3;
      pos2 = moveThePlayer(pos2,sum);
      point2+=pos2;
      turnOfOne = true;     
    }
  }
  return std::min(point1,point2)*roll_time;
}
int main() {
  std::cout << day21() << std::endl;
} 