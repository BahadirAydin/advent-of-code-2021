#include <fstream> 
#include "inputsToVector.h"
#include "Graph.h"

int findAllPaths(std::string inputFileName){
  std::string line;
  std::ifstream Input(inputFileName);
  Graph graph;
  while(std::getline(Input,line)){
    std::vector<std::string> vertices;
    vertices = inputsToVector(line);
    graph.addVertex(vertices[0],std::isupper(vertices[0][0]));
    graph.addVertex(vertices[1],std::isupper(vertices[1][0]));
    graph.addEdge(vertices[0],vertices[1]);
    graph.addEdge(vertices[1],vertices[0]);
  }
  graph.findAllPaths('B'); // Call with 'A' for part A, 'B' for part B.
  //graph.showPaths();

  return graph.getPaths().size();
}
int main(){
  std::cout << findAllPaths("input.txt") << std::endl;
  return 0;
}