#include <iostream>
#include <vector>
#include <tuple>
#include <string>
//This is far from optimal way to read the input but I don't think its important at this point and its always a mess breaking up the inputs ->
// so I just used whatever comes to my mind.
typedef std::pair<int,int> pair;
struct Cube{
  pair x_coords = std::make_pair(0,0);
  pair y_coords = std::make_pair(0,0);
  pair z_coords = std::make_pair(0,0);
  bool status = false;
};
int readNum(std::string &sliced, bool last){
  int track = 0;
  bool negative = false;
  if(sliced[track] == '-'){
    negative = true;
    track++;
  }
  while(sliced[track] != '.' && sliced[track] != ',')
    track++;
  int len;
  if(negative)
    len = track -1;
  else
    len = track;
  int start = 0;
  if(negative)
    start = 1;
  else
    start = 0;
  int num = std::stoi(sliced.substr(start,len));
  if(negative)
    num = -1*num;
  if(last)
    return num;
  sliced = sliced.substr(start+len+2,sliced.length()-start-len-2);
  if(sliced[0] == '=')
    sliced = sliced.substr(1,sliced.length()-1);
  return num;
}
Cube read_input(std::string &input){
    
  Cube result;
  int pos;
  if(input[1] == 'n'){
    result.status = true;
    pos = 5;
  }
  else{
    result.status = false;
    pos = 6;
  }
  std::string sliced = input.substr(pos,input.length()-pos);
  int x1 = readNum(sliced,false);
  int x2 = readNum(sliced,false);
  result.x_coords = std::make_pair(x1,x2);
  int y1 = readNum(sliced,false);
  int y2 = readNum(sliced,false);
  result.y_coords = std::make_pair(y1,y2);
  int z1 = readNum(sliced,false);
  int z2 = readNum(sliced,true);
  result.z_coords = std::make_pair(z1,z2);
  return result;
}