
#include <vector>
#include <iostream>
#define LINE_LEN 100
#define NUM_LINES 100
bool checkLeft(std::vector<std::string> &lines, int depth, int horizontal ){
  if(horizontal==0)
    return true;
  return lines[depth][horizontal] < lines[depth][horizontal-1];
}
bool checkRight(std::vector<std::string> &lines, int depth, int horizontal ){
  if(horizontal==LINE_LEN-1)
    return true;
  return lines[depth][horizontal] < lines[depth][horizontal+1];
}
bool checkUp(std::vector<std::string> &lines, int depth, int horizontal ){
  if(depth==0)
    return true;
  return lines[depth][horizontal] < lines[depth-1][horizontal];
}
bool checkDown(std::vector<std::string> &lines, int depth, int horizontal ){
  if(depth==NUM_LINES-1)
    return true;
  return lines[depth][horizontal] < lines[depth+1][horizontal];
}
bool checkAll(std::vector<std::string> &lines, int depth, int horizontal ){
  return checkLeft(lines,depth,horizontal) && checkRight(lines,depth,horizontal) && checkUp(lines,depth,horizontal) && checkDown(lines,depth,horizontal);
}