#include <iostream>
#include <fstream>
#include <vector> 
#include <cmath>
#define SIZE 100
#define STEP 50
#define DARK false
#define LIGHT true
typedef std::vector<std::vector<bool>> doubleVec;
doubleVec inspectPoint(const doubleVec &image,int y,int x,int step){
  //returns a 3x3 area
  doubleVec result;
  for (int i : {-1, 0, 1}){
    std::vector<bool> v;
    for (int j : {-1, 0, 1}){
      int ypos = y+i;
      int xpos = x+j;
      if(xpos >= 0 && xpos < image.size() && ypos >=0 && ypos < image.size())
        v.push_back(image[ypos][xpos]);
      else{
        if(step%2==0)
          v.push_back(DARK);
        else
          v.push_back(LIGHT);
      }
    }
    result.push_back(v);
  }  
  return result;
}
void print(const doubleVec &v){
  for(std::vector<bool> v0 : v){
    for(bool i  : v0){
      std::cout << i;
    }
    std::cout << std::endl;
  }
}
doubleVec createImage(std::ifstream &input){
  std::string line;
  std::vector<bool> emptyLine(SIZE+120,false);
  doubleVec result;
  for(int i=0;i<60;i++)
    result.push_back(emptyLine);
  
  std::getline(input,line);
  while(std::getline(input,line)){
    std::vector<bool> v;
    for(int i=0;i<60;i++) 
      v.push_back(0);
    for(char c : line){
      if(c == '#')
        v.push_back(LIGHT);
      else
        v.push_back(DARK);
    }
    for(int i=0;i<60;i++) 
      v.push_back(0);
    result.push_back(v);
  }
  for(int i=0;i<60;i++)
    result.push_back(emptyLine);

  return result;
}
int isLit(const doubleVec &area,const std::string conversionStr){

  int result=0;
  int exp = 8;
  for(int i=0;i<3;i++){
    for(int j=0;j<3;j++){
      result += pow(2,exp)*area[i][j];
      exp--;
    }
  }
  if(conversionStr[result] == '#')
    return 1;
  return 0;
}
doubleVec createOutputImage(doubleVec &image,const std::string &conversionStr,int step){
  doubleVec result;
  for(unsigned int y=0;y<image.size();y++){
    std::vector<bool> v;
    for(unsigned x=0;x<image.size();x++){
      doubleVec inspectionArea = inspectPoint(image,y,x,step);
      v.push_back(isLit(inspectionArea,conversionStr));
    }
    result.push_back(v);
  }
  step++;
  return result;
}
int countLit(const doubleVec &image){
  int count=0;
  for(std::vector<bool> v : image){
    for(bool i:v){
      if(i==true)
        count++;
    }
  }
  return count;
}

int day20(){
  std::ifstream Input("input.txt");
  std::string conversionStr;
  std::getline(Input,conversionStr);
  doubleVec image = createImage(Input);
  for(int i=0;i<STEP;i++)
    image = createOutputImage(image,conversionStr,i);
  return countLit(image);
}
int main() {
  std::cout << day20() << std::endl;
} 