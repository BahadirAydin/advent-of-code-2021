#include <iostream>
#include <fstream> 
#define START_0 7
#define START_1 1
int moveThePlayer(int current_position,int sum){
  int new_position = current_position + sum;
  while(new_position>10)
    new_position-=10;
  return new_position;
}
void playTheGame(int pos0,int pos1,bool turnOfZero,int point0,int point1,long long int totalCombs,long long int &won0,long long int &won1){ 
  if(point0 >= 21){
    won0 += totalCombs;
    return;
  }
  else if(point1 >= 21){
    won1 += totalCombs;
    return;
  }
  if(turnOfZero){
    for(int i=3;i<=9;i++){
      int newPos = moveThePlayer(pos0,i);
      int newPoint = point0 + newPos;
      int combs;
      if(i==3 || i==9)
        combs = 1;
      else if(i==4 || i==8)
        combs = 3;
      else if(i==5 || i ==7)
        combs = 6;
      else
        combs = 7;
      long long int newCombs = totalCombs*combs;
      turnOfZero = false;
      playTheGame(newPos,pos1,turnOfZero,newPoint,point1,newCombs,won0,won1);
    }
  }
  else{
    for(int i=3;i<=9;i++){
      int newPos = moveThePlayer(pos1,i);
      int newPoint = point1 + newPos;
      int combs;
      if(i==3 || i==9)
        combs = 1;
      else if(i==4 || i==8)
        combs = 3;
      else if(i==5 || i ==7)
        combs = 6;
      else
        combs = 7;
      long long int newCombs = totalCombs * combs;
      turnOfZero = true;
      playTheGame(pos0,newPos,turnOfZero,point0,newPoint,newCombs,won0,won1);
    }
  }
}
long long int day21(){
  int pos0 = START_0;
  int pos1 = START_1;
  bool turnOfZero=true;
  long long int won0=0;
  long long int won1=0;
  int point0=0,point1=0;
  long long int  totalCombs=1;;
  playTheGame(pos0,pos1,turnOfZero,point0,point1,totalCombs,won0,won1);
  return std::max(won0,won1);
}
int main() {
  std::cout << day21() << std::endl;
} 