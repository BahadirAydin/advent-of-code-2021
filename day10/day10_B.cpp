#include <fstream> 
#include <vector>
#include <iostream>
#include <stack>
#include <algorithm>
#define PTS_ROUND 1
#define PTS_SQUARE 2
#define PTS_CURLY 3
#define PTS_POINTER 4
int match(char x){
  if(x=='(')
    return PTS_ROUND;
  else if(x=='[')
    return PTS_SQUARE;
  else if(x=='{')
    return PTS_CURLY;
  else
    return PTS_POINTER;
}
int checkMatchings(char x,char stack_char){
  if(stack_char == '(' && x != ')') return 1;
  else if(stack_char== '[' && x != ']') return 1;
  else if(stack_char== '{' && x != '}') return 1;
  else if(stack_char== '<' && x != '>') return 1;
  return 0;
}
long int syntaxCheck(std::string inputFileName){
  std::string line;
  std::ifstream Input(inputFileName);
  std::vector<long int> autocompleteScores;
  while(std::getline(Input,line)){
    std::stack<char> stack;
    bool flag =true;
    for(char curr : line){
      if(curr == '(' || curr == '[' || curr == '{' || curr == '<')
        stack.push(curr);
      else{
        int errorPoint = checkMatchings(curr,stack.top());
        if(errorPoint > 0){
          flag = false;
          break; //Discard errorenous lines.
        }
        stack.pop();
      }
    }
    if(flag){
      long int sum = 0;
      while(!stack.empty()){
        long int point = match(stack.top());
        sum = sum*5 + point;
        stack.pop();
      }
      autocompleteScores.push_back(sum);
    }
  }
  std::sort(autocompleteScores.begin(),autocompleteScores.end());
  return autocompleteScores[autocompleteScores.size()/2];
}
int main(){
  std::cout << syntaxCheck("input.txt") << std::endl;
  return 0;
}