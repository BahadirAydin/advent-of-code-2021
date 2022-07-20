#ifndef INPUTSTOVECTOR_H
#define INPUTSTOVECTOR_H
#include <iostream>
#include <vector>
#include <algorithm>
#endif
#define BIG_INT 2000000

struct Node{
  char data;
  Node* next;
  Node(){next = nullptr;};
};

class LinkedList{
public:
  LinkedList(){ headNode = nullptr;} // default constructor.
  LinkedList(const LinkedList &obj){this->headNode = obj.headNode; this-> charCounts = obj.charCounts; } // copy constructor 
  LinkedList& operator=(const LinkedList& rhs){ this-> ~LinkedList(); this->headNode = rhs.headNode; this->charCounts = rhs.charCounts; return *this; } //assignment operator
  ~LinkedList(){ // destructor to avoid mem leak
    Node* current;
    current = headNode;
    while(current){
      Node *tmp = current;
      current = current -> next;
      delete tmp;
      tmp = nullptr;
    }
  }
  void addNodeToBack(char data){
    Node* newNode = new Node;
    newNode -> data = data;
    if(headNode == nullptr){
      headNode = newNode;
      return;
    }
    Node* curr;
    curr = headNode;
    while(curr->next)
      curr = curr->next;
    curr->next = newNode;
    size++;
  }
  void addNodeBetween(char data, Node* current){
    if(current == nullptr)
      return;
    Node* newNode = new Node;
    newNode -> data = data;
    newNode -> next = current->next;
    current-> next = newNode;
    size++;
  }
  void implementRules(std::vector<std::pair<std::string,char>> &rules){
    Node* current;
    current = headNode;
    while(current && current -> next){
      std::string connected;
      connected += current->data;
      connected += current->next->data;
      char ruleToImplement = '-';
      for(std::pair<std::string,char> rule : rules){
        if(connected == rule.first){
          ruleToImplement = rule.second;
          break;
        }
      }
      if(ruleToImplement != '-'){
        Node* tmp = current;
        current = current-> next;
        addNodeBetween(ruleToImplement,tmp);
      }
      else{
        current = current -> next;
        std::cout << "ZORT" << std::endl;
      }
    }
  }
  void countOccurences(){
    Node* current = headNode;

    while(current){
      char data = current ->data;
      bool flag = true;
      for(unsigned int i=0;i<charCounts.size();i++){
        if(charCounts[i].first == data){
            charCounts[i].second += 1;
            flag = false;
            break;
        }   
      }
      if(flag){
        charCounts.push_back(std::pair<char,long long int>(data,1));
      }
      current = current -> next;
    }
  }
  long long int getMostCommon(){
    long long int max = 0;
    for(std::pair<char,int> pair : charCounts){
      if(pair.second > max)
        max = pair.second;
    }
    return max;
  }
  long long int getLeastCommon(){
    long long int min = BIG_INT;
    for(std::pair<char,int> pair : charCounts){
      if(pair.second < min )
        min = pair.second;
    }
    return min;
  }
  void print(){
    Node* current;
    current = headNode;
    while(current && current->next){
      std::cout << " " << current->data << "->"  ;
      current = current -> next;
    }
    std::cout << std::endl;
    if(current)
      std::cout << "LAST NODE: " << current->data << std::endl;
  }
  void printCounts(){
    for(std::pair<char,long long int> x : charCounts){
      std::cout << x.first << " " << x.second << std::endl;
    }
  }
private:
  Node* headNode;
  std::vector<std::pair<char,long long int>> charCounts;
  long int size=0;
};