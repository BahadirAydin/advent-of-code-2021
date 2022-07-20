#include <fstream> 
#include <vector>
#include <algorithm>
#include <iostream>
#include "inputsToVector.h"
#define STEP 40

void addPairs(std::vector<std::string> &names, std::vector<long long int> &count,std::string &name,long long int countToAdd){
  bool flag = true;
  for(unsigned int i = 0;i<names.size();i++){
    if(name == names[i]){
      count[i] += countToAdd;
      flag = false;
      break;
    }
  }
  if(flag){
    names.push_back(name);
    count.push_back(countToAdd);
  }
}
void incrementCharCount(std::vector<long long int> &charCount,std::vector<char> &charNames,char toAdd,long long int incrementCount){
  for(unsigned int i=0; i<charNames.size();i++){
    if(charNames[i] == toAdd){
      charCount[i] += incrementCount;
      return;
    }
  }
  charNames.push_back(toAdd);
  charCount.push_back(incrementCount);
}
char findRule(std::string name,std::vector<std::string> &acceptedConversionNames,std::vector<char> acceptedConversionResults ){
  for(unsigned int i=0;i<acceptedConversionNames.size();i++){
    if(acceptedConversionNames[i] == name)
      return acceptedConversionResults[i];
  }
  return '-';
}
void useRules(std::vector<std::string> &names,std::vector<long long int> &count,std::vector<char> &charNames,std::vector<long long int> &charCount,std::vector<std::string> &acceptedConversionNames,std::vector<char> &acceptedConversionResults){
  
  std::vector<std::string> copy_names(names);
  std::vector<long long int> copy_count(count);
  for(unsigned int i=0; i<copy_names.size();i++){
    char rule = findRule(copy_names[i],acceptedConversionNames,acceptedConversionResults);
    if(rule != '-'){
      long long int toBeAdded = copy_count[i];
      count[i] -= toBeAdded; 
      incrementCharCount(charCount,charNames,rule,toBeAdded);
      std::string newPair;
      newPair += copy_names[i][0];
      newPair += rule;
      addPairs(names,count,newPair,toBeAdded);
      newPair.clear();
      newPair += rule;
      newPair += copy_names[i][1];
      addPairs(names,count,newPair,toBeAdded);
    }
  }

}
long long int ruleImplement(std::string inputFileName){
  std::string line;
  std::ifstream Input(inputFileName);
  std::vector<std::string> acceptedConversionNames;
  std::vector<char> acceptedConversionResults;
  std::vector<std::string> names;
  std::vector<long long int> count;
  std::vector<long long int> charCount;
  std::vector<char> charNames;
 
  std::getline(Input,line);
  for(unsigned int i=0;i<line.size()-1;i++){
    incrementCharCount(charCount,charNames,line[i],1);
    std::string key = line.substr(i,2);
    addPairs(names,count,key,1);
  }
  incrementCharCount(charCount,charNames,line[line.size()-1],1);
  std::getline(Input,line); // to bypass the blank line
  while(std::getline(Input,line)){
    std::pair<std::string,char> x = inputsToRules(line);
    acceptedConversionNames.push_back(x.first);
    acceptedConversionResults.push_back(x.second);
  }  
  for(int i=0;i<STEP;i++){
    useRules(names,count,charNames,charCount,acceptedConversionNames,acceptedConversionResults);
    }
  return *std::max_element(charCount.begin(),charCount.end())-*std::min_element(charCount.begin(),charCount.end());
}
int main(){
  std::cout << ruleImplement("input.txt") << std::endl;
  return 0;
}