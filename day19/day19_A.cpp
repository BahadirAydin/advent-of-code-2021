#include <fstream> 
#include <algorithm>
#include "inputsToVector.h"
#include <queue>
typedef std::tuple<int,int,int> triplet;
typedef std::vector<triplet> vectorOfTriplets;
//THIS WAS THE HARDEST DAY FOR ME SO FAR BY A HUGE MARGIN. SOLUTION IS BRUTE FORCE IT TAKES SOME TIME (~5 mins) BUT IT WORKS AS EXPECTED.

std::vector<vectorOfTriplets> getScannerDatas(std::string inputFileName){
  std::string line;
  std::ifstream Input(inputFileName);
  std::vector<vectorOfTriplets> scannerDatas;
  int currentScanner=0;
  scannerDatas.push_back(vectorOfTriplets());
  while(std::getline(Input,line)){
    if(line.empty()){
      currentScanner++;
      scannerDatas.push_back(vectorOfTriplets());
    }
    else if(line[1] == '-')
      continue;
    else{
      triplet triplet = inputsToVector(line);
      scannerDatas[currentScanner].push_back(triplet);
    }
  }
  return scannerDatas;
}
void printTriplet(const triplet &triplet){
  std::cout << std::get<0>(triplet) << " " <<  std::get<1>(triplet) << " " <<std::get<2>(triplet) << std::endl;
}
void print(const vectorOfTriplets &scannerData){
    for(triplet triplet :scannerData)
      printTriplet(triplet);
}
triplet rotate(const triplet &triplet,int rotation){
  int x = std::get<0>(triplet);
  int y = std::get<1>(triplet);
  int z = std::get<2>(triplet);
  int possibleRotations[24][3] =  {
    {x, y, z}, {x, z, -y}, {x, -y, -z}, {x, -z, y},
    {-x, -y, z}, {-x, z, y}, {-x, y, -z}, {-x, -z, -y},
    {y, z, x}, {y, x, -z}, {y, -z, -x}, {y, -x, z},
    {-y, -z, x}, {-y, x, z}, {-y, z, -x}, {-y, -x, -z},
    {z, x, y}, {z, y, -x}, {z, -x, -y}, {z, -y, x},
    {-z, -x, y}, {-z, y, x}, {-z, x, -y}, {-z, -y, -x}
  };
   return std::make_tuple(possibleRotations[rotation][0],possibleRotations[rotation][1],possibleRotations[rotation][2]);
  //Possible rotations are taken from the r/adventofcode subreddit. Copy-paste from the youtube channel "William Y. Feng".
}
vectorOfTriplets rotateAllBeacons(const vectorOfTriplets &v,int rotation){
  vectorOfTriplets result;
  for(triplet t : v)
    result.push_back(rotate(t,rotation));
  return result;
}
triplet addTriplets(const triplet &t1, const triplet &t2){
  int x = std::get<0>(t1) + std::get<0>(t2);
  int y = std::get<1>(t1) + std::get<1>(t2);
  int z = std::get<2>(t1) + std::get<2>(t2);
  return triplet(x,y,z);
}
triplet substractTriplets(const triplet &t1, const triplet &t2){
  int x = std::get<0>(t1) - std::get<0>(t2);
  int y = std::get<1>(t1) - std::get<1>(t2);
  int z = std::get<2>(t1) - std::get<2>(t2);
  return triplet(x,y,z);
}
vectorOfTriplets substractAll(const vectorOfTriplets &v,const triplet &t){
  vectorOfTriplets result;
  for(unsigned int i=0;i<v.size();i++){
    result.push_back(substractTriplets(v[i],t));
  }
  return result;
}
triplet findOffsetHelper(const vectorOfTriplets &v1,const vectorOfTriplets &v2){
  vectorOfTriplets offsets;
  for(unsigned int i=0;i<v1.size();i++){
    for(unsigned int j=0;j<v2.size();j++){
      if(std::find(offsets.begin(),offsets.end(),substractTriplets(v1[i],v2[j])) == offsets.end())
        offsets.push_back(substractTriplets(v1[i],v2[j]));
    }
  }
   for(unsigned int i=0;i<offsets.size();i++){
    int count=0;
    vectorOfTriplets normalized = substractAll(v1,offsets[i]);
    for(triplet t:normalized){
      if(std::find(v2.begin(),v2.end(),t)!=v2.end()){
        count++;
        if(count == 12)
          return offsets[i];
      }
    }
  }
  return triplet(1500,1500,1500);
}
triplet findOffset(const vectorOfTriplets &v1,vectorOfTriplets &v2){
  triplet offset;
  for(int i=0;i<24;i++){
    offset = std::make_tuple(1500,1500,1500);
    vectorOfTriplets v2_copy = rotateAllBeacons(v2,i);
    offset = findOffsetHelper(v1,v2_copy);
    if(offset != std::make_tuple(1500,1500,1500)){
      v2 = v2_copy;
      for(int i=0;i<v2.size();i++){
        v2[i] = addTriplets(v2[i],offset);
      }
      break;
    }
  }
  return offset;
}


int scanner(){
  std::vector<vectorOfTriplets> allScanners = getScannerDatas("input.txt");
  //print(allScanners);
  vectorOfTriplets allBeacons;
  std::vector<triplet> offsets;
  std::queue<int> queue;
  int i=0;
  queue.push(0);
  while(!queue.empty()){
    i=queue.front();
    queue.pop();
    for(int j=0;j<allScanners.size();j++){
      if(j==i)
        j++;

      if(i==0){
        triplet offset = findOffset(allScanners[0],allScanners[j]);
        if(offset != std::make_tuple(1500,1500,1500) && offset != std::make_tuple(0,0,0)){
          offsets.push_back(offset);
          queue.push(j);
        }
      }
      else{
        triplet offset = findOffset(allScanners[i],allScanners[j]);
        if(offset != std::make_tuple(1500,1500,1500) && offset != std::make_tuple(0,0,0)){
          offsets.push_back(offset);
          queue.push(j);
        }
      }
    }
  }
  for(vectorOfTriplets v : allScanners){
    for(triplet t :v){
      if(std::find(allBeacons.begin(),allBeacons.end(),t)==allBeacons.end())
        allBeacons.push_back(t);
    }
  }
  return allBeacons.size();
}
int main(){
  std::cout << scanner() << std::endl;
  return 0;
}