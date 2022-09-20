#include <iostream>
#include <vector>
//All we need to know about the input is where the A,B,C,D resides. 


struct Amphipod {
  char type;
  int location;
  int depth;
  bool inRoom;
  bool inPosition;
};
void print(Amphipod amph){
    std::cout << "TYPE: " << amph.type << " LOCATION: " << amph.location << " DEPTH:" << amph.depth <<std::endl;
}
void printAmphs(const std::vector<Amphipod> &amphs){
  for(Amphipod m : amphs){
    print(m);
  }
  std::cout << std::endl;
}
int findEnergy(Amphipod &m,Amphipod &copy){
  int multiplier;
  if(m.type == 'A')
    multiplier = 1;
  else if(m.type == 'B')
    multiplier = 10;
  else if(m.type == 'C')
    multiplier = 100;
  else if(m.type == 'D'){
    multiplier = 1000;
  }
  return (m.depth + copy.depth + abs(m.location-copy.location))*multiplier;
}
bool isCaveClear(int location,int depth,const std::vector<Amphipod> &amphs){
  for(int i=0;i<16;i++){
    if(amphs[i].location == location && amphs[i].depth == depth){
      return false;
    }
  }
  return true;
}
bool isWayClear(int from,int to,const std::vector<Amphipod> &amphs){
  if(from > to){
    int tmp = to;
    to = from;
    from = tmp;
  }
  for(int i=0;i<16;i++){
    if(amphs[i].location < to && amphs[i].location > from && amphs[i].depth == 0){
      return false;
    }
  }
  return true;
}
bool canMoveCorridor(int index,int loc,std::vector<Amphipod> &amphs){
  Amphipod m = amphs[index];
  if( m.inPosition || loc == 2 || loc == 4 || loc == 6 || loc == 8){
    return false;
  }
  if(m.inRoom){
    for(int i = 0;i<16;i++){
      if(amphs[i].location == loc &&  amphs[i].depth == 0){
        return false;
      }
    }
    if(m.depth == 1 && isWayClear(m.location,loc,amphs)){
      amphs[index].location = loc;
      amphs[index].depth = 0;
      amphs[index].inRoom = false;
      amphs[index].inPosition = false;
      return true;
    }
    else if(m.depth == 2){
      if(isCaveClear(m.location,1,amphs) && isWayClear(m.location,loc,amphs)){
        amphs[index].location = loc;
        amphs[index].depth = 0;
        amphs[index].inRoom = false;
        amphs[index].inPosition = false;
        return true;
      }
    }
    else if(m.depth == 3){
      if(isCaveClear(m.location,1,amphs) && isCaveClear(m.location,2,amphs)  && isWayClear(m.location,loc,amphs)){
        amphs[index].location = loc;
        amphs[index].depth = 0;
        amphs[index].inRoom = false;
        amphs[index].inPosition = false;
        return true;
      }
    }
    else if(m.depth == 4){
      if(isCaveClear(m.location,1,amphs) && isCaveClear(m.location,2,amphs) && isCaveClear(m.location,3,amphs) && isWayClear(m.location,loc,amphs)){
        amphs[index].location = loc;
        amphs[index].depth = 0;
        amphs[index].inRoom = false;
        amphs[index].inPosition = false;
        return true;
      }
    }
  }
  return false;
}
bool isAmphInPlace(int location,std::vector<Amphipod> amphs,int want){
  int count = 0;
  for(int i=0;i<16;i++){
    if(amphs[i].location == location && amphs[i].inPosition){
      count++;
    }
  }
  if(count == want)
    return true;
  return false;
}
bool canMoveRoom(int index, std::vector<Amphipod> &amphs){
  int roomLoc;
  Amphipod m = amphs[index];
  if(m.inPosition)
    return false;
  if(m.depth == 2 && !isCaveClear(m.location,1,amphs))
    return false;
  else if(m.depth == 3 && !isCaveClear(m.location,1,amphs) && !isCaveClear(m.location,2,amphs)){
    return false;
  }
  else if(m.depth == 4 && !isCaveClear(m.location,1,amphs) && !isCaveClear(m.location,2,amphs)&& !isCaveClear(m.location,3,amphs)){
    return false;
  }
  if(m.type == 'A'){
    roomLoc = 2;
  }
  else if(m.type == 'B'){
    roomLoc = 4;
  }
  else if(m.type == 'C'){
    roomLoc = 6;
  }
  else if(m.type == 'D'){
    roomLoc = 8;
  }
  if(isCaveClear(roomLoc,1,amphs) && isCaveClear(roomLoc,2,amphs)  && isCaveClear(roomLoc,3,amphs)  && isCaveClear(roomLoc,4,amphs) &&  isWayClear(m.location,roomLoc,amphs)){
    amphs[index].location = roomLoc;
    amphs[index].depth = 4;
    amphs[index].inPosition = true;
    amphs[index].inRoom = true;
    return true;
  }
  else if(isCaveClear(roomLoc,1,amphs) && isCaveClear(roomLoc,2,amphs) && isCaveClear(roomLoc,3,amphs) && isAmphInPlace(roomLoc,amphs,1) && isWayClear(m.location,roomLoc,amphs)){
    amphs[index].location = roomLoc;
    amphs[index].depth = 3;
    amphs[index].inPosition = true;
    amphs[index].inRoom = true;
    return true;  
  }
  else if(isCaveClear(roomLoc,1,amphs) && isCaveClear(roomLoc,2,amphs) && isAmphInPlace(roomLoc,amphs,2) && isWayClear(m.location,roomLoc,amphs)){
    amphs[index].location = roomLoc;
    amphs[index].depth = 2;
    amphs[index].inPosition = true;
    amphs[index].inRoom = true;
    return true;  
  }
  else if(isCaveClear(roomLoc,1,amphs) && isAmphInPlace(roomLoc,amphs,3) && isWayClear(m.location,roomLoc,amphs)){
    amphs[index].location = roomLoc;
    amphs[index].depth = 1;
    amphs[index].inPosition = true;
    amphs[index].inRoom = true;
    return true;  
  }
  return false;
}
bool areWeDone(std::vector<Amphipod> amphs){
  for(int i=0;i<16;i++){
    if(amphs[i].inPosition == false){
      return false;
    }
  }
  return true;
}
void initAmphs(std::vector<Amphipod> &amphs){
  for(int i=0;i<16;i++){
    amphs.push_back(Amphipod());
  }
  char types[16] = {'D','D','D','C','D','C','B','C','A','B','A','B','A','A','C','B'};
  for(int i=0;i<16;i++){
    amphs[i].depth = i%4 +1;
    amphs[i].inPosition = false;
    amphs[i].inRoom = true;
    amphs[i].type = types[i];
  }
  //WARNING IF YOU ARE USING ANOTHER INPUT AND THERE IS AN AMPH IN POSITION MAKE SURE TO CHECK IT HERE.

  amphs[0].location = 2;
  amphs[1].location = 2;
  amphs[2].location = 2;
  amphs[3].location = 2;
  amphs[4].location = 4;
  amphs[5].location = 4;
  amphs[6].location = 4;
  amphs[7].location = 4;
  amphs[8].location = 6;
  amphs[9].location = 6;
  amphs[10].location = 6;
  amphs[11].location = 6;
  amphs[12].location = 8;
  amphs[13].location = 8;
  amphs[14].location = 8;
  amphs[15].location = 8;
}
void calculateEnergy(std::vector<Amphipod> amphs,int spent,int &min){
  if(spent >= min){
    return;
  }
  if(areWeDone(amphs)){
    if(spent < min){
      min = spent;
    }
    return;
  }
  for(int i=0;i<16;i++){
    Amphipod copy = amphs[i];
    if(copy.inPosition)
      continue;
    std::vector<Amphipod> copyAmphs(amphs);
    if(canMoveRoom(i,copyAmphs)){
      int newEnergy = spent + findEnergy(copyAmphs[i],copy);
      calculateEnergy(copyAmphs,newEnergy,min);
    }
  }
  for(int i=0;i<16;i++){
    if(amphs[i].inPosition)
      continue;
    for(int k=0;k<11;k++){
      Amphipod copy = amphs[i];
      std::vector<Amphipod> copyAmphs(amphs);
      if(canMoveCorridor(i,k,copyAmphs)){
        int newEnergy = spent + findEnergy(copyAmphs[i],copy);
        calculateEnergy(copyAmphs,newEnergy,min);
      }
    }
  }
}
int main(){
  std::vector<Amphipod> amphs;
  initAmphs(amphs);
  int min=50000;
  calculateEnergy(amphs,0,min);
  std::cout << min << std::endl;
  return 0;
}