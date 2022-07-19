#ifndef GRAPH_H
#define GRAPH_H
#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#endif

class Vertex{
  
public:
  Vertex(std::string &name,bool isBig){
    this -> name = name;
    this -> isBig = isBig;
  }
  void addEdge(Vertex *v){ //since there is no errorenous inputs no need to check if the edge is already in the list.
    adjacencyList.push_back(v);}
  std::string& getName(){return name;}
  bool getisBig(){return isBig;}
  std::vector<Vertex*> &getAdjacencyList(){return adjacencyList;}
  
  void print(){
    std::cout << "EDGE NAME: " << name ;
    if(isBig)
      std::cout << "(BIG CAVE)";
    std::cout << std::endl;
    std::cout << "The list of the caves connected: " << std::endl;
    for(Vertex* v : adjacencyList)
      std::cout << v->getName() << " ";
    std::cout << std::endl;
  }
private:
  std::string name;
  bool isBig;
  std::vector<Vertex*> adjacencyList;
};

class Graph{

public:
  Graph(){};
  Graph(const Graph &obj){
    for(Vertex* v : obj.vertices){
      Vertex* newVertex = new Vertex(v->getName(),v->getisBig());
      this->vertices.push_back(newVertex);
    }
  }
  Graph& operator=(const Graph& rhs){
    this -> ~Graph();
    for(Vertex *v : rhs.vertices){
      Vertex* newVertex = new Vertex(v->getName(),v->getisBig());
      this->vertices.push_back(newVertex);
    }
    return *this;
  }
  ~Graph(){
    for(Vertex* v : vertices){
      delete v;
    }
  }
  bool addVertex(std::string &vertexName,bool isBig){
    for(Vertex* v : vertices){
      if(v->getName() == vertexName)
        return false;
    }
    Vertex* newVertex = new Vertex(vertexName,isBig);
    this->vertices.push_back(newVertex);
    if(vertexName == "start")
      startNode = newVertex;
    return true;
  };
  void addEdge(std::string &from,std::string &to){
    if(to == "start" || from == "end"){return;}
    Vertex* startVertex;
    Vertex* endVertex;
    for(Vertex* v : vertices){
      if(v->getName() == from){
        startVertex = v;
      }
      if(v->getName() == to){
        endVertex = v;
      }
    }
    startVertex -> addEdge(endVertex);     
  }
  void findAllPaths(char part){
    std::vector<std::string> currentPath;
    if(part == 'A')
      findAllPathsUtilPartA(startNode,paths,currentPath);
    if(part == 'B'){
      for(Vertex* v : vertices){
        if(!v->getisBig() && v->getName() != "start" && v->getName() != "end"){
          int timesUsed = 0;
          findAllPathsUtilPartB(startNode,paths,currentPath,v->getName(),timesUsed);
        }
      }
    }
  unsigned size = paths.size();
  for( unsigned i = 0; i < size; ++i ) pathsFinal.insert( paths[i] );
  paths.assign( pathsFinal.begin(), pathsFinal.end() );
  }
  void findAllPathsUtilPartA(Vertex* curr,std::vector<std::vector<std::string>> &paths, std::vector<std::string> currentPath){
    currentPath.push_back(curr->getName());
    if(curr->getName() == "end"){
      paths.push_back(currentPath);
      return;
    }
    for(Vertex *v : curr->getAdjacencyList()){
      if( std::find(currentPath.begin(),currentPath.end(),v->getName()) != currentPath.end() && !v->getisBig())
        continue;
      else{
        findAllPathsUtilPartA(v,paths,currentPath);
      }
    }
  }
  void findAllPathsUtilPartB(Vertex* curr,std::vector<std::vector<std::string>> &paths, std::vector<std::string> currentPath, std::string &nodeTwice, int timesUsed){
    currentPath.push_back(curr->getName());
    if(curr->getName() == nodeTwice)
      timesUsed++;
    if(curr->getName() == "end"){
      paths.push_back(currentPath);
      return;
    }
    for(Vertex *v : curr->getAdjacencyList()){
      if(!v->getisBig() && std::find(currentPath.begin(),currentPath.end(),v->getName()) != currentPath.end()){
        if(v->getName() == nodeTwice && timesUsed < 2){
          findAllPathsUtilPartB(v,paths,currentPath,nodeTwice,timesUsed);
        }
      }
      else{
        findAllPathsUtilPartB(v,paths,currentPath,nodeTwice,timesUsed);
      }
    }
  }
  std::vector<std::vector<std::string>> getPaths(){return paths;}
  void showPaths(){
  for(std::vector<std::string> path : pathsFinal){
    for(std::string node : path){
      std::cout << node << " ";
    }
  std::cout << std::endl;
    }
  std::cout << "There are total of " << paths.size() << " paths from start to end." << std::endl;

  }
  void print(){
    std::cout << "List of all vertices:" << std::endl;
    for(Vertex* v : vertices){
      v->print();
      //std::cout << v->getName() << std::endl;
    }
  }

private:
  std::vector<Vertex*> vertices;
  Vertex* startNode;
  std::vector<std::vector<std::string>> paths;
  std::set<std::vector<std::string>> pathsFinal;

};