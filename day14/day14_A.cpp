#include <fstream> 
#include <vector>
#include <iostream>
#include "inputsToVector.h"
#include "LinkedList.h"
#define STEP 10
//Naive Approach with Linked List (Not usable in big steps because of exponential growth)
// IMPORTANT!!! LOOK AT PART B FOR BETTER APPROACH IN TERMS OF TIME AND MEMORY.

int ruleImplement(std::string inputFileName){
  std::string line;
  std::ifstream Input(inputFileName);
  LinkedList list;
  std::vector<std::pair<std::string,char>> rules;

  std::getline(Input,line);
  for(char x : line){ list.addNodeToBack(x); }
  std::getline(Input,line); // to bypass the blank line
  while(std::getline(Input,line))
    rules.push_back(inputsToRules(line));
  for(int i=0;i<STEP;i++){
    std::cout << "STEP " << i+1 << std::endl;
    list.implementRules(rules);
  }
  //list.print()
  //list.printCounts();
  list.countOccurences();
  return list.getMostCommon()-list.getLeastCommon();
}
int main(){
  std::cout << ruleImplement("input.txt") << std::endl;
  return 0;
}