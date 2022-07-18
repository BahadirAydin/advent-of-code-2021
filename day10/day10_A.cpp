#include <fstream> 
#include <vector>
#include <iostream>
#include <stack>
#define PTS_ROUND 3
#define PTS_SQUARE 57
#define PTS_CURLY 1197
#define PTS_POINTER 25137

int match(char x){
  if(x==')')
    return PTS_ROUND;
  else if(x==']')
    return PTS_SQUARE;
  else if(x=='}')
    return PTS_CURLY;
  else
    return PTS_POINTER;
}
int checkMatchings(char x,char stack_char){
  if(stack_char == '(' && x != ')') return match(x);
  else if(stack_char== '[' && x != ']') return match(x);
  else if(stack_char== '{' && x != '}') return match(x);
  else if(stack_char== '<' && x != '>') return match(x);
  return 0;
}
int syntaxCheck(std::string inputFileName){
  std::stack<char> stack;
  std::string line;
  std::ifstream Input(inputFileName);
  int errorPointSum=0;
  while(std::getline(Input,line)){
    for(char curr : line){
      if(curr == '(' || curr == '[' || curr == '{' || curr == '<')
        stack.push(curr);
      else{
        int errorPoint = checkMatchings(curr,stack.top());
        if(!errorPoint)
          stack.pop();
        else{
          errorPointSum += errorPoint;
          break;
        }
      }
    }
  }
  return errorPointSum;
}
int main(){
  std::cout << syntaxCheck("input.txt") << std::endl;
  return 0;
}