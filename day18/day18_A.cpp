#include <fstream> 
#include <vector>
#include <algorithm>
#include <iostream> 
#include <stack>
#include <cmath>

typedef std::vector<std::pair<int,int>> vectorOfPairs;
void print(const vectorOfPairs &v ){
  for(std::pair<int,int> pair : v){
    std::cout << pair.first << ", depth: " << pair.second << std::endl;
  }
}
//DONE explode tested. Workıng as expected.
vectorOfPairs explode(const vectorOfPairs &v){
  vectorOfPairs result(v);
  for(unsigned int i=0;i<v.size();i++){
    if(v[i].second == 5){
      if(i==0)
        result[i+2].first += v[i+1].first;
      else if(i == v.size()-2)
        result[i-1].first += v[i].first;
      else{
        result[i-1].first += v[i].first;
        result[i+2].first += v[i+1].first;
      }
     result.erase(result.begin()+i);
     result[i].first = 0;
     result[i].second--;
     break;   
    }
  }
  return result;
}
//DONE addition tested and working as expected.
vectorOfPairs addition(const vectorOfPairs &v1,const vectorOfPairs &v2){
  vectorOfPairs result(v1);
  result.insert(result.end(), v2.begin(), v2.end());
  for(unsigned int i=0; i<result.size();i++)
    result[i].second++;
  return result;
}
//DONE split tested and working as expected.
vectorOfPairs split(const vectorOfPairs &v){
  vectorOfPairs result(v);
  for(unsigned int i=0;i<v.size();i++){
    if(v[i].first > 9){
      float x =v[i].first; // integer division gives wrong results.
      int left = std::floor(x/2);
      int right = std::ceil(x/2);
      int depth = v[i].second+1;
      std::pair<int,int> leftPair(left,depth),rightPair(right,depth);
      result.erase(result.begin()+i);
      result.insert(result.begin()+i,rightPair);
      result.insert(result.begin()+i,leftPair);
      break;
    }
  }
  return result;
}
//DONE doReductions tested and working as expected.
vectorOfPairs doReductions(const vectorOfPairs &v){
  vectorOfPairs result(v);
  while(1){
    vectorOfPairs exploded = explode(result);
    if(result != exploded){
      result = exploded;
      continue;
    }
    vectorOfPairs splitted = split(result);
    if(result == splitted)
      break;
    result = splitted;
  }

  return result;
}
//DONE findMangintude tested and working as expected.
int findMagnitude(vectorOfPairs v){
  while(v.size() != 1){
    for(unsigned int i=0;i<v.size()-1;i++){
      if(v[i].second == v[i+1].second){
        int value = v[i].first*3 + v[i+1].first*2;
        int depth = v[i].second - 1;
        v.erase(v.begin()+i);
        v[i].first = value;
        v[i].second = depth;
        break;
      }
    }
  }
  return v[0].first;
}

int snailfish(std::string inputFileName){
  std::string line;
  std::ifstream Input(inputFileName);
  std::vector<vectorOfPairs> allNumbers;
  while(std::getline(Input,line)){
    vectorOfPairs numbers_and_depth;
    std::stack<char> stack;
    int current_depth = 0;
    for(char x: line){
      if(x == '['){
        stack.push(x);
        current_depth++;
      }
      else if(x == ']'){
        stack.pop();
        current_depth--;
      }
      else if(x == ',')
        continue;
      else
        numbers_and_depth.push_back(std::pair<int,int>(x-'0',current_depth)); // First int is the regular number and the second one is its depth. Abstracting the list.
    }
    allNumbers.push_back(numbers_and_depth);
  }
  vectorOfPairs result(allNumbers[0]);
  for(unsigned int i=0;i<allNumbers.size()-1;i++){
    result = addition(result,allNumbers[i+1]);
    result = doReductions(result);
  }
  return findMagnitude(result);
}
int main(){
  std::cout << snailfish("input.txt") << std::endl;
  return 0;
}